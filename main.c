// main.c - Compact Observation Scheme Writer Example C implementation file.
// Revision: 2018-12-15.
// Copyright (C) 2018 Masterloop AS.

#include <stdio.h>
#include "cos.h"
#include "coswrite.h"

int main()
{
  printf("Compact Observation Scheme Writer Example\n");

  // Reserve space for objects on stack.
  const int BUFFER_SIZE = 4096;
  unsigned char buffer[BUFFER_SIZE];
  struct coswrite_handle handle;

  // Initialize COS structure.
  unsigned char header_flags = COS_HEADER_DEFAULT;
  cos_init(&handle, header_flags, buffer, BUFFER_SIZE);

  return 0;
}

