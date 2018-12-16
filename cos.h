// cos.h - Compact Observation Scheme common elements C header file
// Revision: 2018-12-16
// Copyright (C) 2018 Masterloop AS.

// COS Header Flags
#define COS_HEADER_DEFAULT                0x0   // Default flags.
#define COS_HEADER_MULTI_OBSERVATIONS     0x20  // Use multiple observation ids in section.
#define COS_HEADER_MULTI_TIMESTAMPS       0x40  // Use multiple timestamps in section.
#define COS_HEADER_64BIT_TIMESTAMPS       0x80  // Use int64 timestamps ("ticks"), if not set, assume uint32 timestamps ("unix time").

// COS Observation Types
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
