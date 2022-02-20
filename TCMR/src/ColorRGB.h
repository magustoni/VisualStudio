#pragma once
#include "freeglut.h"
typedef unsigned char Byte;
struct ColorRGB
{
public:
	ColorRGB(Byte red = 255, Byte green = 255, Byte blue = 255) {
		set(red, green, blue);
	};
	void set(Byte red = 255, Byte green = 255, Byte blue = 255) {
		rojo = red; verde = green; azul = blue;
	}
	void ponColor() {
		glColor3ub(rojo, verde, azul);
	};
	Byte rojo, verde, azul;
};