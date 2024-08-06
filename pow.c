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

double pow(double x, double y)
{
    union {
	double d;
	unsigned long long ll;
    } u1, u2;

    u1.d = x;
    u2.d = y;
    printf("@ pow %#llx %#llx\n", u1.ll, u2.ll);
    asm("ldi 0xA4\n\t.byte 0x68, 0x1F");
    return 0;
}
