/* xlibm.h
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

/* Implementation-specific declarations only available within libm. */

#include <stddef.h>
#include <stdint.h>

union f32 {
    uint32_t ui;
    float f;
};

union f64 {
    uint64_t ui;
    double d;
};

struct stub_dd {
    const char *func;
    unsigned int tag;
    size_t n;
    struct {
	union f64 arg;
	union f64 res;
    } v[];
};

struct stub_ddd {
    const char *func;
    unsigned int tag;
    size_t n;
    struct {
	union f64 arg1;
	union f64 arg2;
	union f64 res;
    } v[];
};

struct stub_ff {
    const char *func;
    unsigned int tag;
    size_t n;
    struct {
	union f32 arg;
	union f32 res;
    } v[];
};

double _libm_stub_dd(double x, const struct stub_dd *stub);
double _libm_stub_ddd(double x, double y, const struct stub_ddd *stub);
float _libm_stub_ff(float x, const struct stub_ff *stub);
