// coswrite.c - Compact Observation Scheme serializer C implementation file
// Revision: 2018-12-15
// Copyright (C) 2018 Masterloop AS.

#include <memory.h>
#include "cos.h"
#include "coswrite.h"
#include "binaryio.h"

void bio_write(struct coswrite_handle* cwh, unsigned char b)
{
  cwh->buffer[cwh->buffer_used++] = b;  // Append byte and increase buffer used counter.
}

unsigned short get_section_descriptor(unsigned char observation_type, unsigned short observation_count)
{
  return observation_type << 12 | (observation_count & 0xFFF);
}

void cos_init(struct coswrite_handle* cwh, unsigned char header_flags, void* buffer, unsigned int buffer_size)
{
  cwh->header_flags = header_flags;
  cwh->buffer = buffer;
  cwh->buffer_size = buffer_size;
  cwh->buffer_used = 0;
  cwh->section_count = 0;

  cwh->section_start = 0;
  cwh->section_observation_type = 0;
  cwh->section_observation_count = 0;
  cwh->section_observation_id = NULL;
  cwh->section_timestamp = NULL;

  //TODO: Serialize dataset header to buffer using header flag rules.
}

void cos_begin_section(struct coswrite_handle* cwh, unsigned char observation_type, void* observation_id, void* timestamp)
{
  cwh->section_count++;
  cwh->section_start = cwh->buffer_used;
  cwh->section_observation_type = observation_type;
  cwh->section_observation_count = 0;
  cwh->section_observation_id = observation_id;
  cwh->section_timestamp = timestamp;

  //TODO: Serialize section header to buffer using header and section flag rules.
}

void cos_add_observation(struct coswrite_handle* cwh, void* observation_id, void* timestamp, void* value)
{
  cwh->section_observation_count++;

  //TODO: Serialize observation to buffer using header and section flag rules.
}

void cos_end_section(struct coswrite_handle* cwh)
{
  //TODO: Re-serialize number of observation in section header.
  //TODO: Re-serialize number of sections in dataset header.

  cwh->section_start = 0;
  cwh->section_observation_type = 0;
  cwh->section_observation_count = 0;
  cwh->section_observation_id = NULL;
  cwh->section_timestamp = NULL;
}
