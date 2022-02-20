#pragma once
#include "Vector2D.h"
#include "Pelota.h"
#include "ColorRGB.h"
class Esfera : public Pelota //Pelota en ambito 2D
{
private:
	friend class Interaccion;
	friend class Menu;

	float angulo;
		Vector2D posicion;
		Vector2D velocidad;
		Vector2D aceleracion;
public:
	Esfera();
	//virtual ~Esfera() {}

	void setPos(float x, float y);
	void setVel(float vx, float vy);
	void dibuja();
	void mueve(float);
	void rota();
};