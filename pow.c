/* pow.c
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

static const struct stub_ddd pow_stub = {
    "pow", 0xA4, 7, {
	{ {0x3fb999999999999a}, {0x3ff4000000000000}, {0x3faccab8602d2697} },
	{ {0x3fb999999999999a}, {0xbfd8000000000000}, {0x4002f892c7034a03} },
	{ {0x3fb999999999999a}, {0xc017800000000000}, {0x4126e28c6b2d9fa5} },
	{ {0x4024000000000000}, {0xc008000000000000}, {0x3f50624dd2f1a9fc} },
	{ {0x4030000000000000}, {0x3fd0000000000000}, {0x4000000000000000} },
	{ {0x4040000000000000}, {0x3fd5555555555555}, {0x400965fea53d6e3c} },
	{ {0x8000000000000000}, {0x3fe0000000000000}, {0x0000000000000000} },
    }
};

double pow(double x, double y)
{
    return _libm_stub_ddd(x, y, &pow_stub);
}
