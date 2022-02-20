#include "Simbolos.h"

//Dibujo principal se llama desde menu, permite dibujar tanto el boton de Play como engranaje de opciones y tienda en funcion de dos paramentros
void Simbolos::principaldibuja(GLfloat radio_interno, GLfloat radio_externo, GLfloat anchura, GLint iteraciones, GLfloat profundidad, int a, int b)
{
	//Dibujar play y opciones
	if (a)
		DrawPlay();
	if (b)
		DrawStore();

	DrawGear(radio_interno, radio_externo, anchura, iteraciones, profundidad, b);

}

void Simbolos::cartel(float x, float y, float z)
{
	//Dibujar carteles tienda
	glColor3ub(255, 255, 255); //Color blanco
	glBegin(GL_QUADS);
	glVertex3f(x, y, z);
	glVertex3f(x, y - 2, z);
	glVertex3f(x + 3, y - 2, z);
	glVertex3f(x + 3, y, z);
	glEnd();
}

void Simbolos::DrawStore()
{
	//Dibujar tienda, cuadrado y triangulo
	glColor3ub(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.2, -0.65);
	glVertex2f(-0.2, -0.10);
	glVertex2f(0.4, -0.35);
	glEnd();
	////////////////////////////////////////
	glColor3f(255, 255, 255);
	glBegin(GL_POLYGON);
	glVertex2f(-0.45, -0.75);
	glVertex2f(-0.45, 0.05);
	glVertex2f(0.55, 0.05);
	glVertex2f(0.55, -0.75);
	glEnd();
}

void Simbolos::DrawGear(GLfloat radio_interno, GLfloat radio_externo, GLfloat anchura, GLint iteraciones, GLfloat profundidad, int b)
{
	glColor3f(255, 255, 255);
	//Dibujo de engranaje de opciones, se usa tambien para el circulo del boton play
	r0 = radio_interno;
	r1 = radio_externo - profundidad / 2.0;
	r2 = radio_externo + profundidad / 2.0;

	da = 2.0 * PI / iteraciones / 4.0;

	glShadeModel(GL_FLAT);
	glNormal3f(0.0, 0.0, 1.0);

	//Dibujo de arco
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i <= iteraciones; i++)
	{
		if (b)
			angle = i * PI / iteraciones; //Semiarco
		else
			angle = i * 2 * PI / iteraciones; //Arco completo
		glVertex3f(r0 * cos(angle), r0 * sin(angle), anchura * 0.5);
		glNormal3f(0, 0, 1);
		glVertex3f(r1 * cos(angle), r1 * sin(angle), anchura * 0.5);
		glNormal3f(0, 0, 1);
		glVertex3f(r0 * cos(angle + 3 * da), r0 * sin(angle + 3 * da), anchura * 0.5);
		glNormal3f(0, 0, 1);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), anchura * 0.5);
		glNormal3f(0, 0, 1);

	}
	glEnd();


	//Dibujar dientes del engranaje
	glBegin(GL_QUADS);
	da = 2.0 * PI / iteraciones / 4.0;
	for (i = 0; i < iteraciones; i++)
	{
		angle = i * 2.0 * PI / iteraciones;
		glVertex3f(r1 * cos(angle), r1 * sin(angle), anchura * 0.5);
		glNormal3f(0, 0, 1);
		glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), anchura * 0.5);
		glNormal3f(0, 0, 1);
		glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da), anchura * 0.5);
		glNormal3f(0, 0, 1);
		glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da), anchura * 0.5);
		glNormal3f(0, 0, 1);
	}
	glEnd();
}
void Simbolos::DrawPlay()
{
	//Dibujar triangulo del boton play
	glColor3f(255, 255, 255);
	glBegin(GL_TRIANGLES);
	glVertex3f(1.5, 0.0, 0.0);
	glVertex3f(-1.0, 1.25, 0.0);
	glVertex3f(-1.0, -1.25, 0.0);
	glEnd();
}
void Simbolos::back()
{
	//Dibujar boton back en todas las pantallas que lo necesite
	//Dibujo de rectangulo y truangulo para formar flecha
	glColor3f(255, 255, 255);
	glBegin(GL_QUADS);
	glVertex3f(9, 15, 6);
	glVertex3f(9, 15.25, 6);
	glVertex3f(9.5, 15.25, 6);
	glVertex3f(9.5, 15, 6);
	glEnd();
	////////////////////////////////////////////////////
	glBegin(GL_TRIANGLES);
	glVertex3f(9.5, 14.75, 6);
	glVertex3f(10.25, 15.125, 6);
	glVertex3f(9.5, 15.5, 6);
	glEnd();
}
void Simbolos::cruz() //Dibujo de cruz para los carteles de compra de la tienda
{
	glColor3f(255, 255, 255);
	glBegin(GL_LINES);
	glVertex2d(2.4, 10);
	glVertex2d(2.6, 9.5);
	glEnd();
	glBegin(GL_LINES);
	glVertex2d(2.6, 10);
	glVertex2d(2.4, 9.5);
	glEnd();
}
void Simbolos::submenu()
{	
	glDisable(GL_LIGHTING);
	//Dibujar rectangulos de submenus
	glBegin(GL_QUADS);
	glVertex3f(-5, 9, -1);
	glVertex3f(-5, 11.5, -1);
	glVertex3f(5, 11.5, -1);
	glVertex3f(5, 9, -1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5, 5.5, -1);
	glVertex3f(-5, 8, -1);
	glVertex3f(5, 8, -1);
	glVertex3f(5, 5.5, -1);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-5, 2, -1);
	glVertex3f(-5, 4.5, -1);
	glVertex3f(5, 4.5, -1);
	glVertex3f(5, 2, -1);
	glEnd();
	glEnable(GL_LIGHTING);
}