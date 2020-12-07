#pragma once

class Port {
    unsigned short _portAddress;
public:
    Port(unsigned short portAddress);

    unsigned char readByte() const;
    void writeByte(unsigned char data) const;

    unsigned short readWord() const;
    void writeWord(unsigned short data) const;
};

