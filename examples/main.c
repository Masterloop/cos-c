/**
 * @file  main.c
 * @date  2018-12-17
 * @brief Compact Observation Scheme Writer Example main C implementation file.
 * 
 * Copyright (C) 2018 Masterloop AS.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE. 
 */

#include <stdio.h>
#include "examples.h"

int main()
{
  const int BUFFER_SIZE = 50000;
  unsigned char buffer[BUFFER_SIZE];

  printf("Compact Observation Scheme Writer Examples\n");

  example_single_observation(buffer, BUFFER_SIZE);
  example_multi_observation_single_timestamp(buffer, BUFFER_SIZE);
  example_single_observation_multi_timestamp(buffer, BUFFER_SIZE);
  example_multi_observation_multi_timestamp(buffer, BUFFER_SIZE);

  return 0;
}
