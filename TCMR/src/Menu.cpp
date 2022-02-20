#include "Menu.h"
#include <string.h>
#include <iostream>

using namespace std;


Menu::Menu()
{
	//Establecer valores predeterminados para poder cambiar la posicion con mayor facilidad
	z = z1 = z2 = z3 = z4 = 40;
	credy = 3.5;
	logoinicial = efecto = true;
	tienda = TiendaPrincipal;

}
void Menu::iniciar()
{
	//Inicializa la posicion de la pelota y su velocidad para que rebote
	e.setPos(0, 5);
	e.setVel(0, 0);
}
void Menu::logo()
{
	if (efecto) //Efecto de sonido
	{
		ETSIDI::play("sonidos/EF_Sports_Sound_Effect.mp3");
		efecto = false;
	}

	gluLookAt(0, 7.5, 30, // posicion del ojo
		0, 7.5, 0, // hacia que punto mira (0,y,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
	//CODIGO DE DIBUJO
	glPopMatrix;
	glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 255);

	glTranslated(0.0, 7.5, z1);

	//Circulo externo
	glutSolidTorus(0.75, 12, 50, 50);

	//Letra E
	if (z1 < -35.6)
	{
		glPopMatrix();
		glBegin(GL_POLYGON);//Segmento superior
		glVertex3f(-9, 8, z2);
		glVertex3f(0, 8, z2);
		glVertex3f(1, 10, z2);
		glVertex3f(-8, 10, z2);
		glEnd();
		glBegin(GL_POLYGON);//Segmento intermedio
		glVertex3f(-11, 4, z2);
		glVertex3f(-2, 4, z2);
		glVertex3f(-1, 6, z2);
		glVertex3f(-10, 6, z2);
		glEnd();
		glBegin(GL_POLYGON);//Segmento vertical
		glVertex3f(-9.5, 4, z2);
		glVertex3f(-7, 4, z2);
		glVertex3f(-9, 0, z2);
		glVertex3f(-11.5, 0, z2);
		glEnd();
		glBegin(GL_POLYGON);//Segmento inferior
		glVertex3f(-8, 2, z2);
		glVertex3f(-1.5, 2, z2);
		glVertex3f(-2.5, 0, z2);
		glVertex3f(-9, 0, z2);
		glEnd();
		glPushMatrix();
	}
	if (z2 < -25)
	{
		//Letra F
		glPopMatrix();
		glBegin(GL_POLYGON);//Segmento vertical
		glVertex3f(-2.5, 0, z);
		glVertex3f(0, 0, z);
		glVertex3f(5, 10, z);
		glVertex3f(2.5, 10, z);
		glEnd();
		glBegin(GL_POLYGON);//Segmento superior
		glVertex3f(5, 10, z);
		glVertex3f(11, 10, z);
		glVertex3f(10, 8, z);
		glVertex3f(4, 8, z);
		glEnd();
		glBegin(GL_POLYGON);//Segmento inferior
		glVertex3f(3, 6, z);
		glVertex3f(8, 6, z);
		glVertex3f(7, 4, z);
		glVertex3f(2, 4, z);
		glEnd();
		glPushMatrix();
	}

	glTranslated(0.0, 0, -z1);
	if (z3 < 9) //Esperar 1 segundo antes de pasar a la pantalla de menu para que se acabe el efecto de sonido
	{
		Sleep(1000);
		logoinicial = false;
		z3 = 10.1;
	}
	if (z < -25) //Palabra SPORTS en movimiento
	{
		glTranslatef(0, -z3, 0);
		ETSIDI::setFont("fuentes/BebasNeue-Regular.ttf", 50);
		ETSIDI::setTextColor(255, 255, 255);
		glTranslatef(0.4, 0, 0);
		ETSIDI::printxy("SPORTS", -3, 7, 0);
		glTranslatef(-0.4, 0, 0);
	}
}

void Menu::menuprincipal()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (logoinicial)
	{
		logo(); //Hacer el efecto del logo inicial
	}
	else {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0, 7.5, 0, // hacia que punto mira (0,y,0)
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)	////Fondo menu
	//Fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu.png").id);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1);
		glVertex3f(-15, -15, -10);
		glTexCoord2d(1, 1);
		glVertex3f(15, -15, -10);
		glTexCoord2d(1, 0);
		glVertex3f(15, 20, -10);
		glTexCoord2d(0, 0);
		glVertex3f(-15, 20, -10);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//Texto de puntuacion
		    set_puntuacion();
			renderstring2d((char*)"Puntuacion: ", 255, 255, 255, -8, 2.5, 11, 1);
			char punt[10];
			sprintf(punt, "%d", this->puntuacion);
			renderstring2d(punt, 255, 255, 255, -6, 2.5, 11, 1);

		//TItulo del juego
			ETSIDI::setFont("fuentes/Minercraftory.ttf", 35);
			ETSIDI::setTextColor(255, 255, 255);
			ETSIDI::printxy("They C Me Rollin'", -8, 15, 0);

		//Suelo
		c.dibuja(0);

		//Pelota que rebota
		e.setColor(r, g, b);
		e.dibuja();

		glColor3f(255, 255, 255);
		//Boton de play
		glPopMatrix;
		glTranslatef(0, 10, 0);
		s.principaldibuja(2, 2.25, 2, 50, 0, 1, 0);

		//Opciones
		credy = 3.5; //Resetear la variable de creditos antes de entrar
		glTranslatef(12, 7, 0);
		s.principaldibuja(0.2, 0.5, 0.20, 10, 0.15, 0, 0);

		//Tienda
		glTranslatef(0, -14.5, 0);
		s.principaldibuja(0.4, 0.5, 0.20, 50, 0, 0, 1);
		glPushMatrix;
		glutPostRedisplay();
	}
}
void Menu::menuopciones()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0, 7.5, 0, // hacia que punto mira (0,y,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

	//Fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);
	glVertex3f(-15, -15, -10);
	glTexCoord2d(1, 1);
	glVertex3f(15, -15, -10);
	glTexCoord2d(1, 0);
	glVertex3f(15, 20, -10);
	glTexCoord2d(0, 0);
	glVertex3f(-15, 20, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//boton retroceso
	s.back();

	//Opciones del menu
	if (sonido)
		renderstring2d((char*)"SONIDOS: ON", 0, 0, 0, -2.3, 10, -1, 0);
	else
		renderstring2d((char*)"SONIDOS: OFF", 0, 0, 0, -2.3, 10, -1, 0);

	renderstring2d((char*)"CREDITOS", 0, 0, 0, -2.1, 6.5, -1, 0);
	renderstring2d((char*)"GUARDAR Y SALIR", 0, 0, 0, -3.35, 3.1, -1, 0);

	//Titulo del menu OPCIONES
	ETSIDI::setFont("fuentes/Minercraftory.ttf", 20);
	ETSIDI::setTextColor(255, 255, 255);
	glTranslatef(0.5, 0, 0);
	ETSIDI::printxy("OPCIONES", -3, 15, 5);
	glTranslatef(-0.5, 0, 0);

	glColor3ub(255, 255, 255);
	//Dibujo de los carteles del menu
	s.submenu();
	glutPostRedisplay();
}
void Menu::menuniveles()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0, 7.5, 0, // hacia que punto mira (0,y,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
	//boton retroceso
	s.back();
	//Texto 
	renderstring2d((char*)"TUTORIAL", 0, 0, 0, -8.15, 7.65, 11, 1);
	//foto entrada nivel tutorial
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/nube.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-12, 7.5, 5);
	glTexCoord2d(1, 1);    glVertex3f(-7.2, 7.5, 5);
	glTexCoord2d(1, 0);    glVertex3f(-7.2, 17, 5);
	glTexCoord2d(0, 0);    glVertex3f(-12, 17, 5);
	glEnd();
	glEnable(GL_TEXTURE_2D);
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, -5, 7.65, 11, 1);
	char punt1[10];
	sprintf(punt1, "%d", this->puntuacion_niveles[1]);
	renderstring2d(punt1, 0, 0, 0, -3, 7.65, 11, 1);
	//foto entrada al nivel 1
	if (nivel_max_completado < 5)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tierrablock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tierra.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-7.2, 7.5, 5);
	glTexCoord2d(1, 1);    glVertex3f(-2.4, 7.5, 5);
	glTexCoord2d(1, 0);    glVertex3f(-2.4, 17, 5);
	glTexCoord2d(0, 0);    glVertex3f(-7.2, 17, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, -1.5, 7.65, 11, 1);
	char punt2[10];
	sprintf(punt2, "%d", this->puntuacion_niveles[2]);
	renderstring2d(punt2, 0, 0, 0, 0.5, 7.65, 11, 1);
	//foto entrada al nivel 2
	if (nivel_max_completado < 6)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tierrablock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tierra.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-2.4, 7.5, 5);
	glTexCoord2d(1, 1);    glVertex3f(2.4, 7.5, 5);
	glTexCoord2d(1, 0);    glVertex3f(2.4, 17, 5);
	glTexCoord2d(0, 0);    glVertex3f(-2.4, 17, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, 2.35, 7.65, 11, 1);
	char punt3[10];
	sprintf(punt3, "%d", this->puntuacion_niveles[3]);
	renderstring2d(punt3, 0, 0, 0, 4.5, 7.65, 11, 1);
	//foto entrada al nivel 3
	if (nivel_max_completado < 7)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tierrablock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/tierra.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(2.4, 7.5, 5);
	glTexCoord2d(1, 1);    glVertex3f(7.2, 7.5, 5);
	glTexCoord2d(1, 0);    glVertex3f(7.2, 17, 5);
	glTexCoord2d(0, 0);    glVertex3f(2.4, 17, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, 6, 7.65, 11, 1);
	char punt4[10];
	sprintf(punt4, "%d", this->puntuacion_niveles[4]);
	renderstring2d(punt4, 0, 0, 0, 8, 7.65, 11, 1);
	//foto entrada al nivel 4
	if (nivel_max_completado < 8)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/aguablock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/agua.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(7.2, 7.5, 5);
	glTexCoord2d(1, 1);    glVertex3f(12, 7.5, 5);
	glTexCoord2d(1, 0);    glVertex3f(12, 17, 5);
	glTexCoord2d(0, 0);    glVertex3f(7.2, 17, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, -8.7, 7.2, 11, 1);
	char punt5[10];
	sprintf(punt5, "%d", this->puntuacion_niveles[5]);
	renderstring2d(punt5, 0, 0, 0, -6.7, 7.2, 11, 1);
	//foto entrada al nivel 5
	if (nivel_max_completado < 9)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/aguablock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/agua.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-12, -1.7, 5);
	glTexCoord2d(1, 1);    glVertex3f(-7.2, -1.7, 5);
	glTexCoord2d(1, 0);    glVertex3f(-7.2, 7.5, 5);
	glTexCoord2d(0, 0);    glVertex3f(-12, 7.5, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, -5, 7.2, 11, 1);
	char punt6[10];
	sprintf(punt6, "%d", this->puntuacion_niveles[6]);
	renderstring2d(punt6, 0, 0, 0, -3, 7.2, 11, 1);
	//foto entrada al nivel 6
	if (nivel_max_completado < 10)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/aguablock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/agua.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-7.2, -1.7, 5);
	glTexCoord2d(1, 1);    glVertex3f(-2.4, -1.7, 5);
	glTexCoord2d(1, 0);    glVertex3f(-2.4, 7.5, 5);
	glTexCoord2d(0, 0);    glVertex3f(-7.2, 7.5, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, -1.5, 7.2, 11, 1);
	char punt7[10];
	sprintf(punt7, "%d", this->puntuacion_niveles[7]);
	renderstring2d(punt7, 0, 0, 0, 0.5, 7.2, 11, 1);
	//foto entrada al nivel 7
	if (nivel_max_completado < 11)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fuegoblock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fuego.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(-2.4, -1.7, 5);
	glTexCoord2d(1, 1);    glVertex3f(2.4, -1.7, 5);
	glTexCoord2d(1, 0);    glVertex3f(2.4, 7.5, 5);
	glTexCoord2d(0, 0);    glVertex3f(-2.4, 7.5, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, 2.35, 7.2, 11, 1);
	char punt8[10];
	sprintf(punt8, "%d", this->puntuacion_niveles[8]);
	renderstring2d(punt8, 0, 0, 0, 4.5, 7.2, 11, 1);
	//foto entrada al nivel 8
	if (nivel_max_completado < 12)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fuegoblock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fuego.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(2.4, -1.7, 5);
	glTexCoord2d(1, 1);    glVertex3f(7.2, -1.7, 5);
	glTexCoord2d(1, 0);    glVertex3f(7.2, 7.5, 5);
	glTexCoord2d(0, 0);    glVertex3f(2.4, 7.5, 5);
	glEnd();
	//Texto de puntuacion
	renderstring2d((char*)"Puntuacion: ", 0, 0, 0, 6, 7.2, 11, 1);
	char punt9[10];
	sprintf(punt9, "%d", this->puntuacion_niveles[9]);
	renderstring2d(punt9, 0, 0, 0, 8, 7.2, 11, 1);
	//foto entrada al nivel 9
	if (nivel_max_completado < 13)//dibuja la puerta bloqueada en caso de que no se haya completado el nivel anterior
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fuegoblock.png").id);
	else glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fuego.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);    glVertex3f(7.2, -1.7, 5);
	glTexCoord2d(1, 1);    glVertex3f(12, -1.7, 5);
	glTexCoord2d(1, 0);    glVertex3f(12, 7.5, 5);
	glTexCoord2d(0, 0);    glVertex3f(7.2, 7.5, 5);
	glEnd();
	glutPostRedisplay();
}

void Menu::menutienda()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0, 7.5, 0, // hacia que punto mira (0,y,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
	//Fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);
	glVertex3f(-15, -15, -10);
	glTexCoord2d(1, 1);
	glVertex3f(15, -15, -10);
	glTexCoord2d(1, 0);
	glVertex3f(15, 20, -10);
	glTexCoord2d(0, 0);
	glVertex3f(-15, 20, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//boton retroceso
	s.back();

	//Imprimir texto de las monedas que tienes
			renderstring2d((char*)"Cartera: ", 255, 255, 255, -8, 13, 11, 1);
			char cartera[10];
			sprintf(cartera, "%d", this->monedas);
			renderstring2d(cartera, 255, 255, 255, -6, 13, 11, 1);

	//Imprimir titulo Tienda
			ETSIDI::setFont("fuentes/Minercraftory.ttf", 20);
			ETSIDI::setTextColor(255, 255, 255);
			ETSIDI::printxy("TIENDA", -2.5, 15, 0);

			c.dibuja(1);

	//Carteles de cada pelota con distancia fija entre cada uno
	s.cartel(-12, 2, -1);
	renderstring2d((char*)"SS", 0, 0, 0, -10.15, 1.2, 1, 1);
	s.cartel(-6.75, 2, -1);
	renderstring2d((char*)"GS", 0, 0, 0, -5.2, 1.2, 1, 1);
	s.cartel(-1.5, 2, -1);
	renderstring2d((char*)"MH", 0, 0, 0, -0.3, 1.2, 1, 1);
	s.cartel(3.7, 2, -1);
	renderstring2d((char*)"RC", 0, 0, 0, 4.6, 1.2, 1, 1);
	s.cartel(8.9, 2, -1);
	renderstring2d((char*)"CT", 0, 0, 0, 9.4, 1.2, 1, 1);

			if (tienda) //Opcion de compra de pelotas de la tienda
			{
				s.cruz();
				switch (tienda)
				{
					//Imprimir precio de pelota 1 y cambiar color si hay puntuacion suficiente, Imprimir mensaje si no se puede comprar
					//Si el elemento esta comprado imprimir mensaje comprado y no gastar monedas en su seleccion
				case Cartel1: s.cartel(-1.5, 9, 10);					
					if(comprado1) renderstring2d((char*)"Comprado", 0, 0, 0, -0.75, 7.8, 11, 1);
						else renderstring2d((char*)"Monedas: 500", 0, 0, 0, -1.2, 7.8, 11, 1);
					if (compra)
					{
						if (comprado1) { r = 255; g = 0; b = 0; tienda = TiendaPrincipal; compra = false; }
						else if (monedas_minimo(Cartel1)) { r = 255; g = 0; b = 0; comprado1 = true; tienda = TiendaPrincipal; compra = false; }
						else renderstring2d((char*)"Monedas Insuficientes", 255, 0, 0, -2, 8.15, 11, 1);

			}
			break;
			//Imprimir precio de pelota 2 y cambiar color si hay puntuacion suficiente, Imprimir mensaje si no se puede comprar
			//Si el elemento esta comprado imprimir mensaje comprado y no gastar monedas en su seleccion
		case Cartel2: s.cartel(-1.5, 9, 10);
			if (comprado2) renderstring2d((char*)"Comprado", 0, 0, 0, -0.75, 7.8, 11, 1);
			else renderstring2d((char*)"Monedas: 750", 0, 0, 0, -1.2, 7.8, 11, 1);
			if (compra)
			{
				if (comprado2) { r = 255; g = 0; b = 255; tienda = TiendaPrincipal; compra = false; }
				else if (monedas_minimo(Cartel2)) { r = 255; g = 0; b = 255; comprado2 = true; tienda = TiendaPrincipal; compra = false; }
				else renderstring2d((char*)"Monedas Insuficientes", 255, 0, 0, -2, 8.15, 11, 1);

			}
			break;
			//Imprimir precio de pelota 3 y cambiar color si hay puntuacion suficiente, Imprimir mensaje si no se puede comprar
			//Si el elemento esta comprado imprimir mensaje comprado y no gastar monedas en su seleccion
		case Cartel3: s.cartel(-1.5, 9, 10);
			if (comprado3) renderstring2d((char*)"Comprado", 0, 0, 0, -0.75, 7.8, 11, 1);
			else renderstring2d((char*)"Monedas: 1000", 0, 0, 0, -1.2, 7.8, 11, 1);
			if (compra)
			{
				if (comprado3) { r = 255; g = 255; b = 0; tienda = TiendaPrincipal; compra = false; }
				else if (monedas_minimo(Cartel3)) { r = 255; g = 255; b = 0; comprado3 = true; tienda = TiendaPrincipal; compra = false; }
				else renderstring2d((char*)"Monedas Insuficientes", 255, 0, 0, -2, 8.15, 11, 1);

			}

			break;
			//Imprimir precio de pelota 4 y cambiar color si hay puntuacion suficiente, Imprimir mensaje si no se puede comprar
			//Si el elemento esta comprado imprimir mensaje comprado y no gastar monedas en su seleccion
		case Cartel4: s.cartel(-1.5, 9, 10);
			if (comprado4) renderstring2d((char*)"Comprado", 0, 0, 0, -0.75, 7.8, 11, 1);
			else renderstring2d((char*)"Monedas: 750", 0, 0, 0, -1.2, 7.8, 11, 1);
			if (compra)
			{
				if (comprado4) { r = 0; g = 255; b = 0; tienda = TiendaPrincipal; compra = false; }
				else if (monedas_minimo(Cartel4)) { r = 0; g = 255; b = 0; comprado4 = true; tienda = TiendaPrincipal; compra = false; }
				else renderstring2d((char*)"Monedas Insuficientes", 255, 0, 0, -2, 8.15, 11, 1);

			}

			break;
			//Imprimir precio de pelota 5 y cambiar color si hay puntuacion suficiente, Imprimir mensaje si no se puede comprar
			//Si el elemento esta comprado imprimir mensaje comprado y no gastar monedas en su seleccion
		case Cartel5: s.cartel(-1.5, 9, 10);
			if (comprado5) renderstring2d((char*)"Comprado", 0, 0, 0, -0.75, 7.8, 11, 1);
			else renderstring2d((char*)"Monedas: 500", 0, 0, 0, -1.2, 7.8, 11, 1);
			if (compra)
			{
				if (comprado5) { r = 0; g = 0; b = 255; tienda = TiendaPrincipal; compra = false; }
				else if (monedas_minimo(Cartel5)) { r = 0; g = 0; b = 255; comprado5 = true; tienda = TiendaPrincipal; compra = false; }
				else renderstring2d((char*)"Monedas Insuficientes", 255, 0, 0, -2, 8.15, 11, 1);

			}

			break;
		}
	}
	glPopMatrix;
	//Situa las pelotas en la primera posicion y las rota un angulo variable
	glTranslatef(-10, 6.9, 0);
	glRotatef(e2.angulo, 1, 0, 0);

	//Pelota 1 roja
	e2.setColor(255, 0, 0);
	e2.dibuja(); 

	//Pelota 2 morada
	glTranslatef(5, 0, 0);
	e2.setColor(255, 0, 255);
	e2.dibuja();

	//Pelota 3 amarilla
	glTranslatef(5, 0, 0);
	e2.setColor(255, 255, 0);
	e2.dibuja();

	//Pelota 4 verde
	glTranslatef(5, 0, 0);
	e2.setColor(0, 255, 0);
	e2.dibuja();

	//Pelota 5 azul
	glTranslatef(5, 0, 0);
	e2.setColor(0, 0, 255);
	e2.dibuja();
	glPushMatrix;
	glutPostRedisplay();
}
void Menu::menucreditos()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0, 7.5, 0, // hacia que punto mira (0,y,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
	//Fondo
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);
	glVertex3f(-15, -15, -10);
	glTexCoord2d(1, 1);
	glVertex3f(15, -15, -10);
	glTexCoord2d(1, 0);
	glVertex3f(15, 20, -10);
	glTexCoord2d(0, 0);
	glVertex3f(-15, 20, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//boton retroceso
	s.back();

	//Creditos

	renderstring2d((char*)"CREDITOS", 255, 255, 255, -2.1, credy, 0, 0);
	renderstring2d((char*)"INTEGRANTES DEL GRUPO", 255, 255, 255, -4.1, credy - 1.25, 0, 2);
	renderstring2d((char*)"MATEO AGUSTONI GOYCOA", 255, 255, 255, -2.75, credy - 2, 0, 3);
	renderstring2d((char*)"ISMAEL FERNANDEZ DE LA COTERA LORENZO", 255, 255, 255, -5, credy - 2.5, 0, 3);
	renderstring2d((char*)"JAVIER PIO GONZALEZ ALDAY", 255, 255, 255, -3.25, credy - 3, 0, 3);
	renderstring2d((char*)"ADRIAN GONZALEZ DENIA", 255, 255, 255, -2.75, credy - 3.5, 0, 3);
	renderstring2d((char*)"JORGE GOMEZ-PAMO GONZALEZ-CELA", 255, 255, 255, -3.9, credy - 4, 0, 3);
	renderstring2d((char*)"COORDINADOR DE LA ASIGNATURA", 255, 255, 255, -5.25, credy - 5.75, 0, 2);
	renderstring2d((char*)"MIGUEL HERNANDO GUTIERREZ", 255, 255, 255, -3.25, credy - 6.5, 0, 3);
	renderstring2d((char*)"COORDINADOR DEL TRABAJO", 255, 255, 255, -4.5, credy - 8.25, 0, 2);
	renderstring2d((char*)"CRISTOBAL TAPIA GARCIA", 255, 255, 255, -2.85, credy - 9, 0, 3);
	renderstring2d((char*)"EFECTOS DE SONIDO", 255, 255, 255, -3.25, credy - 10.75, 0, 2);
	renderstring2d((char*)"GUILLERMO UBEDA ROMERO", 255, 255, 255, -2.85, credy - 11.5, 0, 3);
	glutPostRedisplay();
}
void Menu::menupausa()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0, 7.5, 0, // hacia que punto mira (0,y,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

	//boton retroceso
	s.back();

	glColor3ub(255, 255, 255);
	//Dibujo de los carteles del menu
	s.submenu();

	//Fondo
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/menu.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);
	glVertex3f(-15, -15, -10);
	glTexCoord2d(1, 1);
	glVertex3f(15, -15, -10);
	glTexCoord2d(1, 0);
	glVertex3f(15, 20, -10);
	glTexCoord2d(0, 0);
	glVertex3f(-15, 20, -10);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	//Opciones dentro del menu
	if (sonido)
		renderstring2d((char*)"SONIDOS: ON", 0, 0, 0, -2.3, 10, -1, 0);
	else
		renderstring2d((char*)"SONIDOS: OFF", 0, 0, 0, -2.3, 10, -1, 0);
	if (guardar)
		renderstring2d((char*)"GUARDADO", 0, 0, 0, -2.1, 6.5, -1, 0);
	else
		renderstring2d((char*)"GUARDAR", 0, 0, 0, -2.1, 6.5, -1, 0);
	renderstring2d((char*)"MENU PRINCIPAL", 0, 0, 0, -3.1, 3, -1, 0);


	//Titula de la pantalla PAUSA
	ETSIDI::setFont("fuentes/Minercraftory.ttf", 20); 
	ETSIDI::setTextColor(255, 255, 255);
	glTranslatef(0.4, 0, 0);
	ETSIDI::printxy("PAUSA", -2, 15, 5);
	glTranslatef(-0.4, 0, 0);

	glutPostRedisplay();
}
void Menu::mueveprincipal()
{
	//Interaccion de movimiento de las letras del logo

	if (z1 > -34) //Circulo principal
		z1 -= 2.1;

	if (z1 < -35.5 and z2 > -25) //Letra E
		z2 -= 2.3;

	if (z2 < -25 and z > -25) //Letra F
		z -= 2.3;

	if (z < -25 and z3 > 10) //Palabra SPORTS
		z3 -= 2.3;

	Interaccion::rebote(e, c);
	e.mueve(0.05);
}
void Menu::muevetienda() //Rotar las pelotas de la tienda en el estante
{
	e2.rota();
}
void Menu::muevecreditos() //Accion de los creditos (se mueven hacia arriba)
{
	credy += 0.05;
}

bool Menu::monedas_minimo(Tiendas t) //Activa variable compra en caso de que las monedas sean mayor a la necesaria, y escribir un mensaje en caso contrario
{
	switch (t)
	{
	case Cartel1: if (this->monedas >= 500) { this->monedas -= 500; return true; } //Pelota 1 precio 500 monedas, restar las monedas en caso de compra
				else  return false;
		break;
	case Cartel2: if (this->monedas >= 750) { this->monedas -= 750; return true; } //Pelota 2 precio 750 monedas, restar las monedas en caso de compra
				else  return false;
		break;
	case Cartel3: if (this->monedas >= 1000) { this->monedas -= 1000; return true; } //Pelota 3 precio 1000 monedas, restar las monedas en caso de compra
				else  return false;
		break;
	case Cartel4: if (this->monedas >= 750) { this->monedas -= 750; return true; } //Pelota 4 precio 750 monedas, restar las monedas en caso de compra
				else  return false;
		break;
	case Cartel5: if (this->monedas >= 500) { this->monedas -= 500; return true; } //Pelota 5 precio 500 monedas, restar las monedas en caso de compra
				else  return false;
		break;
	}
}

//Variables de paso entre coordiador y menu

int Menu::get_color(int a) //Obtener el color de la pelota inicial para pasarla a mundo
{
	switch (a)
	{
	case 1:
		return this->r; break;
	case 2:
		return this->g; break;
	case 3:
		return this->b; break;
	}
}

void Menu::set_Tienda(int t) //saber que cartel de la tienda se ha pulsado para que aparezca la opcion de comprar
{
	switch (t)
	{
	case 0: tienda = TiendaPrincipal; break;
	case 1: tienda = Cartel1; break;
	case 2: tienda = Cartel2; break;
	case 3: tienda = Cartel3; break;
	case 4: tienda = Cartel4; break;
	case 5: tienda = Cartel5; break;
	}
}

void Menu::activar_compra(bool c) //Activar el cartel de compra de cada pelota
{
	compra = c;
}

void Menu::set_monedas(int aux) //Introducir en menu las monedas del mundo como incrementos
{
	monedas += aux;
}

void Menu::set_monedasini(int aux) //Introducir en menu las monedas del fichero
{
	monedas = aux;
}

float Menu::get_monedas() //Obtener las monedas
{
	return monedas;
}

bool Menu::get_compras(int cartel) //Pasar la variable de comprado a coordinador para guardarlo en el fichero
{
	switch (cartel)
	{
	case 1: return comprado1; break;
	case 2: return comprado2; break;
	case 3: return comprado3; break;
	case 4: return comprado4; break;
	case 5: return comprado5; break;
	}
}
void Menu::set_compras(bool c1, bool c2, bool c3, bool c4, bool c5) //Recoger del fichero las compras anteriores;
{
	comprado1 = c1;
	comprado2 = c2;
	comprado3 = c3;
	comprado4 = c4;
	comprado5 = c5;
}
void Menu::set_sonido(bool s) //Establecer el sonido en funcion del menu de pausa
{
	sonido = s;
}
void Menu::set_guardar(bool g) //Establecer la variable de guardado
{
	guardar = g;
}

void Menu::set_nivelmax(int n) //Saber cual es el nivel maximo que se ha conseguido en la partida para desbloquear niveles
{
	nivel_max_completado = n;
}

void Menu::set_puntuacion() //Obtener la puntuacion total del juego
{
	puntuacion = 0;
	for (int i = 0; i < 10; i++)
		puntuacion += puntuacion_niveles[i];
}

void Menu::puntuacion_nivel(int i, int p) //Obtener la puntuacion de cada nivel
{
	if(puntuacion_niveles[i] < p)
	puntuacion_niveles[i] = p;
}

int Menu::get_puntuacion(int i) //Pasar la puntuacion de cada nivel a coordinador para guardar en el fichero
{
	
		return puntuacion_niveles[i];
}


