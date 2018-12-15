// binaryio.c - Endian-consistent binary writer C implementation file
// Revision: 2018-12-15
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

//TODO: Add function pointer as argument for bio_write for all these functions.

void binaryio_write_blob(const unsigned char* value, const unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    bio_write(value[i]);
  }
}

void binaryio_write_int8(unsigned char value)
{
	bio_write(value);
}

void binaryio_writeuint16(unsigned short value)
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
    
    bio_write(b);
  }
}

void binaryio_write_uint32(unsigned int value)
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
    bio_write(b);
  }
}

void binaryio_write_int32(int value)
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
    bio_write(b);
  }
}

void binaryio_write_float(float value)
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
    bio_write(b);
  }
}
