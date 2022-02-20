#pragma once
#include"Vector3D.h"
class Bonus
{
	friend class Interaccion;
public:
	Bonus();
private:
	float radio;
	float altura;
	Vector3D posicion;
	int tipo;
	unsigned char rojo;
	unsigned char verde;
	unsigned char azul;
public:
	void Dibuja(float);
	void setcolor(unsigned char r, unsigned char a, unsigned char v);
	void setPos(Vector3D);
	void setTipo(int);
	int getTipo();//coje el tipo de bonus que es(estrella o llave)
};

