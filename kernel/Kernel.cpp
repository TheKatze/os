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

    _vgaText.newLine();

    _vgaText.print("uwu");
}

void Kernel::run() {
    while (true) {
        __asm__("hlt");
    }
}
