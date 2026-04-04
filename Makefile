# cdp1802-elf-libc
# Copyright (C) 2024-2026  Mikael Pettersson <mikpelinux@gmail.com>
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

ARCH ?= 1802

CROSS_COMPILE=$(TRIPLET)-
AR=$(CROSS_COMPILE)ar
ASFLAGS=-march=$(ARCH)
CC=$(CROSS_COMPILE)gcc
CPPFLAGS=-Iinclude
CFLAGS=-Wall -Os -ffreestanding -march=$(ARCH)

BUILD=	crt0.o libc.a libm.a

CRT=	crt0.o

CTYPE=	ctype.o iscntrl.o isprint.o

LOCALE=	setlocale.o

MATH=	_libm_stub_dd.o _libm_stub_ddd.o _libm_stub_ff.o \
	atanf.o cbrt.o floor.o fmax.o ilogb.o log.o pow.o sqrt.o sqrtf.o

MEMORY=	memchr.o memcmp.o memcpy.o memmove.o mempcpy.o memset.o

MISC=	_assert.o _exit.o _initfini.o _main.o _mcount.o _mulovf.o errno.o stubs.o

SETJMP=	longjmp.o setjmp.o

SIGNAL=	raise.o signal.o

STDIO=	_is_console.o _num2dec.o _putc.o _putint.o _puts.o _vprintf.o _vsnprintf.o \
	_write.o fdopen.o feof.o ferror.o fgetc.o fileno.o fprintf.o fputc.o fputs.o \
	fread.o fseek.o ftell.o fwrite.o getc.o perror.o printf.o putc.o putchar.o puts.o \
	setvbuf.o snprintf.o sprintf.o stdfiles.o ungetc.o vfprintf.o vprintf.o vsnprintf.o \
	vsprintf.o

STDLIB=	abort.o atexit.o calloc.o div.o exit.o free.o getenv.o malloc.o qsort.o \
	rand.o realloc.o srand.o strtoul.o

STRING=	strcat.o strchr.o strcmp.o strcoll.o strcpy.o strdup.o strerror.o strlen.o \
	strncasecmp.o strncat.o strncmp.o strncpy.o strndup.o strnlen.o strrchr.o strspn.o \
	strxfrm.o

TIME=	strftime.o

LIBC=	$(CTYPE) $(LOCALE) $(MEMORY) $(MISC) $(SETJMP) $(SIGNAL) $(STDIO) $(STDLIB) $(STRING) $(TIME)

LIBM=	$(MATH)

build:
	$(MAKE) ARCH=1802 build-arch
	$(MAKE) ARCH=1804 build-arch

build-arch:	$(BUILD)
	mkdir -p build-$(ARCH)
	mv $(BUILD) build-$(ARCH)
	mv *.o build-$(ARCH)

libc.a:	$(LIBC)
	$(AR) ruv libc.a $(LIBC)

libm.a:	$(LIBM)
	$(AR) ruv libm.a $(LIBM)

install:	install-common
	$(MAKE) ARCH=1802 install-arch
	$(MAKE) ARCH=1804 install-arch

install-arch:	build-$(ARCH)
	mkdir -p $(PREFIX)/usr/lib/$(ARCH)
	cd build-$(ARCH) && cp $(BUILD) $(PREFIX)/usr/lib/$(ARCH)

install-common:
	mkdir -p $(PREFIX)/usr/include/sys
	cp include/*.h $(PREFIX)/usr/include/
	cp include/sys/*.h $(PREFIX)/usr/include/sys/

clean:
	rm -f $(BUILD) $(LIBC) $(LIBM)
	rm -rf build-1802 build-1804
