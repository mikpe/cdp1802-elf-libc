# cdp1802-elf-libc
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

TRIPLET=cdp1802-unknown-elf

CROSS_COMPILE=$(TRIPLET)-
AR=$(CROSS_COMPILE)ar
CC=$(CROSS_COMPILE)gcc
CPPFLAGS=-Iinclude
CFLAGS=-Wall -Os -ffreestanding

PREFIX=usr

BUILD=	crt0.o libc.a libm.a

CRT=	crt0.o

CTYPE=	iscntrl.o isprint.o

MATH=	atanf.o floor.o fmax.o ilogb.o pow.o sqrt.o sqrtf.o

MEMORY=	memchr.o memcmp.o memcpy.o memmove.o mempcpy.o memset.o

MISC=	_assert.o _exit.o _mcount.o _mulovf.o errno.o stubs.o

SETJMP=	longjmp.o setjmp.o

SIGNAL=	raise.o signal.o

STDIO=	_is_console.o _num2dec.o _putc.o _putint.o _puts.o _vprintf.o _write.o \
	fprintf.o fputc.o fputs.o fwrite.o perror.o printf.o putchar.o puts.o \
	snprintf.o sprintf.o stdfiles.o vfprintf.o vprintf.o vsprintf.o

STDLIB=	abort.o calloc.o div.o exit.o free.o malloc.o qsort.o rand.o realloc.o srand.o

STRING=	strcat.o strchr.o strcmp.o strcpy.o strdup.o strlen.o strncasecmp.o \
	strncat.o strncmp.o strncpy.o strndup.o strnlen.o strrchr.o strspn.o

LIBC=	$(CTYPE) $(MEMORY) $(MISC) $(SETJMP) $(SIGNAL) $(STDIO) $(STDLIB) $(STRING)

LIBM=	$(MATH)

build:	$(BUILD)

libc.a:	$(LIBC)
	$(AR) ruv libc.a $(LIBC)

libm.a:	$(LIBM)
	$(AR) ruv libm.a $(LIBM)

install:	$(BUILD)
	mkdir -p $(DESTDIR)/$(PREFIX)/lib
	cp $(BUILD) $(DESTDIR)/$(PREFIX)/lib/
	mkdir -p $(DESTDIR)/$(PREFIX)/include/sys
	cp include/*.h $(DESTDIR)/$(PREFIX)/include/
	cp include/sys/*.h $(DESTDIR)/$(PREFIX)/include/sys/

clean:
	rm -f $(BUILD) $(LIBC) $(LIBM)
