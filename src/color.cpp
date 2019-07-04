#include "color.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

Color::Color()
{
    SetRGB(0,0,0);
}

Color::Color(int r, int g, int b)
{
    SetRGB(r, g, b);
}

void Color::SetRGB(int r, int g, int b, int a)
{
    red = r;
    green = g;
    blue = b;
    alpha = a;
    RgbToHsl(red, green, blue, &hue, &saturation, &lightness);
}

void Color::SetHSL(int h, int s, int l)
{
    hue = h;
    saturation = s;
    lightness = l;
    HslToRgb(hue, GetSaturationAsDouble(), GetLightnessAsDouble(), &red, &green, &blue);
}

string Color::IntToHex(int i)
{
    std::stringstream sstream;
    sstream << std::setfill('0') << std::setw(2) << std::hex << i;
    return sstream.str();
}

string Color::GetHexString()
{
    std::stringstream sstream;
    sstream << "#" << GetRedHex() << GetGreenHex() << GetBlueHex() << GetAlphaHex();
    return sstream.str();
}

Color Color::GetContrastColor()
{
    auto luminance = 1 - ( 0.299 * GetRed() + 0.587 * GetGreen() + 0.114 * GetBlue()) / 255;

    auto d = (luminance > 0.5) ? 255 : 0;

    return Color(d,d,d);
}

void Color::RgbToHsl(int red, int green, int blue, int* hue, int* saturation, int* lightness)
{
    double r = (double)red/255;
    double g = (double)green/255;
    double b = (double)blue/255;

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

    *hue = h*360;
    *saturation = round(s*100);
    *lightness = round(l*100);
}

// HSL(138, 0.50f, 0.76f);
// saturation and lightness [0,1]
void Color::HslToRgb(int hue, int saturation, int lightness, int* red, int* green, int* blue)
{
    if (saturation == 0)
    {
        *red = *green = *blue = lightness; // achromatic
    }
    else
    {
        float v1, v2;
        float h = (float)hue / 360;

        v2 = (lightness < 0.5) ? (lightness * (1 + saturation)) : ((lightness + saturation) - (lightness * saturation));
        v1 = 2 * lightness - v2;

        *red = (unsigned char)(255 * HueToRGB(v1, v2, h + (1.0f / 3)));
        *green = (unsigned char)(255 * HueToRGB(v1, v2, h));
        *blue = (unsigned char)(255 * HueToRGB(v1, v2, h - (1.0f / 3)));
    }
}

float Color::HueToRGB(float v1, float v2, float vH)
{
    if (vH < 0)
        vH += 1;

    if (vH > 1)
        vH -= 1;

    if ((6 * vH) < 1)
        return (v1 + (v2 - v1) * 6 * vH);

    if ((2 * vH) < 1)
        return v2;

    if ((3 * vH) < 2)
        return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

    return v1;
}

map<string, string> Color::GetVariables()
{
    map<string, string> variables;
    variables.insert(make_pair("$r$", to_string(red)));
    variables.insert(make_pair("$g$", to_string(green)));
    variables.insert(make_pair("$b$", to_string(blue)));
    variables.insert(make_pair("$a$", to_string(alpha)));
    variables.insert(make_pair("$r_d$", DoubleToString(GetRedAsDouble(),6)));
    variables.insert(make_pair("$g_d$", DoubleToString(GetGreenAsDouble(),6)));
    variables.insert(make_pair("$b_d$", DoubleToString(GetBlueAsDouble(),6)));
    variables.insert(make_pair("$a_d$", DoubleToString(GetAlphaAsDouble(),6)));
    variables.insert(make_pair("$r_d1$", DoubleToString(GetRedAsDouble(),1)));
    variables.insert(make_pair("$g_d1$", DoubleToString(GetGreenAsDouble(),1)));
    variables.insert(make_pair("$b_d1$", DoubleToString(GetBlueAsDouble(),1)));
    variables.insert(make_pair("$a_d1$", DoubleToString(GetAlphaAsDouble(),1)));
    variables.insert(make_pair("$r_d2$", DoubleToString(GetRedAsDouble(),2)));
    variables.insert(make_pair("$g_d2$", DoubleToString(GetGreenAsDouble(),2)));
    variables.insert(make_pair("$b_d2$", DoubleToString(GetBlueAsDouble(),2)));
    variables.insert(make_pair("$a_d2$", DoubleToString(GetAlphaAsDouble(),2)));
    variables.insert(make_pair("$r_d3$", DoubleToString(GetRedAsDouble(),3)));
    variables.insert(make_pair("$g_d3$", DoubleToString(GetGreenAsDouble(),3)));
    variables.insert(make_pair("$b_d3$", DoubleToString(GetBlueAsDouble(),3)));
    variables.insert(make_pair("$a_d3$", DoubleToString(GetAlphaAsDouble(),3)));
    variables.insert(make_pair("$r_d4$", DoubleToString(GetRedAsDouble(),4)));
    variables.insert(make_pair("$g_d4$", DoubleToString(GetGreenAsDouble(),4)));
    variables.insert(make_pair("$b_d4$", DoubleToString(GetBlueAsDouble(),4)));
    variables.insert(make_pair("$a_d4$", DoubleToString(GetAlphaAsDouble(),4)));
    variables.insert(make_pair("$r_d5$", DoubleToString(GetRedAsDouble(),5)));
    variables.insert(make_pair("$g_d5$", DoubleToString(GetGreenAsDouble(),5)));
    variables.insert(make_pair("$b_d5$", DoubleToString(GetBlueAsDouble(),5)));
    variables.insert(make_pair("$a_d5$", DoubleToString(GetAlphaAsDouble(),5)));
    variables.insert(make_pair("$r_d6$", DoubleToString(GetRedAsDouble(),6)));
    variables.insert(make_pair("$g_d6$", DoubleToString(GetGreenAsDouble(),6)));
    variables.insert(make_pair("$b_d6$", DoubleToString(GetBlueAsDouble(),6)));
    variables.insert(make_pair("$a_d6$", DoubleToString(GetAlphaAsDouble(),6)));
    variables.insert(make_pair("$r_hex$", GetRedHex()));
    variables.insert(make_pair("$g_hex$", GetGreenHex()));
    variables.insert(make_pair("$b_hex$", GetBlueHex()));
    variables.insert(make_pair("$a_hex$", GetAlphaHex()));
    variables.insert(make_pair("$h$", to_string(hue)));
    variables.insert(make_pair("$s$", to_string(saturation)));
    variables.insert(make_pair("$l$", to_string(lightness)));
    variables.insert(make_pair("$s_d$", to_string(GetSaturationAsDouble())));
    variables.insert(make_pair("$l_d$", to_string(GetLightnessAsDouble())));

    return variables;
}
