/* calloc.c
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "xlibc.h"

/* This must be compiled with -ffreestanding to avoid gcc turning
 * the malloc+memset sequence into a call to calloc() itself.
 *
 * FIXME: rewrite in assembler
 */
void *calloc(size_t nmemb, size_t size)
{
    struct mulovf res;
    size_t nrbytes;
    void *p;

    res = _mulovf(nmemb, size);
    if (res.overflow) {
	errno = ENOMEM;
	return NULL;
    }
    nrbytes = res.product;

    p = malloc((uint16_t) nrbytes);
    if (p == NULL)
	return p;
    return memset(p, 0, nrbytes);
}
