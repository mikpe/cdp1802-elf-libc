/* cbrt.c
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

#include <math.h>
#include <stdio.h>
#include "xlibm.h"

static const struct stub_dd cbrt_stub = {
    "cbrt", 0xA5, 6, {
	{ {0x3f4cd3755d7a2e9a}, {0x3fb8877effffa02e} },
	{ {0x3fff333333333333}, {0x3ff3fd4493802cf8} },
	{ {0x4008000000000000}, {0x3ff7137449123ef6} },
	{ {0x4001d0e560418937}, {0x3ff4e4ed5ce21e38} },
	{ {0x4050000000000000}, {0x4010000000000000} },
	{ {0x4086c80000000000}, {0x4022000000000001} },
    }
};

double cbrt(double x)
{
    return _libm_stub_dd(x, &cbrt_stub);
}
