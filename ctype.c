/* ctype.c
   Copyright (C) 2026  Mikael Pettersson <mikpelinux@gmail.com>

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

#include <ctype.h>

/* This only supports ASCII. */

const char _ctype_[256+1] = {
/*EOF	   */	0,
/* 0-7     */	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,
/* 8-15    */	_C,	_C|_S,	_C|_S,	_C|_S,	_C|_S,	_C|_S,	_C,	_C,
/* 16-23   */	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,
/* 24-31   */	_C,	_C,	_C,	_C,	_C,	_C,	_C,	_C,
/* !"#$%&' */	_S|_B,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
/*()*+,-./ */	_P,	_P,	_P,	_P,	_P,	_P,	_P,	_P,
/*01234567 */	_N,	_N,	_N,	_N,	_N,	_N,	_N,	_N,
/*89:;<=>? */	_N,	_N,	_P,	_P,	_P,	_P,	_P,	_P,
/*@ABCDEFG */	_P,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U|_X,	_U,
/*HIJKLMNO */	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,
/*PQRSTUVW */	_U,	_U,	_U,	_U,	_U,	_U,	_U,	_U,
/*XYZ[\]^_ */	_U,	_U,	_U,	_P,	_P,	_P,	_P,	_P,
/*`abcdefg */	_P,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L|_X,	_L,
/*hijklmno */	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,
/*pqrstuvw */	_L,	_L,	_L,	_L,	_L,	_L,	_L,	_L,
/*xyz{|}~DEL*/	_L,	_L,	_L,	_P,	_P,	_P,	_P,	_C,
};
