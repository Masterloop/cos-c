/**
 * @file  coswrite.c
 * @date  2018-12-17
 * @brief Compact Observation Scheme serializer C implementation file.
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
#include "cos.h"
#include "coswrite.h"
#include "binaryio.h"

void bio_writer(void* bio_handle, unsigned char b)
{
  struct coswrite_handle* cwh = (struct coswrite_handle*) bio_handle;

  cwh->buffer[cwh->buffer_pos] = b;         // Append byte at buffer_pos position (allow re-writing of sections).

  if (cwh->buffer_pos == cwh->buffer_used)  // If at the end, increase buffer_used with 1.
  {
    cwh->buffer_used++;
  }

  cwh->buffer_pos++;  // Advance writing position by one byte.
}

unsigned short get_observation_descriptor(unsigned char observation_type, unsigned short observation_id)
{
  return observation_type << 12 | (observation_id & 0xFFF);
}

void cos_write_header(struct coswrite_handle* cwh)
{
  unsigned char version = 1;
  binaryio_write_uint8(bio_writer, cwh, version);
  binaryio_write_uint8(bio_writer, cwh, cwh->header_flags);
  binaryio_write_uint16(bio_writer, cwh, cwh->section_count);
}

void cos_init(struct coswrite_handle* cwh, unsigned char header_flags, uint8_t* buffer, size_t buffer_size)
{
  memset(buffer, 0, buffer_size);

  cwh->header_flags = header_flags;
  cwh->buffer = buffer;
  cwh->buffer_size = buffer_size;
  cwh->buffer_pos = 0;
  cwh->buffer_used = 0;
  cwh->section_count = 0;

  cwh->section_start = 0;
  cwh->section_observation_type = 0;
  cwh->section_observation_count = 0;
  cwh->section_observation_id = NULL;
  cwh->section_timestamp = NULL;

  cos_write_header(cwh);
}

void cos_write_current_section_header(struct coswrite_handle* cwh)
{
  if ((cwh->header_flags & COS_HEADER_MULTI_OBSERVATIONS) == 0)
  {
    unsigned short obs_descr = get_observation_descriptor(cwh->section_observation_type, *(unsigned short*) cwh->section_observation_id);
    binaryio_write_uint16(bio_writer, cwh, obs_descr);
  }

  if (cwh->header_flags & COS_HEADER_64BIT_TIMESTAMPS)
  {
    binaryio_write_int64(bio_writer, cwh, *(int64_t*)cwh->section_timestamp);
  }
  else
  {
    binaryio_write_uint32(bio_writer, cwh, *(unsigned int*)cwh->section_timestamp);
  }

  binaryio_write_uint16(bio_writer, cwh, cwh->section_observation_count);
}

void cos_begin_section(struct coswrite_handle* cwh, void* observation_type, void* observation_id, void* timestamp)
{
  cwh->section_count++;
  cwh->section_start = cwh->buffer_pos;
  if ((cwh->header_flags & COS_HEADER_MULTI_OBSERVATIONS) == 0)
  {
    cwh->section_observation_type = *(unsigned char*)observation_type;
  }
  else
  {
    cwh->section_observation_type = COS_OBS_TYPE_UNDEFINED;
  }
  cwh->section_observation_count = 0;
  cwh->section_observation_id = observation_id;
  cwh->section_timestamp = timestamp;

  cos_write_current_section_header(cwh);
}

void cos_write_observation_value(struct coswrite_handle* cwh, unsigned observation_type, void* value)
{
  unsigned short l;
  switch (observation_type)
  {
    case COS_OBS_TYPE_BOOLEAN:
      binaryio_write_uint8(bio_writer, cwh, *(unsigned char*)value);
      break;
    case COS_OBS_TYPE_DOUBLE:
      binaryio_write_double(bio_writer, cwh, *(double*)value);
      break;
    case COS_OBS_TYPE_FLOAT:
      binaryio_write_float(bio_writer, cwh, *(float*)value);
      break;
    case COS_OBS_TYPE_INT32:
      binaryio_write_int32(bio_writer, cwh, *(int*)value);
      break;
    case COS_OBS_TYPE_INT16:
      binaryio_write_int16(bio_writer, cwh, *(short*)value);
      break;
    case COS_OBS_TYPE_UINT16:
      binaryio_write_uint16(bio_writer, cwh, *(unsigned short*)value);
      break;
    case COS_OBS_TYPE_INT8:
      binaryio_write_int8(bio_writer, cwh, *(char*)value);
      break;
    case COS_OBS_TYPE_UINT8:
      binaryio_write_uint8(bio_writer, cwh, *(unsigned char*)value);
      break;
    case COS_OBS_TYPE_POSITION_2D:
      binaryio_write_float(bio_writer, cwh, *(&((float*)value)[0]));
      binaryio_write_float(bio_writer, cwh, *(&((float*)value)[1]));
      break;
    case COS_OBS_TYPE_POSITION_3D:
      binaryio_write_float(bio_writer, cwh, *(&((float*)value)[0]));
      binaryio_write_float(bio_writer, cwh, *(&((float*)value)[1]));
      binaryio_write_float(bio_writer, cwh, *(&((float*)value)[2]));
      break;
    case COS_OBS_TYPE_ASCII:
      l = (unsigned short)strlen((char*)value);
      binaryio_write_uint16(bio_writer, cwh, l);
      binaryio_write_bytes(bio_writer, cwh, (unsigned char*)value, l);
      break;
    case COS_OBS_TYPE_UTF8:
      l = (unsigned short)strlen((char*)value);
      binaryio_write_uint16(bio_writer, cwh, l);
      binaryio_write_bytes(bio_writer, cwh, (unsigned char*)value, l);
      break;
  }
}

void cos_write_observation(struct coswrite_handle* cwh, unsigned char* observation_type, unsigned short* observation_id, void* timestamp, void* value)
{
  if (cwh->header_flags & COS_HEADER_MULTI_OBSERVATIONS)
  {
    unsigned short obs_descr = get_observation_descriptor(*observation_type, *observation_id);
    binaryio_write_uint16(bio_writer, cwh, obs_descr);
  }

  if (cwh->header_flags & COS_HEADER_MULTI_TIMESTAMPS)
  {
    if (cwh->header_flags & COS_HEADER_64BIT_TIMESTAMPS)
    {
      int64_t delta64 = *((int64_t*)timestamp) - *((int64_t*)cwh->section_timestamp);
      binaryio_write_int64(bio_writer, cwh, delta64);
    }
    else
    {
      unsigned int delta32 = *((unsigned int*)timestamp) - *((unsigned int*)cwh->section_timestamp);
      binaryio_write_uint16(bio_writer, cwh, (unsigned short)delta32);
    }
  }
  
  if (cwh->header_flags & COS_HEADER_MULTI_OBSERVATIONS)
  {
    cos_write_observation_value(cwh, *observation_type, value);
  }
  else
  {
    cos_write_observation_value(cwh, cwh->section_observation_type, value);
  }
}

void cos_add_observation(struct coswrite_handle* cwh, unsigned char* observation_type, unsigned short* observation_id, void* timestamp, void* value)
{
  cwh->section_observation_count++;

  cos_write_observation(cwh, observation_type, observation_id, timestamp, value);
}

void cos_end_section(struct coswrite_handle* cwh)
{
  // Update section header
  cwh->buffer_pos = cwh->section_start;
  cos_write_current_section_header(cwh);

  // Update dataset header
  cwh->buffer_pos = 0;
  cos_write_header(cwh);

  // Set current position to allow further writing.
  cwh->buffer_pos = cwh->buffer_used;

  // Reset section meta data.
  cwh->section_start = 0;
  cwh->section_observation_type = 0;
  cwh->section_observation_count = 0;
  cwh->section_observation_id = NULL;
  cwh->section_timestamp = NULL;
}
