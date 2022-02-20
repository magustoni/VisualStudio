#pragma once
#include "freeglut.h"
#include "math.h"
#include "Caja.h"
#include "Esfera.h"
#include "Interaccion.h"
#include "Interfaz.h"
#include "Simbolos.h"
#include "ETSIDI.h"

class Menu : protected Interfaz
{
private:
	enum Tiendas { TiendaPrincipal, Cartel1, Cartel2, Cartel3, Cartel4, Cartel5 }; //Carteles de la tienda
	Tiendas tienda;
	Simbolos s;
	Caja c;
	Esfera e, e2;
	bool efecto, logoinicial;
	float z, z1, z2, z3, z4; //Variuables del desplazamiento del logo inicial
	float credy; //Variable de desplazamiento de los creditos
	int puntuacion, monedas = 0;
	int puntuacion_niveles[10];
	bool comprado1, comprado2, comprado3, comprado4, comprado5; //Booleanas a guardar en caso de compra en la tienda
	int nivel_max_completado;
public:
	Menu();

	void iniciar();
	//Pantallas de menus
	void logo();
	void menuprincipal();
	void menuopciones();
	void menuniveles();
	void menutienda();
	void menucreditos();
	void menupausa();

	//Variables de la tienda
	void set_Tienda(int t);
	void activar_compra(bool);
	bool monedas_minimo(Tiendas);
	void set_monedas(int);
	void set_monedasini(int);
	float get_monedas();
	bool get_compras(int);
	void set_compras(bool c1, bool c2, bool c3, bool c4, bool c);

	//Otras variables
	void set_sonido(bool);
	int get_color(int);
	void set_guardar(bool);
	void set_nivelmax(int);

	//Puntuacion
	void set_puntuacion();
	void puntuacion_nivel(int, int);
	int get_puntuacion(int);

	//Movimiento de pantallas
	void mueveprincipal();
	void muevetienda();
	void muevecreditos();
};



