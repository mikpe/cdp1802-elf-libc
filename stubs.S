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

.macro	STUB	name
	.global	\name
	.type	\name, @function
\name:
.endm

	.text
STUB	__libc_stderr
STUB	__libc_stdout
STUB	__sigsetjmp
STUB	__stack_chk_fail
STUB	__stack_chk_guard
STUB	_mcount
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
STUB	assert
STUB	atan
STUB	atanf
STUB	atanh
STUB	atanhf
STUB	atanhl
STUB	atanl
STUB	atoi
STUB	cbrt
STUB	cbrtf
STUB	cbrtl
STUB	calloc
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
STUB	floor
STUB	floorf
STUB	floorl
STUB	fmax
STUB	fmaxl
STUB	fopen
STUB	fork
STUB	fprintf
STUB	fputc
STUB	fputs
STUB	free
STUB	fwrite
STUB	ilogb
STUB	ilogbf
STUB	ilogbl
STUB	iscntrl
STUB	isprint
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
STUB	malloc
STUB	memchr
STUB	memcmp
STUB	memcpy
STUB	memmove
STUB	mempcpy
STUB	memset
STUB	mmap
STUB	nearbyint
STUB	nearbyintf
STUB	nearbyintl
STUB	posix_memalign
STUB	pow
STUB	printf
STUB	qsort
STUB	rand
STUB	realloc
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
STUB	snprintf
STUB	sprintf
STUB	sqrt
STUB	sqrtf
STUB	sqrtl
STUB	strcat
STUB	strchr
STUB	strcmp
STUB	strcpy
STUB	strdup
STUB	strlen
STUB	strncasecmp
STUB	strncat
STUB	strncmp
STUB	strncpy
STUB	strndup
STUB	strrchr
STUB	strspn
STUB	tan
STUB	tanf
STUB	tanh
STUB	tanhf
STUB	tanhl
STUB	tanl
STUB	tgamma
STUB	tgammaf
STUB	tgammal
STUB	tmpnam
STUB	trunc
STUB	truncf
STUB	truncl
STUB	vfprintf
STUB	vprintf
STUB	vsprintf

	lbr	abort	; FIXME: just a stub for now
