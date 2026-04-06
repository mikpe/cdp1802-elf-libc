/* strftime.c
   Copyright (C) 2026  Mikael Pettersson <mikpelinux@gmail.com>

   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

struct obuf {
    char *s;
    size_t n;
};

static bool append_char(struct obuf *o, char c)
{
    if (!o->n)
	return false;
    o->n--;
    *(o->s++) = c;
    return true;
}

static bool append_str(struct obuf *o, const char *s)
{
    char c;

    while ((c = *s++) != '\0')
	if (!append_char(o, c))
	    return false;
    return true;
}

static const char *wdays[7] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

static const char *months[12] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

static bool is_leap_year(int tm_year)
{
    int y = tm_year + 1900;
    return ((y % 4) == 0) && ((y % 100) != 0 || ((y % 400) == 0));
}

static int week_nr(const struct tm *tm)
{
    int wknr;

    wknr = (tm->tm_yday + 7U - ((tm->tm_wday + 6U) % 7)) / 7;

    if (((tm->tm_wday + 371U - tm->tm_yday - 2) % 7) <= 2)
	++wknr;

    if (wknr == 0) {
	wknr = 52;
	/* If 31 December of previous year is a Thursday,
	   or a Friday of a leap year, then the previous
	   year has 53 weeks.  */
	int dec31 = (tm->tm_wday + 7U - tm->tm_yday - 1) % 7;
	if (dec31 == 4 || (dec31 == 5 && is_leap_year((tm->tm_year % 400) - 1)))
	    wknr = 53;
    } else if (wknr == 53) {
	/* If 1 January is not a Thursday, and not a Wednesday
	   of a leap year, then this year has only 52 weeks.  */
	int jan1 = (tm->tm_wday + 371U - tm->tm_yday) % 7;
	if (jan1 != 4 && (jan1 != 3 || !is_leap_year(tm->tm_year)))
	    wknr = 1;
    }

    return wknr;
}

/* Reduce the character after '%' to a symbolic conversion specifier.  */

#define CONV_a		0
#define CONV_A		1
#define CONV_bh		2	/* 'b' and 'h' */
#define CONV_B		3
#define CONV_c		4
#define CONV_C		5
#define CONV_d		6
#define CONV_Dx		7	/* 'D' and 'x' */
#define CONV_e		8
#define CONV_EO		9	/* 'E' and 'O' */
#define CONV_F		10
#define CONV_Gg		11	/* 'G' and 'g' */
#define CONV_H		12
#define CONV_I		13
#define CONV_j		14
#define CONV_m		15
#define CONV_M		16
#define CONV_n		17
#define CONV_p		18
#define CONV_r		19
#define CONV_R		20
#define CONV_S		21
#define CONV_t		22
#define CONV_TX		23	/* 'T' and 'X' */
#define CONV_u		24
#define CONV_U		25
#define CONV_V		26
#define CONV_w		27
#define CONV_W		28
#define CONV_y		29
#define CONV_Y		30
#define CONV_PCNT	31	/* '%' */

/* TBD: 'z', 'Z' */

static const struct ch2conv {
    char c;
    unsigned char conv;
} ch2convs[] = {
    /* Must be sorted by the ASCII value of the conversion specifier.  */
    { '%', CONV_PCNT },
    { 'A', CONV_A },
    { 'B', CONV_B },
    { 'C', CONV_C },
    { 'D', CONV_Dx },
    { 'E', CONV_EO },
    { 'F', CONV_F },
    { 'G', CONV_Gg },
    { 'H', CONV_H },
    { 'I', CONV_I },
    { 'M', CONV_M },
    { 'O', CONV_EO },
    { 'R', CONV_R },
    { 'S', CONV_S },
    { 'T', CONV_TX },
    { 'U', CONV_U },
    { 'V', CONV_V },
    { 'W', CONV_W },
    { 'X', CONV_TX },
    { 'Y', CONV_Y },
    { 'a', CONV_a },
    { 'b', CONV_bh },
    { 'c', CONV_c },
    { 'd', CONV_d },
    { 'e', CONV_e },
    { 'g', CONV_Gg },
    { 'h', CONV_bh },
    { 'j', CONV_j },
    { 'm', CONV_m },
    { 'n', CONV_n },
    { 'p', CONV_p },
    { 'r', CONV_r },
    { 't', CONV_t },
    { 'u', CONV_u },
    { 'w', CONV_w },
    { 'x', CONV_Dx },
    { 'y', CONV_y },
};

static unsigned char ch2conv(char c)
{
    unsigned char n = sizeof(ch2convs)/sizeof(ch2convs[0]);
    const struct ch2conv *ch2conv = &ch2convs[0];

    for (; n; ++ch2conv, --n)
	if (ch2conv->c == c)
	    return ch2conv->conv;

    return -1;
}

static bool do_strftime(struct obuf *o, const char *fmt, const struct tm *tm)
{
    char c;

    while ((c = *fmt++) != '\0') {
	char buf[5];
	const char *str;
	int num, width;

	if (c != '%')
	    goto do_append_char;

	/* Default number format is "%02u".  */
	width = 2;

	/* 'E' and 'O' modifiers need to loop.  */
	for (;;) {
	    c = *fmt++;
	    switch (ch2conv(c)) {
	    case CONV_a:
		strncpy(buf, wdays[tm->tm_wday], 3);
		buf[3] = '\0';
		goto do_append_buf;
	    case CONV_A:
		str = wdays[tm->tm_wday];
		goto do_append_str;
	    case CONV_bh:
		strncpy(buf, months[tm->tm_mon], 3);
		buf[3] = '\0';
		goto do_append_buf;
	    case CONV_B:
		str = months[tm->tm_mon];
		goto do_append_str;
	    case CONV_c:
		str = "%a %b %e %T %Y";
		goto do_recurse;
	    case CONV_C:
		num = (tm->tm_year + 1900) / 100;
		goto do_append_num;
	    case CONV_d:
		num = tm->tm_mday;
		goto do_append_num;
	    case CONV_Dx:
		str = "%m/%d/%y";
		goto do_recurse;
	    case CONV_e:
		/* Pads with space not zero otherwise this could use do_append_num.  */
		snprintf(buf, 3, "%2u", tm->tm_mday);
		goto do_append_buf;
	    case CONV_EO:
		/* Alternative era-based format modifier, or alternative
		   numeric symbols modifier.  Ignored.  */
		continue;
	    case CONV_F:
		str = "%Y-%m-%d";
		goto do_recurse;
	    case CONV_Gg:
		num = tm->tm_year + 1900L;
		if (tm->tm_yday < 3 && week_nr(tm) != 1)
		    --num;
		else if (tm->tm_yday > 360 && week_nr(tm) == 1)
		    ++num;
		if (c == 'g')
		    num %= 100;
		else
		    width = 4;
		goto do_append_num;
	    case CONV_H:
		num = tm->tm_hour;
		goto do_append_num;
	    case CONV_I:
		num = tm->tm_hour;
		if (num > 12)
		    num -= 12;
		else if (num == 0)
		    num = 12;
		goto do_append_num;
	    case CONV_j:
		num = tm->tm_yday + 1;
		width = 3;
		goto do_append_num;
	    case CONV_m:
		num = tm->tm_mon + 1;
		goto do_append_num;
	    case CONV_M:
		num = tm->tm_min;
		goto do_append_num;
	    case CONV_n:
		c = '\n';
		goto do_append_char;
	    case CONV_p:
		buf[0] = (tm->tm_hour >= 12) ? 'P' : 'A';
		buf[1] = 'M';
		buf[2] = '\0';
		goto do_append_buf;
	    case CONV_r:
		str = "%I:%M:%S %p";
		goto do_recurse;
	    case CONV_R:
		str = "%H:%M";
		goto do_recurse;
	    case CONV_S:
		num = tm->tm_sec;
		goto do_append_num;
	    case CONV_t:
		c = '\t';
		goto do_append_char;
	    case CONV_TX:
		str = "%H:%M:%S";
		goto do_recurse;
	    case CONV_u:
		c = '0' + (tm->tm_wday ? tm->tm_wday : 7);
		goto do_append_char;
	    case CONV_U:
		num = (tm->tm_yday + 7U - tm->tm_wday) / 7;
		goto do_append_num;
	    case CONV_V:
		num = week_nr(tm);
		goto do_append_num;
	    case CONV_w:
		c = '0' + tm->tm_wday;
		goto do_append_char;
	    case CONV_W:
		num = (tm->tm_yday + 7U - ((tm->tm_wday + 6U) % 7)) / 7;
		goto do_append_num;
	    case CONV_y:
		num = (tm->tm_year + 1900) % 100;
		goto do_append_num;
	    case CONV_Y:
		num = tm->tm_year + 1900;
		goto do_append_num;
	    case CONV_PCNT:
		c = '%';
		goto do_append_char;
	    }
	}

    do_append_num:
	snprintf(buf, sizeof buf, "%0*u", width, num);

    do_append_buf:
	/* This is for the default which is to output buf[].  */
	str = buf;

	/* This is for when the string is a literal, or a tail of buf[].  */
    do_append_str:
	if (!append_str(o, str))
	    return false;
	continue;

	/* This is for when the output is a single character.  */
    do_append_char:
	if (!append_char(o, c))
	    return false;
	continue;

	/* This is for when we call ourselves recursively (1-deep only).  */
    do_recurse:
	if (!do_strftime(o, str, tm))
	    return false;
	continue;
    }

    return true;
}

size_t strftime(char *s, size_t max, const char *fmt, const struct tm *tm)
{
    struct obuf o;

    o.s = s;
    o.n = max;
    if (do_strftime(&o, fmt, tm) && append_char(&o, '\0'))
	return (max - o.n) - 1;

    /* There is unfortunately no errno value defined for this case.  */
    return 0;
}
