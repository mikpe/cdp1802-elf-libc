/* math.h
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

#ifndef _MATH_H
#define _MATH_H

double acos(double x);
float acosf(float x);
double acosh(double x);
double asin(double x);
float asinf(float x);
double asinh(double x);
double atan(double x);
double atan2(double x, double y);
float atan2f(float x, float y);
float atanf(float x);
double atanh(double x);
double cbrt(double x);
double ceil(double x);
float ceilf(float x);
double copysign(double x, double y);
double cos(double x);
float cosf(float x);
double cosh(double x);
float coshf(float x);
double erf(double x);
double erfc(double x);
double exp(double x);
double exp2(double x);
float expf(float x);
double expm1(double x);
double fabs(double x);
float fabsf(float x);
double fdim(double x, double y);
double floor(double x);
float floorf(float x);
double fma(double x, double y, double z);
double fmax(double x, double y);
double fmin(double x, double y);
double fmod(double x, double y);
float fmodf(float x, float y);
double frexp(double x, int *exp);
float frexpf(float x, int *exp);
double hypot(double x, double y);
int ilogb(double x);
double ldexp(double x, int exp);
float ldexpf(float x, int exp);
double lgamma(double x);
long long llrint(double x);
long long llround(double x);
double log(double x);
double log10(double x);
float log10f(float x);
double log1p(double x);
double log2(double x);
double logb(double x);
float logf(float x);
long lrint(double x);
long lround(double x);
double modf(double x, double *iptr);
float modff(float x, float *iptr);
double nan(const char *tagp);
double nearbyint(double x);
double nextafter(double x, double y);
double nexttoward(double x, double y);
double pow(double x, double y);
float powf(float x, float y);
double remainder(double x, double y);
double remquo(double x, double y, int *quo);
double rint(double x);
double round(double x);
double scalbln(double x, long exp);
double scalbn(double x, int exp);
double sin(double x);
void sincos(double x, double *sin, double *cos);
float sinf(float x);
double sinh(double x);
float sinhf(float x);
double sqrt(double x);
float sqrtf(float x);
double tan(double x);
float tanf(float x);
double tanh(double x);
float tanhf(float x);
double tgamma(double x);
double trunc(double x);

#define isnan(x) __builtin_isnan ((x))
#define signbit(x) __builtin_signbit ((x))

#endif /* !_MATH_H */
