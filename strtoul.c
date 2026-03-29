/* strtoul.c
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

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/* isspace() as defined for C and POSIX locales, without ctype dependency.  */
static bool my_isspace(unsigned char c)
{
    switch (c) {
    case ' ':
    case '\f':
    case '\n':
    case '\r':
    case '\t':
    case '\v':
	return true;
    default:
	return false;
    }
}

/* If the character denotes a digit in base [2,36], return the
   value of that digit, otherwise return a value > 36.  */
static unsigned char digit_value(unsigned char c)
{
    if (c >= '0' && c <= '9')
	return c - '0';
    if (c >= 'a' && c <= 'z')
	return c - ('a' - 10);
    if (c >= 'A' && c <= 'Z')
	return c - ('A' - 10);
    return 255;
}

/* Table indexed by base - 2 giving the largest unsigned long that can
   be multiplied by that base without overflowing.  */
static unsigned long multlim[36-2+1] = {
#define MULTLIM(B) ULONG_MAX / (unsigned long)(B)
    MULTLIM( 2), MULTLIM( 3), MULTLIM( 4), MULTLIM( 5), MULTLIM( 6),
    MULTLIM( 7), MULTLIM( 8), MULTLIM( 9), MULTLIM(10), MULTLIM(11),
    MULTLIM(12), MULTLIM(13), MULTLIM(14), MULTLIM(15), MULTLIM(16),
    MULTLIM(17), MULTLIM(18), MULTLIM(19), MULTLIM(20), MULTLIM(21),
    MULTLIM(22), MULTLIM(23), MULTLIM(24), MULTLIM(25), MULTLIM(26),
    MULTLIM(27), MULTLIM(28), MULTLIM(29), MULTLIM(30), MULTLIM(31),
    MULTLIM(32), MULTLIM(33), MULTLIM(34), MULTLIM(35), MULTLIM(36)
#undef MULTLIM
};

unsigned long strtoul(const char *nptr, char **endptr, int base0)
{
    const char *s;
    unsigned char c;	/* INV: c == s[-1] */
    bool minus;
    unsigned char base;	/* final base in a single byte */
    bool any;		/* have we seen any digits? */
    unsigned long mlim;	/* for multiplication overflow check */
    unsigned long acc;	/* where we accumulate the value */
    unsigned long tmp;	/* for addition overflow check */
    unsigned char digit;

    s = nptr;
    c = *s++;

    /* Skip leading whitespace.  */
    while (my_isspace(c))
	c = *s++;

    /* Check for +/- prefix.  */
    minus = false;
    switch (c) {
    case '-':
	minus = true;
	/*FALLTHROUGH*/
    case '+':
	c = *s++;
	break;
    }

    /* Check base and 0/0x prefixes.  */
    if (base0 == 0) {
	base = 10;
	if (c == '0') {
	    base = 8;
	    if (s[0] == 'x' || s[0] == 'X') {
		base = 16;
		++s;
		c = *s++;
	    }
	}
    } else if (base0 == 16) {
	base = 16;
	if (c == '0' && (s[0] == 'x' || s[0] == 'X')) {
	    ++s;
	    c = *s++;
	}
    } else if (base0 < 2 || base0 > 36) {
	if (endptr)
	    *endptr = (char*)nptr;
	errno = EINVAL;
	return 0;
    } else
	base = base0;

    /* Now c == s[-1] is the first digit, if any.  */
    any = false;
    acc = 0;
    mlim = multlim[base - 2];

    /* Accumulate digits while checking for overflow.  */
    while ((digit = digit_value(c)) < base) {
	any = true;
	if (acc <= mlim) {
	    acc *= base;
	    tmp = acc + digit;
	    if (tmp >= acc) {
		acc = tmp;
		c = *s++;
		continue;
	    }
	}
	/* Overflow.  */
	minus = false;
	acc = ULONG_MAX;
	errno = ERANGE;
	break;
    }

    /* Number scanned, set return values.  */
    if (endptr)
	*endptr = (char*)(any ? s - 1 : nptr);
    if (minus)
	acc = -acc;
    return acc;
}

#ifdef TEST
#include <stdio.h>

static const struct test {
    const char *str;
    unsigned char base;
    bool overflow;
} tests[] = {
    { "11111111111111111111111111111111", 2, false },
    { "100000000000000000000000000000000", 2, true },
    { "37777777777", 8, false },
    { "40000000000", 8, true },
    { "4294967295", 10, false },
    { "4294967296", 10, true },
    { "ffffffff", 16, false },
    { "100000000", 16, true },
    { "1z141z3", 36, false },
    { "1z141z4", 36, true },
};

static int test(const struct test *t)
{
    char *endptr;
    unsigned long v;

    errno = 0;
    v = strtoul(t->str, &endptr, t->base);
    if (v == -1UL &&
	(t->overflow
	 ? (errno && *endptr)
	 : !(errno || *endptr)))
	return 0;
    printf("strtoul(\"%s\", %u) returned %lu errno %d *endptr %u\n",
	   t->str, t->base, v, errno, *endptr);
    return 1;
}

int main(void)
{
    int i, err;

    err = 0;
    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i)
	err += test(&tests[i]);
    if (!err)
	printf("all tests ok\n");
    return !!err;
}
#endif
