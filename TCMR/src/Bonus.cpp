#include "Bonus.h"
#include"freeglut.h"
#include <iostream>

using namespace std;
Bonus::Bonus() {
	radio = 0.1;
	altura = 0.5;
	posicion.x = -1;
	posicion.y = 1.1;
	posicion.z = 0;
	setcolor(255, 0, 100);
}


void Bonus::Dibuja(float angulo)
{
	

	switch (tipo)
	{
	case 0: //estrella
		glPushMatrix();
		glTranslated(posicion.x, posicion.y, posicion.z);
		glRotatef(angulo, 0, 1, 0);
		//esfera de estrella
		glColor3ub(255, rojo, azul);
		glutSolidSphere(radio, 100, 100);
		//conos puntas estrellas
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glRotated(45, 1, 0, 0);
		glutSolidCone(radio, altura, 100, 100);
		glPopMatrix();
		break;
	case 1: //llave(compuesta de cilindros y un toro)
		glPushMatrix();
		glColor3ub(255, rojo, azul);
		glTranslated(posicion.x, posicion.y, posicion.z);
		//toro para hacer la anilla
		glRotatef(angulo, 0, 1, 0);
		glutSolidTorus(0.02, 0.2, 100, 100);
		//cilindros para componer los dientes de la llave
		glTranslated(0.2, 0, 0);
		glPushMatrix();
		GLUquadricObj* quadratic1;
		quadratic1 = gluNewQuadric();
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		gluCylinder(quadratic1, 0.02, 0.02, 0.4, 32, 32);
		glPopMatrix();
		glTranslated(0.25, 0, 0);
		glPushMatrix();
		GLUquadricObj* quadratic2;
		quadratic2 = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic2, 0.02, 0.02, 0.2, 32, 32);
		glPopMatrix();
		glTranslated(0.14, 0.02, 0);
		glPushMatrix();
		GLUquadricObj* quadratic3;
		quadratic3 = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(quadratic3, 0.02, 0.02, 0.22, 32, 32);
		glPopMatrix();
		glPopMatrix();
		break;
	default:
		break;
	}
	
	
}

//poner color al bonus
void Bonus::setcolor(unsigned char r, unsigned char a, unsigned char v)
{
	verde = v;
	azul = a;
	rojo = r;
}
//asignar posicion al bonus
void Bonus::setPos(Vector3D aux)
{
	posicion.x = aux.x;
	posicion.y = aux.y;
	posicion.z = aux.z;
}
//asignar tipo de bonus
void Bonus::setTipo(int tipo)
{
	this->tipo = tipo;
}
//cojer el tipo de bonus para pasar a coordinador si es estrella o llave y que se la pase a mundo
int Bonus::getTipo() {
	int a;
	a=tipo;
	cout << a << (tipo) << altura << endl;
	return a;
}
