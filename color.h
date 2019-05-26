#pragma once

#include<string>

class Color
{
    private:
    int red = 0;
    int green = 0;
    int blue = 0;
    int hue = 0;
    int saturation = 0;
    int luminence = 0;


    protected:

    public:
    Color();
    Color(int r, int g, int b);
    void set(int r, int g, int b);

    int GetRed();
    int GetGreen();
    int GetBlue();
    double GetRedAsDouble();
    double GetGreenAsDouble();
    double GetBlueAsDouble();
    std::string GetRedHex();
    std::string GetGreenHex();
    std::string GetBlueHex();
    std::string GetHexString();
    std::string IntToHex(int i);
    Color GetContrastColor();
};