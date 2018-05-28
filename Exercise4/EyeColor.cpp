#include "EyeColor.h"
std::string eyeColorToString(EyeColor eye) {
	using namespace std;

	switch (eye) {
	case blue:	return string("bleu");
	case green: return string("vert");
	case brown: return string("marron");
	case black: return string("noir");
	case none:  return string("none");
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