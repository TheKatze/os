#include "Types.hpp"

struct InterruptFrame {
  unsigned32 instructionPointer;
  unsigned32 cs;
  unsigned32 flags;
  unsigned32 stackPointer;
  unsigned32 stackStart;
};

__attribute__((interrupt))
void interrupt_handler(InterruptFrame* frame) {

}
