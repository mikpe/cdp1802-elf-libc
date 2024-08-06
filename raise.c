/* raise.c
   Copyright (C) 2024  Mikael Pettersson <mikpelinux@gmail.com>

   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library.  If not, see <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "xlibc.h"

int raise(int sig)
{
    unsigned int i;
    _sighandler_t *slot, handler;

    i = sig - SIGABRT;
    if (i >= _NSIG) {
	errno = EINVAL;
	return -1;
    }
    slot = &_sighandlers[i];
    handler = *slot;
    if (handler == SIG_DFL) {
	_puts("terminating due to signal ");
	_putint(sig);
	putchar('\n');
	_exit(1);
    } else if (handler != SIG_IGN) {
	*slot = SIG_DFL;
	(*handler)(sig);
    }
    return 0;
}
