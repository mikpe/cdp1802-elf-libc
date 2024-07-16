# _mulovf.S
# Copyright (C) 2024  Mikael Pettersson <mikpelinux@gmail.com>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this library.  If not, see <http://www.gnu.org/licenses/>.

#include "asm-macros.h"

/* size_t multiplication with overflow detection, based on the
   following C code then hand-optimized:

   struct mulovf _mulovf(size_t a, size_t b)
   {
       unsigned long x = (unsigned long)a * (unsigned long)b;
       return (struct mulovf){ !!(x >> 16), (size_t)x };
   }
 */

BEGINF	_mulovf
	;; zero-extend the arguments from 16 to 32 bits
	glo	ARG1
	plo	ARG3
	ghi	ARG1
	phi	ARG3
	glo	ARG0
	plo	ARG1
	ghi	ARG0
	phi	ARG1
	ldi	0
	plo	ARG2
	phi	ARG2
	plo	ARG0
	phi	ARG0
	;; multiply
	sep	4
	.hword	__mulsi3
	;; low 16 bits of product already in ARG1
	ghi	ARG0
	str	SP
	glo	ARG0
	or
	plo	ARG0	; ARG0 low is non-zero iff overflow
	RET
ENDF	_mulovf
