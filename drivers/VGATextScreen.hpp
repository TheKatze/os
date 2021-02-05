#pragma once

#include "../util/Point.hpp"

#include "Port.hpp"

class VGATextScreen {
public:
    VGATextScreen();
    ~VGATextScreen() = default;

    enum Color : unsigned char {
        Black = 0x0, Blue = 0x1, Green = 0x2, Cyan = 0x3, Red = 0x4, Magenta = 0x5, Yellow = 0x6, LightGray = 0x7,
        DarkGray = 0x8, LightBlue = 0x9, LightGreen = 0xa, LightCyan = 0xb, LightRed = 0xc, LightMagenta = 0xd, LightYellow = 0xe, White = 0xf
    };

    void clearScreen();
    void print(const char* message, Point<unsigned> location, Color foreground, Color background);
    void print(const char* message, Point<unsigned> location, Color foreground);
    void print(const char* message, Point<unsigned> location);
    void print(const char* message, Color foreground, Color background);
    void print(const char* message, Color foreground);
    void print(const char* message);

    void newLine();

    void setCursorLocation(Point<unsigned> location);
    Point<unsigned> getCursorLocation() const;
    Point<unsigned> readCursorLocation();

    void setColourScheme(Color foreground, Color background);
private:
    const void* VIDEO_ADDRESS = (void*) 0xb8000;
    const unsigned int MAX_ROWS = 25;
    const unsigned int MAX_COLS = 80;

    Port _ctrl;
    Port _data;

    Color _foreground;
    Color _background;

    Point<unsigned> _cursorLocation;

    void print(const char* message, Point<unsigned> location, char colour);

    unsigned int getMemoryOffset() const;
    unsigned int getMemoryOffset(Point<unsigned> location) const;

    static inline char colourToChar(Color foreground, Color background) {
        return (char)(background << 4 | foreground);
    }
};

