#include "VGATextScreen.hpp"


VGATextScreen::VGATextScreen() 
    : _ctrl(0x3d4)
    , _data(0x3d5)
    , _foreground(Colour::White)
    , _background(Colour::Black)
    , _cursorLocation({0, 0}) {}

void VGATextScreen::clearScreen() {}

void VGATextScreen::print(char* message, UPoint location, Colour foreground, Colour background) {
    unsigned char colour = background << 1 | foreground;
    print(message, location, colour);
}

void VGATextScreen::print(char *message, UPoint location, VGATextScreen::Colour foreground) {
    print(message, location, foreground, _background);
}

void VGATextScreen::print(char* message, UPoint location) {
    print(message, location, _foreground);
}

void VGATextScreen::print(char* message) {
    print(message, _cursorLocation);
}

void VGATextScreen::print(char *message, UPoint location, unsigned char colour) {

}

UPoint VGATextScreen::getCursorLocation() {
    return _cursorLocation;
}

void VGATextScreen::setColourScheme(VGATextScreen::Colour foreground, VGATextScreen::Colour background) {
    _foreground = foreground;
    _background = background;
}

void VGATextScreen::setCursorLocation(UPoint location) {
    _cursorLocation = location;
}
