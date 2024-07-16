# memmove.S
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

/* void *memmove(void *dst, const void *src, size_t n);
 */

#define DST	ARG0
#define SRC	ARG1
#define N	ARG2
#define TMP	ARG3

BEGINF	memmove
	;; if SRC < DST && DST < SRC + N then we must copy backwards
	glo	DST	; compute SRC - DST
	str	SP
	glo	SRC
	sm
	ghi	DST
	str	SP
	ghi	SRC
	smb
	lbdf	memcpy	; if >= then no borrow, i.e. carry set

	glo	N	; compute TMP = SRC + N
	str	SP
	glo	SRC
	add
	plo	TMP
	ghi	N
	str	SP
	ghi	SRC
	adc
	phi	TMP

	glo	TMP	; compute DST - TMP
	str	SP
	glo	DST
	sm
	ghi	TMP
	str	SP
	ghi	DST
	smb
	lbdf	memcpy	; if >= then no borrow, i.e. carry set

	;; copy backwards
	glo	N	; compute DST += N
	str	SP
	glo	DST
	add
	plo	DST
	ghi	N
	str	SP
	ghi	DST
	adc
	phi	DST

	lbr	1f

0:	;; *--DST = *--TMP, --N
	dec	TMP
	ldn	TMP
	dec	DST
	str	DST
	dec	N

1:	;; if (N != 0) goto 0b
	glo	N
	lbnz	0b
	ghi	N
	lbnz	0b

	;; return with initial DST in ARG0
	RET
ENDF	memmove
