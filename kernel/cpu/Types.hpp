#pragma once

typedef unsigned int unsigned32;
typedef int signed32;

typedef unsigned short unsigned16;
typedef short signed16;

typedef unsigned char unsigned8;
typedef char signed8;

inline unsigned16 low16(unsigned32 address) {
  return (address) & 0xFFFF;
}

inline unsigned16 high16(unsigned32 address) {
  return ((address) >> 16) & 0xFFFF;
}
