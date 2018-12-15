# Compact Observation Scheme (COS) Specification

An open, cross platform, cross endian-ness data format for efficient writing and transfer of IoT observation data, with minimal dependencies and no need for dynamic memory usage.


## Data Types

uint8   - unsigned char
uint16  - unsigned short16
unint32 - unsigned int32
int32   - signed int32
uint64  - unsigned int64
int64   - signed int64


## Structures

### COS Header

version         uint8        // Always 1 for this version.
header_flags    uint8        // Encoded according to "Header Flags" table below.
sections_count  uint16       // Number of sections included in dataset.
sections        COS Section  // Observation data sections multiplied by "section_count".

#### Header Flags
0x1   <Reserved>
0x2   <Reserved>
0x4   <Reserved>
0x8   Use multiple observation ids in section.
0x10  Use 16-bit observation ids (if not set, use 8-bit observation ids).
0x20  Use multiple timestamps in section.
0x40  Use observation timestamps relative to section timestamp.
0x80  Use int64 timestamps ("ticks"), if not set, assume uint32 timestamps ("unix time").

### COS Section
section_descriptor  uint16           // Value encoded acording to "Section Descriptor" table below.
timestamp           uint32 | int64   // Present only if header flag 0x20 is not set, data type depends on header flag 0x80.
observation_id      uint8 | uint16   // Present only if header flag 0x8 is not set, data type depends on header flag 0x10.
observations        COS Observation  // Repeated observations_count times

#### Section Descriptor
Bits 15-12: observations_type   // Numeric value according to "Observation Type" table below.
Bits 11-0:  observations_count  // Number of observations in observation section (max 4096 observations per section).

#### Observation Type
1   boolean
2   double
3   float
4   int32
5   int16
6   uint16
7   int8
8   uint8
9   position
10  ascii string
11  utf8 string

### COS Observation
timestamp_rel   uint16            // Present only if header flag 0x20 is set and 0x40 is set.
timestamp_abs   uint32 | int64    // Present only if header flag 0x20 is set and 0x40 is not set, data type depends on header flag 0x80.
observation_id  uint8 | uint16    // Present only if header flag 0x8 is set, data type depends on header flag 0x10.
value           ObservationType   // Data type depends on "section_descriptor" element "observations_type".


## Examples of use

### Observations of one data type with one timestamp

### Observations of one data type with multiple timestamps

### Observations of multiple data types with one timestamp

### Observations of multiple data types with multiple timestamps
