/* vsnprintf.c
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

#include <stdarg.h>
#include <stdio.h>
#include "xlibio.h"

int vsnprintf(char *str, size_t size, const char *fmt, va_list ap)
{
    int n;
    struct odev o;

    o.s = str;
    o.n = size ? size - 1 : 0;

    n = _vprintf(&o, fmt, ap);
    if (size)
	_putc(&o, '\0');
    return n;
}
