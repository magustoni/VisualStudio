#pragma once
#include "Pared.h"



class Caja
{
private:

	//Objetos de Pared que se van a dibujar
	Pared suelo;
	Pared estante;
	Pared pared;
	Pared parede;

	//Interaccion con los objetos
	friend class Interaccion;

public:
	Caja();
	void dibuja(int a);
};