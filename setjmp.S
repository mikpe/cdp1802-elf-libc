# setjmp.S
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

/* int setjmp(jmp_buf env);
 */

#define ENV	ARG0
#define TMPSP	ARG1
#define OLINK	ARG2

.macro	PUSH	regno
	glo	\regno
	stxd
	ghi	\regno
	stxd
.endm

BEGINF	setjmp
	;; set up TMPSP to point to high byte of old LINK at SP + 1
	glo	SP
	plo	TMPSP
	ghi	SP
	phi	TMPSP
	inc	TMPSP

	;; read old LINK
	lda	TMPSP
	phi	OLINK
	ldn	TMPSP
	plo	OLINK

	;; Adjust ENV to point to the end of the jmp_buf, then set X to ENV.
	;; We can then use STXD to write to it with auto-decrement.
	glo	ENV
	adi	(7*2)-1
	plo	ENV
	ghi	ENV
	adci	0
	phi	ENV
	sex	ENV

	;; save callee-save registers (r12-r15), LINK, OLINK, and TMPSP
	PUSH	15
	PUSH	14
	PUSH	13
	PUSH	12
	PUSH	LINK
	PUSH	OLINK
	PUSH	TMPSP	; TMPSP point to where OLINK should be pushed

	;; skip caller-save (call-clobbered) registers: r7-r11, D, X
	;; skip reserved registers: r0-r1, r4-r5
	;; skip PC (r3) as longjmp will return to LINK

	;; return 0
	ldi	0
	plo	ARG0
	phi	ARG0
	RET
ENDF	setjmp
