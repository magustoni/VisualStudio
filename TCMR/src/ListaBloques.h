#pragma once
#define MAX_BLOQUES 360
#include "Bloque.h"
#include "Pelota.h"

class ListaBloques
{
	friend class Interaccion;
public:
	ListaBloques();
	bool agregar(Bloque *b, int tipo, int rotacion, Int3D);
	void cambiar_bloque(bool permiso, int tipo, int rotacion, int);
	void destruirContenido();
	void dibujar(bool);
	int get_numero() { return numero; }
	int comprobar_bloque(int posicion) {return lista[posicion]->get_tipo(); } //Dada una posicion en la lista, devuelve el tipo de bloque
	int pos_lista(Int3D pos); //Dada una posicion matricial, devuelve la posicion en la lista
	Bloque inicio();
	Bloque meta();
private:
	Bloque* lista[MAX_BLOQUES];
	int numero;
};