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
STUB	atoi
STUB	calloc
STUB	fclose
STUB	fflush
STUB	floor
STUB	fmax
STUB	fopen
STUB	fork
STUB	fprintf
STUB	fputc
STUB	fputs
STUB	free
STUB	fwrite
STUB	ilogb
STUB	iscntrl
STUB	isprint
STUB	malloc
STUB	memchr
STUB	memcmp
STUB	memcpy
STUB	memmove
STUB	mempcpy
STUB	memset
STUB	mmap
STUB	posix_memalign
STUB	pow
STUB	printf
STUB	qsort
STUB	rand
STUB	realloc
STUB	remove
STUB	sigsetjmp
STUB	sin
STUB	snprintf
STUB	sprintf
STUB	sqrt
STUB	sqrtf
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
STUB	tmpnam
STUB	vfprintf
STUB	vprintf
STUB	vsprintf

	lbr	abort	; FIXME: just a stub for now
