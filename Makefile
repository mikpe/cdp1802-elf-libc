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
CFLAGS=-Wall -Os

PREFIX=usr

BUILD=	crt0.o libc.a libm.a

CRT=	crt0.o
LIBC=	_exit.o abort.o exit.o putchar.o puts.o stubs.o
LIBM=

build:	$(BUILD)

libc.a:	$(LIBC)
	$(AR) ruv libc.a $(LIBC)

libm.a:	$(LIBM)
	$(AR) ruv libm.a $(LIBM)

install:	$(BUILD)
	mkdir -p $(DESTDIR)/$(PREFIX)/lib
	cp $(BUILD) $(DESTDIR)/$(PREFIX)/lib/
	mkdir -p $(DESTDIR)/$(PREFIX)/include
	cp include/*.h $(DESTDIR)/$(PREFIX)/include/

clean:
	rm -f $(BUILD) $(LIBC) $(LIBM)
