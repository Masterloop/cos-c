/**
 * @file  cos.h
 * @date  2018-12-17
 * @brief Compact Observation Scheme common elements C header file.
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

#ifndef COS_H

// COS Header Flags
#define COS_HEADER_DEFAULT                0x0   // Default flags.
#define COS_HEADER_MULTI_OBSERVATIONS     0x20  // Use multiple observation ids in section.
#define COS_HEADER_MULTI_TIMESTAMPS       0x40  // Use multiple timestamps in section.
#define COS_HEADER_64BIT_TIMESTAMPS       0x80  // Use int64 timestamps ("ticks"), if not set, assume uint32 timestamps ("unix time").

// COS Observation Types
#define COS_OBS_TYPE_UNDEFINED    0
#define COS_OBS_TYPE_BOOLEAN      1
#define COS_OBS_TYPE_DOUBLE       2
#define COS_OBS_TYPE_FLOAT        3
#define COS_OBS_TYPE_INT32        4
#define COS_OBS_TYPE_INT16        5
#define COS_OBS_TYPE_UINT16       6
#define COS_OBS_TYPE_INT8         7
#define COS_OBS_TYPE_UINT8        8
#define COS_OBS_TYPE_POSITION_2D  9
#define COS_OBS_TYPE_POSITION_3D  10
#define COS_OBS_TYPE_ASCII        11
#define COS_OBS_TYPE_UTF8         12

#define COS_H
#endif
