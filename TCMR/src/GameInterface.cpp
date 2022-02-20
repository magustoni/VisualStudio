#include "GameInterface.h"

//Dibujado de todos los componentes de la interfaz del jugador
float GameInterface::calculo_vision_alpha(float lado_x, float lado_z, float pos_x, float pos_z) {
	float x = lado_x + pos_x; //Translado las coords a un sitema de referencia situado en el centro del prisma
	float z = lado_z + pos_z;
	float alpha;

	if ((x<0) && (z>0)) {
		alpha = (180.0 / PI) * (atan2(x,z));
		return alpha;
	}
	else if ((x<0) && (z<0)) {
		alpha = (180.0 / PI) * (atan2(z, x));
		return 90.0 + alpha;
	}
	else if ((x>0) && (z<0)) {
		alpha = (180.0 / PI) * (atan2(x, z));
		return 180.0 + alpha;
	}
	else if ((x>0) && (z>0)) {
		alpha = (180.0 / PI) * (atan2(z, x));
		return 270.0 + alpha;
	}
	else if ((x == 0) && (z > 0)) {
		return 0.0;
	}
	else if ((x < 0) && (z == 0)) {
		return 90.0;
	}
	else if ((x == 0) && (z < 0)) {
		return 180.0;
	}
	else if ((x > 0) && (z == 0)) {
		return 270.0;
	}

	/*Esta función tiene como objetivo el cáculo del ángulo de la primera rotación respecto al eje Y 
	del sistema de referencia del mundo para el dibujado en tiempo de ejecución el inventario en la 
	vista del jugador. Este ángulo representaría la posición del observador en el plano horizontal
	teniendo en cuenta sus coordenadas esféricas.*/
}

float GameInterface::calculo_vision_beta(float lado_x, float lado_y, float lado_z, float pos_x, float pos_y, float pos_z) {
	float cateto = abs(pos_y - lado_y);
	float hipotenusa = sqrt((pos_x)*(lado_x) + (pos_y)*(lado_y) + (pos_z)*(lado_z));
	float beta = (180.0 / PI) * (asin(cateto / hipotenusa));
	return beta;
	/*Como en la función anterior, esta función se encarga del cálculo del ángulo de elevación
	del observador respecto al centro del plano horizontal donde se encuentra el punto de vista.
	Con beta se realizaría la segunda rotación respecto al eje X de sist de referencia.*/
}

void GameInterface::dibujarInventario() {

	//Cambio de posición de dibujado
	glPopMatrix;
	gluLookAt(0, 10, 20,  // posicion del ojo
		0, 10, 25,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    
	glTranslatef(0, 10, 25); //Translación del sist de referencia al punto al que se mira

	//DIBUJADO DEL INVENTARIO
	glDisable(GL_LIGHTING);
	glTranslatef(-11, 9, 23);
	//Dibujado botón de ajustes
	s.DrawGear(0.2, 0.5, 0.20, 10, 0.15, 0);
	glTranslatef(11, -9, -23);

	
	//Background total del inventario.
	glEnable(GL_TEXTURE_2D);
	switch (dificultad) {
	case 0:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_aire.png").id); break;
	case 1:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_tierra.png").id); break;
	case 2:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_agua.png").id); break;
	case 3:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_fuego.png").id); break;
	}
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);
	glVertex3f(-30, -10, 26);
	glTexCoord2d(1, 1);
	glVertex3f(30, -10, 26);
	glTexCoord2d(1, 0);
	glVertex3f(30, 40, 26);
	glTexCoord2d(0, 0);
	glVertex3f(-30, 40, 26);
	glEnd();


	//Background del inventario
	glBegin(GL_POLYGON); //Cuadrado RECTA (fila 1, columna 3)
	glColor3ub(255, 0, 0); //ROJO
	glVertex3f(-6, 7.5, 25);
	glVertex3f(-12, 7.5, 25);
	glVertex3f(-12, 1.5, 25);
	glVertex3f(-6, 1.5, 25);
	glEnd();

	glBegin(GL_POLYGON); //Cuadrado CURVA (fila 1, columna 2)
	glColor3ub(0, 255, 0); //VERDE
	glVertex3f(3, 7.5, 25);
	glVertex3f(-3, 7.5, 25);
	glVertex3f(-3, 1.5, 25);
	glVertex3f(3, 1.5, 25);
	glEnd();

	glBegin(GL_POLYGON); //Cuadrado RAMPA (fila 1, columna 1)
	glColor3ub(0, 0, 255); //AZUL
	glVertex3f(12, 7.5, 25);
	glVertex3f(6, 7.5, 25);
	glVertex3f(6, 1.5, 25);
	glVertex3f(12, 1.5, 25);
	glEnd();

	glBegin(GL_POLYGON); //Cuadrado CURVA (fila 2, columna 3)
	glColor3ub(255, 0, 255); //MAGENTA
	glVertex3f(-6, -1.5, 25);
	glVertex3f(-12, -1.5, 25);
	glVertex3f(-12, -7.5, 25);
	glVertex3f(-6, -7.5, 25);
	glEnd();

	glBegin(GL_POLYGON); //Cuadrado CURVA (fila 2, columna 2)
	glColor3ub(0, 255, 255); //CYAN
	glVertex3f(3, -1.5, 25);
	glVertex3f(-3, -1.5, 25);
	glVertex3f(-3, -7.5, 25);
	glVertex3f(3, -7.5, 25);
	glEnd();

	glBegin(GL_POLYGON); //Cuadrado CURVA (fila 2, columna 1)
	glColor3ub(255, 255, 0); //AMARILLO
	glVertex3f(12, -1.5, 25);
	glVertex3f(6, -1.5, 25);
	glVertex3f(6, -7.5, 25);
	glVertex3f(12, -7.5, 25);
	glEnd();


	//Dibujado de las imágenes de los bloques
	//Recta
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/recta.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex3f(11, 6.5, 24);
	glTexCoord2d(1, 0);
	glVertex3f(7, 6.5, 24);
	glTexCoord2d(1, 1);
	glVertex3f(7, 2.5, 24);
	glTexCoord2d(0, 1);
	glVertex3f(11, 2.5, 24);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Curva
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/curva.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex3f(2, 6.5, 24);
	glTexCoord2d(1, 0);
	glVertex3f(-2, 6.5, 24);
	glTexCoord2d(1, 1);
	glVertex3f(-2, 2.5, 24);
	glTexCoord2d(0, 1);
	glVertex3f(2, 2.5, 24);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Rampa
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/rampa.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex3f(-7, 6.5, 24);
	glTexCoord2d(1, 0);
	glVertex3f(-11, 6.5, 24);
	glTexCoord2d(1, 1);
	glVertex3f(-11, 2.5, 24);
	glTexCoord2d(0, 1);
	glVertex3f(-7, 2.5, 24);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Trampolín
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/trampolin.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex3f(11, -2.5, 24);
	glTexCoord2d(1, 0);
	glVertex3f(7, -2.5, 24);
	glTexCoord2d(1, 1);
	glVertex3f(7, -6.5, 24);
	glTexCoord2d(0, 1);
	glVertex3f(11, -6.5, 24);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Rebote
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/rebote.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex3f(2, -2.5, 24);
	glTexCoord2d(1, 0);
	glVertex3f(-2, -2.5, 24);
	glTexCoord2d(1, 1);
	glVertex3f(-2, -6.5, 24);
	glTexCoord2d(0, 1);
	glVertex3f(2, -6.5, 24);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	//Aire
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/aire.png").id);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 0);
	glVertex3f(-7, -2.5, 24);
	glTexCoord2d(1, 0);
	glVertex3f(-11, -2.5, 24);
	glTexCoord2d(1, 1);
	glVertex3f(-11, -6.5, 24);
	glTexCoord2d(0, 1);
	glVertex3f(-7, -6.5, 24);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_LIGHTING);
	//Devolvemos el sist de referencia a su sitio
	glTranslatef(0, -10, -25);
	glPushMatrix;
	glutPostRedisplay();
}

void GameInterface::set_dificultad(int d)
{
	dificultad = d;
}

