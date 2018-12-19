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
#include <memory.h>
#include "base64.h"
#include "examples.h"

void write_binary(const char* filename, uint8_t* data, size_t size)
{
  FILE* f = fopen(filename, "wb");
  fwrite(data, size, 1, f);
  fclose(f);
}

int main()
{
  const size_t BUFFER_SIZE = 10000;
  const size_t BUFFER_SIZE_B64 = (4 * (BUFFER_SIZE + 2)) / 3;
  uint8_t buffer[BUFFER_SIZE];
  size_t buffer_used;
  uint8_t buffer_b64[BUFFER_SIZE_B64];
  size_t buffer_used_b64;

  printf("Compact Observation Scheme Writer Examples\n");

  buffer_used = example_single_observation_single_timestamp(buffer, BUFFER_SIZE);
  write_binary("single_observation_single_timestamp.cos", buffer, buffer_used);
  memset(buffer_b64, 0, BUFFER_SIZE_B64);
  buffer_used_b64 = base64_encode(buffer_b64, buffer, buffer_used);
  write_binary("single_observation_single_timestamp.b64", buffer_b64, buffer_used_b64);
  printf("%s\n", buffer_b64);

  buffer_used = example_multi_observation_single_timestamp(buffer, BUFFER_SIZE);
  write_binary("multi_observation_single_timestamp.cos", buffer, buffer_used);
  memset(buffer_b64, 0, BUFFER_SIZE_B64);
  buffer_used_b64 = base64_encode(buffer_b64, buffer, buffer_used);
  write_binary("multi_observation_single_timestamp.b64", buffer_b64, buffer_used_b64);
  printf("%s\n", buffer_b64);

  buffer_used = example_single_observation_multi_timestamp(buffer, BUFFER_SIZE);
  write_binary("single_observation_multi_timestamp.cos", buffer, buffer_used);
  memset(buffer_b64, 0, BUFFER_SIZE_B64);
  buffer_used_b64 = base64_encode(buffer_b64, buffer, buffer_used);
  write_binary("single_observation_multi_timestamp.b64", buffer_b64, buffer_used_b64);
  printf("%s\n", buffer_b64);

  buffer_used = example_multi_observation_multi_timestamp(buffer, BUFFER_SIZE);
  write_binary("multi_observation_multi_timestamp.cos", buffer, buffer_used);
  memset(buffer_b64, 0, BUFFER_SIZE_B64);
  buffer_used_b64 = base64_encode(buffer_b64, buffer, buffer_used);
  write_binary("multi_observation_multi_timestamp.b64", buffer_b64, buffer_used_b64);
  printf("%s\n", buffer_b64);

  buffer_used = example_multi_observation_multi_timestamp_multi_types(buffer, BUFFER_SIZE);
  write_binary("example_multi_observation_multi_timestamp_multi_types.cos", buffer, buffer_used);
  memset(buffer_b64, 0, BUFFER_SIZE_B64);
  buffer_used_b64 = base64_encode(buffer_b64, buffer, buffer_used);
  write_binary("example_multi_observation_multi_timestamp_multi_types.b64", buffer_b64, buffer_used_b64);
  printf("%s\n", buffer_b64);

  printf("Examples Completed.\n");

  return 0;
}
