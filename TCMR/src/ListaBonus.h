#pragma once
#define MAX_BONUS 30
#include"Bonus.h"
#include"Vector3D.h"
#include"Esfera.h"

class ListaBonus
{
	friend class Interaccion;
public:
	ListaBonus();
	bool agregar(Bonus* b, int tipo, Vector3D);
	void dibujar(float);
	void eliminar(int index);
	void eliminar(Bonus* e);
	void destruirContenido();

	Bonus* colision(Pelota *e);//detecta si se produce una colusion entre un bonus y la pelota en los distintos niveles


private:
	Bonus* lista[MAX_BONUS];
	int numero;
};

