#include "Port.hpp"

Port::Port(unsigned short portAddress) {
    _portAddress = portAddress;
}

unsigned char Port::readByte() const {
    unsigned char result;

    __asm__("in %%dx, %%al" : "=a" (result) : "d" (_portAddress));

    return result;
}

void Port::writeByte(unsigned char data) const {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (_portAddress));
}

unsigned short Port::readWord() const {
    unsigned char result;

    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (_portAddress));

    return result;
}

void Port::writeWord(unsigned short data) const {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (_portAddress));
}

