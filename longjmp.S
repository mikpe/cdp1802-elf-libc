# longjmp.S
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

/* void setjmp(jmp_buf env, int val);
 */

#define ENV	ARG0
#define VAL	ARG1
#define TMPSP	ARG2
#define RA	ARG3

.macro	POP	regno
	lda	ENV
	phi	\regno
	lda	ENV
	plo	\regno
.endm

BEGINF	longjmp
	;; if (VAL == 0) VAL = 1
	ghi	VAL
	lbnz	1f
	glo	VAL
	lsnz		; skip LDI below if LOW(VAL) != 0
	ldi	1
	plo	VAL
1:
	;; restore original call frame
	POP	TMPSP
	POP	RA	; stacked RA in original setjmp() call
	sex	TMPSP
	glo	RA
	stxd
	ghi	RA
	stxd
	glo	TMPSP
	plo	SP
	ghi	TMPSP
	phi	SP

	;; restore remaining registers
	POP	11
	POP	12
	POP	13
	POP	14
	POP	15

	;; return VAL
	glo	VAL
	plo	ARG0
	ghi	VAL
	phi	ARG0
	RET
ENDF	longjmp
