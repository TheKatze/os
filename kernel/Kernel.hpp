extern "C" int main(void);

#include "../drivers/VGATextScreen.hpp"

class Kernel {
    VGATextScreen _vgaText;
public:
    Kernel();

    void run();
};

