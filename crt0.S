# _crt0.S
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

/* void _start(void);
 *
 * - entered with interrupts disabled, P=X=0
 * - boot params written to top of RAM:
 *     -2:   ENVP
 *     -4:   ARGV
 *     -6:   ARGC
 *     -8:   0x1802 magic cookie
 *     ..    environment strings
 *     ENVP: NULL-terminated array of pointers to environment strings
 *     ..    argument strings
 *     ARGV: NULL-terminated array of pointers to argument strings
 *     ..    available as stack
 * - verify magic cookie, load ARGC, ARGV, and ENVP into argument registers
 * - initialize NCRT (R4-R5)
 * - initialize SP from ARGV and push NULL RA
 * - initialize PC
 * - tail-call __libc_main(argc, argv, envp)
 */

#define ARGC	ARG0
#define ARGV	ARG1
#define ENVP	ARG2

BEGINF	_start
	;; use SP to access the boot args record
	ldi	0xff
	phi	SP
	ldi	0xf8
	plo	SP
	sex	SP

	;; check magic cookie
	ldxa
	xri	0x18
	lbnz	1f
	ldxa
	xri	0x02
	lbnz	1f	; no match

	;; match, load argument registers
	ldxa
	phi	ARGC
	ldxa
	plo	ARGC
	ldxa
	phi	ARGV
	ldxa
	plo	ARGV
	ldxa
	phi	ENVP
	ldxa
	plo	ENVP

	;; copy ARGV to SP
	ghi	ARGV
	phi	SP
	glo	ARGV
	plo	SP
	lbr	2f

1:	;; no match, put safe dummy values in the argument registers
	ldi	0x00
	phi	ARGC
	plo	ARGC	; ARGC = 0
	phi	SP
	plo	SP	; SP = 0
	dec	SP
	stxd
	str	SP	; SP = -2, ((void**)SP)[0] = NULL
	ghi	SP
	phi	ARGV
	phi	ENVP
	glo	SP
	plo	ARGV	; *ARGV == NULL
	plo	ENVP	; *ENVP == NULL

2:	dec	SP	; point to next available byte, as if STXD was used

	;; initialize NCRT
	ldi	%hi(.CALRTN)
	phi	CALL
	ldi	%lo(.CALRTN)
	plo	CALL
	ldi	%hi(.RETRTN)
	phi	RETN
	ldi	%lo(.RETRTN)
	plo	RETN

	;; push NULL RA
	ldi	0
	stxd
	stxd

	;; initialize PC
	ldi	%hi(3f)
	phi	PC
	ldi	%lo(3f)
	plo	PC
	sep	PC
3:
	;; tail-call __libc_main()
	lbr	__libc_main
	;; NOTREACHED

	;; This is the New Call and Return Technique (NCRT), which differs
	;; from the old Standard Call and Return Technique (SCRT) as follows:
	;;
	;; - NCRT does not reserve R6 for a LINK register, as it's redundant
	;;   and making R6 a general-purpose register is much more useful
	;; - NCRT stores return addresses in BIG-endian order, matching the
	;;   the processor's general behaviour and the 1804AC instructions

.EXITC:
	;; At this point, P=4, X=2, PC=CALLEE, CALLER's RA1 is on stack
	sep	PC		; jump to CALLEE, leaving CALL=.CALRTN
.CALRTN:
	;; CALLER did
	;;	; P=3
	;;	sep	CALL
	;; RA0:	.byte	%hi(CALLEE)
	;;	.byte	%low(CALLEE)
	;; RA1:	; wants to return here
	;;
	;; At this point, P=4, CALL=.CALRTN, PC=RA0.
	;; First step: increment PC and push RA1 on the stack
	sex	SP		; X points to stack
	inc	PC
	inc	PC
	glo	PC
	stxd			; push LOW(RA1) on the stack
	ghi	PC
	stxd			; push HIGH(RA1) on the stack
	;; Second step: decrement PC and load CALLEE into PC
	dec	PC
	ldn	PC		; D = LOW(CALLEE)
	str	SP		; MEM[SP] = LOW(CALLEE)
	dec	PC
	ldn	PC		; D = HIGH(CALLEE)
	phi	PC		; HIGH(PC) = HIGH(CALLEE)
	ldn	SP
	plo	PC		; LOW(PC) = LOW(CALLEE)
	lbr	.EXITC

.EXITR:
	;; At this point, P=5, X=2, PC=RA1, CALLER's SP has been restored
	sep	PC		; jump to CALLER, leaving RETN=.RETRTN
.RETRTN:
	;; CALLEE did:
	;;	; P=3, SP as on entry to CALLEE
	;;	sep	RETN
	;;
	;; At this point, P=5, CALLER's RA1 is on stack
	;; First step: pop PC off SP
	sex	SP		; X points to stack
	inc	SP		; STXD decrements R(X) after storing to M(R(X))
	lda	SP		; same as LDXA here, but fewer dynamic dependencies
	phi	PC		; Pop HIGH half of saved RA1
	ldn	SP		; same as LDX here, but fewer dynamic dependencies
	plo	PC		; Pop LOW half of saved RA1
	lbr	.EXITR

ENDF	_start
