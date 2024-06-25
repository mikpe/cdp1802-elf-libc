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
 * - store ENVP in environ
 * - initialize SCRT (R4-R6)
 * - initialize SP from ARGV and push NULL LINK
 * - initialize PC
 * - call exit(main(argc, argv, envp))
 */

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
	phi	ARG0
	ldxa
	plo	ARG0	; ARGC
	ldxa
	phi	ARG1
	ldxa
	plo	ARG1	; ARGV
	ldxa
	phi	ARG2
	ldxa
	plo	ARG2	; ENVP

	;; copy ARGV to SP
	ghi	ARG1
	phi	SP
	glo	ARG1
	plo	SP
	lbr	2f

1:	;; no match, put safe dummy values in the argument registers
	ldi	0x00
	phi	ARG0
	plo	ARG0	; ARGC = 0
	phi	SP
	plo	SP
	dec	SP
	stxd
	str	SP	; SP = -2, ((void**)SP)[0] = NULL
	ghi	SP
	phi	ARG1
	phi	ARG2
	glo	SP
	plo	ARG1	; *ARGC == NULL
	plo	ARG2	; *ENVP == NULL

2:	dec	SP	; point to next available byte, as if STXD was used

	;; store envp (ARG2) in environ (uses LINK as a scratch reg)
	ldi	%hi(environ)
	phi	LINK
	ldi	%lo(environ)
	plo	LINK
	ghi	ARG2
	str	LINK
	glo	ARG2
	inc	LINK
	str	LINK

	;; initialize SCRT
	ldi	%hi(.CALRTN)
	phi	CALL
	ldi	%lo(.CALRTN)
	plo	CALL
	ldi	%hi(.RETRTN)
	phi	RETN
	ldi	%lo(.RETRTN)
	plo	RETN
	ldi	0
	phi	LINK
	plo	LINK

	;; push NULL LINK
	stxd
	stxd

	;; initialize PC
	ldi	%hi(3f)
	phi	PC
	ldi	%lo(3f)
	plo	PC
	sep	PC
3:
	;; call main()
	sep	CALL
	.hword	main
	;; tailcall exit()
	lbr	exit

	;; RCA's original SCRT software pushes LINK on the stack in
	;; LITTLE-endian order, even though the CPU is BIG-endian.
	;; The 1804AC SCAL/SRET instructions are compatible except
	;; for pushing LINK in BIG-endian order.  This SCRT software
	;; pushes LINK in BIG-endian order.

.EXITC:
	;; At this point, P=4, X=2, PC=&CALLEE, LINK=&RA1, CALLER's LINK is on stack
	sep	PC		; jump to CALLEE, leaving CALL=&CALRTN and LINK=&RA1
.CALRTN:
	;; CALLER did
	;;	; P=3
	;;	sep	CALL
	;; RA0:	.byte	%hi(CALLEE)
	;;	.byte	%low(CALLEE)
	;; RA1:	; wants to return here
	;;
	;; At this point, P=4, CALL=&CALRTN, PC=&RA0.
	;; First step: push LINK on the stack
	sex	SP		; X points to stack
	glo	LINK
	stxd			; push LOW(LINK) on the stack
	ghi	LINK
	stxd			; push HIGH(LINK) on the stack
	;; Second step: copy PC (&RA0) to LINK
	ghi	PC
	phi	LINK		; Copy HIGH half of RA0 to LINK
	glo	PC
	plo	LINK		; Copy LOW half of RA0 to LINK
	;; Third step: load &CALLEE from LINK to PC and update LINK to &RA1
	lda	LINK		; D = M(LINK++)
	phi	PC		; Copy HIGH half of &CALLEE to PC
	lda	LINK		; D = M(LINK++)
	plo	PC		; Copy LOW half of &CALLEE to PC
	lbr	.EXITC

.EXITR:
	;; At this point, P=5, X=2, PC=&RA1, CALLER's LINK has been restored
	sep	PC		; jump to CALLER, leaving RETN=&RETRTN
.RETRTN:
	;; CALLEE did:
	;;	; P=3, SP as on entry to CALLEE
	;;	sep	RETN
	;;
	;; At this point, P=5, LINK=&RA1, CALLER's LINK is on stack
	;; First step: copy LINK to PC
	ghi	LINK
	phi	PC		; Copy HIGH half of LINK to PC
	glo	LINK
	plo	PC		; Copy LOW half of LINK to PC
	;; Second step: pop LINK off SP
	sex	SP		; X points to stack
	inc	SP		; STXD decrements R(X) after storing to M(R(X))
	ldxa
	phi	LINK		; Pop HIGH half of saved LINK
	ldx
	plo	LINK		; Pop LOW half of saved LINK
	lbr	.EXITR

ENDF	_start

	.bss
	.global	environ
	.type	environ, @object
	.size	environ, 2
environ:
	.zero	2
