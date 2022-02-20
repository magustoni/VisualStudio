#include "Interfaz.h"
#include <iostream>

using namespace std;

Interfaz::Interfaz()
{
	height = 6;
	angle = 0.0;
	distance = 20;
	tipp = 1.57;
	x_click = 0;
	y_click = 0;
	new_mouse = 0;
	r = g = b = 255;
	sonido = true;
	sonido_aux = false;
}

void Interfaz::renderstring2d(char string[], float r, float g, float b, float x, float y, float z, int a) //Diferenciar tipo de letra segun el parametro a
{
	//Renderizado de texto, se llama a esta funcion siempre que se quiera escribir texto
	glColor3f(r, g, b);

	glRasterPos3f(x, y, z);
	for (unsigned int i = 0; i < strlen(string); i++)
	{
		switch (a) //Eleccion de la fuente en funcion del parametro a
		{
		case 0:

			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]); break; //Fuente TImes new roman
		case 1:
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]); break; //Fuente bit
		case 2:
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]); break; //Fuente helvetica
		case 3:
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]); break; //Fuente bit
		}
	}
}
void Interfaz::Raton_juego(int boton, int estado, int x, int y, bool zoom)
{
	if (estado == GLUT_DOWN)
	{
		if (boton == 3 and !zoom and height < 8)
			height++;
		if (boton == 4 and zoom and distance < 30)
			distance++;
		if (boton == 4 and !zoom and height > 0)
			height--;
		if (boton == 3 and zoom and distance > 10)
			distance--;
	}
	x_click = x;
	y_click = y;
	new_mouse = 1;

}

void Interfaz::Raton_menuprincipal(int boton, int estado, int x, int y)
{
	//Menu inicial detecta click de raton
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Al pulsar se establece la coordinacion en Niveles
		//Pixels de la ventanta boton play
		if (x > 380 and x < 515)
			if (y < 340 and y > 190)
				set_coordinacion = 3;

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Al pulsar se establece la coordinacion en Opciones
		//Pixels de la ventana boton opciones
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
				set_coordinacion = 2;

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Al pulsar se establece la coordinacion en Tienda
		//Pixels de la ventana boton de tienda
		if (x > 815 and x < 855)
			if (y < 535 and y > 485)
				set_coordinacion = 4;
}
void Interfaz::Raton_menuniveles(int boton, int estado, int x, int y)
{

    //Submenu de juegos
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Al pulsar se regresa al MenuPrincipal
		//Pixels de la ventana boton back (dibujo de flecha)
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
				set_coordinacion = 1;

	//Pixels de las puertas de niveles en orden

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 1 temática aire, hasta nivel 5
		if (x > 0 and x < 180)
			if (y < 350 and y > 0)
			{
				set_nivel = 1;
				set_coordinacion = 5;
			}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 6 tematica tierra
		if (nivel_max_completado > 4)//bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 180 and x < 360)
				if (y < 350 and y > 0)
				{
					set_nivel = 6;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 7 tematica tierra
		if (nivel_max_completado > 5)//bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 360 and x < 540)
				if (y < 350 and y > 0)
				{
					set_nivel = 7;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 8 tematica tierra
		if (nivel_max_completado > 6) //bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 540 and x < 900)
				if (y < 350 and y > 60)
				{
					set_nivel = 8;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 9 tematica agua
		if (nivel_max_completado > 7) //bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 720 and x < 900)
				if (y < 350 and y > 60)
				{
					set_nivel = 9;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 10 tematica agua
		if (nivel_max_completado > 8) //bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 0 and x < 180)
				if (y < 600 and y > 350)
				{
					set_nivel = 10;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 11 tematica agua
		if (nivel_max_completado > 9)//bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 180 and x < 360)
				if (y < 600 and y > 350)
				{
					set_nivel = 11;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 12 tematica fuego
		if (nivel_max_completado > 10)//bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 360 and x < 540)
				if (y < 600 and y > 350)
				{
					set_nivel = 12;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 13 tematica fuego
		if (nivel_max_completado > 11)//bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 540 and x < 720)
				if (y < 600 and y > 350)
				{
					set_nivel = 13;
					set_coordinacion = 5;
				}
		}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Nivel 14 tematica fuego
		if (nivel_max_completado > 12)//bloqueado si no se ha compleado el nivel anterior
		{
			if (x > 720 and x < 900)
				if (y < 600 and y > 350)
				{
					set_nivel = 14;
					set_coordinacion = 5;
				}
		}
	
}
void Interfaz::Raton_menuopciones(int boton, int estado, int x, int y)
{
	//Submenu de opciones
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))
		//Pixels de la ventana boton back
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
				set_coordinacion = 1;

	//Pixels de cada boton del submenu en orden
	sonido_aux = sonido;
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Sonido
		if (x > 290 and x < 595)
			if (y > 225 and y < 305)
				sonido = !sonido;


	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Creditos
		if (x > 290 and x < 595)
			if (y > 335 and y < 410)
				set_coordinacion = 6;

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))//Salir
		if (x > 290 and x < 595)
			if (y > 460 and y < 520)
				guardar = true;

}
void Interfaz::Raton_menutienda(int boton, int estado, int x, int y)
{
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))
		//Pixels de la ventana boton back
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
			{
				set_coordinacion = 1;	set_tienda = 0;
			}

	//Pixels de los carteles de la tienda
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Cartel1
		if (x > 74 and x < 174)
			if (y < 590 and y > 522)
			{
				set_tienda = 1;
				compra = false;
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))//Cartel2
		if (x > 235 and x < 335)
			if (y < 590 and y > 522)
			{
				set_tienda = 2;
				compra = false;
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))//Cartel3
		if (x > 400 and x < 500)
			if (y < 590 and y > 522)
			{
				set_tienda = 3;
				compra = false;
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))//Cartel4
		if (x > 565 and x < 660)
			if (y < 590 and y > 522)
			{
				set_tienda = 4;
				compra = false;
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))//Cartel5
		if (x > 725 and x < 820)
			if (y < 590 and y > 522)
			{
				set_tienda = 5;
				compra = false;
			}

	//Pixel cartel de compra por producto el cartel es el mismo, se establece la variable compra a true para activar la opcion de comprar el objeto
	if (set_tienda == 1)
		if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Comprar pelota 1
			if (x > 380 and x < 520)
				if (y < 375 and y > 270)
					compra = true;


	if (set_tienda == 2)
		if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Comprar pelota 2
			if (x > 380 and x < 520)
				if (y < 375 and y > 270)
					compra = true;

	if (set_tienda == 3)
		if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Comprar pelota 3
			if (x > 380 and x < 520)
				if (y < 375 and y > 270)
					compra = true;
	if (set_tienda == 4)
		if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Comprar pelota 4
			if (x > 380 and x < 520)
				if (y < 375 and y > 270)
					compra = true;
	if (set_tienda == 5)
		if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Comprar pelota 5
			if (x > 380 and x < 520)
				if (y < 375 and y > 270)
					compra = true;


	//Pixel cruz de exit
	if (set_tienda)
		if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))
			if (x > 525 and x < 535)
				if (y < 285 and y > 265)
					set_tienda = 0;
}
void Interfaz::Raton_menucreditos(int boton, int estado, int x, int y)
{
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Volver al menu
		//Pixels de la ventana boton back
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
				set_coordinacion = 1;
}

//AÑADIR AQUÍ LOS COLIDERS DEL RATÓN PARA LA GAMEINTERFACE (INVENTARIO Y BOTÓN DE PAUSA Y PLAY)
void Interfaz::Raton_menupausa(int boton, int estado, int x, int y)
{
	//Submenu de opciones
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))
		//Pixels de la ventana boton back
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
				set_coordinacion = 5;

	//Pixels de cada boton del submenu en orden
	sonido_aux = sonido;
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Sonido
		if (x > 290 and x < 595)
			if (y > 225 and y < 305)
				sonido = !sonido;


	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Guardar
		if (x > 290 and x < 595)
			if (y > 335 and y < 410)
				guardar = 1;
			
				

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))//Menu
		if (x > 290 and x < 595)
			if (y > 460 and y < 520)
				set_coordinacion = 1;

}

//Aqui poner los coliders de las casillas de elección de bloques del inventario
void Interfaz::Raton_inventario(int boton, int estado, int x, int y) {

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON))
		//Pixels de la ventana boton opciones
		if (x > 815 and x < 855)
			if (y < 60 and y > 25)
				set_coordinacion = 7;

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Casilla recta
		if (x > 0 and x < 300)
			if (y < 350 and y > 0){
				//SELECCIÓN BLOQUE RECTA
				tipo = 1;
				inventario = false; //Tras pulsar sobre el bloque deseado, se cierra el inventario
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Casilla curva
		if (x > 300 and x < 600)
			if (y < 350 and y > 0){
				//SELECCIÓN BLOQUE CURVA
				tipo = 2;
				inventario = false; //Tras pulsar sobre el bloque deseado, se cierra el inventario
			}
				
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Casilla rampa
		if (x > 600 and x < 800)
			if (y < 350 and y > 0) {
				//SELECCIÓN BLOQUE RAMPA
				tipo = 3;
				inventario = false; //Tras pulsar sobre el bloque deseado, se cierra el inventario
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Casilla trampolín
		if (x > 0 and x < 300)
			if (y < 700 and y > 350) {
				//SELECCIÓN BLOQUE TRAMPOLÍN
				tipo = 4;
				inventario = false; //Tras pulsar sobre el bloque deseado, se cierra el inventario
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Casilla rebote
		if (x > 300 and x < 600)
			if (y < 700 and y > 350) {
				//SELECCIÓN BLOQUE REBOTE
				tipo = 5;
				inventario = false; //Tras pulsar sobre el bloque deseado, se cierra el inventario
			}

	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //Casilla aire (eliminar bloques)
		if (x > 600 and x < 900)
			if (y < 700 and y > 350) {
				//SELECCIÓN BLOQUE AIRE
				tipo = 0;
				inventario = false; //Tras pulsar sobre el bloque deseado, se cierra el inventario
			}
	if ((estado == GLUT_DOWN) and (boton == GLUT_LEFT_BUTTON)) //BOTÓN DE PAUSA
		if (x > 800 and x < 900)
			if (y < 200 and y > 0) {
				this->estado = 2;
				inventario = false;
			}

}


void Interfaz::Motion(int x, int y)
{
	float turn_del, tipp_del, y_del; // variables de uso local

	static int x_sav, y_sav; // guarda la posicion de x e y anterior

	// printf ("   Motion:  %5d ->   x = %5d, y = %5d.", ++c, x, y);

	if (new_mouse) {  // solo si justo presionas un boton, si lo mantienes no se cumple
		new_mouse = 0;
		x_sav = x_click;
		y_sav = y_click;
	}

	turn_del = x - x_sav;
	angle += turn_del / 60; // se ha cogido una reduccion de 60 para que no gire demasiado rápido

	tipp_del = y - y_sav;
	tipp -= tipp_del / 60; //Angulo vertical invertido

	//Limites del angulo vertical
	if (tipp > PI / 2) tipp = PI / 2 ; //Mirando en horizontal
	if (tipp < 0.5)tipp = 0.5; //Mirando en vertical

	x_sav = x; // guarda los valores de x e y para la siguiente, si se mantiene presionado el boton
	y_sav = y; // si se suelta se activaría el if(new_mouse) y se cogerían los valores que se tomaron en la funcion  Mouse()
}



//Metodos de paso 

int Interfaz::get_interfaz()
{
	return set_coordinacion;
}
void Interfaz::set_interfaz(int i)
{
	set_coordinacion = i;
}
int Interfaz::get_tienda()
{
	return set_tienda;
}
bool Interfaz::get_activarcompra()
{
	return compra;
}
bool Interfaz::get_sonido()
{
	return sonido;
}
int Interfaz::get_nivel()
{
	return set_nivel;
}
bool Interfaz::get_guardar()
{
	return guardar;
}

void Interfaz::set_guardar(bool _guardar)
{
	guardar = _guardar;
}

void Interfaz::set_nivelmax(int a)
{
	nivel_max_completado = a;
}
