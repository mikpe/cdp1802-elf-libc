/* _initfini.c
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

typedef void (*initfini_ptr)(void);

/* These magic symbols are provided by the linker.  */
extern const initfini_ptr __preinit_array_start[];
extern const initfini_ptr __preinit_array_end[];
extern const initfini_ptr __init_array_start[];
extern const initfini_ptr __init_array_end[];
extern const initfini_ptr __fini_array_start[];
extern const initfini_ptr __fini_array_end[];

static void init(const initfini_ptr *start, const initfini_ptr *end)
{
    const initfini_ptr *ppfn;

    ppfn = start;
    while (ppfn != end) {
	const initfini_ptr pfn = *ppfn++;
	(*pfn)();
    }
}

void __libc_init_array(void)
{
    init(__preinit_array_start, __preinit_array_end);
    init(__init_array_start, __init_array_end);
}

void __libc_fini_array(void)
{
    const initfini_ptr *ppfn;

    ppfn = __fini_array_end;
    while (ppfn != __fini_array_start) {
	const initfini_ptr pfn = *--ppfn;
	(*pfn)();
    }
}
