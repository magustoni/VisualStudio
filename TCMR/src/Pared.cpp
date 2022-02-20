#include "Pared.h"
#include "freeglut.h"



Pared::Pared()
{

}
void Pared::setColor(Byte r, Byte g, Byte b)
{
	color.rojo = r;
	color.azul = b;
	color.verde = g;
}
void Pared::setPos(float x1, float y1, float x2, float y2, float z)
{
	limite1.x = x1;
	limite1.y = y1;
	limite2.x = x2;
	limite2.y = y2;
	limitez = z;
}
float Pared::distancia(Vector2D punto, Vector2D* direccion)
{
	Vector2D u = (punto - limite1);
	Vector2D v = (limite2 - limite1).unitario();
	float longitud = (limite1 - limite2).modulo();
	Vector2D dir;
	float valor = u * v;
	float distancia = 0;
	if (valor < 0)
		dir = u;
	else if (valor > longitud)
		dir = (punto - limite2);
	else
		dir = u - v * valor;
	distancia = dir.modulo();
	if (direccion != 0) //si nos dan un vector…
		*direccion = dir.unitario();
	return distancia;



}
void Pared::dibuja()
{
	glDisable(GL_LIGHTING);
	color.ponColor();
	glBegin(GL_POLYGON);
	glVertex3f(limite1.x, limite1.y, limitez);
	glVertex3f(limite2.x, limite2.y, limitez);
	glVertex3f(limite2.x, limite2.y, -limitez);
	glVertex3f(limite1.x, limite1.y, -limitez);
	glEnd();
	glEnable(GL_LIGHTING);
}



Pared::~Pared() {}