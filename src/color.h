#pragma once

#include<iterator>
#include<map>
#include<string>
#include<math.h>
#include<iostream>
#include<sstream>
#include<iomanip>

using namespace std;

class Color
{
private:
    int red = 0;
    int green = 0;
    int blue = 0;
    int alpha = 0;
    int hue = 0;
    int saturation = 0;
    int lightness = 0;
    double RoundTo(double value, int n)
    {
        return floor(value*pow(10,n)+0.5)/pow(10,n);
    }
    string DoubleToString(double value, int precision)
    {
        std::stringstream sstream;
        sstream << fixed << setprecision(precision) << value;
        return sstream.str();
    }


protected:
    void RgbToHsl(int red, int green, int blue, int* hue, int* saturation, int* lightness);
    void HslToRgb(int hue, int saturation, int lightness, int* red, int* green, int* blue);
    float HueToRGB(float v1, float v2, float vH);

public:
    Color();
    Color(int r, int g, int b);
    void SetRGB(int r, int g, int b, int a = 255);
    void SetHSL(int h, int s, int l);

    int GetRed() {return red;}
    int GetGreen() {return green;}
    int GetBlue() {return blue;}
    int GetAlpha() {return alpha;}
    double GetRedAsDouble() {return (double)red/255;}
    double GetGreenAsDouble() {return (double)green/255;}
    double GetBlueAsDouble() {return (double)blue/255;}
    double GetAlphaAsDouble() {return (double)alpha/255;}
    string GetRedHex() {return IntToHex(red);}
    string GetGreenHex() {return IntToHex(green);}
    string GetBlueHex() {return IntToHex(blue);}
    string GetAlphaHex() {return IntToHex(alpha);}
    string GetHexString();
    double GetSaturationAsDouble() { return (double)saturation/100; }
    double GetLightnessAsDouble() { return (double)lightness/100; }

    string IntToHex(int i);
    Color GetContrastColor();
    map<string, string> GetVariables();
};
