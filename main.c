// main.c - Compact Observation Scheme Writer Example C implementation file.
// Revision: 2018-12-16.
// Copyright (C) 2018 Masterloop AS.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cos.h"
#include "coswrite.h"

int main()
{
  printf("Compact Observation Scheme Writer Example\n");

  // Test data
  unsigned short obs_id = 1;
  unsigned char obs_type = COS_OBS_TYPE_INT32;
  unsigned int timestamp = (unsigned int) time(NULL);
  int value = 42;

  // Reserve space for objects on stack.
  const int BUFFER_SIZE = 50000;
  unsigned char buffer[BUFFER_SIZE];
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_MULTI_OBSERVATIONS;
  cos_create(&handle, header_flags, buffer, BUFFER_SIZE);

  printf(" > Begin Section\n");
  cos_begin_section(&handle, obs_type, &obs_id, &timestamp);

  printf("   > Add Observation\n");
  for (int i = 0; i < 100; i++)
  {
    unsigned short oid = obs_id + i;
    cos_add_observation(&handle, obs_type, oid, &timestamp, &value);
  }

  printf(" > End Section\n");
  cos_end_section(&handle);

  printf("Size of COS buffer: %d\n", handle.buffer_used);

  return 0;
}

