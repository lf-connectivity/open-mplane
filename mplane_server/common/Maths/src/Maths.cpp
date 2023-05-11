/*!
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * \file      Maths.cpp
 * \brief     General maths routines
 *
 *
 * \details
 *
 */

//=============================================================================================================
// INCLUDE
//=============================================================================================================

#include "Maths.h"

using namespace Mplane;

//=============================================================================================================
// LOCAL
//=============================================================================================================
// Powers of neg 10 quick reference, static scope.
const float powneg10[38] = {
    1.0f,   0.1f,   0.01f,  1e-3f,  1e-4f,  1e-5f,  1e-6f,  1e-7f,
    1e-8f,  1e-9f,  1e-10f, 1e-11f, 1e-12f, 1e-13f, 1e-14f, 1e-15f,
    1e-16f, 1e-17f, 1e-18f, 1e-19f, 1e-20f, 1e-21f, 1e-22f, 1e-23f,
    1e-24f, 1e-25f, 1e-26f, 1e-27f, 1e-28f, 1e-29f, 1e-30f, 1e-31f,
    1e-32f, 1e-33f, 1e-34f, 1e-35f, 1e-36f, 1e-37f};
const float powpos10[38] = {
    1.0f,   10.0f,  100.0f, 1e+3f,  1e+4f,  1e+5f,  1e+6f,  1e+7f,
    1e+8f,  1e+9f,  1e+10f, 1e+11f, 1e+12f, 1e+13f, 1e+14f, 1e+15f,
    1e+16f, 1e+17f, 1e+18f, 1e+19f, 1e+20f, 1e+21f, 1e+22f, 1e+23f,
    1e+24f, 1e+25f, 1e+26f, 1e+27f, 1e+28f, 1e+29f, 1e+30f, 1e+31f,
    1e+32f, 1e+33f, 1e+34f, 1e+35f, 1e+36f, 1e+37f};

//=============================================================================================================
// PUBLIC
//=============================================================================================================

//-------------------------------------------------------------------------------------------------------------
float
Maths::char2float(const char* str, char** endptr) {
  float number = 0.0;
  int exponent = 0;
  int negative = 0;
  char* p = (char*)str;
  int num_digits = 0;

  // Skip leading spaces (isspace() definition of whitespace includes CR LF etc
  // and not behaviour what I want
  while (*p == ' ')
    p++;

  // Handle optional sign
  switch (*p) {
    case '-':
      negative = 1; // Fall through to increment position (don't break)
    case '+':
      p++;
  }

  // Process string of digits
  while ((*p >= '0') && (*p <= '9')) { // while is a digit
    number = number * 10.0f + (*p - '0');
    p++;
    num_digits++;
  }

  // Process decimal part
  if (*p == '.') {
    int num_decimals = 0;

    p++;
    while ((*p >= '0') && (*p <= '9')) { // while is a digit
      number = number * 10.0f + (*p - '0');
      p++;
      num_digits++;
      num_decimals++;
    }

    exponent -= num_decimals;
  }

  // break out early if no digits found
  if (num_digits == 0) {
    if (endptr)
      *endptr = p;
    return 0.0f;
  }

  // Correct for sign
  if (negative)
    number = -number;

  // Process an exponent string
  if (*p == 'e' || *p == 'E') {

    // Handle optional sign
    negative = 0;
    switch (*++p) {
      case '-':
        negative = 1; // Fall through to increment pos
      case '+':
        p++;
    }

    // Process string of digits
    int n = 0;
    while ((*p >= '0') && (*p <= '9')) { // while is a digit
      n = n * 10 + (*p - '0');
      p++;
    }

    if (negative)
      exponent -= n;
    else
      exponent += n;
  }

  // Scale the result limiting at the end stops if the bounds of a float are
  // exceeded
  if (exponent < 0) {
    if (exponent > -38)
      number *= powneg10[-exponent];
    else
      number = 0.0f;
  } else {
    if (exponent < +38)
      number *= powpos10[exponent];
    else
      number = 1e38f;
  }

  if (endptr)
    *endptr = p;

  return number;
}

//-------------------------------------------------------------------------------------------------------------
float
Maths::str2float(const std::string& str) {
  return char2float(str.c_str());
}

//-------------------------------------------------------------------------------------------------------------
float
Maths::ieee754toFloat(UINT32 ieee754) {
  union U {
    UINT32 uival;
    float fval;
  };

  U u;
  u.uival = ieee754;
  return u.fval;
}

//-------------------------------------------------------------------------------------------------------------
UINT32
Maths::floatToIeee754(float fval) {
  union U {
    UINT32 uival;
    float fval;
  };

  U u;
  u.fval = fval;
  return u.uival;
}

//-------------------------------------------------------------------------------------------------------------
bool
Maths::floatEqual(float lhs, float rhs, float accuracy) {
  return fabs(lhs - rhs) <= accuracy;
}
