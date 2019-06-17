#include <iostream>
#include <string>
#include "config.h"
#include "ini.h"

using namespace std;

bool Config::LoadConfiguration()
{
    // create a file instance
    mINI::INIFile file(filePath);

    // create a data structure
    if(file.read(ini))
    {
        width = GetInteger("global", "width", 0);
        height = GetInteger("global", "height", 0);
        copyToClipboardAfterPick = GetBoolean("global", "copy_to_clipboard_after_pick", false);
        quitAfterPick = GetBoolean("global", "quit_after_pick", false);
        pixelSize = GetInteger("magnifier", "pixel_size", -1);
        pixelsPerRow = GetInteger("magnifier", "pixels_per_row", -1);


        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "CopyToClipboardAfterPick: " << copyToClipboardAfterPick << endl;
        cout << "QuitAfterPick: " << quitAfterPick << endl;
        cout << "PixelSize: " << pixelSize << endl;
        cout << "PixelsPerRow: " << pixelsPerRow << endl;

        return true;
    }

    return false;

    // INIReader reader((string)getenv("HOME")+"/.picket/config.ini");

    // if (reader.ParseError() != 0) {
    //     cout << "Can't load 'config.ini'\n";
    //     return false;
    // }

    // width = reader.GetInteger("global", "width", 0);
    // height = reader.GetInteger("global", "height", 0);
    // copyToClipboardAfterPick = reader.GetBoolean("global", "copy_to_clipboard_after_pick", false);
    // quitAfterPick = reader.GetBoolean("global", "quit_after_pick", false);
    // pixelSize = reader.GetInteger("magnifier", "pixel_size", -1);
    // pixelsPerRow = reader.GetInteger("magnifier", "pixels_per_row", -1);

    // cout << "Config loaded form 'config.ini'." << endl;
}

int Config::GetWidth() { return width; }
int Config::GetHeight() { return height; }
bool Config::ShouldCopyAfterPick() { return copyToClipboardAfterPick; }
bool Config::ShouldQuitAfterPick() { return quitAfterPick; }

string Config::Get(string section, string name, string default_value)
{
    if(ini.has(section))
    {
        if(ini[section].has(name))
        {
            return ini.get(section).get(name);
        }
    }

    return default_value;
}

long Config::GetInteger(string section, string name, long default_value)
{
    string valstr = Get(section, name, "");
    const char* value = valstr.c_str();
    char* end;
    // This parses "1234" (decimal) and also "0x4D2" (hex)
    long n = strtol(value, &end, 0);
    return end > value ? n : default_value;
}

double Config::GetReal(string section, string name, double default_value)
{
    string valstr = Get(section, name, "");
    const char* value = valstr.c_str();
    char* end;
    double n = strtod(value, &end);
    return end > value ? n : default_value;
}

bool Config::GetBoolean(string section, string name, bool default_value)
{
    string valstr = Get(section, name, "");
    // Convert to lower case to make string comparisons case-insensitive
    transform(valstr.begin(), valstr.end(), valstr.begin(), ::tolower);
    if (valstr == "true" || valstr == "yes" || valstr == "on" || valstr == "1")
        return true;
    else if (valstr == "false" || valstr == "no" || valstr == "off" || valstr == "0")
        return false;
    else
        return default_value;
}
