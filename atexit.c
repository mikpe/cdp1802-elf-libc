/* atexit.c
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

#include <stdlib.h>
#include "xlibc.h"

/* To avoid wasting memory we only support 4 calls to atexit() instead of the
   32 required by C and POSIX.  TODO: use malloc() if that isn't enough?  */
typedef void (*funcptr_t)(void);
static funcptr_t atfuncs[4];
static unsigned char atnr;

/* TODO: this should share code with __libc_fini_array() */
void __libc_atexit(void)
{
    unsigned int i;

    for (i = atnr; i != 0;) {
	funcptr_t funcptr = atfuncs[--i];
	(*funcptr)();
    }
}

int atexit(funcptr_t funcptr)
{
    unsigned int i;

    i = atnr;
    if (i > sizeof(atfuncs)/sizeof(atfuncs[0]))
	return -1;

    atfuncs[i] = funcptr;
    atnr = i + 1;
    return 0;
}
