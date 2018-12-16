// binaryio.c - Endian-consistent binary writer C implementation file
// Revision: 2018-12-16
// Copyright (C) 2018 Masterloop AS.

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

void binaryio_write_straight(void (*bio_writerp)(void*, unsigned char), void* bio_handle, const void* value, const unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    bio_writerp(bio_handle, ((unsigned char*)value)[i]);
  }
}

void binaryio_write_endianness(void (*bio_writerp)(void*, unsigned char), void* bio_handle, const void* value, const unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    unsigned char b = ((unsigned char*)value)[i];
    if (is_little_endian() == 1)
    {
      b = ((unsigned char*)value)[size - i - 1];
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
  unsigned char bytes[2];
  memcpy(bytes, &value, 2);
  for (int i = 0; i < 2; i++)
  {
    unsigned char b = bytes[i];
    if (is_little_endian() == 1)
    {
      b = bytes[2 - i - 1];
    }
    
    bio_writerp(bio_handle, b);
  }
}

void binaryio_write_int16(void (*bio_writerp)(void*, unsigned char), void* bio_handle, short value)
{
  unsigned char bytes[2];
  memcpy(bytes, &value, 2);
  for (int i = 0; i < 2; i++)
  {
    unsigned char b = bytes[i];
    if (is_little_endian() == 1)
    {
      b = bytes[2 - i - 1];
    }
    
    bio_writerp(bio_handle, b);
  }
}

void binaryio_write_uint32(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned int value)
{
  unsigned char bytes[4];
  memcpy(bytes, &value, 4);
  for (int i = 0; i < 4; i++)
  {
    unsigned char b = bytes[i];
    if (is_little_endian() == 1)
    {
      b = bytes[4 - i - 1];
    }
    bio_writerp(bio_handle, b);
  }
}

void binaryio_write_int32(void (*bio_writerp)(void*, unsigned char), void* bio_handle, int value)
{
  unsigned char bytes[4];
  memcpy(bytes, &value, 4);
  for (int i = 0; i < 4; i++)
  {
    unsigned char b = bytes[i];
    if (is_little_endian() == 1)
    {
      b = bytes[4 - i - 1];
    }
    bio_writerp(bio_handle, b);
  }
}

void binaryio_write_int64(void (*bio_writerp)(void*, unsigned char), void* bio_handle, int64_t value)
{
  unsigned char bytes[8];
  memcpy(bytes, &value, 8);
  for (int i = 0; i < 8; i++)
  {
    unsigned char b = bytes[i];
    if (is_little_endian() == 1)
    {
      b = bytes[8 - i - 1];
    }
    bio_writerp(bio_handle, b);
  }
}

void binaryio_write_float(void (*bio_writerp)(void*, unsigned char), void* bio_handle, float value)
{
  unsigned char bytes[4];
  memcpy(bytes, &value, 4);
  for (int i = 0; i < 4; i++)
  {
    unsigned char b = bytes[i];
    if (is_little_endian() == 1)
    {
      b = bytes[4 - i - 1];
    }
    bio_writerp(bio_handle, b);
  }
}
