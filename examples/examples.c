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

size_t example_single_observation_single_timestamp(uint8_t* buffer, size_t buffer_size)
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

  printf("Size of COS buffer: %zu\n", handle.buffer_used);

  return handle.buffer_used;
}

size_t example_multi_observation_single_timestamp(uint8_t* buffer, size_t buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 10;
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

  printf("Size of COS buffer: %zu\n", handle.buffer_used);

  return handle.buffer_used;
}

size_t example_single_observation_multi_timestamp(uint8_t* buffer, size_t buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 10;
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
    unsigned int t = timestamp - observation_count + n;
    cos_add_observation(&handle, NULL, NULL, &t, &value);
  }

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %zu\n", handle.buffer_used);

  return handle.buffer_used;
}

size_t example_multi_observation_multi_timestamp(uint8_t* buffer, size_t buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 10;
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
    unsigned int t = timestamp - observation_count + n;
    unsigned short obs_id = 1 + n;
    cos_add_observation(&handle, &obs_type, &obs_id, &t, &value);
  }

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %zu\n", handle.buffer_used);

  return handle.buffer_used;
}

size_t example_multi_observation_multi_timestamp_multi_types(uint8_t* buffer, size_t buffer_size)
{
  printf("[%s]\n", __func__);

  // Test data
  unsigned short observation_count = 10;
  unsigned char obs_type;
  time_t timestamp;
  time(&timestamp);

  // Reserve space for objects on stack.
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_MULTI_OBSERVATIONS | COS_HEADER_MULTI_TIMESTAMPS;
  cos_init(&handle, header_flags, buffer, buffer_size);

  printf(" > Begin Section\n");
  cos_begin_section(&handle, NULL, NULL, &timestamp);

  printf(" > Adding observations\n");
  unsigned short obs_id;
  unsigned int t;

  obs_type = COS_OBS_TYPE_BOOLEAN;
  obs_id = 2;
  unsigned char v_bool = 1;
  t = timestamp - 11;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_bool);

  obs_type = COS_OBS_TYPE_DOUBLE;
  obs_id = 3;
  double v_double = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862;
  t = timestamp - 10;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_double);

  obs_type = COS_OBS_TYPE_FLOAT;
  obs_id = 3;
  float v_float = 3.1415926;
  t = timestamp - 9;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_float);

  obs_type = COS_OBS_TYPE_INT32;
  obs_id = 4;
  signed int v_int32 = 2147483647;
  t = timestamp - 8;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_int32);

  obs_type = COS_OBS_TYPE_INT16;
  obs_id = 4;
  signed short v_int16 = 32767;
  t = timestamp - 7;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_int16);

  obs_type = COS_OBS_TYPE_UINT16;
  obs_id = 4;
  unsigned short v_uint16 = 65535;
  t = timestamp - 6;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_uint16);

  obs_type = COS_OBS_TYPE_INT8;
  obs_id = 4;
  signed char v_int8 = 127;
  t = timestamp - 5;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_int8);

  obs_type = COS_OBS_TYPE_UINT8;
  obs_id = 4;
  unsigned char v_uint8 = 255;
  t = timestamp - 4;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, &v_uint8);

  obs_type = COS_OBS_TYPE_POSITION_2D;
  obs_id = 5;
  float v_pos2d[2];
  v_pos2d[0] = 58.9325;
  v_pos2d[1] = 5.7053;
  t = timestamp - 3;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, v_pos2d);

  obs_type = COS_OBS_TYPE_POSITION_3D;
  obs_id = 5;
  float v_pos3d[3];
  v_pos3d[0] = 58.9325;
  v_pos3d[1] = 5.7053;
  v_pos3d[2] = 70.123;
  t = timestamp - 2;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, v_pos3d);

  obs_type = COS_OBS_TYPE_ASCII;
  obs_id = 6;
  char* v_ascii = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
  t = timestamp - 1;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, v_ascii);

  obs_type = COS_OBS_TYPE_UTF8;
  obs_id = 6;
  char* v_utf8 = "\xc3\x98yvind the Viking";
  t = timestamp - 1;
  cos_add_observation(&handle, &obs_type, &obs_id, &t, v_utf8);

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %zu\n", handle.buffer_used);

  return handle.buffer_used;
}
