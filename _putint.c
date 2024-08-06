/* _putint.c
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

#include "xlibc.h"

void _putint(int val)
{
    char buf[16];
    char sign;
    int n;

    sign = 0;
    if (val < 0) {
	sign = '-';
	val = -(unsigned int)val;
    }
    n = _num2dec((unsigned char*)&val, 8 * sizeof val, buf + 1, sizeof buf - 2);
    buf[n + 1] = '\0';
    if (sign) {
	buf[0] = '-';
	_puts(buf);
    } else
	_puts(buf + 1);
}
