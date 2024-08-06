/* sqrtf.c
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

float sqrtf(float x)
{
    union {
	float f;
	unsigned long l;
    } u;

    u.f = x;
    printf("@ sqrtf %#lx\n", u.l);
    asm("ldi 0xA2\n\t.byte 0x68, 0x1F");
    return 0;
}
