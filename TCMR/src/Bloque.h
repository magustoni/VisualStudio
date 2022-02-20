#pragma once
#include "Int3D.h"
class Bloque
{
	friend class Interaccion;
private:
	int tipo;
	int rotacion;
	Int3D posicion;

public:
	Bloque();
	Bloque(int tipo, int rotacion, Int3D pos);
	void dibujar(bool wire); //Dibuja el bloque solido o como hilos en funcion de "wire"
	void cambiar(int tipo, int rotacion) { this->tipo = tipo; this->rotacion = rotacion; } //Cambia el tipo y rotacion de un bloque

	void set_Pos(Int3D pos); //Cambia la posicion de un bloque
	Int3D get_pos() { return this->posicion; }

	void set_Rot(int rotacion) { this->rotacion = rotacion; }
	int get_Rot() { return this->rotacion; }

	void set_tipo(int tipo) { this->tipo = tipo; }
	int get_tipo() { return this->tipo; }
};