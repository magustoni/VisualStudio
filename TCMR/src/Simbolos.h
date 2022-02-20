#pragma once
#include "freeglut.h"
#include <math.h>

#define PI 3.14

class Simbolos
{
private:
	GLint i;
	GLfloat r0, r1, r2;
	GLfloat angle, da;
	GLfloat u, v, len;
public:
	//Metodos de dibujo de cada simbolo
	void DrawPlay();
	void DrawStore();
	void DrawGear(GLfloat, GLfloat, GLfloat, GLint, GLfloat, int);
	void back();
	void cruz();
	void submenu();
	void principaldibuja(GLfloat radio_interno, GLfloat radio_externo, GLfloat anchura, GLint iteraciones, GLfloat profundidad, int a, int b);
	void cartel(float x, float y, float z);
};


