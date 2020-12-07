#include "Kernel.hpp"


extern "C"
int main(void) {
    Kernel().run();

    return 0;
}

Kernel::Kernel() : _vgaText() {
    _vgaText.clearScreen();
}

void Kernel::run() {
    while (true) {}
}

