/* _libm_stub_ff.c
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

float _libm_stub_ff(float x, const struct stub_ff *stub)
{
    union f32 a;
    unsigned int i;

    a.f = x;

    for (i = 0; i < stub->n; ++i)
	if (a.ui == stub->v[i].arg.ui)
	    return stub->v[i].res.f;

    printf("@ %s %#lx\n", stub->func, a.ui);
    asm volatile("glo %0\n\t.byte 0x68, 0x1F" : : "r"(stub->tag));
    __builtin_unreachable();
}
