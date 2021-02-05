#pragma once

#include "Types.hpp"

typedef struct {
  unsigned16 lowOffset;
  unsigned16 kernelSegment = 0x08;
  unsigned8 zero = 0x00;
  unsigned8 flags = 0x8E;
  unsigned16 highOffset;
} __attribute__((packed)) InterruptDescriptor;

class IDT {
  static struct {
    unsigned16 limit;
    unsigned32 base;
  } __attribute__((packed)) idt;

  static const unsigned32 entries = 256;

  static InterruptDescriptor _descriptorTable[entries];
public:
  static void registerHandler(int n, unsigned32 handlerAddress);
  static void load();
};
