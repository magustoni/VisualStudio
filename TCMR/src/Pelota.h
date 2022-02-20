#pragma once
#include "freeglut.h"
#include "Vector3D.h"
#include "ColorRGB.h"

class Pelota //Pelota en ambito 3D
{
	friend class Interaccion;
	friend class Menu;
protected:
	ColorRGB color;
	Vector3D pos;
	Vector3D vel;
	Vector3D ac;
	float radio;
	bool mover;
	
public:
	Pelota();
	float vel_nom;
	void setColor(unsigned char red, unsigned char green, unsigned char blue);
	virtual void mueve(float t);
	virtual void dibuja();
	void teclado(unsigned char);
	Vector3D get_pos();
	virtual void set_pos(float, float, float);
	virtual void set_vel(float, float, float);
};