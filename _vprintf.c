/* _vprintf.c
   Copyright (C) 2024  Mikael Pettersson <mikpelinux@gmail.com>

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
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "xlibc.h"
#include "xlibio.h"

/* Printf format conversion state:
 * - initialized when scanning the printf format conversion specification
 * - updated when converting the field
 * - interpreted during output of the field
 */
struct pfmt {
    /* Decoded printf format conversion specification. */
    unsigned char flags;
    unsigned char lmod;
    unsigned char conv;
    unsigned int width;
    int prec;
    /* The runtime value taken from the va_list. */
    union {
	void *ptr;
	uint64_t u64;
	uint8_t u8[8];
	double d;
    } val;
    /* Buffer to output, set up during conversion. */
    char *buf;
    /* Extra field widths, set up during conversion. */
    unsigned int n0;	/* number of characters in buf first segment */
    unsigned int nz0;	/* number of zeros to output after first segment */
    unsigned int n1;	/* number of characters in buf second segment */
    unsigned int nz1;	/* number of zeros to output after second segment */
    unsigned int n2;	/* number of characters in buf third segment */
    unsigned int nz2;	/* number of zeros to output after third segment */
};

#define FLG_ALT		0x01
#define FLG_ZERO	0x02
#define FLG_LEFT	0x04
#define FLG_SPACE	0x08
#define FLG_SIGN	0x10
#define FLG_UPCASE	0x20	/* synthesized by %X */

#define LMOD_NONE	0
#define LMOD_INT8	1
#define LMOD_INT16	2
#define LMOD_INT32	3
#define LMOD_INT64	4

#define CONV_DECIMAL	0
#define CONV_UNSIGNED	1
#define CONV_OCTAL	2
#define CONV_HEX	3
#define CONV_CHAR	4
#define CONV_STRING	5
#define CONV_NWRITTEN	6
#define CONV_PERCENT	7
#define CONV_TEXT	8
#define CONV_FLOATING	9
#define CONV_ERR	10

/* Figure out the sizes of some symbolic types. */

#if UINTMAX_MAX == UINT64_MAX
#define LMOD_J		LMOD_INT64
#endif

#if SIZE_MAX == UINT64_MAX
#define LMOD_Z		LMOD_INT64
#elif SIZE_MAX == UINT32_MAX
#define LMOD_Z		LMOD_INT32
#elif SIZE_MAX == UINT16_MAX
#define LMOD_Z		LMOD_INT16
#endif

#if PTRDIFF_MAX == INT64_MAX
#define LMOD_T		LMOD_INT64
#elif PTRDIFF_MAX == INT32_MAX
#define LMOD_T		LMOD_INT32
#elif PTRDIFF_MAX == INT16_MAX
#define LMOD_T		LMOD_INT16
#endif

static const char *scan_pfmt(struct pfmt *pfmt, const char *fmt, va_list *ap)
{
    unsigned char flags, lmod;
    unsigned int width;
    int prec;

    memset(pfmt, 0, sizeof *pfmt);

    if (*fmt == '\0') {
	pfmt->conv = CONV_TEXT;	/* signal non-error */
	return NULL;
    }

    /* scan a sequence of ordinary characters */
    if (*fmt != '%') {
	unsigned int n;

	pfmt->conv = CONV_TEXT;
	pfmt->val.ptr = (char*)fmt;
	n = 0;
	do {
	    ++n;
	    ++fmt;
	} while (*fmt != '\0' && *fmt != '%');
	pfmt->prec = n;
	return fmt;
    }

    /* scan flags */
    flags = 0;
    for (;;) {
	switch (*++fmt) {
	case '#':
	    flags |= FLG_ALT;
	    continue;
	case '0':
	    flags |= FLG_ZERO;
	    continue;
	case '-':
	    flags |= FLG_LEFT;
	    continue;
	case ' ':
	    flags |= FLG_SPACE;
	    continue;
	case '+':
	    flags |= FLG_SIGN;
	    continue;
	default:
	    break;
	}
	break;
    }
    pfmt->flags = flags;

    /* scan field width */
    if (*fmt == '*') {
	++fmt;
	width = va_arg(*ap, unsigned int);
	if ((int)width < 0) {
	    width = -width;
	    pfmt->flags |= FLG_LEFT;
	}
    } else {
	width = 0;
	if (*fmt >= '1' && *fmt <= '9') {
	    do {
		width = (((width << 2) + width) << 1) + (*fmt++ - '0');
	    } while (*fmt >= '0' && *fmt <= '9');
	}
    }
    pfmt->width = width;

    /* scan precision */
    if (*fmt == '.') {
	++fmt;
	if (*fmt == '*') {
	    prec = va_arg(*ap, int);
	} else {
	    prec = 0;
	    while (*fmt >= '0' && *fmt <= '9')
		prec = (((prec << 2) + prec) << 1) + (*fmt++ - '0');
	}
    } else
	prec = -1;
    pfmt->prec = prec;

    /* scan length modifier */
    lmod = LMOD_NONE;
    switch (*fmt++) {
    case 'h':
	if (*fmt == 'h') {
	    ++fmt;
	    lmod = LMOD_INT8;
	} else
	    lmod = LMOD_INT16;
	break;
    case 'l':
	if (*fmt == 'l') {
	    ++fmt;
	    lmod = LMOD_INT64;
	} else {
	    lmod = (sizeof(long) == sizeof(uint64_t)) ? LMOD_INT64 : LMOD_INT32;
	}
	break;
    case 'L':
	/* We'll need to extend this for long double support. */
	break;
    case 'j':
	lmod = LMOD_J;
	break;
    case 'z':
	lmod = LMOD_Z;
	break;
    case 't':
	lmod = LMOD_T;
	break;
    default:
	--fmt;
	break;
    }
    pfmt->lmod = lmod;

    /* scan conversion specifier, consume argument */
    switch (*fmt++) {
    case 'd': case 'i':
	pfmt->conv = CONV_DECIMAL;
	goto get_integer;
    case 'u':
	pfmt->conv = CONV_UNSIGNED;
	goto get_integer;
    case 'o':
	pfmt->conv = CONV_OCTAL;
	goto get_integer;
    case 'X':
	pfmt->flags |= FLG_UPCASE;
	/*FALLTHROUGH*/
    case 'x':
	pfmt->conv = CONV_HEX;
    get_integer:
	if (lmod == LMOD_NONE) {
	    lmod = (sizeof(int) == sizeof(uint16_t)) ? LMOD_INT16 : LMOD_INT32;
	    pfmt->lmod = lmod;
	}
	switch (lmod) {
	case LMOD_INT64:
	    pfmt->val.u64 = va_arg(*ap, uint64_t);
	    break;
	case LMOD_INT32:
	    pfmt->val.u64 = va_arg(*ap, uint32_t);
	    break;
	case LMOD_INT16:
	    pfmt->val.u64 = (uint16_t)va_arg(*ap, unsigned int);
	    break;
	case LMOD_INT8:
	    pfmt->val.u64 = (uint8_t)va_arg(*ap, unsigned int);
	    break;
	}
	break;
    case 'e': case 'E': case 'f': case 'F': case 'g': case 'G': case 'a': case 'A':
	/* We'll need to extend this for "proper" FP support. */
	pfmt->conv = CONV_FLOATING;
	pfmt->val.d = va_arg(*ap, double);
	break;
    case 'c':
	pfmt->conv = CONV_CHAR;
	pfmt->val.u64 = (unsigned char)va_arg(*ap, unsigned int);
	break;
    case 's':
	pfmt->conv = CONV_STRING;
	pfmt->val.ptr = va_arg(*ap, char *);
	break;
    case 'p':
	pfmt->lmod = LMOD_T;
	pfmt->conv = CONV_HEX;
	pfmt->val.u64 = (uintptr_t)va_arg(*ap, void *);
	break;
    case 'n':
	if (lmod == LMOD_NONE)
	    pfmt->lmod = (sizeof(int) == sizeof(uint16_t)) ? LMOD_INT16 : LMOD_INT32;
	pfmt->conv = CONV_NWRITTEN;
	pfmt->val.ptr = va_arg(*ap, int *);
	break;
    case '%':
	pfmt->conv = CONV_PERCENT;
	break;
    default:
	pfmt->conv = CONV_ERR;
	return NULL;
    }

    return fmt;
}

static int emit_padding(struct odev *o, int n, char ch)
{
    int i;

    if (n <= 0)
	return 0;

    i = n;
    do {
	_putc(o, ch);
    } while (--i != 0);

    return n;
}

static int emit_spaces(struct odev *o, int n)
{
    return emit_padding(o, n, ' ');
}

static int emit_zeros(struct odev *o, int n)
{
    return emit_padding(o, n, '0');
}

static int emit_buf(struct odev *o, int n, char **bufp)
{
    if (n <= 0)
	return 0;

    _write(o, *bufp, n);
    *bufp += n;
    return n;
}

static int emit_field(struct odev *o, struct pfmt *pfmt)
{
    int nwritten;
    int nspaces;

    nwritten = 0;
    nspaces = pfmt->width - (pfmt->n0 + pfmt->nz0 + pfmt->n1 + pfmt->nz1 + pfmt->n2 + pfmt->nz2);
    if (!(pfmt->flags & FLG_LEFT))
	nwritten += emit_spaces(o, nspaces);
    nwritten += emit_buf(o, pfmt->n0, &pfmt->buf);
    nwritten += emit_zeros(o, pfmt->nz0);
    nwritten += emit_buf(o, pfmt->n1, &pfmt->buf);
    nwritten += emit_zeros(o, pfmt->nz1);
    nwritten += emit_buf(o, pfmt->n2, &pfmt->buf);
    nwritten += emit_zeros(o, pfmt->nz2);
    if (pfmt->flags & FLG_LEFT)
	nwritten += emit_spaces(o, nspaces);

    return nwritten;
}

static int emit_integer(struct odev *o, struct pfmt *pfmt)
{
    int prec;
    int i;

    prec = pfmt->prec;
    if (prec < 0)
	prec = 1;
    if (pfmt->n1 < prec)
	pfmt->nz0 = prec - pfmt->n1;

    if (prec > 0
	&& (pfmt->flags & (FLG_LEFT | FLG_ZERO)) == FLG_ZERO
	&& (i = pfmt->width - pfmt->n0 - pfmt->nz0 - pfmt->n1) > 0)
	pfmt->nz0 += i;

    return emit_field(o, pfmt);
}

static int emit_signed(struct odev *o, struct pfmt *pfmt)
{
    char buf[20];
    char sign;
    int n;

    if ((int64_t)pfmt->val.u64 < 0) {
	sign = '-';
	pfmt->val.u64 = -pfmt->val.u64;
    } else if (pfmt->flags & FLG_SIGN)
	sign = '+';
    else if (pfmt->flags & FLG_SPACE)
	sign = ' ';
    else
	sign = 0;

    n = _num2dec(&pfmt->val.u8[0], 64, buf + 1, sizeof buf - 1);
    pfmt->n1 = n;

    if (sign) {
	buf[0] = sign;
	pfmt->n0 = 1;
	pfmt->buf = buf;
    } else
	pfmt->buf = buf + 1;

    return emit_integer(o, pfmt);
}

static int emit_unsigned(struct odev *o, struct pfmt *pfmt)
{
    char buf[20];
    int n;

    n = _num2dec(&pfmt->val.u8[0], 64, buf, sizeof buf);
    pfmt->n1 = n;

    pfmt->buf = buf;

    return emit_integer(o, pfmt);
}

static int emit_hex(struct odev *o, struct pfmt *pfmt)
{
    char buf[64/4 + 2];
    char *str = buf + sizeof buf;
    unsigned char letter0 = (pfmt->flags & FLG_UPCASE) ? 'A' - 10 : 'a' - 10;
    uint64_t val;
    int n;

    n = 0;
    val = pfmt->val.u64;
    while (val) {
	unsigned int dig = val & 15;
	*--str = ((dig < 10) ? '0' : letter0) + dig;
	++n;
	val >>= 4;
    }
    pfmt->n1 = n;

    if ((pfmt->flags & FLG_ALT) && n != 0) {
	*--str = (pfmt->flags & FLG_UPCASE) ? 'X' : 'x';
	*--str = '0';
	pfmt->n0 = 2;
    }
    pfmt->buf = str;

    return emit_integer(o, pfmt);
}

static int emit_oct(struct odev *o, struct pfmt *pfmt)
{
    char buf[(64 + 2) / 3 + 1];
    char *str = buf + sizeof buf;
    uint64_t val;
    int n;

    n = 0;
    val = pfmt->val.u64;
    while (val) {
	unsigned int dig = val & 7;
	*--str = '0' + dig;
	++n;
	val >>= 3;
    }
    pfmt->n1 = n;

    if ((pfmt->flags & FLG_ALT) && n != 0) {
	*--str = '0';
	pfmt->n0 = 1;
    }
    pfmt->buf = str;

    return emit_integer(o, pfmt);
}

static int emit_floating(struct odev *o, struct pfmt *pfmt)
{
    static const char nofp[8] = "**NOFP**";
    _write(o, nofp, sizeof nofp);
    return sizeof nofp;
}

static int emit_char(struct odev *o, const struct pfmt *pfmt)
{
    _putc(o, (unsigned char)pfmt->val.u64);
    return 1;
}

static int emit_string(struct odev *o, const struct pfmt *pfmt)
{
    const char *s;
    size_t n;

    s = (const char*)pfmt->val.ptr;
    if (pfmt->prec >= 0)
	n = strnlen(s, pfmt->prec);
    else
	n = strlen(s);
    _write(o, s, n);
    return n;
}

static int emit_nwritten(const struct pfmt *pfmt, int nwritten)
{
    switch (pfmt->lmod) {
    case LMOD_INT8:
	*(uint8_t*)pfmt->val.ptr = (uint8_t)nwritten;
	break;
    case LMOD_NONE:
	*(uint16_t*)pfmt->val.ptr = (uint16_t)nwritten;
	break;
    case LMOD_INT32:
	*(uint32_t*)pfmt->val.ptr = (uint32_t)nwritten;
	break;
    case LMOD_INT64:
	*(uint64_t*)pfmt->val.ptr = (uint64_t)nwritten;
	break;
    }
    return 0;
}

static int emit_percent(struct odev *o)
{
    _putc(o, '%');
    return 1;
}

static int emit_text(struct odev *o, const struct pfmt *pfmt)
{
    _write(o, (const char*)pfmt->val.ptr, pfmt->prec);
    return pfmt->prec;
}

static int emit_pfmt(struct odev *o, struct pfmt *pfmt, int nwritten)
{
    switch (pfmt->conv) {
    case CONV_DECIMAL:
	return emit_signed(o, pfmt);
    case CONV_UNSIGNED:
	return emit_unsigned(o, pfmt);
    case CONV_OCTAL:
	return emit_oct(o, pfmt);
    case CONV_HEX:
	return emit_hex(o, pfmt);
    case CONV_CHAR:
	return emit_char(o, pfmt);
    case CONV_STRING:
	return emit_string(o, pfmt);
    case CONV_NWRITTEN:
	return emit_nwritten(pfmt, nwritten);
    case CONV_PERCENT:
	return emit_percent(o);
    case CONV_TEXT:
	return emit_text(o, pfmt);
    case CONV_FLOATING:
	return emit_floating(o, pfmt);
    default:
	return 0;
    }
}

int _vprintf(struct odev *o, const char *fmt, va_list ap)
{
    int nwritten = 0;
    struct pfmt pfmt;

    while ((fmt = scan_pfmt(&pfmt, fmt, &ap)) != NULL) {
	nwritten += emit_pfmt(o, &pfmt, nwritten);
    }
    if (pfmt.conv == CONV_ERR) {
	errno = EINVAL;
	return -1;
    }
    return nwritten;
}

#ifdef TEST

struct test {
    int (*testf)(struct odev *);
    const char *expected;
};

static int t_printf(struct odev *o, const char *fmt, ...)
{
    va_list ap;
    int n;

    va_start(ap, fmt);
    n = _vprintf(o, fmt, ap);
    va_end(ap);
    return n;
}

static int test00(struct odev *o) { return t_printf(o, "gazonk"); }

static const struct test tests[] = {
    { test00, "gazonk" }
};

static int test(unsigned int i)
{
    const struct test *t = &tests[i];
    char buf[256];
    int n;
    struct odev o;

    memset(buf, 0, sizeof buf);

    o.s = buf;
    o.n = sizeof buf;

    n = (*t->testf)(&o);
    if (n >= sizeof buf
	|| n != strlen(t->expected)
	|| strcmp(buf, t->expected) != 0) {
	fprintf(stderr, "test %u: '%s' != '%s'\n", i, buf, t->expected);
	return 1;
    }
    return 0;
}

int main(void)
{
    unsigned int errors = 0;
    unsigned int i;

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i)
	errors += test(i);

    printf("%u errors\n", errors);
    return !!errors;
}

#endif
