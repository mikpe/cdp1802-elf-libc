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
    "pow", 0xA4, 103, {
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
	{ {0x4022333333333333}, {0x3ff4000000000000}, {0x402f9c4b7f0db437} },
	{ {0x4022333333333333}, {0xbfd8000000000000}, {0x3fdbf5cc3337c933} },
	{ {0x4022333333333333}, {0xc017800000000000}, {0x3ec377cff8fd6b29} },
	{ {0x4024000000000000}, {0xc006147ae147ae20}, {0x3f5c78dd6e7dfef0} },
	{ {0x4024000000000000}, {0xc00628f5c28f5c34}, {0x3f5bd2f33cab6bbe} },
	{ {0x4024000000000000}, {0xc0063d70a3d70a48}, {0x3f5b30cfdf8212af} },
	{ {0x4024000000000000}, {0xc00651eb851eb85c}, {0x3f5a925d5505cd3d} },
	{ {0x4024000000000000}, {0xc006666666666670}, {0x3f59f7861b793759} },
	{ {0x4024000000000000}, {0xc0067ae147ae1484}, {0x3f5960352e725dab} },
	{ {0x4024000000000000}, {0xc0068f5c28f5c298}, {0x3f58cc5604006eae} },
	{ {0x4024000000000000}, {0xc006a3d70a3d70ac}, {0x3f583bd489e20b6f} },
	{ {0x4024000000000000}, {0xc006b851eb851ec0}, {0x3f57ae9d22cbd736} },
	{ {0x4024000000000000}, {0xc006ccccccccccd4}, {0x3f57249ca3bee74d} },
	{ {0x4024000000000000}, {0xc006e147ae147ae8}, {0x3f569dc0516eb66c} },
	{ {0x4024000000000000}, {0xc006f5c28f5c28fc}, {0x3f5619f5ddb64173} },
	{ {0x4024000000000000}, {0xc0070a3d70a3d710}, {0x3f55992b651bf4fb} },
	{ {0x4024000000000000}, {0xc0071eb851eb8524}, {0x3f551b4f6c641580} },
	{ {0x4024000000000000}, {0xc007333333333338}, {0x3f54a050de314dba} },
	{ {0x4024000000000000}, {0xc00747ae147ae14c}, {0x3f54281f08b310b3} },
	{ {0x4024000000000000}, {0xc0075c28f5c28f60}, {0x3f53b2a99b617f0a} },
	{ {0x4024000000000000}, {0xc00770a3d70a3d74}, {0x3f533fe0a4c6809e} },
	{ {0x4024000000000000}, {0xc007851eb851eb88}, {0x3f52cfb49053c5ba} },
	{ {0x4024000000000000}, {0xc00799999999999c}, {0x3f52621624456485} },
	{ {0x4024000000000000}, {0xc007ae147ae147b0}, {0x3f51f6f67f90c93f} },
	{ {0x4024000000000000}, {0xc007c28f5c28f5c4}, {0x3f518e4717dfb17b} },
	{ {0x4024000000000000}, {0xc007d70a3d70a3d8}, {0x3f5127f9b796ec24} },
	{ {0x4024000000000000}, {0xc007eb851eb851ec}, {0x3f50c4007be899c4} },
	{ {0x4024000000000000}, {0xc008000000000000}, {0x3f50624dd2f1a9fc} },
	{ {0x4024333333333333}, {0x3ff4000000000000}, {0x4032015f05f9f75a} },
	{ {0x4024333333333333}, {0xbfd8000000000000}, {0x3fdae357dc4c94ac} },
	{ {0x4024333333333333}, {0xc017800000000000}, {0x3eb51a36cdc36f22} },
	{ {0x4026333333333333}, {0x3ff4000000000000}, {0x403442bb06b3a892} },
	{ {0x4026333333333333}, {0xbfd8000000000000}, {0x3fd9f3e947758c13} },
	{ {0x4026333333333333}, {0xc017800000000000}, {0x3ea83ca6a650ccb8} },
	{ {0x4028333333333333}, {0x3ff4000000000000}, {0x40369141c2ae5e05} },
	{ {0x4028333333333333}, {0xbfd8000000000000}, {0x3fd9206f6eaf59f1} },
	{ {0x4028333333333333}, {0xc017800000000000}, {0x3e9d33c48cb9a913} },
	{ {0x402a333333333333}, {0x3ff4000000000000}, {0x4038ec1f9d292f26} },
	{ {0x402a333333333333}, {0xbfd8000000000000}, {0x3fd863b786ef3336} },
	{ {0x402a333333333333}, {0xc017800000000000}, {0x3e9250af2d8726af} },
	{ {0x402c333333333333}, {0x3ff4000000000000}, {0x403b529d9c28e820} },
	{ {0x402c333333333333}, {0xbfd8000000000000}, {0x3fd7b9d4faf47b3c} },
	{ {0x402c333333333333}, {0xc017800000000000}, {0x3e87c6c786146ecb} },
	{ {0x402e333333333333}, {0xbfd8000000000000}, {0x3fd71fc0c29e537c} },
	{ {0x402e333333333333}, {0xc017800000000000}, {0x3e7fcb5c42c4ccc4} },
	{ {0x402e333333333333}, {0x3ff4000000000000}, {0x403dc41bc0146175} },
	{ {0x4030000000000000}, {0x3fd0000000000000}, {0x4000000000000000} },
	{ {0x403019999999999a}, {0x3ff4000000000000}, {0x4040200663d8d36c} },
	{ {0x403019999999999a}, {0xbfd8000000000000}, {0x3fd69319b0915e68} },
	{ {0x403019999999999a}, {0xc017800000000000}, {0x3e75d06ab11b9cc4} },
	{ {0x403119999999999a}, {0x3ff4000000000000}, {0x404162f979cf9221} },
	{ {0x403119999999999a}, {0xbfd8000000000000}, {0x3fd611f92c3f2bb5} },
	{ {0x403119999999999a}, {0xc017800000000000}, {0x3e6e9ef242abad9c} },
	{ {0x403219999999999a}, {0x3ff4000000000000}, {0x4042aaaec0bd1071} },
	{ {0x403219999999999a}, {0xbfd8000000000000}, {0x3fd59ad503a54d52} },
	{ {0x403219999999999a}, {0xc017800000000000}, {0x3e65edafee7dcc35} },
	{ {0x403319999999999a}, {0x3ff4000000000000}, {0x4043f6f356fc256d} },
	{ {0x403319999999999a}, {0xbfd8000000000000}, {0x3fd52c69e1f107b6} },
	{ {0x403319999999999a}, {0xc017800000000000}, {0x3e5ff9f1d32a54dc} },
	{ {0x403419999999999a}, {0x3ff4000000000000}, {0x404547990e0711df} },
	{ {0x403419999999999a}, {0xbfd8000000000000}, {0x3fd4c5aba13fd670} },
	{ {0x403419999999999a}, {0xc017800000000000}, {0x3e57b173188ad0d2} },
	{ {0x403519999999999a}, {0x3ff4000000000000}, {0x40469c75c483d238} },
	{ {0x403519999999999a}, {0xbfd8000000000000}, {0x3fd465b9ab42332b} },
	{ {0x403519999999999a}, {0xc017800000000000}, {0x3e51d029d88a8695} },
	{ {0x403619999999999a}, {0x3ff4000000000000}, {0x4047f562de0ce177} },
	{ {0x403619999999999a}, {0xbfd8000000000000}, {0x3fd40bd6387c11f5} },
	{ {0x403619999999999a}, {0xc017800000000000}, {0x3e4b24162ba07380} },
	{ {0x403719999999999a}, {0x3ff4000000000000}, {0x4049523cd244cc5f} },
	{ {0x403719999999999a}, {0xbfd8000000000000}, {0x3fd3b75fa0717855} },
	{ {0x403719999999999a}, {0xc017800000000000}, {0x3e44ed57cbeb35f1} },
	{ {0x403819999999999a}, {0x3ff4000000000000}, {0x404ab2e2ce60f4b1} },
	{ {0x403819999999999a}, {0xbfd8000000000000}, {0x3fd367cb2ce27503} },
	{ {0x403819999999999a}, {0xc017800000000000}, {0x3e405091c668d342} },
	{ {0x4040000000000000}, {0x3fd5555555555555}, {0x400965fea53d6e3c} },
	{ {0x8000000000000000}, {0x3fe0000000000000}, {0x0000000000000000} },
    }
};

double pow(double x, double y)
{
    return _libm_stub_ddd(x, y, &pow_stub);
}
