#include "Bloque.h"
#include "freeglut.h"
#include <math.h>
#define Pi 3.1415926535897

Bloque::Bloque()
{
	tipo = 0;
	rotacion = 0;
	posicion.x = posicion.y = posicion.z = 0;;
}
Bloque::Bloque(int tipo, int rotacion, Int3D pos)
{
	this->tipo = tipo;
	this->rotacion = rotacion;
	posicion.x = pos.x;
	posicion.y = pos.y;
	posicion.z = pos.z;
}

void Bloque::dibujar(bool wire)
{
	glDisable(GL_LIGHTING);
	//Se traslada a la posicion del bloque, y se rota el sistema de referencia para dibujarlo bien orientado
	glTranslatef(posicion.x, posicion.y, posicion.z);
	glRotatef(rotacion * 90, 0, 1, 0);
	glColor3ub(200, 0, 0);//Color general

	switch (tipo) {
	case 0:	//Aire
		break;

	case 10://Entrada
		//Bloque y lineas exteriores
		glutSolidCube(1);
		glColor3ub(0, 0, 0);
		glutWireCube(1.002);

		//Flechas (1 por cada lado)
		glColor3ub(255, 255, 0);

		glBegin(GL_POLYGON);
		glVertex3f(-0.4, 0.501, 0.05);
		glVertex3f(-0.4, 0.501, -0.05);
		glVertex3f(0.0, 0.501, -0.05);
		glVertex3f(0.0, 0.501, 0.05);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.501, -0.25);
		glVertex3f(0.0, 0.501, 0.25);
		glVertex3f(0.4, 0.501, 0.0);
		glEnd();

		glRotatef(90, 1, 0, 0);

		glBegin(GL_POLYGON);
		glVertex3f(-0.4, 0.501, 0.05);
		glVertex3f(-0.4, 0.501, -0.05);
		glVertex3f(0.0, 0.501, -0.05);
		glVertex3f(0.0, 0.501, 0.05);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.501, -0.25);
		glVertex3f(0.0, 0.501, 0.25);
		glVertex3f(0.4, 0.501, 0.0);
		glEnd();

		glRotatef(90, 1, 0, 0);

		glBegin(GL_POLYGON);
		glVertex3f(-0.4, 0.501, 0.05);
		glVertex3f(-0.4, 0.501, -0.05);
		glVertex3f(0.0, 0.501, -0.05);
		glVertex3f(0.0, 0.501, 0.05);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.501, -0.25);
		glVertex3f(0.0, 0.501, 0.25);
		glVertex3f(0.4, 0.501, 0.0);
		glEnd();

		glRotatef(90, 1, 0, 0);

		glBegin(GL_POLYGON);
		glVertex3f(-0.4, 0.501, 0.05);
		glVertex3f(-0.4, 0.501, -0.05);
		glVertex3f(0.0, 0.501, -0.05);
		glVertex3f(0.0, 0.501, 0.05);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex3f(0.0, 0.501, -0.25);
		glVertex3f(0.0, 0.501, 0.25);
		glVertex3f(0.4, 0.501, 0.0);
		glEnd();

		glRotatef(90, 1, 0, 0);
		break;

	case 11://Meta
	{
		//Traslaciones para comodidad al dibujar
		glTranslatef(-0.5, -0.5, -0.5);
		glTranslatef(0.05, 0.05, 0.05);

		bool color = 0;

		//Se dibujan 10*10*10 minibloques de colores alternativos blanco/negro
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 10; k++) {
					if (color)glColor3ub(255, 255, 255);
					else glColor3ub(0, 0, 0);

					glutSolidCube(0.1);
					glTranslatef(0, 0, 0.1);

					color = !color;
				}
				glTranslatef(0, 0.1, -1);
				color = !color;
			}
			glTranslatef(0.1, -1, 0);
			color = !color;
		}

		//Vuelta al sistema de referencia normal
		glTranslatef(-0.05, -0.05, -0.05);
		glTranslatef(-0.5, 0.5, 0.5);
		break;
	}
	case 12://Meta bloqueada
		//Bloque base
		glColor3ub(0, 0, 0);
		glutWireCube(1.01);
		glColor3ub(255, 255, 255);
		glutSolidCube(1);

		//Candados
		for (int i = 0; i < 4; i++) {
			glRotatef(90, 0, 1, 0);
			glTranslatef(0.501, 0, 0);

			//Cuerpo del candado
			glColor3ub(240, 190, 100);
			glBegin(GL_POLYGON);
			glVertex3f(0, 0.1, -0.2);
			glVertex3f(0, -0.3, -0.2);
			glVertex3f(0, -0.3, 0.2);
			glVertex3f(0, 0.1, 0.2);
			glEnd();

			//Agujero cerradura
			glTranslatef(0.01, -0.05, 0);
			glColor3ub(0, 0, 0);
			glBegin(GL_POLYGON);
			for (float i = 0; i < 2 * Pi; i += 0.01)
				glVertex3f(0, 0.05 * cos(i), 0.05 * sin(i));
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0.02);
			glVertex3f(0, -0.15, 0.02);
			glVertex3f(0, -0.15, -0.02);
			glVertex3f(0, 0, -0.02);
			glEnd();
			glTranslatef(-0.01, 0.15, 0);

			//Aro
			glColor3ub(200, 190, 180);
			glBegin(GL_POLYGON); //Pata lateral
			glVertex3f(0, 0, 0.15);
			glVertex3f(0, 0.1, 0.15);
			glVertex3f(0, 0.1, 0.1);
			glVertex3f(0, 0, 0.1);
			glEnd();
			for (float j = 0.1; j <= 0.15; j += 0.001) { //Circulo externo
				glBegin(GL_LINE_STRIP);
				for (float i = 0; i <= Pi; i += 0.01)
					glVertex3f(0, j * sin(i) + 0.1, j * cos(i));
				glEnd();
			}
			glBegin(GL_POLYGON); //Pata lateral
			glVertex3f(0, 0, -0.15);
			glVertex3f(0, 0.1, -0.15);
			glVertex3f(0, 0.1, -0.1);
			glVertex3f(0, 0, -0.1);
			glEnd();

			glTranslatef(-0.501, -0.1, 0);
		}
		break;
	case 13://Muerte
		//Esfera base
		glutSolidSphere(0.3, 50, 50);

		//Pinchos
		glColor3ub(200, 200, 200);
		for (int i = 0; i < 4; i++) {
			glRotatef(360 * i / 4, 0, 1, 0);
			glTranslatef(0, 0, 0.27);
			glutSolidCone(0.08, 0.2, 50, 50);
			glTranslatef(0, 0, -0.27);
			glRotatef(-360 * i / 4, 0, 1, 0);
		}
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, 0.27);
		glutSolidCone(0.08, 0.2, 50, 50);
		glTranslatef(0, 0, -0.27);
		glRotatef(180, 1, 0, 0);
		glTranslatef(0, 0, 0.27);
		glutSolidCone(0.08, 0.2, 50, 50);
		glTranslatef(0, 0, -0.27);
		glRotatef(90, 1, 0, 0);
		break;
	case 1://Recta
		if (!wire) {
			//Superficie superior
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, 0.5, -0.5);
			glVertex3f(0.5, 0.5, -0.5);
			glVertex3f(0.5, 0.5, 0.5);
			glVertex3f(-0.5, 0.5, 0.5);
			glEnd();

			//Superficie inferior
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glEnd();

			//Superficies laterales
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, 0.5, -0.5);
			glVertex3f(0.5, 0.5, 0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, -0.5, 0.5);
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(-0.5, 0.5, -0.5);
			glVertex3f(-0.5, 0.5, 0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(-0.5, 0.5, -0.5);
			glVertex3f(0.5, 0.5, -0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glVertex3f(-0.5, 0.5, 0.5);
			glVertex3f(0.5, 0.5, 0.5);
			glEnd();

			glColor3ub(0, 0, 0);
		}

		//Lineas exteriores
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.501, -0.501, -0.501);
		glVertex3f(0.501, -0.501, -0.501);
		glVertex3f(0.501, -0.501, 0.501);
		glVertex3f(-0.501, -0.501, 0.501);
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.501, 0.501, -0.501);
		glVertex3f(0.501, 0.501, -0.501);
		glVertex3f(0.501, 0.501, 0.501);
		glVertex3f(-0.501, 0.501, 0.501);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.501, -0.501, 0.501);
		glVertex3f(0.501, 0.501, 0.501);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.501, -0.501, -0.501);
		glVertex3f(0.501, 0.501, -0.501);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.501, -0.501, -0.501);
		glVertex3f(-0.501, 0.501, -0.501);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.501, -0.501, 0.501);
		glVertex3f(-0.501, 0.501, 0.501);
		glEnd();

		//Lineas centrales
		glBegin(GL_LINES);
		glVertex3f(-0.501, 0.51, -0.3);
		glVertex3f(0.501, 0.51, -0.3);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.501, 0.51, 0.3);
		glVertex3f(0.501, 0.51, 0.3);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.3, 0.51, -0.501);
		glVertex3f(-0.3, 0.51, 0.501);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.3, 0.51, -0.501);
		glVertex3f(0.3, 0.51, 0.501);
		glEnd();
		break;

	case 2://Curva
		glTranslatef(-0.5, -0.5, -0.5);

		if (!wire) {
			//Superficie lateral curva
			glBegin(GL_POLYGON);
			for (float j = 0.01; j < 1; j += 0.01) {
				for (float i = Pi / 2; i > 0; i -= 0.01) {
					glVertex3f(cos(i), j, sin(i));
				}
			}
			glEnd();

			//Superficie inferior
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, 1);
			for (float i = Pi / 2; i > 0; i -= 0.01) {
				glVertex3f(cos(i), 0, sin(i));
			}
			glEnd();

			//Superficie superior
			glBegin(GL_POLYGON);
			glVertex3f(0, 1, 0);
			glVertex3f(0, 1, 1);
			for (float i = Pi / 2; i > 0; i -= 0.01) {
				glVertex3f(cos(i), 1, sin(i));
			}
			glEnd();

			//Superficies laterales rectas
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(0, 1, 1);
			glVertex3f(0, 0, 1);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 1, 0);
			glVertex3f(1, 1, 0);
			glVertex3f(1, 0, 0);
			glEnd();

			glColor3ub(0, 0, 0);
		}
		
		//Lineas exteriores rectas
		glBegin(GL_LINES);
		glVertex3f(-0.01, -0.01, -0.01);
		glVertex3f(-0.01, 1.01, -0.01);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.01, -0.01, -0.01);
		glVertex3f(-0.01, 1.01, -0.01);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(1.01, -0.01, -0.01);
		glVertex3f(1.01, 1.01, -0.01);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.01, -0.01, 1.01);
		glVertex3f(-0.01, 1.01, 1.01);
		glEnd();

		//Lineas exteriores curvas
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.01, -0.01, -0.01);
		glVertex3f(-0.01, -0.01, 1.01);
		for (float i = Pi / 2; i > 0; i -= 0.01) {
			glVertex3f(1.01*cos(i), -0.01, 1.01*sin(i));
		}
		glEnd();
		glBegin(GL_LINE_LOOP);
		glVertex3f(-0.01, 1.01, -0.01);
		glVertex3f(-0.01, 1.01, 1.01);
		for (float i = Pi / 2; i > 0; i -= 0.01) {
			glVertex3f(1.01*cos(i), 1.01, 1.01*sin(i));
		}
		glEnd();

		//Lineas centrales direccion
		glBegin(GL_LINE_STRIP);
		for (float i = Pi / 2; i > 0; i -= 0.01) {
			glVertex3f(0.2 * cos(i), 1.01, 0.2 * sin(i));
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (float i = Pi / 2; i > 0; i -= 0.01) {
			glVertex3f(0.8 * cos(i), 1.01, 0.8 * sin(i));
		}
		glEnd();

		glBegin(GL_LINE_STRIP);
		for (float i = Pi / 2; i > 0; i -= 0.01) {
			glVertex3f(0.2 * cos(i), -0.01, 0.2 * sin(i));
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (float i = Pi / 2; i > 0; i -= 0.01) {
			glVertex3f(0.8 * cos(i), -0.01, 0.8 * sin(i));
		}
		glEnd();

		glTranslatef(0.5, 0.5, 0.5);
		break;

	case 3://Rampa
		if (!wire) {
			//Flanco superior
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glVertex3f(0.5, 0.5, 0.5);
			glVertex3f(0.5, 0.5, -0.5);
			glEnd();
			//Superficies laterales
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, -0.5, 0.5);
			glVertex3f(0.5, 0.5, 0.5);
			glVertex3f(0.5, -0.5, 0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(0.5, 0.5, -0.5);
			glVertex3f(0.5, -0.5, -0.5);
			glEnd();
			//Superficie trasera
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, 0.5, -0.5);
			glVertex3f(0.5, 0.5, 0.5);
			glEnd();
			//Superficie inferior
			glBegin(GL_POLYGON);
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glEnd();

			glColor3ub(0, 0, 0);
		}

		//Lineas exteriores
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(-0.5, -0.5, 0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.5, 0.5, -0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.5, -0.5, -0.5);
		glVertex3f(0.5, 0.5, -0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, 0.5, 0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.5, -0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, -0.5);
		glEnd();

		//Lineas centrales
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.49, 0.3);
		glVertex3f(0.5, 0.51, 0.3);
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(-0.5, -0.49, -0.3);
		glVertex3f(0.5, 0.51, -0.3);
		glEnd();
		break;

	case 4://Trampolin
		if (!wire) {
			//Prisma inferior
			glBegin(GL_POLYGON);//Tapa inferior
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glEnd();
			glBegin(GL_POLYGON);//Tapa superior
			glVertex3f(-0.5, -0.3, -0.5);
			glVertex3f(0.5, -0.3, -0.5);
			glVertex3f(0.5, -0.3, 0.5);
			glVertex3f(-0.5, -0.3, 0.5);
			glEnd();
			glBegin(GL_POLYGON);//Tapas laterales
			glVertex3f(-0.5, -0.5, -0.5);
			glVertex3f(-0.5, -0.3, -0.5);
			glVertex3f(-0.5, -0.3, 0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.3, -0.5);
			glVertex3f(-0.5, -0.3, -0.5);
			glVertex3f(-0.5, -0.5, -0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, -0.5);
			glVertex3f(0.5, -0.3, -0.5);
			glVertex3f(0.5, -0.3, 0.5);
			glVertex3f(0.5, -0.5, 0.5);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.5, -0.5, 0.5);
			glVertex3f(0.5, -0.3, 0.5);
			glVertex3f(-0.5, -0.3, 0.5);
			glVertex3f(-0.5, -0.5, 0.5);
			glEnd();

			//Prisma superior
			glBegin(GL_POLYGON);//Tapa inferior
			glVertex3f(-0.2, 0.4, -0.2);
			glVertex3f(0.2, 0.4, -0.2);
			glVertex3f(0.2, 0.4, 0.2);
			glVertex3f(-0.2, 0.4, 0.2);
			glEnd();
			glBegin(GL_POLYGON);//Tapa superior
			glVertex3f(-0.2, 0.5, -0.2);
			glVertex3f(0.2, 0.5, -0.2);
			glVertex3f(0.2, 0.5, 0.2);
			glVertex3f(-0.2, 0.5, 0.2);
			glEnd();
			glBegin(GL_POLYGON);//Tapas laterales
			glVertex3f(-0.2, 0.4, -0.2);
			glVertex3f(-0.2, 0.5, -0.2);
			glVertex3f(-0.2, 0.5, 0.2);
			glVertex3f(-0.2, 0.4, 0.2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.2, 0.4, -0.2);
			glVertex3f(0.2, 0.5, -0.2);
			glVertex3f(-0.2, 0.5, -0.2);
			glVertex3f(-0.2, 0.4, -0.2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.2, 0.4, -0.2);
			glVertex3f(0.2, 0.5, -0.2);
			glVertex3f(0.2, 0.5, 0.2);
			glVertex3f(0.2, 0.4, 0.2);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex3f(0.2, 0.4, 0.2);
			glVertex3f(0.2, 0.5, 0.2);
			glVertex3f(-0.2, 0.5, 0.2);
			glVertex3f(-0.2, 0.4, 0.2);
			glEnd();

			glColor3ub(0, 0, 0);
		}

		//Lineas inferiores
		glBegin(GL_LINES);//Tapa superior
		glVertex3f(0.501, -0.299, -0.501);
		glVertex3f(0.501, -0.299, 0.501);
		glVertex3f(-0.501, -0.299, -0.501);
		glVertex3f(-0.501, -0.299, 0.501);
		glVertex3f(-0.501, -0.299, 0.501);
		glVertex3f(0.501, -0.299, 0.501);
		glVertex3f(-0.501, -0.299, -0.501);
		glVertex3f(0.501, -0.299, -0.501);
		glEnd();
		glBegin(GL_LINES);//Tapa inferior
		glVertex3f(0.501, -0.501, -0.501);
		glVertex3f(0.501, -0.501, 0.501);
		glVertex3f(-0.501, -0.501, -0.501);
		glVertex3f(-0.501, -0.501, 0.501);
		glVertex3f(-0.501, -0.501, 0.501);
		glVertex3f(0.501, -0.501, 0.501);
		glVertex3f(-0.501, -0.501, -0.501);
		glVertex3f(0.501, -0.501, -0.501);
		glEnd();
		glBegin(GL_LINES);//Tapas laterales
		glVertex3f(-0.501, -0.501, -0.501);
		glVertex3f(-0.501, -0.299, -0.501);
		glVertex3f(0.501, -0.501, 0.501);
		glVertex3f(0.501, -0.299, 0.501);
		glVertex3f(-0.501, -0.501, 0.501);
		glVertex3f(-0.501, -0.299, 0.501);
		glVertex3f(0.501, -0.501, -0.501);
		glVertex3f(0.501, -0.299, -0.501);
		glEnd();

		//Lineas superiores
		glBegin(GL_LINES);//Tapa inferior
		glVertex3f(0.201, 0.399, -0.201);
		glVertex3f(0.201, 0.399, 0.201);
		glVertex3f(-0.201, 0.399, -0.201);
		glVertex3f(-0.201, 0.399, 0.201);
		glVertex3f(-0.201, 0.399, 0.201);
		glVertex3f(0.201, 0.399, 0.201);
		glVertex3f(-0.201, 0.399, -0.201);
		glVertex3f(0.201, 0.399, -0.201);
		glEnd();
		glBegin(GL_LINES);//Tapa superior
		glVertex3f(0.201, 0.501, -0.201);
		glVertex3f(0.201, 0.501, 0.201);
		glVertex3f(-0.201, 0.501, -0.201);
		glVertex3f(-0.201, 0.501, 0.201);
		glVertex3f(-0.201, 0.501, 0.201);
		glVertex3f(0.201, 0.501, 0.201);
		glVertex3f(-0.201, 0.501, -0.201);
		glVertex3f(0.201, 0.501, -0.201);
		glEnd();
		glBegin(GL_LINES);//Tapas laterales
		glVertex3f(-0.201, 0.501, -0.201);
		glVertex3f(-0.201, 0.399, -0.201);
		glVertex3f(0.201, 0.501, 0.201);
		glVertex3f(0.201, 0.399, 0.201);
		glVertex3f(-0.201, 0.501, 0.201);
		glVertex3f(-0.201, 0.399, 0.201);
		glVertex3f(0.201, 0.501, -0.201);
		glVertex3f(0.201, 0.399, -0.201);
		glEnd();

		//Muelle
		glColor3ub(100, 100, 100);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < 10 * Pi; i += 0.01)
			glVertex3f(0.2 * cos(i), -0.3 + i * 0.7 / (10 * Pi), 0.2 * sin(i));
		glEnd();
		break;

	case 5: {//Bloque de rebote
			if (!wire) {
			glutSolidCube(1);

			//Circulos y cruces
			glColor3ub(0, 0, 0);
			double radio, calx, caly;

			glTranslated(0, 0.5, 0);//Y+
			//for (radio = 0.1; radio < 0.51; radio += 0.09) {
			//	glBegin(GL_POINTS);
			//	for (double i = 0.0; i < 10; i += 0.001) {
			//		calx = radio * cos(i);
			//		caly = radio * sin(i);
			//		glVertex3f(calx, 0, caly);
			//	}
			//	glEnd();
			//}
			//glBegin(GL_LINES);
			//glVertex3f(0.0, 0.01, -0.5);
			//glVertex3f(0.0, 0.01, 0.5);
			//glVertex3f(-0.5, 0.01, 0.0);
			//glVertex3f(0.5, 0.01, 0.0);
			//glEnd();

			glTranslated(0, -0.5, 0.5);//Z+
			for (radio = 0.1; radio < 0.51; radio += 0.09) {
				glBegin(GL_POINTS);
				for (double i = 0.0; i < 10; i += 0.001) {
					calx = radio * cos(i);
					caly = radio * sin(i);
					glVertex3f(calx, caly, 0);
				}
				glEnd();
			}
			glBegin(GL_LINES);
			glVertex3f(0.0, 0.5, 0.01);
			glVertex3f(0.0, -0.5, 0.01);
			glVertex3f(-0.5, 0.0, 0.01);
			glVertex3f(0.5, 0.0, 0.01);
			glEnd();

			glTranslated(0.5, 0, -0.5);//X+
			for (radio = 0.1; radio < 0.51; radio += 0.09) {
				glBegin(GL_POINTS);
				for (double i = 0.0; i < 10; i += 0.001) {
					calx = radio * cos(i);
					caly = radio * sin(i);
					glVertex3f(0, calx, caly);
				}
				glEnd();
			}
			glBegin(GL_LINES);
			glVertex3f(0.01, 0.5, 0.0);
			glVertex3f(0.01, -0.5, 0.0);
			glVertex3f(0.01, 0.0, 0.5);
			glVertex3f(0.01, 0.0, -0.5);
			glEnd();

			glTranslated(-0.5, -0.5, 0);//Y-
			//for (radio = 0.1; radio < 0.51; radio += 0.09) {
			//	glBegin(GL_POINTS);
			//	for (double i = 0.0; i < 10; i += 0.001) {
			//		calx = radio * cos(i);
			//		caly = radio * sin(i);
			//		glVertex3f(calx, 0, caly);
			//	}
			//	glEnd();
			//}
			//glBegin(GL_LINES);
			//glVertex3f(0.0, -0.01, -0.5);
			//glVertex3f(0.0, -0.01, 0.5);
			//glVertex3f(-0.5, -0.01, 0.0);
			//glVertex3f(0.5, -0.01, 0.0);
			//glEnd();

			glTranslated(0, 0.5, -0.5);//Z-
			for (radio = 0.1; radio < 0.51; radio += 0.09) {
				glBegin(GL_POINTS);
				for (double i = 0.0; i < 10; i += 0.001) {
					calx = radio * cos(i);
					caly = radio * sin(i);
					glVertex3f(calx, caly, 0);
				}
				glEnd();
			}
			glBegin(GL_LINES);
			glVertex3f(0.0, 0.5, -0.01);
			glVertex3f(0.0, -0.5, -0.01);
			glVertex3f(-0.5, 0.0, -0.01);
			glVertex3f(0.5, 0.0, -0.01);
			glEnd();

			glTranslated(-0.5, 0, 0.5);//X-
			for (radio = 0.1; radio < 0.51; radio += 0.09) {
				glBegin(GL_POINTS);
				for (double i = 0.0; i < 10; i += 0.001) {
					calx = radio * cos(i);
					caly = radio * sin(i);
					glVertex3f(0, calx, caly);
				}
				glEnd();
			}
			glBegin(GL_LINES);
			glVertex3f(-0.01, 0.5, 0.0);
			glVertex3f(-0.01, -0.5, 0.0);
			glVertex3f(-0.01, 0.0, 0.5);
			glVertex3f(-0.01, 0.0, -0.5);
			glEnd();

			glTranslated(0.5, 0, 0);
			glColor3ub(0, 0, 0);
		}
		glutWireCube(1.002);
		break;
	}
	default:
		glColor3ub(0, 0, 0);
		glutWireCube(1.002);
		break;
	}

	//Vuelta al sistema de referencia normal
	glRotatef(-rotacion * 90, 0, 1, 0);
	glTranslatef(-posicion.x, -posicion.y, -posicion.z);
	glEnable(GL_LIGHTING);
}

void Bloque::set_Pos(Int3D pos)
{
	posicion.x = pos.x;
	posicion.y = pos.y;
	posicion.z = pos.z;
}