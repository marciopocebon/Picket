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
    int lastFormat = 1;
    bool startImmediatePick = false;
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

    int GetWidth() { return width; }
    int GetHeight() { return height; }
    int GetLastFormat() { return lastFormat; }
    bool ShouldStartImmediatePick() { return startImmediatePick; }
    bool ShouldCopyAfterPick() { return copyToClipboardAfterPick; }
    bool ShouldQuitAfterPick() { return quitAfterPick; }
    int GetPixelSize() { return pixelSize; }
    int GetPixelsPerRow() { return pixelsPerRow; }

    void SetWidth(int w) { width = w; }
    void SetHeight(int h) { height = h; }
    void SetLastFormat(int lastFormatIndex) { lastFormat = lastFormatIndex; }
    void SetImmediatePick(bool pick) { startImmediatePick = pick; }
    void SetCopyAfterPick(bool copy) { copyToClipboardAfterPick = copy; }
    void SetQuitAfterPick(bool quit) { quitAfterPick = quit; }
    void SetPixelSize(int pixSize) { pixelSize = pixSize; }
    void SetPixelsPerRow(int pixPerRow) { pixelsPerRow = pixPerRow; }

    bool LoadConfiguration();
    bool SaveConfiguration();
};
