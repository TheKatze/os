#pragma once

extern "C" int main(void);

#include "../drivers/VGATextScreen.hpp"
#include "cpu/Interrupts.hpp"

class Kernel {
    VGATextScreen _vgaText;
public:
    Kernel();

    void run();
};

