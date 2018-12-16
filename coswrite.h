// coswrite.h - Compact Observation Scheme serializer C header file
// Revision: 2018-12-16
// Copyright (C) 2018 Masterloop AS.

#ifndef COSWRITE_H

#include <stdint.h>

struct coswrite_handle
{
  unsigned char   header_flags;   // Header flags.
  unsigned char*  buffer;         // Data buffer.
  unsigned int    buffer_size;    // Max size of data buffer.
  unsigned int    buffer_pos;     // Current writing position in buffer.
  unsigned int    buffer_used;    // Number of used bytes in data buffer.
  unsigned short  section_count;  // Number of sections in dataset.

  unsigned int    section_start;              // Start byte position in buffer for active section or 0 if no active section.
  unsigned char   section_observation_type;   // Observation type in current section.
  unsigned short  section_observation_count;  // Number of observations in current section.
  void*           section_observation_id;     // Observation identifier of current section (if not multi observation mode).
  void*           section_timestamp;          // Timestamp of current section (if not multi timestamp mode).
};

void cos_create(struct coswrite_handle* cwh, unsigned char header_flags, void* buffer, unsigned int buffer_size);
void cos_begin_section(struct coswrite_handle* cwh, unsigned char observation_type, void* observation_id, void* timestamp);
void cos_add_observation(struct coswrite_handle* cwh, unsigned char observation_type, unsigned short observation_id, void* timestamp, void* value);
void cos_end_section(struct coswrite_handle* cwh);

#define COSWRITE_H
#endif
