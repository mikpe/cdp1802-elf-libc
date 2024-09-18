/* sqrt.c
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

static const struct stub_dd sqrt_stub = {
    "sqrt", 0xA3, 3, {
	{ {0x3fd6666666666666}, {0x3fe2ee73dadc9b57} },
	{ {0x4008000000000000}, {0x3ffbb67ae8584caa} },
	{ {0x7fffffffffffffff}, {0x7fffffffffffffff} },
    }
};

double sqrt(double x)
{
    return _libm_stub_dd(x, &sqrt_stub);
}
