#include "stringutil.h"
#include <iostream>

string trim(const string& str) {
    string s = str;
    // Lambda to check space
    auto isSpace = [](unsigned char c) { return isspace(c); };
    // Remove leading spaces
    s.erase(s.begin(), find_if(s.begin(), s.end(), 
             [isSpace](unsigned char c) { return !isSpace(c); }));
    // Remove trailing spaces
    s.erase(find_if(s.rbegin(), s.rend(), 
             [isSpace](unsigned char c) { return !isSpace(c); }).base(), s.end());
    return s;
}

string toLowerCase(const string& str) {
    string lowerCaseStr;
    lowerCaseStr.resize(str.size());
    transform(str.begin(), str.end(), lowerCaseStr.begin(),
                   [](unsigned char c) { return tolower(c); });

    return lowerCaseStr;
}

