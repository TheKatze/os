#include "VGATextScreen.hpp"


VGATextScreen::VGATextScreen() 
    : _ctrl(0x3d4)
    , _data(0x3d5)
    , _foreground(Color::White)
    , _background(Color::Black)
    , _cursorLocation(readCursorLocation()) {

}

void VGATextScreen::clearScreen() {
    unsigned int screenSize = MAX_COLS * MAX_ROWS;

    char* vgaScreen = (char*) VIDEO_ADDRESS;
    char colour = colourToChar(_foreground, _background);

    for (int i = 0; i < screenSize * 2; i += 2) {
        vgaScreen[i] = ' ';
        vgaScreen[i + 1] = colour;
    }

    setCursorLocation({0, MAX_ROWS - 1});
}

void VGATextScreen::print(const char* message, Point<unsigned> location, Color foreground, Color background) {
    print(message, location, colourToChar(foreground, background));
}

void VGATextScreen::print(const char* message, Point<unsigned> location, VGATextScreen::Color foreground) {
    print(message, location, foreground, _background);
}

void VGATextScreen::print(const char* message, Point<unsigned> location) {
    print(message, location, _foreground);
}

void VGATextScreen::print(const char* message, VGATextScreen::Color foreground, VGATextScreen::Color background) {
    print(message, _cursorLocation, colourToChar(foreground, background));
}

void VGATextScreen::print(const char* message, VGATextScreen::Color foreground) {
    print(message, foreground, _background);
}

void VGATextScreen::print(const char* message) {
    print(message, _cursorLocation);
}

void VGATextScreen::newLine() {
    char* vgaScreen = (char*) VIDEO_ADDRESS;

    // TODO: Use memcopy
    for (unsigned y = 1; y < MAX_ROWS; y++)
    {
        for (unsigned x = 0; x < MAX_COLS; x++)
        {
            vgaScreen[getMemoryOffset({x, y - 1})] = vgaScreen[getMemoryOffset({x, y})];
            vgaScreen[getMemoryOffset({x, y - 1}) + 1] = vgaScreen[getMemoryOffset({x, y}) + 1]; 

            vgaScreen[getMemoryOffset({x, y})] = ' ';
            vgaScreen[getMemoryOffset({x, y}) + 1] = colourToChar(_foreground, _background);           
        }
        
    }
    
    setCursorLocation({0, MAX_ROWS - 1});
}

void VGATextScreen::print(const char* message, Point<unsigned> location, char colour) {
    char* vgaScreen = (char*) VIDEO_ADDRESS;

    bool isCustomLocation = location != _cursorLocation;

    Point<unsigned> oldLocation = _cursorLocation;
    _cursorLocation = location;

    for (const char* c = message; *c != '\0'; c++) {
        char character = *c;

        switch (character) {
            case '\n':
            case '\r':
                newLine();
                break;
            default:
                unsigned int offset = getMemoryOffset();
                vgaScreen[offset] = character;
                vgaScreen[offset + 1] = colour;

                if (++_cursorLocation.x >= MAX_COLS) {
                    newLine();
                }
                setCursorLocation({_cursorLocation.x, _cursorLocation.y});

                break;
        }
    }

    if (isCustomLocation)
        setCursorLocation(oldLocation);
}

Point<unsigned> VGATextScreen::getCursorLocation() const {
    return _cursorLocation;
}

void VGATextScreen::setColourScheme(VGATextScreen::Color foreground, VGATextScreen::Color background) {
    _foreground = foreground;
    _background = background;
}

void VGATextScreen::setCursorLocation(Point<unsigned> location) {
    _cursorLocation = location;

    unsigned int offset = location.y * MAX_COLS + location.x;

    _ctrl.writeByte(14);
    _data.writeByte(offset >> 8);
    _ctrl.writeByte(15);
    _data.writeByte(offset & 0xff);
}

Point<unsigned> VGATextScreen::readCursorLocation() {
    _ctrl.writeByte(14);
    unsigned int offset = _data.readByte() << 8;
    _ctrl.writeByte(15);
    offset += _data.readByte();

    return Point<unsigned>(offset % MAX_COLS, offset / MAX_COLS);
}

unsigned int VGATextScreen::getMemoryOffset() const {
    return 2 * (_cursorLocation.y * MAX_COLS + _cursorLocation.x);
}

unsigned int VGATextScreen::getMemoryOffset(Point<unsigned> location) const {
    return 2 * (location.y * MAX_COLS + location.x);
}
