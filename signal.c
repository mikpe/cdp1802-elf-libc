/* signal.c
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

_sighandler_t _sighandlers[_NSIG]; /* indexed by sig-1 */

_sighandler_t signal(int sig, _sighandler_t handler)
{
    unsigned int i;
    _sighandler_t *slot, old;

    i = sig - SIGABRT;
    if (i >= _NSIG) {
	errno = EINVAL;
	return SIG_ERR;
    }
    slot = &_sighandlers[i];
    old = *slot;
    *slot = handler;
    return old;
}
