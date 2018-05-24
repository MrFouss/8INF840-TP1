#pragma once
#include <string>

enum EyeColor { empty=-1, blue = 0, green = 1, brown = 2, black = 3 };

std::string eyeColorToString(EyeColor eye);
EyeColor itoEyeColor(int i);