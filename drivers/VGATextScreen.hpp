#pragma once

#include "../util/Point.hpp"

#include "Port.hpp"

class VGATextScreen {
public:
    VGATextScreen();
    ~VGATextScreen() = default;

    enum Colour : unsigned char {
        Black = 0x0, Blue = 0x1, Green = 0x2, Aqua = 0x3, Red = 0x4, Purple = 0x5, Yellow = 0x6, LightGray = 0x7,
        DarkGray = 0x8, LightBlue = 0x9, LightGreen = 0xa, LightAqua = 0xb, LightRed = 0xc, LightPurple = 0xd, LightYellow = 0xe, White = 0xf
    };

    void clearScreen();
    void print(char* message, UPoint location, Colour foreground, Colour background);
    void print(char* message, UPoint location, Colour foreground);
    void print(char* message, UPoint location);
    void print(char* message);

    UPoint getCursorLocation();
    void setCursorLocation(UPoint location);

    void setColourScheme(Colour foreground, Colour background);
private:
    unsigned int VIDEO_ADDRESS = 0xb8000;
    unsigned short MAX_ROWS = 25;
    unsigned short MAX_COLS = 80;

    Port _ctrl;
    Port _data;

    Colour _foreground;
    Colour _background;

    UPoint _cursorLocation;

    void print(char* message, UPoint location, unsigned char colour);
};

