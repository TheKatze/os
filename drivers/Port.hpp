#pragma once

class Port {
    unsigned short _portAddress;
public:
    Port(unsigned short portAddress);

    unsigned char readByte();
    void writeByte(unsigned char data);

    unsigned short readWord();
    void writeWord(unsigned short data);
};

