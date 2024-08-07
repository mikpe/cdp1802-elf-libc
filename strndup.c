/* strndup.c
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

#include <stdint-gcc.h>
#include <stdlib.h>
#include <string.h>

/* FIXME: rewrite in assembler */

char *strndup(const char *src, size_t n)
{
    char *tmp;

    /* n = strnlen(src, n); */
    tmp = memchr(src, '\0', n);
    if (tmp != NULL)
	n = tmp - src;

    tmp = malloc(n + 1);
    if (tmp != NULL) {
	memcpy(tmp, src, n);
	tmp[n] = '\0';
    }

    return tmp;
}
