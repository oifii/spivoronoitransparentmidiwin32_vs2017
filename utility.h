#pragma once

#ifndef _UTILITY_H
#define _UTILITY_H

#include <string>

std::string space2underscore(std::string text);
std::string dot2dash(std::string text);
std::string ampersand2underscore(std::string text);

unsigned long seed();
float RandomFloat(float a, float b);
int RandomInt(int lowest, int highest);

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr);
// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string &str);

#endif //_UTILITY_H
