/* _write.c
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

#include <stdio.h>
#include <string.h>
#include "xlibio.h"

/* FIXME: rewrite in assembler */

void _write(struct odev *o, const char *s, size_t n)
{
    if (o->s) {
	if (n > o->n)
	    n = o->n;
	memcpy(o->s, s, n);
	o->s += n;
	o->n -= n;
    } else {
	while (n) {
	    putchar(*s++);
	    --n;
	}
    }
}
