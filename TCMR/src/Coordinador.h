#pragma once
#include "Mundo.h"
#include "Menu.h"
#include "Interfaz.h"

class Coordinador
{
	friend class Mundo;
protected:

	//Estados de juego
	enum Pantallas { MenuPrincipal = 1, Opciones, Niveles, Tienda, Juego, Creditos, Pausa};
	Pantallas game_stage;

	//Objetos de otras clases
	Menu me;
	Mundo mu;
	Interfaz i;

	//Color para cambiar pelota del mundo
	int rojocoord, verdecoord, azulcoord;

	//puntuación, niveles y monedas
	int puntuacion_niveles[10];
	int nivel_max_completado;
	int moneda;

	//Variables de guardado y sonido
	bool guardar;
	bool sound;
	bool comprado1, comprado2, comprado3, comprado4, comprado5; //Booleanas a guardar en caso de compra en la tienda

public:
	void inicializa();
	void dibuja();

	//Metodos de teclas llamar al metodo del mundo
	void teclas(unsigned char key);
	void teclasespeciales(unsigned char key);

	//Movimiento segun el estado del juego
	void mueve();

	//Raton y movimiento de pantalla segun los estados del juego
	void mouse(int button, int x, int y, int state);
	void motion(int x, int y);

	//Establecer estado de juego
	void set_gamestage();
	int get_stage();

	//Metodos de cambio 
	void change_color();
	void pass_monedas();
	void compras();


	//Metodo de guardado de pelotas compradas en la tienda
	bool get_comprado1() { return comprado1; }
	bool get_comprado2() { return comprado2; }
	bool get_comprado3() { return comprado3; }
	bool get_comprado4() { return comprado4; }
	bool get_comprado5() { return comprado5; }

	//Pasar sonido y guardar partida (Opciones y pausa)
	void pass_sound();
	void guardar_partida();
};


