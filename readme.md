# Compact Observation Scheme (COS) Specification

An open, cross platform, cross endian-ness data format for efficient writing and transfer of IoT observation data, with minimal dependencies and no need for dynamic memory usage.

Note: Observations must have timestamps sorted chronologically (ascending).

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
0x8   <Reserved>
0x10  <Reserved>
0x20  Use multiple observation descriptors in section.
0x40  Use multiple timestamps in section.
0x80  Use int64 timestamps ("ticks"), if not set, assume uint32 timestamps ("unix time").

### COS Section
observation_descr   Observation Descriptor  // Present only if flag 0x20 is not set.
timestamp_abs       uint32 | int64          // Data type depends on header flag 0x80.
observations_count  uint16                  // Number of observations in section.
observations        COS Observation         // Repeated observations_count times

### COS Observation
observation_descr  Observation Descriptor  // Present only if header flag 0x20 is set.
timestamp_rel      uint16 | int64          // Present only if header flag 0x40 is set, data type depends on header flag 0x80.
value              ObservationType         // Data type depends on "observation_descr" element "observations_type".

#### Observation Descriptor

Serialized as a 16 bit unsigned short.

Bits 15-12: observation_type  // Numeric value according to "Observation Type" table below.
Bits 11-0:  observation_id    // Observation identifier (max id: 4095).

#### Observation Type
1   boolean
2   double
3   float
4   int32
5   int16
6   uint16
7   int8
8   uint8
9   position 2d
10  position 3d
11  ascii string


## Examples of use

### Observations of one data type with one timestamp

### Observations of one data type with multiple timestamps

### Observations of multiple data types with one timestamp

### Observations of multiple data types with multiple timestamps
