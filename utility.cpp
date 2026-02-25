#include "stdafx.h"

#include "utility.h"

#include <string>


std::string space2underscore(std::string text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
		if (*it == ' ') {
			*it = '_';
		}
	}
	return text;
}

std::string dot2dash(std::string text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
		if (*it == '.') {
			*it = '-';
		}
	}
	return text;
}

std::string ampersand2underscore(std::string text) {
	for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
		if (*it == '&') {
			*it = '_';
		}
	}
	return text;
}



unsigned long seed()
{
	/* The time comes in a maximum resolution of 10e-7 seconds, but Windows
	 * works on systems that might not actually have that kind of resolution.
	 * Usually it is around 10e-4. So we'll just discard the likely-zero bits.
	 */
	FILETIME       t;
	ULARGE_INTEGER i;
	GetSystemTimeAsFileTime(&t);
	i.u.LowPart = t.dwLowDateTime;
	i.u.HighPart = t.dwHighDateTime;
	return i.QuadPart / 1000;
}

float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int RandomInt(int lowest, int highest)
{
	int range = (highest - lowest) + 1;
	//2020august14, spi, begin
	int random_integer = lowest + int(range*rand() / (RAND_MAX + 1.0));
	//int random_integer = lowest + (rand() % range);
	//int random_integer = (double)rand() / ((double)RAND_MAX + 1.0) * (highest - lowest) + lowest;
	//2020august14, spi, end
	return random_integer;
}







// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string &str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}
