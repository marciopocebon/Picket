#include "color.h"
#include <iostream>
#include <sstream>
#include <iomanip> 

Color::Color()
{
    set(0,0,0);
}

Color::Color(int r, int g, int b)
{
    set(r, g, b);
}

void Color::set(int r, int g, int b)
{
    red = r;
    green = g;
    blue = b;
}

std::string Color::IntToHex(int i)
{
    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(2) << std::hex << i;
    return sstream.str();
}

int Color::GetRed() {return red;}

int Color::GetGreen() {return green;}

int Color::GetBlue() {return blue;}

double Color::GetRedAsDouble() {return (double)red/256;}

double Color::GetGreenAsDouble() {return (double)green/256;}

double Color::GetBlueAsDouble() {return (double)blue/256;}

std::string Color::GetRedHex() {return IntToHex(red);}

std::string Color::GetGreenHex() {return IntToHex(green);}

std::string Color::GetBlueHex() {return IntToHex(blue);}

std::string Color::GetHexString()
{
    std::stringstream sstream;
    sstream << "#" << GetRedHex() << GetGreenHex() << GetBlueHex();
    return sstream.str();
}

Color Color::GetContrastColor()
{
    auto luminance = 1 - ( 0.299 * this->GetRed() + 0.587 * this->GetGreen() + 0.114 * this->GetBlue()) / 255;

    auto d = (luminance > 0.5) ? 255 : 0;

    return Color(d,d,d);
}