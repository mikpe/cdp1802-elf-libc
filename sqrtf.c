/* sqrtf.c
   Copyright (C) 2024-2026  Mikael Pettersson <mikpelinux@gmail.com>

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

#include <math.h>
#include <stdio.h>
#include "xlibm.h"

static const struct stub_ff sqrtf_stub = {
    "sqrtf", 0xA2, 4, {
	{ {0x40800000}, {0x40000000} },
	{ {0x41800000}, {0x40800000} },
	{ {0x41e80000}, {0x40ac5345} },
	{ {0x42800000}, {0x41000000} },
    }
};

float sqrtf(float x)
{
    return _libm_stub_ff(x, &sqrtf_stub);
}
