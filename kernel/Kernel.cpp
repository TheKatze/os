#include "Kernel.hpp"


extern "C"
int main(void) {
    Kernel().run();

    return 0;
}

Kernel::Kernel() : _vgaText() {
    _vgaText.clearScreen();

    _vgaText.print("Hello, World!\n");
    _vgaText.print("This is my OS");
}

void Kernel::run() {
    while (true) {}
}
