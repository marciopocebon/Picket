#include "color.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

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
    CalculateHSL();
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

void Color::CalculateHSL()
{
    double r = GetRedAsDouble();
    double g = GetGreenAsDouble();
    double b = GetBlueAsDouble();

    double colors[] = { r,g,b };

    auto max = *std::max_element(colors, colors + 3);
    auto min = *std::min_element(colors, colors + 3);
    auto h = (max + min) / 2;
    auto s = (max + min) / 2;
    auto l = (max + min) / 2;

    if (max == min)
    {
        h = s = 0; // achromatic
    }
    else
    {
        auto d = max - min;
        s = l > 0.5 ? d / (2 - max - min) : d / (max + min);

        if(max == r)
            h = (g - b) / d + (g < b ? 6 : 0);
        else if(max == g)
            h = (b - r) / d + 2;
        else if(max == b)
            h = (r - g) / d + 4;
    }

    h /= 6;

    hue = h;
    saturation = s;
    lightness = l;
}

map<string, string> Color::GetVariables()
{
    map<string, string> variables;
    variables.insert(make_pair("$r$", to_string(red)));
    variables.insert(make_pair("$g$", to_string(green)));
    variables.insert(make_pair("$b$", to_string(blue)));
    variables.insert(make_pair("$r_d$", to_string(GetRedAsDouble())));
    variables.insert(make_pair("$g_d$", to_string(GetGreenAsDouble())));
    variables.insert(make_pair("$b_d$", to_string(GetBlueAsDouble())));
    variables.insert(make_pair("$r#$", GetRedHex()));
    variables.insert(make_pair("$g#$", GetGreenHex()));
    variables.insert(make_pair("$b#$", GetBlueHex()));
    variables.insert(make_pair("$h$", to_string(hue)));
    variables.insert(make_pair("$s$", to_string(saturation)));
    variables.insert(make_pair("$l$", to_string(lightness)));

    return variables;
}
