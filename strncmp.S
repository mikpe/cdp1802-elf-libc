# strncmp.S
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

/* int strncmp(const char *s1, const char *s2, size_t n);
 */

#define S1	ARG0
#define S2	ARG1
#define N	ARG2
#define C1	ARG3
#define C2	STATIC_CHAIN

BEGINF	strncmp
	lbr	1f

0:	;; C1 = *S1++, C2 = *S2++
	lda	S1
	plo	C1
	lda	S2
	plo	C2

	;; compute C1 - C2 into D and DF
	str	SP	; C2 is still in D
	glo	C1
	sm
	lbnf	7f	; if < then borrow, i.e. carry clear
	lbnz	8f	; if > then non-zero

	;; C1 == C2, if C1 == 0 goto 9f
	glo	C1
	lbz	9f

	dec	N

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b

	;; equal, set RES = <0,0>
	lskp

7:	;; less-than, set RES = <-1,-1>
	ldi	0xff
	lskp

8:	;; greater-than, set RES = <1,1>
	ldi	1

9:	;; return with <D,D> in ARG0
	plo	ARG0
	phi	ARG0
	RET
ENDF	strncmp
