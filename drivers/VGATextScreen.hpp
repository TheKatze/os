#pragma once

#include "../util/Point.hpp"

#include "Port.hpp"

class VGATextScreen {
public:
    VGATextScreen();
    ~VGATextScreen() = default;

    enum Colour : unsigned char {
        Black = 0x0, Blue = 0x1, Green = 0x2, Cyan = 0x3, Red = 0x4, Magenta = 0x5, Yellow = 0x6, LightGray = 0x7,
        DarkGray = 0x8, LightBlue = 0x9, LightGreen = 0xa, LightCyan = 0xb, LightRed = 0xc, LightMagenta = 0xd, LightYellow = 0xe, White = 0xf
    };

    void clearScreen();
    void print(char* message, UPoint location, Colour foreground, Colour background);
    void print(char* message, UPoint location, Colour foreground);
    void print(char* message, UPoint location);
    void print(char* message, Colour foreground, Colour background);
    void print(char* message, Colour foreground);
    void print(char* message);

    void setCursorLocation(UPoint location);
    UPoint getCursorLocation() const;
    UPoint readCursorLocation();

    void setColourScheme(Colour foreground, Colour background);
private:
    const void* VIDEO_ADDRESS = (void*) 0xb8000;
    unsigned short maxRows = 25;
    unsigned short maxCols = 80;

    Port _ctrl;
    Port _data;

    Colour _foreground;
    Colour _background;

    UPoint _cursorLocation;

    void print(char* message, UPoint location, char colour);

    unsigned int getMemoryOffset() const;

    static inline char colourToChar(Colour foreground, Colour background) {
        return (char)(background << 4 | foreground);
    }
};

