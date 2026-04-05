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
#define CONV_H		11
#define CONV_I		12
#define CONV_j		13
#define CONV_m		14
#define CONV_M		15
#define CONV_n		16
#define CONV_p		17
#define CONV_r		18
#define CONV_R		19
#define CONV_S		20
#define CONV_t		21
#define CONV_TX		22	/* 'T' and 'X' */
#define CONV_u		23
#define CONV_w		24
#define CONV_y		25
#define CONV_Y		26
#define CONV_PCNT	27	/* '%' */

/* TBD: 'g', 'G', 'U', 'V', 'W', 'z', 'Z' */

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
    { 'H', CONV_H },
    { 'I', CONV_I },
    { 'M', CONV_M },
    { 'O', CONV_EO },
    { 'R', CONV_R },
    { 'S', CONV_S },
    { 'T', CONV_TX },
    { 'X', CONV_TX },
    { 'Y', CONV_Y },
    { 'a', CONV_a },
    { 'b', CONV_bh },
    { 'c', CONV_c },
    { 'd', CONV_d },
    { 'e', CONV_e },
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

	if (c != '%')
	    goto do_append_char;

	/* 'E' and 'O' modifiers need to loop.  */
	for (;;) {
	    c = *fmt++;
	    switch (ch2conv(c)) {
	    case CONV_a:
		strncpy(buf, wdays[tm->tm_wday], 3);
		buf[3] = '\0';
		break;
	    case CONV_A:
		str = wdays[tm->tm_wday];
		goto do_append_str;
	    case CONV_bh:
		strncpy(buf, months[tm->tm_mon], 3);
		buf[3] = '\0';
		break;
	    case CONV_B:
		str = months[tm->tm_mon];
		goto do_append_str;
	    case CONV_c:
		str = "%a %b %e %T %Y";
		goto do_recurse;
	    case CONV_C:
		snprintf(buf, 5, "%04u", tm->tm_year + 1900);
		buf[2] = '\0';	/* truncate after century part */
		break;
	    case CONV_d:
		snprintf(buf, 3, "%02u", tm->tm_mday);
		break;
	    case CONV_Dx:
		str = "%m/%d/%y";
		goto do_recurse;
	    case CONV_e:
		snprintf(buf, 3, "%2u", tm->tm_mday);
		break;
	    case CONV_EO:
		/* Alternative era-based format modifier, or alternative
		   numeric symbols modifier.  Ignored.  */
		continue;
	    case CONV_F:
		str = "%Y-%m-%d";
		goto do_recurse;
	    case CONV_H:
		snprintf(buf, 3, "%02u", tm->tm_hour);
		break;
	    case CONV_I:
	    {
		int hr = tm->tm_hour;
		if (hr > 12)
		    hr -= 12;
		else if (hr == 0)
		    hr = 12;
		snprintf(buf, 3, "%02u", hr);
		break;
	    }
	    case CONV_j:
		snprintf(buf, 4, "%03u", tm->tm_yday + 1);
		break;
	    case CONV_m:
		snprintf(buf, 3, "%02u", tm->tm_mon + 1);
		break;
	    case CONV_M:
		snprintf(buf, 3, "%02u", tm->tm_min);
		break;
	    case CONV_n:
		c = '\n';
		goto do_append_char;
	    case CONV_p:
		buf[0] = (tm->tm_hour >= 12) ? 'P' : 'A';
		buf[1] = 'M';
		buf[2] = '\0';
		break;
	    case CONV_r:
		str = "%I:%M:%S %p";
		goto do_recurse;
	    case CONV_R:
		str = "%H:%M";
		goto do_recurse;
	    case CONV_S:
		snprintf(buf, 3, "%02u", tm->tm_sec);
		break;
	    case CONV_t:
		c = '\t';
		goto do_append_char;
	    case CONV_TX:
		str = "%H:%M:%S";
		goto do_recurse;
	    case CONV_u:
		c = '0' + (tm->tm_wday ? tm->tm_wday : 7);
		goto do_append_char;
	    case CONV_w:
		c = '0' + tm->tm_wday;
		goto do_append_char;
	    case CONV_y:
		snprintf(buf, 5, "%04u", tm->tm_year + 1900);
		str = buf+2;
		goto do_append_str;
	    case CONV_Y:
		snprintf(buf, 5, "%04u", tm->tm_year + 1900);
		break;
	    case CONV_PCNT:
		c = '%';
		goto do_append_char;
	    }
	}

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
