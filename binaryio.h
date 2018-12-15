// binaryio.h - Endian-consistent binary writer C header file
// Revision: 2018-12-15
// Copyright (C) 2018 Masterloop AS.

#ifndef BINARYIO_H

void binaryio_write_blob(const unsigned char* value, unsigned int size);
void binaryio_write_int8(unsigned char value);
void binaryio_writeuint16(unsigned short value);

void binaryio_write_uint32(unsigned int value);
void binaryio_write_int32(int value);
void binaryio_write_float(float value);

#define BINARYIO_H
#endif
