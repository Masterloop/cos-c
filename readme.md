# Compact Observation Scheme (COS) Specification

An open, cross platform, cross endian-ness data format for efficient writing and transfer of IoT observation data, with minimal dependencies and no need for dynamic memory usage.

_Note: Observations must have timestamps sorted chronologically (ascending)._

## Data Types
- uint8   - unsigned char
- uint16  - unsigned short16
- unint32 - unsigned int32
- int32   - signed int32
- uint64  - unsigned int64
- int64   - signed int64


## Structures

### COS Header
```
version         uint8        // Always 1 for this version.
header_flags    uint8        // Encoded according to "Header Flags" table below.
sections_count  uint16       // Number of sections included in dataset.
sections        COS Section  // Observation data sections multiplied by "section_count".
```

#### Header Flags
```
0x1   <Reserved>
0x2   <Reserved>
0x4   <Reserved>
0x8   <Reserved>
0x10  <Reserved>
0x20  Use multiple observation descriptors in section.
0x40  Use multiple timestamps in section.
0x80  Use int64 timestamps ("ticks"), if not set, assume uint32 timestamps ("unix time").
```

### COS Section
```
observation_descr   Observation Descriptor  // Present only if flag 0x20 is not set.
timestamp_abs       uint32 | int64          // Data type depends on header flag 0x80.
observations_count  uint16                  // Number of observations in section.
observations        COS Observation         // Repeated observations_count times.
```
### COS Observation
```
observation_descr  Observation Descriptor  // Present only if header flag 0x20 is set.
timestamp_rel      uint16 | int64          // Present only if header flag 0x40 is set, data type depends on header flag 0x80.
value              ObservationType         // Data type depends on "observation_descr" element "observations_type".
```

#### Observation Descriptor
```
Serialized as a 16 bit unsigned short.

Bits 15-12: observation_type  // Numeric value according to "Observation Types" table below.
Bits 11-0:  observation_id    // Observation identifier (max id: 4095).
```

#### Observation Types
1.  boolean
2.  double
3.  float
4.  int32
5.  int16
6.  uint16
7.  int8
8.  uint8
9.  position2d
10. position3d
11. ascii
12. utf8

#### Provision of Observation Value

##### boolean
Provided as unsigned char, 0 = false, 1 = true.

##### double
Provided as native double type.

##### float
Provided as native float type.

##### int32
Provided as native signed int.

##### int16
Provided as native signed short.

##### uint16
Provided as native unsigned short.

##### int8
Provided as native signed char.

##### uint8
Provided as native unsigned char.

##### position2d
Structure consisting of the following elements:
- Latitude provided as native float (decimal degrees in WGS84 datum).
- Longitude provided as native float (decimal degrees in WGS84 datum).

##### position3d
Structure consisting of the following elements:
- Latitude provided as native float (decimal degrees in WGS84 datum).
- Longitude provided as native float (decimal degrees in WGS84 datum).
- Altitude provided as native float (meters in WGS84 datum).

##### ascii
Structure consisting of the following elements:
- Length of string provided as unsigned short.
- Char array provided as char[].

##### utf8
Structure consisting of the following elements:
- Length of string provided as unsigned short.
- Char array provided as unsigned char[] with UTF8 encoding.

## Examples of use

#### Observations of one data type with one timestamp
[Example provided in example.c](examples/examples.c).

#### Observations of one data type with multiple timestamps
[Example provided in example.c](examples/examples.c).

#### Observations of multiple data types with one timestamp
[Example provided in example.c](examples/examples.c).

#### Observations of multiple data types with multiple timestamps
[Example provided in example.c](examples/examples.c).

#### Observations of multiple data types with multiple timestamps and multiple data types
[Example provided in example.c](examples/examples.c).
