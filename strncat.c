/* strncat.c
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

#include <string.h>

/* FIXME: rewrite in assembler */

char *strncat(char *dst, const char *src, size_t n)
{
    char *p;

    for (p = dst; *p != '\0'; ++p)
	;

    for (;; --n) {
	if (n == 0) {
	    *p = '\0';
	    break;
	}
	if ((*p++ = *src++) == '\0')
	    break;
    }

    return dst;
}
