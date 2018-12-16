// binaryio.h - Endian-consistent binary writer C header file
// Revision: 2018-12-16
// Copyright (C) 2018 Masterloop AS.

#include <stdlib.h>

#ifndef BINARYIO_H

void binaryio_write_straight(void (*bio_writerp)(void*, unsigned char), void* bio_handle, const void* value, const unsigned int size);
void binaryio_write_endianness(void (*bio_writerp)(void*, unsigned char), void* bio_handle, const void* value, const unsigned int size);

void binaryio_write_int8(void (*bio_writerp)(void*, unsigned char), void* bio_handle, char value);
void binaryio_write_uint8(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned char value);
void binaryio_write_int16(void (*bio_writerp)(void*, unsigned char), void* bio_handle, short value);
void binaryio_write_uint16(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned short value);

void binaryio_write_uint32(void (*bio_writerp)(void*, unsigned char), void* bio_handle, unsigned int value);
void binaryio_write_int32(void (*bio_writerp)(void*, unsigned char), void* bio_handle, int value);
void binaryio_write_int64(void (*bio_writerp)(void*, unsigned char), void* bio_handle, int64_t value);
void binaryio_write_float(void (*bio_writerp)(void*, unsigned char), void* bio_handle, float value);

#define BINARYIO_H
#endif
