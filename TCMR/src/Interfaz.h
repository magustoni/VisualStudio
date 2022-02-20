#pragma once
#include "freeglut.h"
#include "Int3D.h"
#include "ETSIDI.h"
#include <math.h>

#define PI 3.1416
class Interfaz
{
protected:

	//Variables de coordinacion, estado, tienda, nivel y guardar
	int set_coordinacion = 1;
	int set_tienda = 0;
	int set_nivel = 0;
	bool guardar = 0;
	int nivel_max_completado;

	//Colores, sirve para el paso de color d ela pelota de menu a mundo
	int r, g, b;

	//Sonido y compras de la tienda, relacion entre Menu y Mundo a traves de coordinacion
	bool sonido, sonido_aux, compra;

	//mouse
	int x_click; // guarda el valor x de la posicion del ratón
	int y_click; // guarda el valor y de la posicion del ratón
	bool new_mouse; // booleano que avisa de que se se ha pulsado algun boton del raton
					// no se vuelve a activar hasta que no se suelte el boton

	//vista
	float angle; // guarda el valor del angulo horizontal de la vista esférica
	float tipp;  // guarda el valor del angulo vertical de la vista esférica
	float distance;  // guarda el radio de la vista esférica
	float height;  // guarda el valor en el eje Y del centro de la vista esférica
	
	//Variables afectadas por el inventario
	bool inventario = 0; //0 si no se dibuja el inventario, 1 si se dibuja el inventario. Para uso dentro de la clase Mundo
	int tipo; // guarda el valor del tipo de bloque que tienes en uso ahora
	int estado; //2 si estado de PAUSA. 1 si jugando, 0 si te has pasado los niveles
public:
	Interfaz();
	//Renderizado de texto
	static void renderstring2d(char string[], float r, float g, float b, float x, float y, float z, int a);

	//Funciones de raton en funcion de la pantalla en la que te encuentres
	void Raton_menuprincipal(int, int, int, int);
	void Raton_menuopciones(int, int, int, int);
	void Raton_menuniveles(int, int, int, int);
	void Raton_menutienda(int, int, int, int);
	void Raton_menucreditos(int, int, int, int);
	void Raton_menupausa(int, int, int, int);
	void Raton_inventario(int, int, int, int);
	void Raton_juego(int, int, int, int, bool);

	void Motion(int, int); //Movimiento de la vista

	//variables de paso a coordinador
	int get_interfaz();
	void set_interfaz(int);
	int get_tienda();
	bool get_activarcompra();
	bool get_sonido();
	int get_nivel();
	bool get_guardar();
	void set_guardar(bool);
	void set_nivelmax(int);
};

