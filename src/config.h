#pragma once

#include <string>
#include "ini.h"

using namespace std;

class Config
{
private:

    mINI::INIStructure ini;
    int width = 0;
    int height = 0;
    bool copyToClipboardAfterPick = false;
    bool quitAfterPick = false;

    int pixelSize = 8;
    int pixelsPerRow = 13;
    string filePath = (string)getenv("HOME")+"/.picket/config.ini";

    string Get(string section, string name, string default_value);
    long GetInteger(string section, string name, long default_value);
    double GetReal(string section, string name, double default_value);
    bool GetBoolean(string section, string name, bool default_value);

public:
    int GetWidth();
    int GetHeight();
    bool ShouldCopyAfterPick();
    bool ShouldQuitAfterPick();
    bool LoadConfiguration();
};
