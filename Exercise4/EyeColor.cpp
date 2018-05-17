#include "EyeColor.h"
std::string eyeColorToString(EyeColor eye) {
	using namespace std;

	switch (eye) {
	case blue:	return string("blue");
	case green: return string("green");
	case brown: return string("brown");
	case black: return string("blue");
	default:	return string("UNKNOWN COLOR");
	}
}

EyeColor itoEyeColor(int i) {
	switch (i) {
	case 0: return blue;
	case 1: return green;
	case 2: return brown;
	case 3: return black;
	}
}