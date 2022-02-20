#include "Mundo.h"
#include "freeglut.h"
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

void Mundo::dibuja()
{
	if (inventario) {
		interfaz_jugador.set_dificultad(dificultad);
		interfaz_jugador.dibujarInventario(); //Dibujado del la selección de bloques
	}
	else {

		gluLookAt(float(distance * cos(angle) * sin(tipp)), float(distance * cos(tipp)) + height, float(distance * sin(angle) * sin(tipp)),  // posicion del ojo
			size.x / 2 - 0.5, height - 0.5, size.z / 2 - 0.5,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

		//Sprites de fondo

		glDisable(GL_LIGHTING);

		glEnable(GL_TEXTURE_2D);//Paredes
		switch (dificultad) {
		case 0:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_aire.png").id); break;
		case 1:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_tierra.png").id); break;
		case 2:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_agua.png").id); break;
		case 3:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/fondo_fuego.png").id); break;
		}

		for (int i = 0; i < 4; i++) {
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);
			glVertex3f(-30, -10, 30);
			glTexCoord2d(1, 1);
			glVertex3f(30, -10, 30);
			glTexCoord2d(1, 0);
			glVertex3f(30, 40, 30);
			glTexCoord2d(0, 0);
			glVertex3f(-30, 40, 30);
			glEnd();
			glRotatef(90, 0, 1, 0);
		}
		glDisable(GL_TEXTURE_2D);

		glRotatef(90, 1, 0, 0);
		glEnable(GL_TEXTURE_2D);//Suelo
		switch (dificultad) {
		case 0:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/suelo_aire.png").id); break;
		case 1:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/suelo_tierra.png").id); break;
		case 2:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/suelo_agua.png").id); break;
		case 3:glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/suelo_fuego.png").id); break;
		}

		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glTexCoord2d(0, 1);
		glVertex3f(-30, -30, 1);
		glTexCoord2d(1, 1);
		glVertex3f(30, -30, 1);
		glTexCoord2d(1, 0);
		glVertex3f(30, 30, 1);
		glTexCoord2d(0, 0);
		glVertex3f(-30, 30, 1);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glRotatef(-90, 1, 0, 0);

		glEnable(GL_LIGHTING);


		// comienzo de dibujar los limites del mapa con lineas
		// los limites se dibujan un pelin más grandes que el mapa
		// para evitar que los bloques que estén en los bordes las tapen
		// asi queda más bonito
		// por eso se quita todo el rato 0.4 y 0.6
		// quito 0.5 porque las coordenadas están puestas con el centro del cuadrado
		// como el cuadrado mide 1 hay que quitarle 0.5 para llegar a la cara
		// quito 0.1 cuando estoy por la zona del origen
		// sumo 0.1 cuando no estoy por la zona del origen

		glDisable(GL_LIGHTING); // para lineas queda mejar quitar el efecto de la luz

		glColor3ub(255, 255, 255);
		glBegin(GL_LINES);

		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(size.x, 2.0, 0.0);

		glVertex3d(-0.6, -0.6, -0.6);
		glVertex3d(size.x - 0.4, -0.6, -0.6);

		glVertex3d(-0.6, -0.6, -0.6);
		glVertex3d(-0.6, -0.6, size.z - 0.4);

		glVertex3d(size.x - 0.4, -0.6, size.z - 0.4);
		glVertex3d(-0.6, -0.6, size.z - 0.4);

		glVertex3d(size.x - 0.4, -0.6, size.z - 0.4);
		glVertex3d(size.x - 0.4, -0.6, -0.6);

		glVertex3d(-0.6, size.y - 0.4, -0.6);
		glVertex3d(size.x - 0.4, size.y - 0.4, -0.6);

		glVertex3d(-0.6, size.y - 0.4, -0.6);
		glVertex3d(-0.6, size.y - 0.4, size.z - 0.4);

		glVertex3d(size.x - 0.4, size.y - 0.4, size.z - 0.4);
		glVertex3d(-0.6, size.y - 0.4, size.z - 0.4);

		glVertex3d(size.x - 0.4, size.y - 0.4, size.z - 0.4);
		glVertex3d(size.x - 0.4, size.y - 0.4, -0.6);

		glVertex3d(-0.6, -0.6, -0.6);
		glVertex3d(-0.6, size.y - 0.4, -0.6);

		glVertex3d(-0.6, -0.6, size.z - 0.4);
		glVertex3d(-0.6, size.y - 0.4, size.z - 0.4);

		glVertex3d(size.x - 0.4, -0.6, size.z - 0.4);
		glVertex3d(size.x - 0.4, size.y - 0.4, size.z - 0.4);

		glVertex3d(size.x - 0.4, -0.6, -0.6);
		glVertex3d(size.x - 0.4, size.y - 0.4, -0.6);

		glEnd();
		glEnable(GL_LIGHTING);

		//Dibuja la matriz y el bloque de selección
		if (!begin) {
		glDisable(GL_LIGHTING);
		// se toma el color del bloque que tengas elegido
		glColor3ub(255, 255, 255);
		glTranslatef(select.x, select.y, select.z);
		glutWireCube(1.2);
		glTranslatef(-select.x, -select.y, -select.z);

		// se dibuja la red que te muestra a que altura estás añadiendo bloques
		// se le rsto 0,5 igual que antes para pasar del centro a la cara del cubo
		glBegin(GL_LINES);

		for (int i = 0; i <= size.x; i++)
		{
			glVertex3d(i - 0.5, select.y - 0.5, size.z - 0.5);
			glVertex3d(i - 0.5, select.y - 0.5, -0.5);
		}
		for (int i = 0; i <= size.z; i++)
		{
			glVertex3d(size.x - 0.5, select.y - 0.5, i - 0.5);
			glVertex3d(-0.5, select.y - 0.5, i - 0.5);
		}
		glEnd();
		fantasma.dibujar(0);
		glEnable(GL_LIGHTING);
		}

		bloques.dibujar(wire);
		pelota.setColor(rojo, verde, azul);
		pelota.dibuja();
		Bonuss.dibujar(angulo);
		//interfaz_jugador.dibujar(float(distance * cos(angle) * sin(tipp)), float(distance * cos(tipp)) + height, float(distance * sin(angle) * sin(tipp)), size.x / 2 - 0.5, height - 0.5, size.z / 2 - 0.5);
	}
}

void Mundo::inicializa(int _nivel_max_completado)
{
	nivel_max_completado = _nivel_max_completado;
	cout << nivel_max_completado << endl;
	estado = 1;
	intentos = 0;
	bloques_puestos = 0;
	rojo = verde = azul = 255;
	size.x = 6;
	size.y = 10;
	size.z = 6;
	select.x = 0;
	select.y = 0;
	select.z = 0;
	nivel = 1;
	zoom = 0;
	dificultad = 0;

	for(int j = 0; j < size.y; j++)
		for(int k = 0; k < size.z; k++)
			for (int i = 0; i < size.x; i++)
			{
				Int3D pos;
				pos.x = i;
				pos.y = j;
				pos.z = k;
				Bloque *aux = new Bloque();
				bloques.agregar(aux, 0, 0, pos);
			}
	
	cargar_nivel(true);
}

void Mundo::mouse(int button, int x, int y, int state) // solo se activa al presionar un boton del raton
{
	if (!inventario) {
		Raton_juego(button, state, x, y, zoom); // Si no está mostrándose el inventario, se activa la visión esférica
	}
	else {
		Raton_inventario(button, state, x, y); //Al mostrarse el inventario, se activan los colliders de las casillas de los bloques
	}
}

void Mundo::motion(int x, int y)  // se llama a esta funcion cuando se detectan variacion en la posicion del raton
{
	Motion(x, y);
}
void Mundo::tecla(unsigned char key) // realiza cambios en funcion de la tecla y llama a Mapa.tecla()
{
	//Controles de la seleccion
	//Solo disponibles si no estas simulando
	if (!begin) {

		// w siempre sera ir hacia adelante, s hacia atras, d a la derecha y a la izquierda
		// sin importar la vista que tengas
		if (abs(cos(angle)) > abs(sin(angle))) {
			if (cos(angle) > 0.0) {
				if (key == 's' and select.x < size.x - 1)
					select.x++;
				if (key == 'w' and select.x > 0)
					select.x--;
				if (key == 'a' and select.z < size.z - 1)
					select.z++;
				if (key == 'd' and select.z > 0)
					select.z--;
			}
			else {
				if (key == 'w' and select.x < size.x - 1)
					select.x++;
				if (key == 's' and select.x > 0)
					select.x--;
				if (key == 'd' and select.z < size.z - 1)
					select.z++;
				if (key == 'a' and select.z > 0)
					select.z--;
			}

		}
		if (abs(sin(angle)) > abs(cos(angle))) {
			if (sin(angle) > 0.0) {
				if (key == 'd' and select.x < size.x - 1)
					select.x++;
				if (key == 'a' and select.x > 0)
					select.x--;
				if (key == 's' and select.z < size.z - 1)
					select.z++;
				if (key == 'w' and select.z > 0)
					select.z--;
			}
			else {
				if (key == 'a' and select.x < size.x - 1)
					select.x++;
				if (key == 'd' and select.x > 0)
					select.x--;
				if (key == 'w' and select.z < size.z - 1)
					select.z++;
				if (key == 's' and select.z > 0)
					select.z--;
			}
		}

		if (key == 'e' && select.y < size.y - 1) //Elevar la selección
			select.y++;
		if (key == 'q' && select.y > 0) //Bajar la selección
			select.y--;

		if (key == ' ') //Colocar bloque
		{
			if (tipo)
				bloques_puestos++;
			int pos = select.x + size.x * select.z + size.x * size.z * select.y;
			bloques.cambiar_bloque(false, tipo, rotacion, pos);
			if (sonido and tipo)
				ETSIDI::play("sonidos/Bloque.mp3");
			if (sonido and !tipo)
				ETSIDI::play("sonidos/Cuack.mp3");
		}

		if (key == '0') //Seleccionar aire
			tipo = 0;
		if (key == '1') //Seleccionar recta
			tipo = 1;
		if (key == '2') //Seleccionar curva
			tipo = 2;
		if (key == '3') //Seleccionar rampa
			tipo = 3;
		if (key == '4') //Seleccionar trampolin
			tipo = 4;
		if (key == '5') //Seleccionar rebote
			tipo = 5;


		if (key == 'r') //Rotar bloque seleccionado
		{
			if (rotacion == 3)
				rotacion = 0;
			else
				rotacion++;
		}
	}

	if (key == 'p') //Menú de pausa
		estado = 2;

	if (key == 'n') //Recargar nivel
		cargar_nivel(false);

	if (key == 'm') { //Reiniciar nivel
		int aux = intentos;
		cargar_nivel(true);
		intentos = aux + 1;
	}
	if (key == 'k') // Activa o desactiva la variable wire
		wire = !wire;
	if (key == 'b') //Comenzar simulación
		begin = 1;

	pelota.teclado(key);

	if (key == 'z') //Activa o desactiva el modo zoom (con la rueda del raton)
		zoom = !zoom;
	
	if ((key == 'f') and !inventario) { //Pulsar i para dibujar el inventario cuando no está
		set_inventario(true); //Pongo a true la variable inventario para utilizar los coliders de las distintas casillas
	}
	if ((key == 'g') and inventario) { //Pulsar i para dibujar el inventario cuando no está
		set_inventario(false); //Pongo a true la variable inventario para utilizar los coliders de las distintas casillas
	}

	////////////////////////Para probar los niveles ("." sube 1 nivel y "," baja 1 nivel)
	if (key == '.') { nivel++; this->cargar_nivel(true); }
	if (key == ',') { nivel--; this->cargar_nivel(true); }
	/////////////////////////
}

void Mundo::special_tecla(int key){}
void Mundo::mueve()
{
	Bonus *aux=Bonuss.colision(&pelota);
	if (aux != 0) { //Detectada colision con bonus
		if (aux->getTipo() == 1) //Llave
			bloques.cambiar_bloque(true, 11, 0, bloques.pos_lista(bloques.meta().get_pos())); //Desbloquea la meta
		if (aux->getTipo() == 0) //Estrella
			monedas += 75;//suma 75 monedas
		Bonuss.eliminar(aux);//borra el bonus del nivel
		if(sonido)
			ETSIDI::play("sonidos/V.mp3");//sonido al cojer un bonus
	}
	if (begin) //Begin inicia el movimiento
		pelota.mueve(0.025f);

	//Gestiona el bloque fantasma de selección
	fantasma.set_tipo(tipo);
	fantasma.set_Rot(rotacion);
	fantasma.set_Pos(select);

	angulo++;
	if (angle > 2 * PI) angle -= 2 * PI;
	if (angle < 0) angle += 2 * PI;
}
void Mundo::cargar_nivel(bool reset) {

	if (reset) {
		for (int i = 0; i < bloques.get_numero(); i++) //Reinicia todos los bloques del mapa
			bloques.cambiar_bloque(true, 0, 0, i);
		Bonuss.destruirContenido();
		bloques_puestos = 0;
		intentos = 0;
	}
	begin = 0;

	//OJO el bloque inicial nunca puede estar en la altura máxima del mapa porque la pelota empezaria fuera
	//Bloque inicial (tipo 10) posicion maxima 323
	switch (nivel) { //Carga el estado inicial de cada nivel
	default:
		if (nivel > 14) //Fin del juego
			estado = 0;
		else
			nivel = 1;

		//TUTORIAL
	case 1://Inicio y meta alineadas
		bloques.cambiar_bloque(true, 10, 2, 5); //Inicio
		bloques.cambiar_bloque(true, 11, 0, 0); //Meta

		bloques_minimo = 4; //Minimos bloques para superar el nivel
		dificultad = 0;
		break;
	case 2: {//Esquinas opuestas en la base
		bloques.cambiar_bloque(true, 10, 2, 35);
		bloques.cambiar_bloque(true, 11, 0, 0);

		Vector3D pos_estrella(5, 1, 0); //Bonus estrella
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 9;
		dificultad = 0;
		break;
	}
	case 3: {//Esquinas opuestas en la base con obstaculos
		bloques.cambiar_bloque(true, 10, 2, 35);
		bloques.cambiar_bloque(true, 11, 0, 0);

		bloques.cambiar_bloque(true, 13, 0, 1); //Muertes
		bloques.cambiar_bloque(true, 13, 0, 6);

		Vector3D pos_estrella(5, 1, 0);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 9;
		dificultad = 0;
		break;
	}
	case 4: {//Esquinas opuestas con meta bloqueada
		bloques.cambiar_bloque(true, 10, 2, 35);
		bloques.cambiar_bloque(true, 12, 0, 0); //Meta bloqueada

		Vector3D pos_llave(0, 1, 5); //Bonus llave
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(3, 1, 5);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 9;
		dificultad = 0;
		break;
	}
	case 5: {//Esquinas opuestas con altura
		bloques.cambiar_bloque(true, 10, 2, 35);
		bloques.cambiar_bloque(true, 11, 0, 108);

		Vector3D pos_estrella(5, 5, 5);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 9;
		dificultad = 0;
		break;
	}
		  //FIN TUTORIAL

	case 6: {//Llave con caida libre
		bloques.cambiar_bloque(true, 10, 0, 318);
		bloques.cambiar_bloque(true, 12, 0, 0);

		bloques.cambiar_bloque(true, 13, 0, 124);
		bloques.cambiar_bloque(true, 13, 0, 129);
		bloques.cambiar_bloque(true, 13, 0, 131);
		bloques.cambiar_bloque(true, 13, 0, 136);

		Vector3D pos_llave(4, 3, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(4, 1, 0);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 12;
		dificultad = 1;
		break;
	}
	case 7: {//Llave con trampolin sensilla
		bloques.cambiar_bloque(true, 10, 3, 0);
		bloques.cambiar_bloque(true, 12, 0, 5);

		for (int i = 108; i < 120; i++)
			bloques.cambiar_bloque(true, 13, 0, i);
		bloques.cambiar_bloque(true, 0, 0, 110);
		bloques.cambiar_bloque(true, 0, 0, 111);

		Vector3D pos_llave(3, 4, 0);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(3, 5, 2);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 4;
		dificultad = 1;
		break;
	}
	case 8: {//Llave con trampolin y curvas
		bloques.cambiar_bloque(true, 10, 0, 30);
		bloques.cambiar_bloque(true, 12, 0, 0);

		bloques.cambiar_bloque(true, 13, 0, 129);
		bloques.cambiar_bloque(true, 13, 0, 131);
		bloques.cambiar_bloque(true, 13, 0, 136);

		Vector3D pos_llave(4, 3, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(1, 5, 5);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 12;
		dificultad = 1;
		break;
	}
	case 9: {//Mucha altura y muertes
		bloques.cambiar_bloque(true, 10, 0, 0);
		bloques.cambiar_bloque(true, 12, 0, 359);

		bloques.cambiar_bloque(true, 13, 0, 73);
		bloques.cambiar_bloque(true, 13, 0, 87);
		bloques.cambiar_bloque(true, 13, 0, 95);
		bloques.cambiar_bloque(true, 13, 0, 103);
		bloques.cambiar_bloque(true, 13, 0, 135);
		bloques.cambiar_bloque(true, 13, 0, 164);
		bloques.cambiar_bloque(true, 13, 0, 187);
		bloques.cambiar_bloque(true, 13, 0, 200);
		bloques.cambiar_bloque(true, 13, 0, 214);

		Vector3D pos_llave(4, 3, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(4, 6, 2);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 15;
		dificultad = 2;
		break;
	}
	case 10: {//Llave muy por encima
		bloques.cambiar_bloque(true, 10, 0, 0);
		bloques.cambiar_bloque(true, 12, 0, 35);

		bloques.cambiar_bloque(true, 13, 0, 71);
		bloques.cambiar_bloque(true, 13, 0, 84);
		bloques.cambiar_bloque(true, 13, 0, 99);
		bloques.cambiar_bloque(true, 13, 0, 109);
		bloques.cambiar_bloque(true, 13, 0, 131);
		bloques.cambiar_bloque(true, 13, 0, 168);
		bloques.cambiar_bloque(true, 13, 0, 182);
		bloques.cambiar_bloque(true, 13, 0, 207);
		bloques.cambiar_bloque(true, 13, 0, 240);
		bloques.cambiar_bloque(true, 13, 0, 274);
		bloques.cambiar_bloque(true, 13, 0, 289);
		bloques.cambiar_bloque(true, 13, 0, 312);
		bloques.cambiar_bloque(true, 13, 0, 332);

		Vector3D pos_llave(3, 9, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(0, 1, 1);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 18;
		dificultad = 2;
		break;
	}
	case 11: {//Llave muy por debajo
		bloques.cambiar_bloque(true, 10, 2, 323);
		bloques.cambiar_bloque(true, 12, 0, 288);

		bloques.cambiar_bloque(true, 13, 0, 20);
		bloques.cambiar_bloque(true, 13, 0, 47);
		bloques.cambiar_bloque(true, 13, 0, 74);
		bloques.cambiar_bloque(true, 13, 0, 89);
		bloques.cambiar_bloque(true, 13, 0, 102);
		bloques.cambiar_bloque(true, 13, 0, 113);
		bloques.cambiar_bloque(true, 13, 0, 126);
		bloques.cambiar_bloque(true, 13, 0, 156);
		bloques.cambiar_bloque(true, 13, 0, 179);
		bloques.cambiar_bloque(true, 13, 0, 203);
		bloques.cambiar_bloque(true, 13, 0, 225);
		bloques.cambiar_bloque(true, 13, 0, 248);
		bloques.cambiar_bloque(true, 13, 0, 270);
		bloques.cambiar_bloque(true, 13, 0, 315);
		bloques.cambiar_bloque(true, 13, 0, 329);

		Vector3D pos_llave(3, 1, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(2, 3, 1);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 10;
		dificultad = 2;
		break;
	}
	case 12: { //Muchisimas muertes
		bloques.cambiar_bloque(true, 10, 0, 254);
		bloques.cambiar_bloque(true, 12, 0, 123);

		bloques.cambiar_bloque(true, 13, 0, 54);
		bloques.cambiar_bloque(true, 13, 0, 320);
		bloques.cambiar_bloque(true, 13, 0, 12);
		bloques.cambiar_bloque(true, 13, 0, 37);
		bloques.cambiar_bloque(true, 13, 0, 162);
		bloques.cambiar_bloque(true, 13, 0, 214);
		bloques.cambiar_bloque(true, 13, 0, 287);
		bloques.cambiar_bloque(true, 13, 0, 195);
		bloques.cambiar_bloque(true, 13, 0, 145);
		bloques.cambiar_bloque(true, 13, 0, 223);
		bloques.cambiar_bloque(true, 13, 0, 165);
		bloques.cambiar_bloque(true, 13, 0, 236);
		bloques.cambiar_bloque(true, 13, 0, 135);
		bloques.cambiar_bloque(true, 13, 0, 132);
		bloques.cambiar_bloque(true, 13, 0, 276);
		bloques.cambiar_bloque(true, 13, 0, 46);

		Vector3D pos_llave(2, 7, 1);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(5, 1, 2);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 6;
		dificultad = 3;
		break;
	}
	case 13: { //Aun mas muertes
		bloques.cambiar_bloque(true, 10, 3, 127);
		bloques.cambiar_bloque(true, 12, 0, 26);

		bloques.cambiar_bloque(true, 13, 0, 112);
		bloques.cambiar_bloque(true, 13, 0, 45);
		bloques.cambiar_bloque(true, 13, 0, 134);
		bloques.cambiar_bloque(true, 13, 0, 304);
		bloques.cambiar_bloque(true, 13, 0, 28);
		bloques.cambiar_bloque(true, 13, 0, 103);
		bloques.cambiar_bloque(true, 13, 0, 276);
		bloques.cambiar_bloque(true, 13, 0, 264);
		bloques.cambiar_bloque(true, 13, 0, 134);
		bloques.cambiar_bloque(true, 13, 0, 126);
		bloques.cambiar_bloque(true, 13, 0, 39);
		bloques.cambiar_bloque(true, 13, 0, 228);
		bloques.cambiar_bloque(true, 13, 0, 129);
		bloques.cambiar_bloque(true, 13, 0, 299);
		bloques.cambiar_bloque(true, 13, 0, 319);
		bloques.cambiar_bloque(true, 13, 0, 20);
		bloques.cambiar_bloque(true, 13, 0, 329);
		bloques.cambiar_bloque(true, 13, 0, 130);

		Vector3D pos_llave(4, 5, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(2, 3, 3);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 15;
		dificultad = 3;
		break;
	}
	case 14: { //Muchas muertes y aleatorias, cambia cada vez
		if (reset) //Solo se cambia si reseteas el nivel
			for (int i = 0; i < 25; i++) //25 bloques de muerte aleatorios
				bloques.cambiar_bloque(true, 13, 0, rand() % 359);

		bloques.cambiar_bloque(true, 10, 2, 259);
		bloques.cambiar_bloque(true, 12, 0, 198);

		//Por si acaso un bloque de muerte tapa posiciones necesarias
		bloques.cambiar_bloque(true, 0, 0, 258);
		bloques.cambiar_bloque(true, 0, 0, 294);
		bloques.cambiar_bloque(true, 0, 0, 345);
		bloques.cambiar_bloque(true, 0, 0, 229);
		bloques.cambiar_bloque(true, 0, 0, 295);

		Vector3D pos_llave(3, 9, 3);
		Bonuss.agregar(new Bonus(), 1, pos_llave);
		Vector3D pos_estrella(1, 6, 2);
		Bonuss.agregar(new Bonus(), 0, pos_estrella);

		bloques_minimo = 12;
		dificultad = 3;
		break;
	}
	}
	
	//Posicion y velocidad iniciales de la pelota
	pelota.set_pos(bloques.inicio().get_pos().x, bloques.inicio().get_pos().y + 1, bloques.inicio().get_pos().z); //Mueve la pelota al punto de inicio del nivel
	pelota.set_vel(0.0, 0.0, 0.0);

}
bool Mundo::win() {

	//Posicion de la pelota
	Vector3D pos = pelota.get_pos();
	Int3D pos_aux((int)pos.x, (int)pos.y, (int)pos.z);

	if (pos.x - pos_aux.x >= 0.5)
		pos_aux.x++;
	if (pos.y - pos_aux.y >= 0.5)
		pos_aux.y++;
	if (pos.z - pos_aux.z >= 0.5)
		pos_aux.z++;

	if (bloques.comprobar_bloque(bloques.pos_lista(pos_aux)) == 11) //Comprueba si la pelota esta tocando el bloque de meta
	{
		int punt_aux = 2000 + (bloques_minimo - bloques_puestos) * 100 - intentos * 100;
		if (punt_aux > 0)
			puntuacion = punt_aux;
		if(nivel_max_completado<nivel)
			nivel_max_completado++;
		if (sonido)
			ETSIDI::play("sonidos/win.mp3");
		return true;
	}

	return false;
}
bool Mundo::die(){

	//Posicion de la pelota
	Vector3D pos = pelota.get_pos();
	Int3D pos_aux((int)pos.x, (int)pos.y, (int)pos.z);


	if (pos.x - pos_aux.x >= 0.5)
		pos_aux.x++;
	if (pos.y - pos_aux.y >= 0.5)
		pos_aux.y++;
	if (pos.z - pos_aux.z >= 0.5)
		pos_aux.z++;

	//Comprueba si la pelota esta tocando algun bloque de muerte o fuera de los limites
	if (bloques.comprobar_bloque(bloques.pos_lista(pos_aux)) == 13 or Interaccion::Rebote(bloques, pelota, 0.025f, size)) { 
		intentos++;
		if(sonido)
			ETSIDI::play("sonidos/Muerte.mp3");
		return true;
	}

	return false;
}
void Mundo::set_pelota_color(int r, int g, int b) //Cambio de color de la pelota in game en funcion de la tienda
{
	rojo = r;
	azul = b;
	verde = g;
}
void Mundo::set_sonido(bool s)
{
	sonido = s;
}
float Mundo::get_monedas() //Obtener las monedas de mundo
{
	return monedas;
}
void Mundo::set_monedas(int aux) //Establecer las monedas de mundo, cada vez que se llama a esta funcion las monedas de mundo se reestablecen
{
	monedas = aux;
}
int Mundo::get_estado()
{
	return estado;
}
void Mundo::set_estado(int _estado) {
	estado = _estado;
}
void Mundo::set_nivel(int n)
{
	nivel = n;
}
