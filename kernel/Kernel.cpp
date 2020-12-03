#include "Kernel.hpp"
#include "../drivers/Port.hpp"

extern "C"
int main(void) {
    Kernel().run();

    return 0;
}

Kernel::Kernel(void) {
    char* video_memory = (char*) 0xb8000;
    *video_memory = '-';
}

void Kernel::run(void) {
    while (true) {}
}

