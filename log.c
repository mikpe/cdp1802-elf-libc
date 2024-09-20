/* log.c
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

static const struct stub_dd log_stub = {
    "log", 0xA6, 10, {
	{ {0xc056c00000000000}, {0xfff8000000000000} },
	{ {0xc057000000000000}, {0xfff8000000000000} },
	{ {0xc057400000000000}, {0xfff8000000000000} },
	{ {0xc057800000000000}, {0xfff8000000000000} },
	{ {0xc057c00000000000}, {0xfff8000000000000} },
	{ {0xc058000000000000}, {0xfff8000000000000} },
	{ {0xc058400000000000}, {0xfff8000000000000} },
	{ {0xc058800000000000}, {0xfff8000000000000} },
	{ {0xc058c00000000000}, {0xfff8000000000000} },
	{ {0xc059000000000000}, {0xfff8000000000000} },
    }
};

double log(double x)
{
    return _libm_stub_dd(x, &log_stub);
}
