/**
 * @file  examples.c
 * @date  2018-12-17
 * @brief Compact Observation Scheme Writer Example C implementation file.
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
#include <stdlib.h>
#include <time.h>
#include "../cos.h"
#include "../coswrite.h"

void example_single_observation(unsigned char* buffer, unsigned int buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short obs_id = 1;
  unsigned char obs_type = COS_OBS_TYPE_INT32;
  unsigned int timestamp = (unsigned int) time(NULL);
  int value = 42;

  // Reserve space for objects on stack.
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_DEFAULT;
  cos_init(&handle, header_flags, buffer, buffer_size);

  printf(" > Begin Section\n");
  cos_begin_section(&handle, &obs_type, &obs_id, &timestamp);

  printf(" > Addding 1 observation\n");
  cos_add_observation(&handle, NULL, NULL, NULL, &value);

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %d\n\n", handle.buffer_used);
}

void example_multi_observation_single_timestamp(unsigned char* buffer, unsigned int buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 1000;
  unsigned int timestamp = (unsigned int) time(NULL);
  unsigned char obs_type = COS_OBS_TYPE_INT32;
  int value = 42;

  // Reserve space for objects on stack.
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_MULTI_OBSERVATIONS;
  cos_init(&handle, header_flags, buffer, buffer_size);

  printf(" > Begin Section\n");
  cos_begin_section(&handle, NULL, NULL, &timestamp);

  printf(" > Adding %d observations\n", observation_count);
  for (unsigned short n = 0; n <= observation_count; n++)
  {
    unsigned short obs_id = 1 + n;
    cos_add_observation(&handle, &obs_type, &obs_id, NULL, &value);
  }

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %d\n\n", handle.buffer_used);}

void example_single_observation_multi_timestamp(unsigned char* buffer, unsigned int buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 1000;
  unsigned short obs_id = 1;
  unsigned char obs_type = COS_OBS_TYPE_INT32;
  unsigned int timestamp = (unsigned int) time(NULL);
  int value = 42;

  // Reserve space for objects on stack.
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_MULTI_TIMESTAMPS;
  cos_init(&handle, header_flags, buffer, buffer_size);

  printf(" > Begin Section\n");
  cos_begin_section(&handle, &obs_type, &obs_id, &timestamp);

  printf(" > Adding %d observations\n", observation_count);
  for (unsigned short n = 0; n < observation_count; n++)
  {
    unsigned int t = timestamp + n;
    cos_add_observation(&handle, NULL, NULL, &t, &value);
  }

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %d\n\n", handle.buffer_used);
}

void example_multi_observation_multi_timestamp(unsigned char* buffer, unsigned int buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 1000;
  unsigned char obs_type = COS_OBS_TYPE_INT32;
  unsigned int timestamp = (unsigned int) time(NULL);
  int value = 42;

  // Reserve space for objects on stack.
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_MULTI_OBSERVATIONS | COS_HEADER_MULTI_TIMESTAMPS;
  cos_init(&handle, header_flags, buffer, buffer_size);

  printf(" > Begin Section\n");
  cos_begin_section(&handle, NULL, NULL, &timestamp);

  printf(" > Adding %d observations\n", observation_count);
  for (unsigned short n = 0; n < observation_count; n++)
  {
    unsigned int t = timestamp + n;
    unsigned short obs_id = 1 + n;
    cos_add_observation(&handle, &obs_type, &obs_id, &t, &value);
  }

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %d\n\n", handle.buffer_used);
}
