/* signal.h
   Copyright (C) 2024-2026  Mikael Pettersson <mikpelinux@gmail.com>

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

#ifndef _SIGNAL_H
#define _SIGNAL_H

#include <sys/cdefs.h>

__BEGIN_DECLS

typedef char sig_atomic_t;

typedef void (*_sighandler_t)(int);

extern _sighandler_t _sighandlers[];

#define SIG_DFL ((_sighandler_t)0)
#define SIG_ERR ((_sighandler_t)-1)
#define SIG_IGN ((_sighandler_t)1)

#define SIGABRT 1
#define SIGFPE  2
#define SIGILL  3
#define SIGSEGV 4
#define SIGTERM 5
#define _NSIG   5

_sighandler_t signal(int sig, _sighandler_t handler);
int raise(int sig);

__END_DECLS

#endif /* !_SIGNAL_H */
