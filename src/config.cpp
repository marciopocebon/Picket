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
        startImmediatePick = GetBoolean("global", "start_immediate_pick", false);
        copyToClipboardAfterPick = GetBoolean("global", "copy_to_clipboard_after_pick", false);
        quitAfterPick = GetBoolean("global", "quit_after_pick", false);
        lastFormat = GetInteger("global", "last_format", 1);
        pixelSize = GetInteger("magnifier", "pixel_size", -1);
        pixelsPerRow = GetInteger("magnifier", "pixels_per_row", -1);

        // cout << "Width: " << width << endl;
        // cout << "Height: " << height << endl;
        // cout << "CopyToClipboardAfterPick: " << copyToClipboardAfterPick << endl;
        // cout << "QuitAfterPick: " << quitAfterPick << endl;
        // cout << "LastFormat: " << lastFormat << endl;
        // cout << "PixelSize: " << pixelSize << endl;
        // cout << "PixelsPerRow: " << pixelsPerRow << endl;

        return true;
    }

    return false;
}

bool Config::SaveConfiguration()
{
    mINI::INIFile file(filePath);

    ini["global"]["width"] = to_string(width);
    ini["global"]["height"] = to_string(height);
    ini["global"]["start_immediate_pick"] = to_string(startImmediatePick);
    ini["global"]["copy_to_clipboard_after_pick"] = to_string(copyToClipboardAfterPick);
    ini["global"]["quit_after_pick"] = to_string(quitAfterPick);
    ini["global"]["last_format"] = to_string(lastFormat);
    ini["magnifier"]["pixel_size"] = to_string(pixelSize);
    ini["magnifier"]["pixels_per_row"] = to_string(pixelsPerRow);

    return file.write(ini, true);
}

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
