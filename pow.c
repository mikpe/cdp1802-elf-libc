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
    "pow", 0xA4, 39, {
	{ {0x3fb999999999999a}, {0x3ff4000000000000}, {0x3faccab8602d2697} },
	{ {0x3fb999999999999a}, {0xbfd8000000000000}, {0x4002f892c7034a03} },
	{ {0x3fb999999999999a}, {0xc017800000000000}, {0x4126e28c6b2d9fa5} },
	{ {0x3ff199999999999a}, {0x3ff4000000000000}, {0x3ff2063f23a34371} },
	{ {0x3ff199999999999a}, {0xbfd8000000000000}, {0x3feee060b3ddd38e} },
	{ {0x3ff199999999999a}, {0xc017800000000000}, {0x3fe247975acd8f5c} },
	{ {0x4000cccccccccccd}, {0x3ff4000000000000}, {0x4004394f0eb49499} },
	{ {0x4000cccccccccccd}, {0xbfd8000000000000}, {0x3fe83a5edba9d095} },
	{ {0x4000cccccccccccd}, {0xc017800000000000}, {0x3f8a330cde1c83e1} },
	{ {0x4008cccccccccccd}, {0x3ff4000000000000}, {0x401074220b1e1408} },
	{ {0x4008cccccccccccd}, {0xc017800000000000}, {0x3f5543e5cde6204a} },
	{ {0x4008cccccccccccd}, {0xbfd8000000000000}, {0x3fe4ef8fe6aa4319} },
	{ {0x4010666666666666}, {0x3ff4000000000000}, {0x4017563345415884} },
	{ {0x4010666666666666}, {0xbfd8000000000000}, {0x3fe2da18b127b701} },
	{ {0x4010666666666666}, {0xc017800000000000}, {0x3f307539cfc73920} },
	{ {0x4014666666666666}, {0x3ff4000000000000}, {0x401ea81109007d99} },
	{ {0x4014666666666666}, {0xbfd8000000000000}, {0x3fe15ed60df58f84} },
	{ {0x4014666666666666}, {0xc017800000000000}, {0x3f124340ba1c2fc6} },
	{ {0x4018666666666666}, {0x3ff4000000000000}, {0x40232c50248f15b9} },
	{ {0x4018666666666666}, {0xbfd8000000000000}, {0x3fe03e1098328ed1} },
	{ {0x4018666666666666}, {0xc017800000000000}, {0x3ef983b68b329323} },
	{ {0x401c666666666666}, {0x3ff4000000000000}, {0x40272defc08b64de} },
	{ {0x401c666666666666}, {0xbfd8000000000000}, {0x3fdeaff02e17009d} },
	{ {0x401c666666666666}, {0xc017800000000000}, {0x3ee4ea99bb6efc31} },
	{ {0x4020333333333333}, {0x3ff4000000000000}, {0x402b546d034adba0} },
	{ {0x4020333333333333}, {0xbfd8000000000000}, {0x3fdd352f0e7a3ac4} },
	{ {0x4020333333333333}, {0xc017800000000000}, {0x3ed349fdf535468f} },
	{ {0x4024000000000000}, {0xc0075c28f5c28f60}, {0x3f53b2a99b617f0a} },
	{ {0x4024000000000000}, {0xc00770a3d70a3d74}, {0x3f533fe0a4c6809e} },
	{ {0x4024000000000000}, {0xc007851eb851eb88}, {0x3f52cfb49053c5ba} },
	{ {0x4024000000000000}, {0xc00799999999999c}, {0x3f52621624456485} },
	{ {0x4024000000000000}, {0xc007ae147ae147b0}, {0x3f51f6f67f90c93f} },
	{ {0x4024000000000000}, {0xc007c28f5c28f5c4}, {0x3f518e4717dfb17b} },
	{ {0x4024000000000000}, {0xc007d70a3d70a3d8}, {0x3f5127f9b796ec24} },
	{ {0x4024000000000000}, {0xc007eb851eb851ec}, {0x3f50c4007be899c4} },
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
