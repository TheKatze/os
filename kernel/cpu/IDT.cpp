#include "IDT.hpp"

void IDT::registerHandler(int n, unsigned32 handlerAddress) {
  _descriptorTable[n].lowOffset = low16(handlerAddress);
  _descriptorTable[n].highOffset = high16(handlerAddress);
}

void IDT::load() {
  idt.base = (unsigned32) &_descriptorTable;
  idt.limit = IDT::entries * sizeof(InterruptDescriptor) - 1;

  __asm__ __volatile__("lidtl (%0)" : : "r" (&idt));
}
