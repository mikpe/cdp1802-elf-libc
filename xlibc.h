/* xlibc.h
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

/* Implementation-specific declarations only available within libc. */

#include <stddef.h>
#include <stdint.h>

/* dummy _mcount() for -pg */
void _mcount(void);

/* size_t multiplication with overflow detection, usage:
 *
 * struct mulovf res = _mulovf(a, b);
 * if (res.overflow) handle overflow;
 * else use res.product;
 */
struct mulovf {	/* FIXME: assumes big-endian with 16-bit word size */
    size_t overflow;
    size_t product;
};
struct mulovf _mulovf(size_t a, size_t b);

/* Convert a number from binary to a decimal string. */
size_t _num2dec(const uint8_t *num, size_t nrbits, char *buf, size_t bufsz);

/* Convert an integer to decimal and output it to the console. */
void _putint(int val);

/* output s to the console without extra newline */
void _puts(const char *s);
