/**
 * @file  coswrite.h
 * @date  2018-12-17
 * @brief Compact Observation Scheme serializer C header file.
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

#include <stdint.h>

#ifndef COSWRITE_H

/**
 * @brief A structure to keep the state of a Compact Observation Scheme dataset during writing.
 */
struct coswrite_handle
{
  unsigned char   header_flags;   /**< Header flags. */
  unsigned char*  buffer;         /**< Data buffer. */
  unsigned int    buffer_size;    /**< Max size of data buffer. */
  unsigned int    buffer_pos;     /**< Current writing position in buffer. */
  unsigned int    buffer_used;    /**< Number of used bytes in data buffer. */
  unsigned short  section_count;  /**< Number of sections in dataset. */

  unsigned int    section_start;              /**< Start byte position in buffer for active section or 0 if no active section. */
  unsigned char   section_observation_type;   /**< Observation type in current section. */
  unsigned short  section_observation_count;  /**< Number of observations in current section. */
  void*           section_observation_id;     /**< Observation identifier of current section (if not multi observation mode). */
  void*           section_timestamp;          /**< Timestamp of current section (if not multi timestamp mode). */
};

/**
 * @brief Initialize a Compact Observation Scheme dataset.
 * 
 * This function initializes a new Compact Observation Scheme dataset using a memory buffer provided as argument.
 * The provided buffer must have enough capacity to store the entire dataset, and no re-allocations are done.
 * 
 * @param cwh             Pointer to a coswrite_handle object used throughout the dataset creation.
 * @param header_flags    Option flags OR-ed using flags specified within the "cos.h" definition file.
 * @param buffer          Pointer to an array of unsigned chars.
 * @param buffer_size     Size of buffer byte array.
 */
void cos_init(struct coswrite_handle* cwh, unsigned char header_flags, unsigned char* buffer, unsigned int buffer_size);

/**
 * @brief Begins a new Compact Observation Scheme section.
 * 
 * A section is a grouping of observations.
 * A section can consist of:
 *   - One and only one timestamp and one or more observation ids.
 *   - One and only one observation id and one or more timestamps.
 *   - One or more timestamps and one or more observation ids.
 * 
 * @param cwh               Pointer to a coswrite_handle object that has been initialized with "cos_init(..)".
 * @param observation_type  Pointer to observation type (or NULL if multi observation mode).
 * @param observation_id    Pointer to observation id (or NULL if multi observation mode).
 * @param timestamp         Pointer to timestamp, data type according to header_flags (or NULL if multi timestamp mode).
 */
void cos_begin_section(struct coswrite_handle* cwh, void* observation_type, void* observation_id, void* timestamp);

/**
 * @brief Adds a single observation to the current Compact Observation Scheme section.
 * 
 * @param cwh               Pointer to a coswrite_handle object, having an active section created by "cos_begin_section(..)".
 * @param observation_type  Pointer to observation type according to observation types defined in "cos.h" (or NULL if single observation mode).
 * @param observation_id    Pointer to observation identifier (or NULL if single observation mode).
 * @param timestamp         Pointer to timestamp, data type according to header_flags (or NULL if single timestamp mode).
 * @param value             Pointer to observation value, provided according to "readme.md" documentation.
 */
void cos_add_observation(struct coswrite_handle* cwh, unsigned char* observation_type, unsigned short* observation_id, void* timestamp, void* value);

/**
 * @brief Ends a Compact Observation Scheme section.
 * 
 * Updates dataset and section headers with counters.
 * IMPORTANT: It is essential to call this function before starting a new section or exporting the dataset.
 * @param cwh   Pointer to a coswrite_handle object, having an active section created by "cos_begin_section(..)".
 */
void cos_end_section(struct coswrite_handle* cwh);

#define COSWRITE_H
#endif
