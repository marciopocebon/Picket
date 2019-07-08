#pragma once

#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>

using namespace std;

class ColorFormatManager
{
 private:
    string filepath = "";
    map<string, string> formats;
    map<string, string> variables;
    string ReplaceVariable(string original, string var, string replacement);
    vector<string> GetVariableKeys();
    string formatsString = "#FORMATS\n"
    "[RGB]Color($r$, $g$, $b$);\n"
    "[RGBA]Color($r$, $g$, $b$, $a$);\n"
    "# This is a comment\n"
    "[RGB_1.0]Color($r_d$, $g_d3$, $b_d4$);\n"
    "[RGBA_1.0]Color($r_d5$, $g_d6$, $b_d5$, $a_d4$);\n"
    "----\n"
    "[HSL]Color($h$, $s$, $l$);\n"
    "# Hex color value\n"
    "[HEX]#$r_hex$$g_hex$$b_hex$\n";

 protected:

 public:
    ColorFormatManager(string path);
    bool FormatFileExists();
    bool CreateFormatFile();
    void LoadFormats();
    void SetVariables(map<string, string> vars);
    string FindFormatKey(string line);
    string GetFormatString(string line);
    vector<string> GetFormatsKeys();
    string GetFormat(string key);
};
