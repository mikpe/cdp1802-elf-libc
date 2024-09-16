# stubs.S
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

	.local	stubnr
	.set	stubnr, 0

.macro	STUB	name
	.global	\name
	.type	\name, @function
\name:
	.set	stubnr, stubnr + 1
	ldi	stubnr
	.byte	0x68, 0x1F	; causes NYI message and exit from sim1802
.endm

	.text
STUB	__sigsetjmp
STUB	__stack_chk_fail
STUB	__stack_chk_guard
STUB	acos
STUB	acosf
STUB	acosh
STUB	acoshf
STUB	acoshl
STUB	acosl
STUB	asin
STUB	asinf
STUB	asinh
STUB	asinhf
STUB	asinhl
STUB	asinl
STUB	atan
STUB	atanh
STUB	atanhf
STUB	atanhl
STUB	atanl
STUB	atoi
STUB	cbrt
STUB	cbrtf
STUB	cbrtl
STUB	ceil
STUB	ceilf
STUB	ceill
STUB	cos
STUB	cosf
STUB	cosh
STUB	coshf
STUB	coshl
STUB	cosl
STUB	erf
STUB	erfc
STUB	erfcf
STUB	erfcl
STUB	erff
STUB	erfl
STUB	exp
STUB	exp2
STUB	exp2f
STUB	exp2l
STUB	expf
STUB	expl
STUB	expm1
STUB	expm1f
STUB	expm1l
STUB	fclose
STUB	fflush
STUB	fgets
STUB	floorf
STUB	floorl
STUB	fmaxl
STUB	fopen
STUB	fork
STUB	ilogbf
STUB	ilogbl
STUB	llrint
STUB	llrintf
STUB	llrintl
STUB	llround
STUB	llroundf
STUB	llroundl
STUB	log
STUB	log10
STUB	log10f
STUB	log10l
STUB	log1p
STUB	log1pf
STUB	log1pl
STUB	log2
STUB	log2f
STUB	log2l
STUB	logb
STUB	logbf
STUB	logbl
STUB	logf
STUB	logl
STUB	lrint
STUB	lrintf
STUB	lrintl
STUB	lround
STUB	lroundf
STUB	lroundl
STUB	nearbyint
STUB	nearbyintf
STUB	nearbyintl
STUB	remove
STUB	rint
STUB	rintf
STUB	rintl
STUB	round
STUB	roundf
STUB	roundl
STUB	sigsetjmp
STUB	sin
STUB	sinf
STUB	sinh
STUB	sinhf
STUB	sinhl
STUB	sinl
STUB	sqrtl
STUB	tan
STUB	tanf
STUB	tanh
STUB	tanhf
STUB	tanhl
STUB	tanl
STUB	tgamma
STUB	tgammaf
STUB	tgammal
STUB	trunc
STUB	truncf
STUB	truncl
