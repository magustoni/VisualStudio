#pragma once
#include "Menu.h"
#include "ETSIDI.h"
#include "Interaccion.h"
#include "Simbolos.h"
#include "freeglut.h"
#include <math.h>
#define PI 3.141592653595



class GameInterface {

	Simbolos s;
	friend class Interfaz; //amistad con clase Interfez para la utilizaci�n de m�todos de 
	friend class Mundo; //Amistad con clase mundo para la utilizaci�n de algunos de sus m�todos p�blicos
	float pos_x, pos_y, pos_z; //Posici�n del observador
	int dificultad = 0;
	 
public:
	void dibujarInventario(); //Dibuhjado de todos los elementos del inventario del jugador
	void set_dificultad(int); //Introducci�n del valor de dificultad para el dibujados de los distintos fondos
	float calculo_vision_alpha(float lado_x, float lado_z, float pos_x, float pos_z); //Funci�n de c�lculo del primer �ngulo de rotaci�n de la transformaci�n del sistema de referencia pra el dibujado de la interfaz del jugador.
	float calculo_vision_beta(float lado_x, float lado_y, float lado_z, float pos_x, float pos_y, float pos_z); //Funci�n de c�lculo del segundo �ngulo de rotaci�n de la transformaci�n del sistema de referencia pra el dibujado de la interfaz del jugador.
};