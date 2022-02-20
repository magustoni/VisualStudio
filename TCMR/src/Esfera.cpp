#include "Esfera.h"
#include "freeglut.h"


Esfera::Esfera()
{
	radio = 1.0;
	angulo = 0.0;
	posicion.x = 0.0;
	posicion.y = 0.0;
	velocidad.x = 0.0;
	velocidad.y = 0.0;

	color.rojo = color.verde = 255;
	color.azul = 100;
	aceleracion.y = -9.8;
}



void Esfera::setPos(float x, float y)
{
	posicion.x = x;
	posicion.y = y;
}

void Esfera::setVel(float vx, float vy)
{
	velocidad.x = vx;
	velocidad.y = vy;
}
void Esfera::dibuja()
{

	color.ponColor();
	glTranslatef(posicion.x, posicion.y, 0);
	glutSolidSphere(radio, 20, 20);
	glTranslatef(-posicion.x, -posicion.y, 0);

}

void Esfera::mueve(float t)
{
	posicion = posicion + velocidad * t + aceleracion * (0.5 * t * t);
	velocidad = velocidad + aceleracion * t;
}

void Esfera::rota()
{
	angulo += 5;
}