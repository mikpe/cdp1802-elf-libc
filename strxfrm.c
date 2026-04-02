/* strxfrm.c
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

#include <string.h>

/* We only support the C/POSIX locale, so strxfrm() reduces to a strcpy()
   that checks the destination size first.  */

size_t strxfrm(char *dest, const char *src, size_t n)
{
    size_t len;

    len = strlen(src);
    if (len < n)
	strcpy(dest, src);
    return len;
}
