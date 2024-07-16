/* realloc.c
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

#include <stdlib.h>
#include <string.h>

/* This is probably overly simplistic... */

void *realloc(void *src, size_t nrbytes)
{
    void *dst;

    dst = (nrbytes != 0) ? malloc(nrbytes) : NULL;
    if (src != NULL && dst != NULL)
	memcpy(dst, src, nrbytes);
    free(src);
    return dst;
}
