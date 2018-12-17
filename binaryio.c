/**
 * @file  binaryio.c
 * @date  2018-12-17
 * @brief Endian-consistent binary writer C implementation file.
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

#include <memory.h>
#include "binaryio.h"

unsigned char is_little_endian()
{
	int n = 1;
	if (*(char *)&n == 1)
	{
	  return 1;
	}
	else
	{
	  return 0;
	}
}

void binaryio_write_bytes(void (*bio_writerp)(void*, unsigned char), void* bio_handle, const unsigned char* bytes, const unsigned int size)
{
  for (unsigned int i = 0; i < size; i++)
  {
    bio_writerp(bio_handle, bytes[i]);
  }
}

void binaryio_write_with_endianness(void (*bio_writerp)(void*, unsigned char), void* bio_handle, const void* bytes, const unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    unsigned char b = ((unsigned char*)(bytes))[i];
    if (is_little_endian() == 1)
    {
      b = ((unsigned char*)(bytes))[size - i - 1];
    }
    bio_writerp(bio_handle, b);
  }
}

void binaryio_write_int8(void (*bio_writerp)(void*, unsigned char), void* bio_handle, char value)
{
	bio_writerp(bio_handle, value);
}

void binaryio_write_uint8(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned char value)
{
	bio_writerp(bio_handle, value);
}

void binaryio_write_uint16(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned short value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 2);
}

void binaryio_write_int16(void (*bio_writerp)(void*, unsigned char), void* bio_handle, short value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 2);
}

void binaryio_write_uint32(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned int value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 4);
}

void binaryio_write_int32(void (*bio_writerp)(void*, unsigned char), void* bio_handle, int value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 4);
}

void binaryio_write_int64(void (*bio_writerp)(void*, unsigned char), void* bio_handle, int64_t value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 8);
}

void binaryio_write_float(void (*bio_writerp)(void*, unsigned char), void* bio_handle, float value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 4);
}

void binaryio_write_double(void (*bio_writerp)(void*, unsigned char), void* bio_handle, double value)
{
  binaryio_write_with_endianness(bio_writerp, bio_handle, &value, 8);
}
