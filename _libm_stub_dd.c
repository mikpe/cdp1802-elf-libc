/* _libm_stub_dd.c
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

#include "xlibm.h"
#include <stdio.h>

double _libm_stub_dd(double x, const struct stub_dd *stub)
{
    union f64 a;
    unsigned int i;

    a.d = x;

    for (i = 0; i < stub->n; ++i)
	if (a.ui == stub->v[i].arg.ui)
	    return stub->v[i].res.d;

    printf("@ %s %#llx\n", stub->func, a.ui);
    asm volatile("glo %0\n\t.byte 0x68, 0x1F" : : "r"(stub->tag));
    __builtin_unreachable();
}
