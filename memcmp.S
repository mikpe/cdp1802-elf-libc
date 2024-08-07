# memcmp.S
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

/* int memcmp(const void *s1, const void *s2, size_t n);
 */

#define S1	ARG0
#define S2	ARG1
#define N	ARG2

BEGINF	memcmp
	lbr	1f

0:	;; compute *S1++ - *S2++ into D and DF
	lda	S2
	str	SP
	lda	S1
	sm
	lbnf	2f	; if < then borrow, i.e. carry clear
	lbnz	3f	; if > then non-zero

	;; --N
	dec	N

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b
	;; D = 0 -> RES = <0,0>
	lbr    4f

2:	;; less-than, set RES = <-1,-1>
	ldi	0xff
	lskp

3:	;; greater-than, set RES = <1,1>
	ldi	1

4:	;; return with <D,D> in ARG0
	plo	ARG0
	phi	ARG0
	RET
ENDF	memcmp
