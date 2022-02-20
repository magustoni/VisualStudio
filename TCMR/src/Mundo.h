#include "Vector3D.h"
#include "Int3D.h"
#include "Pelota.h"
#include "Interaccion.h"
#include <iostream>
#include "Menu.h"
#include "ListaBloques.h"
#include"ListaBonus.h"
#include "GameInterface.h"

using namespace std;
class Mundo : protected Interfaz
{
	friend Interaccion;
protected:
	//Bloque bloque[8]; // los tipos de bloques
	ListaBloques bloques;
	ListaBonus Bonuss;
	Pelota pelota;
	int rojo, verde, azul;
	int rotacion;
	float angulo;
	bool zoom = 0;
	int puntuacion=0;
	bool wire; // booleano true( se ve todo en wire) false(se ve todo sólido)
	Vector3D size; // tamaño del mapa en tipo Vector3D
	//bloque
	Int3D select; // select guarda las coordenadas del lugar donde vas a situar el bloque
	//bool colocar = false; // booleano que se activa cuando quieres poner un bloque
	//mouse
	Bloque fantasma;
	int nivel = 0;
	bool begin = 0, reset;
	int dificultad = 0;
	//puntuación
	int bloques_puestos = 0;
	int intentos = 0;
	int nivel_max_completado = 2;

	float monedas = 0;
	//Contadores de bloques disponibles por el jugador (variarán al pasar de nivel y durante la ejecución del nivel)
	int cont_llave; //Contador de llaves recogidas
	int cont_bonus; //Contador de bonus
	int cont_intentos; //Contador de intentos 
	int cont_bloq_recta; //Contador de bloques de tipo recta
	int cont_bloq_curva; //Contador de bloques de tipo curva
	int cont_bloq_rampa; //Contador de bloques de tipo rampa
	int cont_bloq_trampolin; //Contador de bloques de tipo trampolín
	int bloques_minimo;

	GameInterface interfaz_jugador;


public:
	int get_estado();
	void set_estado(int);
	void tecla(unsigned char key); 
	void special_tecla(int key);
	void inicializa(int);
	void dibuja(); // situa la vista y llama a la funcion dibuja de Mapa
	void mouse(int, int, int, int); // lee el estado del ratón
									// cambia el valor de distance en función de la rueda
	void motion(int, int);  //cambia el valor de angle, tipp y Height
							// en función de mouse_rot y el cambio en la posicion x e y del raton
	void mueve();
	void cargar_nivel(bool reset);
	int get_nivel_max() { return nivel_max_completado; }
	bool win();
	bool die();
	void level_up() { nivel++; this->cargar_nivel(1); }
	void set_pelota_color(int r, int g, int b);
	float get_monedas();
	void set_monedas(int);
	void unlock();
	int get_puntuacion() { return puntuacion; }
	int get_nivel() { return nivel; }
	void set_nivel(int n);
	void set_sonido(bool);
	
	
	//DEFINIÓN FUNCIONES PARA LA TOMA DE DATOS DE LOS CONTAODRES DE BLOQUES PARA LA INTERFAZ DE JUEGO (game interface)
	int get_cont_nivel() { return nivel; }
	int get_cont_llave() { return cont_llave; }
	int get_cont_bonus() { return cont_bonus; }
	int get_cont_intentos() { return cont_intentos; }
	int get_cont_bloq_recta() { return cont_bloq_recta; }
	int get_cont_bloq_curva() { return cont_bloq_curva; }
	int get_cont_bloq_rampa() { return cont_bloq_rampa; }
	int get_cont_bloq_trampolin() { return cont_bloq_trampolin; }

	//Métodos del inventario
	void set_inventario(bool inv) { inventario = inv; }
	bool get_inventario() { return inventario; } //Comprobación de si hay que dibujar o no el inventariio
	void set_tipo_bloque(int tip_bloq) { tipo = tip_bloq; }

};