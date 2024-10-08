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

static const uint64_t cbrt_tab[] = {
    0x3f4cd3755d7a2e9a,
    0x3fff333333333333,
    0x4008000000000000,
    0x4001d0e560418937,
    0x4050000000000000,
    0x4086c80000000000,
};

static void gen_cbrt_stub(void)
{
    int i;
    union f64 arg;
    union f64 res;

    printf("static const struct stub_dd cbrt_stub = {\n");
    printf("    \"cbrt\", 0xA5, %zu, {\n", ARRAY_SIZE(cbrt_tab));
    for (i = 0; i < ARRAY_SIZE(cbrt_tab); ++i) {
	arg.ui = cbrt_tab[i];
	res.f = cbrt(arg.f);
	printf("\t{ {0x%016lx}, {0x%016lx} },\n", arg.ui, res.ui);
    }
    printf("    }\n};\n");
}

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

static const uint64_t log_tab[] = {
    0xc053800000000000,
    0xc053c00000000000,
    0xc054000000000000,
    0xc054400000000000,
    0xc054800000000000,
    0xc054c00000000000,
    0xc055000000000000,
    0xc055400000000000,
    0xc055800000000000,
    0xc055c00000000000,
    0xc056000000000000,
    0xc056400000000000,
    0xc056800000000000,
    0xc056c00000000000,
    0xc057000000000000,
    0xc057400000000000,
    0xc057800000000000,
    0xc057c00000000000,
    0xc058000000000000,
    0xc058400000000000,
    0xc058800000000000,
    0xc058c00000000000,
    0xc059000000000000,
};

static void gen_log_stub(void)
{
    int i;
    union f64 arg;
    union f64 res;

    printf("static const struct stub_dd log_stub = {\n");
    printf("    \"log\", 0xA6, %zu, {\n", ARRAY_SIZE(log_tab));
    for (i = 0; i < ARRAY_SIZE(log_tab); ++i) {
	arg.ui = log_tab[i];
	res.f = log(arg.f);
	printf("\t{ {0x%016lx}, {0x%016lx} },\n", arg.ui, res.ui);
    }
    printf("    }\n};\n");
}

static const struct dd pow_tab[] = {
    { 0x3fb999999999999a, 0x3ff4000000000000 },
    { 0x3fb999999999999a, 0xbfd8000000000000 },
    { 0x3fb999999999999a, 0xc017800000000000 },
    { 0x3ff199999999999a, 0x3ff4000000000000 },
    { 0x3ff199999999999a, 0xbfd8000000000000 },
    { 0x3ff199999999999a, 0xc017800000000000 },
    { 0x4000cccccccccccd, 0x3ff4000000000000 },
    { 0x4000cccccccccccd, 0xbfd8000000000000 },
    { 0x4000cccccccccccd, 0xc017800000000000 },
    { 0x4008cccccccccccd, 0x3ff4000000000000 },
    { 0x4008cccccccccccd, 0xc017800000000000 },
    { 0x4008cccccccccccd, 0xbfd8000000000000 },
    { 0x4010666666666666, 0x3ff4000000000000 },
    { 0x4010666666666666, 0xbfd8000000000000 },
    { 0x4010666666666666, 0xc017800000000000 },
    { 0x4014666666666666, 0x3ff4000000000000 },
    { 0x4014666666666666, 0xbfd8000000000000 },
    { 0x4014666666666666, 0xc017800000000000 },
    { 0x4018666666666666, 0x3ff4000000000000 },
    { 0x4018666666666666, 0xbfd8000000000000 },
    { 0x4018666666666666, 0xc017800000000000 },
    { 0x401c666666666666, 0x3ff4000000000000 },
    { 0x401c666666666666, 0xbfd8000000000000 },
    { 0x401c666666666666, 0xc017800000000000 },
    { 0x4020333333333333, 0x3ff4000000000000 },
    { 0x4020333333333333, 0xbfd8000000000000 },
    { 0x4020333333333333, 0xc017800000000000 },
    { 0x4022333333333333, 0x3ff4000000000000 },
    { 0x4022333333333333, 0xbfd8000000000000 },
    { 0x4022333333333333, 0xc017800000000000 },
    { 0x4024000000000000, 0xc00628f5c28f5c34 },
    { 0x4024000000000000, 0xc0063d70a3d70a48 },
    { 0x4024000000000000, 0xc00651eb851eb85c },
    { 0x4024000000000000, 0xc006666666666670 },
    { 0x4024000000000000, 0xc0067ae147ae1484 },
    { 0x4024000000000000, 0xc0068f5c28f5c298 },
    { 0x4024000000000000, 0xc006a3d70a3d70ac },
    { 0x4024000000000000, 0xc006b851eb851ec0 },
    { 0x4024000000000000, 0xc006ccccccccccd4 },
    { 0x4024000000000000, 0xc006e147ae147ae8 },
    { 0x4024000000000000, 0xc006f5c28f5c28fc },
    { 0x4024000000000000, 0xc0070a3d70a3d710 },
    { 0x4024000000000000, 0xc0071eb851eb8524 },
    { 0x4024000000000000, 0xc007333333333338 },
    { 0x4024000000000000, 0xc00747ae147ae14c },
    { 0x4024000000000000, 0xc0075c28f5c28f60 },
    { 0x4024000000000000, 0xc00770a3d70a3d74 },
    { 0x4024000000000000, 0xc007851eb851eb88 },
    { 0x4024000000000000, 0xc00799999999999c },
    { 0x4024000000000000, 0xc007ae147ae147b0 },
    { 0x4024000000000000, 0xc007c28f5c28f5c4 },
    { 0x4024000000000000, 0xc007d70a3d70a3d8 },
    { 0x4024000000000000, 0xc007eb851eb851ec },
    { 0x4024000000000000, 0xc008000000000000 },
    { 0x4024333333333333, 0x3ff4000000000000 },
    { 0x4024333333333333, 0xbfd8000000000000 },
    { 0x4024333333333333, 0xc017800000000000 },
    { 0x4026333333333333, 0x3ff4000000000000 },
    { 0x4026333333333333, 0xbfd8000000000000 },
    { 0x4026333333333333, 0xc017800000000000 },
    { 0x4028333333333333, 0x3ff4000000000000 },
    { 0x4028333333333333, 0xbfd8000000000000 },
    { 0x4028333333333333, 0xc017800000000000 },
    { 0x402a333333333333, 0x3ff4000000000000 },
    { 0x402a333333333333, 0xbfd8000000000000 },
    { 0x402a333333333333, 0xc017800000000000 },
    { 0x402c333333333333, 0x3ff4000000000000 },
    { 0x402c333333333333, 0xbfd8000000000000 },
    { 0x402c333333333333, 0xc017800000000000 },
    { 0x402e333333333333, 0xbfd8000000000000 },
    { 0x402e333333333333, 0xc017800000000000 },
    { 0x402e333333333333, 0x3ff4000000000000 },
    { 0x4030000000000000, 0x3fd0000000000000 },
    { 0x403019999999999a, 0x3ff4000000000000 },
    { 0x403019999999999a, 0xbfd8000000000000 },
    { 0x403019999999999a, 0xc017800000000000 },
    { 0x403119999999999a, 0x3ff4000000000000 },
    { 0x403119999999999a, 0xbfd8000000000000 },
    { 0x403119999999999a, 0xc017800000000000 },
    { 0x403219999999999a, 0x3ff4000000000000 },
    { 0x403219999999999a, 0xbfd8000000000000 },
    { 0x403219999999999a, 0xc017800000000000 },
    { 0x403319999999999a, 0x3ff4000000000000 },
    { 0x403319999999999a, 0xbfd8000000000000 },
    { 0x403319999999999a, 0xc017800000000000 },
    { 0x403419999999999a, 0x3ff4000000000000 },
    { 0x403419999999999a, 0xbfd8000000000000 },
    { 0x403419999999999a, 0xc017800000000000 },
    { 0x403519999999999a, 0x3ff4000000000000 },
    { 0x403519999999999a, 0xbfd8000000000000 },
    { 0x403519999999999a, 0xc017800000000000 },
    { 0x403619999999999a, 0x3ff4000000000000 },
    { 0x403619999999999a, 0xbfd8000000000000 },
    { 0x403619999999999a, 0xc017800000000000 },
    { 0x403719999999999a, 0x3ff4000000000000 },
    { 0x403719999999999a, 0xbfd8000000000000 },
    { 0x403719999999999a, 0xc017800000000000 },
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
    0x3f4cd3755d7a2e9a,
    0x3fd6666666666666,
    0x3ff0200040000000,
    0x3fff333333333333,
    0x4008000000000000,
    0x4001d0e560418937,
    0x4010000000000000,
    0x4070000000000000,
    0x7fffffffffffffff,
    0x8000000000000000,
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
    gen_cbrt_stub();
    gen_floor_stub();
    gen_log_stub();
    gen_pow_stub();
    gen_sqrt_stub();
    gen_sqrtf_stub();
    return 0;
}
