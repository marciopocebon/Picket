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
    map<string, string> formats;
    map<string, string> variables;
    string ReplaceVariable(string original, string var, string replacement);
    vector<string> GetVariableKeys();

 protected:

 public:
    ColorFormatManager();
    void LoadFormats(string);
    void SetVariables(map<string, string> vars);
    string FindFormatKey(string line);
    string GetFormatString(string line);
    vector<string> GetFormatsKeys();
    string GetFormat(string key);
};
