/* gen-stubs.c
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

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(A[0]))

union f32 {
    uint32_t ui;
    float f;
};

union f64 {
    uint64_t ui;
    double f;
};

struct dd {
    uint64_t x;
    uint64_t y;
};

static const uint64_t floor_tab[] = {
    0x408ffffff0000000,
};

static void gen_floor_stub(void)
{
    int i;
    union f64 arg;
    union f64 res;

    printf("static const struct stub_dd floor_stub = {\n");
    printf("    \"floor\", 0xA1, %zu, {\n", ARRAY_SIZE(floor_tab));
    for (i = 0; i < ARRAY_SIZE(floor_tab); ++i) {
	arg.ui = floor_tab[i];
	res.f = floor(arg.f);
	printf("\t{ {0x%016lx}, {0x%016lx} },\n", arg.ui, res.ui);
    }
    printf("    }\n};\n");
}

static const struct dd pow_tab[] = {
    { 0x3fb999999999999a, 0x3ff4000000000000 },
    { 0x3fb999999999999a, 0xbfd8000000000000 },
    { 0x3fb999999999999a, 0xc017800000000000 },
    { 0x4024000000000000, 0xc008000000000000 },
    { 0x4030000000000000, 0x3fd0000000000000 },
    { 0x4040000000000000, 0x3fd5555555555555 },
    { 0x8000000000000000, 0x3fe0000000000000 },
};

static void gen_pow_stub(void)
{
    int i;
    union f64 arg1, arg2;
    union f64 res;

    printf("static const struct stub_ddd pow_stub = {\n");
    printf("    \"pow\", 0xA4, %zu, {\n", ARRAY_SIZE(pow_tab));
    for (i = 0; i < ARRAY_SIZE(pow_tab); ++i) {
	arg1.ui = pow_tab[i].x;
	arg2.ui = pow_tab[i].y;
	res.f = pow(arg1.f, arg2.f);
	printf("\t{ {0x%016lx}, {0x%016lx}, {0x%016lx} },\n", arg1.ui, arg2.ui, res.ui);
    }
    printf("    }\n};\n");
}

static const uint64_t sqrt_tab[] = {
    0x3fd6666666666666,
    0x4008000000000000,
    0x7fffffffffffffff,
};

static void gen_sqrt_stub(void)
{
    int i;
    union f64 arg;
    union f64 res;

    printf("static const struct stub_dd sqrt_stub = {\n");
    printf("    \"sqrt\", 0xA3, %zu, {\n", ARRAY_SIZE(sqrt_tab));
    for (i = 0; i < ARRAY_SIZE(sqrt_tab); ++i) {
	arg.ui = sqrt_tab[i];
	res.f = sqrt(arg.f);
	printf("\t{ {0x%016lx}, {0x%016lx} },\n", arg.ui, res.ui);
    }
    printf("    }\n};\n");
}

static const uint32_t sqrtf_tab[] = {
    0x41e80000,
};

static void gen_sqrtf_stub(void)
{
    int i;
    union f32 arg;
    union f32 res;

    printf("static const struct stub_ff sqrtf_stub = {\n");
    printf("    \"sqrtf\", 0xA2, %zu, {\n", ARRAY_SIZE(sqrtf_tab));
    for (i = 0; i < ARRAY_SIZE(sqrtf_tab); ++i) {
	arg.ui = sqrtf_tab[i];
	res.f = sqrtf(arg.f);
	printf("\t{ {0x%08x}, {0x%08x} },\n", arg.ui, res.ui);
    }
    printf("    }\n};\n");
}

int main(void)
{
    gen_floor_stub();
    gen_pow_stub();
    gen_sqrt_stub();
    gen_sqrtf_stub();
    return 0;
}