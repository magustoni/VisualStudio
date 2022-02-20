#include "Interaccion.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include"ETSIDI.h"
#define PI 3.14159265359
//-1 1 -1 -1 1 -1 1 1 -1 1 -1 1 -1 1 1 1 1 -1 1 -1 1 -1 1 1 -1 1 -1 -1 1 -1-1 1 -1 -1 1 -1 1 1 -1 1 -1 1 -1 1 1 1 1 -1 1 -1 1 -1 1 1 -1 1 -1 -1 1 -1
using namespace std;

bool Interaccion::Rebote(ListaBloques l, Pelota& p, float t, Vector3D size)
{

	static bool comienzo_trampolin = 0;
	static float altura_inicial_trampolin;
	static bool entrada_giro = 1;
	static float vel_inicial_trampolin;
	static float vel_giro_trampolin;
	static float posicion_inicial_trampolin;
	static int sen_trampolin;
	static int i_trampolin;

	// rampa
	bool pass_rampa = 1;

	//curva
	bool pass_curva = 0;

	static float caida_vel;
	static int caida_libre = 0;


	bool die = 0;
	int interaccion = 0;
	static int enter = 0;
	static int pre_interaccion;
	static double e_vel;

	static double angle;
	static Vector3D pre_pos;
	double radio = 0.5;
	int i_pos[9];
	int i = 0;
	double* vel[9];
	double* pos[9];
	double lado[3];

	vel[0] = vel[4] = vel[7] = &p.vel.x;
	vel[1] = vel[3] = vel[8] = &p.vel.z;
	vel[2] = vel[5] = vel[6] = &p.vel.y;

	pos[0] = pos[4] = pos[7] = &p.pos.x;
	pos[1] = pos[3] = pos[8] = &p.pos.z;
	pos[2] = pos[5] = pos[6] = &p.pos.y;

	i_pos[0] = i_pos[4] = i_pos[7] = int(p.pos.x);
	i_pos[1] = i_pos[3] = i_pos[8] = int(p.pos.z);
	i_pos[2] = i_pos[5] = i_pos[6] = int(p.pos.y);

	lado[0] = size.x;
	lado[1] = size.z;
	lado[2] = size.y;

	int tipo[27] = { 3 };
	int ori[27]{ 26 };
	int al[21];
	static int sen;
	int dir = 1;


	if (*pos[0] - i_pos[0] >= 0.5)
		i_pos[0]++;
	if (*pos[1] - i_pos[1] >= 0.5)
		i_pos[1]++;
	if (*pos[2] - i_pos[2] >= 0.5)
		i_pos[2]++;


	int a = 0;
	for (int y = -1; y <= 1; y++)
	{
		for (int z = -1; z <= 1; z++)
		{
			for (int x = -1; x <= 1; x++)
			{
				if (i_pos[0] + x < size.x and i_pos[2] + y < size.y and i_pos[1] + z < size.z and i_pos[0] + x >= 0 and i_pos[2] + y >= 0 and i_pos[1] + z >= 0)
				{
					a = i_pos[0] + x + (i_pos[1] + z) * size.x + (i_pos[2] + y) * size.x * size.z;
					tipo[x + 1 + (z + 1) * 3 + (y + 1) * 9] = l.lista[a]->tipo;
					ori[x + 1 + (z + 1) * 3 + (y + 1) * 9] = l.lista[a]->rotacion;
				}
				else
				{
					tipo[x + 1 + (z + 1) * 3 + (y + 1) * 9] = 1;
					ori[x + 1 + (z + 1) * 3 + (y + 1) * 9] = 26;
				}
			}
		}
	}



	if ((tipo[4] == 10 or tipo[13] == 10) and abs(p.pos.y - i_pos[2]) <= 0.1) // si la pelota se encuentra encima o debajo de un bloque de salida
	{
		caida_libre = 0;
		p.mover = 1;
		comienzo_trampolin = false;
		entrada_giro = 1;
		enter = 0;
		switch (ori[4])
		{
		case 0:
			p.vel.y = 0.0;
			p.vel.z = 0.0;
			p.vel.x = 3.0;
			break;
		case 1:
			p.vel.y = 0.0;
			p.vel.x = 0.0;
			p.vel.z = -3.0;
			break;
		case 2:
			p.vel.y = 0.0;
			p.vel.z = 0.0;
			p.vel.x = -3.0;
			break;
		case 3:
			p.vel.y = 0.0;
			p.vel.x = 0.0;
			p.vel.z = 3.0;
			break;
		}
	}
	else
	{
		al[0] = al[10] = al[17] = tipo[12];
		al[1] = al[8] = al[15] = tipo[13];
		al[2] = al[11] = al[18] = tipo[14];
		al[3] = al[7] = al[19] = tipo[10];
		al[4] = al[9] = al[20] = tipo[16];
		al[5] = al[12] = al[14] = tipo[4];
		al[6] = al[13] = al[16] = tipo[22];


		int way[8] = { 3, 2, 1, 0, 1, 2, 3, 0 };
		if (p.vel.x == 0.0 and p.vel.y == 0 and p.vel.z == 0 and !comienzo_trampolin)
			p.vel.y = -3.0;

		if (interaccion == 1 and(pre_pos.x != i_pos[0] or pre_pos.z != i_pos[1] or pre_pos.y != i_pos[2]))
			enter = 0;
		if (pre_pos.x != i_pos[0] or pre_pos.z != i_pos[1])
		{
			p.mover = 1;
			if(pre_interaccion == 1)
				pass_curva = 1;
		}


			if (abs(p.vel.y) > 0.01)
			{
				i = 2;
				if (p.vel.y > 0.01)
					dir = 1;
				if (p.vel.y < -0.01)
					dir = -1;
			}


			if (abs(p.vel.x) > 0.01)
			{
				i = 0;

				if (p.vel.x > 0.01)
					dir = 1;
				if (p.vel.x < -0.01)
					dir = -1;

				//cambio de direccion
				if (((p.pos.x <= i_pos[0] and dir == 1) or (p.pos.x >= i_pos[0] and dir == -1)) and (tipo[4] == 2 or tipo[22] == 2) and !pass_curva) {
					if ((ori[4] == way[dir + 1] and tipo[4] == 2) or (ori[22] == way[dir + 1] and tipo[22] == 2)) {
						interaccion = 1;
						if (p.mover)
							sen = 1;
					}
					if ((ori[4] == way[dir + 2] and tipo[4] == 2) or (ori[22] == way[dir + 2] and tipo[22] == 2)) {
						interaccion = 1;
						if (p.mover)
							sen = -1;
					}

					cout << "x_cambio_direccion    " << ori[4] << ' ' << ori[22] << endl;
				}
				//rampa
				else {
					pass_rampa = 1;
					if ((ori[13] == 0 and tipo[13] == 3) or (ori[4] == 0 and tipo[4] == 3) /*or (ori[14] == 0 and tipo[14] == 3 and p.pos.x >= i_pos[0] + 0.2929)*/) {
						interaccion = 2;
						if (p.mover)
							sen = 1;
						cout << "x_rampa" << endl;
						if (dir == 1)
							pass_rampa = 0;
					}
					if (pass_rampa and ((ori[4] == 2 and tipo[4] == 3) or (ori[13] == 2 and tipo[13] == 3)/* or (ori[12] == 2 and tipo[12] == 3 and p.pos.x <= i_pos[0] - 0.2929)*/)) {
						interaccion = 2;
						if (p.mover)
							sen = -1;
						cout << "x_rampa" << endl;
					}
				}
			}



			if (abs(p.vel.z) > 0.01)
			{
				i = 1;
				if (p.vel.z > 0.01)
					dir = 1;
				if (p.vel.z < -0.01)
					dir = -1;

				if (((p.pos.z <= i_pos[1] and dir == 1) or (p.pos.z >= i_pos[1] and dir == -1)) and (tipo[4] == 2 or tipo[22] == 2) and !pass_curva) {
					if ((ori[4] == way[4 + dir + 1] and tipo[4] == 2) or (ori[22] == way[4 + dir + 1] and tipo[22] == 2)) {
						interaccion = 1;
						if (p.mover)
							sen = 1;
					}
					if ((ori[4] == way[4 + dir + 2] and tipo[4] == 2) or (ori[22] == way[4 + dir + 2] and tipo[22] == 2)) {
						interaccion = 1;
						if (p.mover)
							sen = -1;
					}

					cout << "z_cambio direccion" << endl;
				}

				//rampa
				else {
					pass_rampa = 1;
					if ((ori[13] == 3 and tipo[13] == 3) or (ori[4] == 3 and tipo[4] == 3 and p.pos.z <= i_pos[1] + 0.2929) /*or (ori[16] == 0 and tipo[16] == 3 and p.pos.z >= i_pos[1] + 0.2929)*/) {
						interaccion = 2;
						if (p.mover)
							sen = 1;
						cout << "z_rampa" << endl;
						if (dir == 1)
							pass_rampa = 0;
					}
					if (pass_rampa and ((ori[4] == 1 and tipo[4] == 3 and p.pos.z >= i_pos[1] - 0.2929) or (ori[13] == 1 and tipo[13] == 3)/* or (ori[10] == 2 and tipo[10] == 3 and p.pos.z <= i_pos[1] - 0.2929)*/)) {
						interaccion = 2;
						if (p.mover)
							sen = -1;
						cout << "z_rampa" << endl;
					}
				}

			}


			if (i != 0)
			{
				if (*pos[i * 3] - i_pos[i * 3] >= 0.5)
					i_pos[i * 3]++;
				if (*pos[i * 3 + 1] - i_pos[i * 3 + 1] >= 0.5)
					i_pos[i * 3 + 1]++;
				if (*pos[i * 3 + 2] - i_pos[i * 3 + 2] >= 0.5)
					i_pos[i * 3 + 2]++;
			}
			if(!pass_curva)
			{
			//______________________________________________________________________ bloque trampolin________________________________________________________________

			if (comienzo_trampolin or (tipo[4] == 4 and ((*pos[i] <= i_pos[i] and dir == -1) or (*pos[i] >= i_pos[i] and dir == 1)))) {
				if (!comienzo_trampolin)
				{

					if (caida_libre)
					{
						*vel[caida_libre - 1] = caida_vel;
						i = caida_libre - 1;
						caida_libre = 0;
					}
					else
					{
						sen_trampolin = dir;
					}
					enter = 3;
					i_trampolin = i;
					altura_inicial_trampolin = p.pos.y;
					posicion_inicial_trampolin = *pos[i];
					vel_inicial_trampolin = *vel[i];
					*vel[2] = abs(*vel[i]);
					if (i != 2)
						*vel[i] = 0;
					i = 2;
					dir = 1;
					angle = 0.0;
					comienzo_trampolin = true;
					entrada_giro = true;
				}
				p.mover = true;
				if (*pos[2] - altura_inicial_trampolin >= 2.5 and angle < PI and ((i_trampolin == 0 and p.pos.x < lado[0] - 1.0 and p.pos.x > 0.0) or (i_trampolin == 1 and p.pos.z < lado[1] - 1.0 and p.pos.z > 0.0)))
				{
					if(entrada_giro)
					{
						entrada_giro = false;
						vel_giro_trampolin = *vel[2];
						*vel[2] = 0.0;
					}
					p.mover = false;
					angle += vel_giro_trampolin * t / radio;
					*pos[2] = i_pos[2] + 0.5 * sin(angle) - 0.5;
					*pos[i_trampolin] = posicion_inicial_trampolin + double(sen_trampolin) * abs(0.5 - 0.5 * cos(angle));
				}
				if (angle >= PI)
				{
					vel_giro_trampolin = 0.0;
					*vel[i_trampolin] = vel_inicial_trampolin;
					comienzo_trampolin = false;
					//*vel[2] *= -1;
					p.mover = true;
					i = i_trampolin;
					*pos[i * 3] = i_pos[i * 3];
				}
				cout << i << "_trampolin  " << angle << ' ' << altura_inicial_trampolin << ' ' << *pos[2] << endl;
				interaccion = 3;
			}


			//__________________________________________________________________ caida libre pared  bloque   rebote _____________________________________________________________________________________

			// ________________________caida libre
			if (p.mover and (tipo[4] == 0 or tipo[4] == 11) and i != 2 and ((*pos[i] >= i_pos[i] and dir == 1) or (*pos[i] <= i_pos[i] and dir == -1))) {
				if (!caida_libre)
				{
					caida_vel = *vel[i];
					caida_libre = i + 1;
				}
				comienzo_trampolin = false;
				p.vel.y = -abs(*vel[i]);
				if (abs(p.vel.y) < 0.1)
					p.vel.y = -3;
				*vel[i] = 0.0;
				cout << i << "_caida_libre" << endl;
			}
			// pared__________________________________________
			else if ((dir == -1 and *pos[i] <= 0.0) or (*pos[i] >= lado[i] - 1.0 and dir == 1)) {
				die = 1;
				cout << i << "_pared" << endl;
			}

			//bloque parada en seco
			else if (((al[i * 7] == 1 or al[i * 7] == 2 or (al[i * 7] == 4 and !comienzo_trampolin) or (i == 2 and al[i*7] == 3)) and *pos[i] <= i_pos[i] and dir == -1) or
				((al[i * 7 + 2] == 1 or al[i * 7 + 2] == 2 or (al[i * 7 + 2] == 4 and !comienzo_trampolin) or (i == 2 and al[i * 7 + 2] == 3)) and *pos[i] >= i_pos[i] and dir == 1))
			{
				if (vel_giro_trampolin > 0.0)
				{
					vel_giro_trampolin = 0.0;
					*vel[i_trampolin] = vel_inicial_trampolin;
					p.mover = true;
					i = i_trampolin;
				}
				*vel[i] = 0.0;
				cout << i << "_bloque" << endl;
				if (p.mover)
				{
					if (caida_libre)
					{
						*vel[caida_libre - 1] = caida_vel;
						caida_libre = 0;
					}
					comienzo_trampolin = false;

					*pos[i] = i_pos[i];
				}
			}

			//bloque rebote y cambio de sentido
			else if ((al[i * 7] == 5 and *pos[i] < i_pos[i] and dir == -1) or (al[i * 7 + 2] == 5 and *pos[i] > i_pos[i] and dir == 1))
			{
				if (vel_giro_trampolin > 0.0)
				{
					vel_giro_trampolin = 0.0;
					*vel[i_trampolin] = vel_inicial_trampolin;
					p.mover = true;
					i = i_trampolin;
				}
				if (p.mover)
				{
					comienzo_trampolin = false;
					*pos[i] = i_pos[i];
				}
				*vel[i] *= -1;
				cout << i << "_bloque_rebote" << endl;
			}

			//_________________________________________________________interacciones y caida libre_________________________________________________________________________

			if (interaccion == 2) // bloque subida/bajada
			{
				if (enter == 0)
				{
					enter = 2;
					if( i != 2)
					p.pos.y += 0.2;
				}
				p.mover = false;
				*pos[i * 3] += *vel[i * 3] * t;
				*pos[i * 3 + 2] += *vel[i * 3] * t * sen;
			}

			else if (interaccion == 1) // bloque cambio dirección
			{
				if (enter == 0)
				{
 					enter = 1;
					e_vel = sen * *vel[i * 3];
					angle = 0.0;
					angle += abs(*vel[i * 3] * t / radio);
					//*pos[i * 3] += 0.0001 * dir;
				}
				else
				{
					*pos[i * 3] = i_pos[i * 3] - dir * (0.5 - 0.5 * sin(angle));
					*pos[i * 3 + 1] = i_pos[i * 3 + 1] + sen * dir * (0.5 - 0.5 * cos(angle));
				}
				p.mover = false;
				cout << "angle  " << angle << endl;
				angle += abs(*vel[i * 3] * t / radio);

			}


			//__________________________________________________________________________fin interacciones ___________________________________________________________________________
		}
		if (interaccion != 1 and pre_interaccion == 1) {
			*vel[i * 3 + 1] = e_vel;
			*vel[i * 3] = 0.0;
			//*pos[i * 3] = i_pos[i * 3];
			//*pos[i * 3 + 1] = i_pos[i * 3 + 1] - 0.5 * sen * dir;
			p.mover = 1;
			enter = 0;
		}
		if (interaccion != 2 and pre_interaccion == 2) {
			p.mover = 1;
			p.pos.y = i_pos[2];
			enter = 0;
		}
	}
	pre_interaccion = interaccion;
	pre_pos.x = i_pos[0];
	pre_pos.y = i_pos[2];
	pre_pos.z = i_pos[1];
	return die;
}

bool Interaccion::rebote(Esfera& e, Pared p) //Rebote de la pelota con el suelo del menu 2D
{
	Vector2D dir;
	float dif = p.distancia(e.posicion, &dir) - e.radio;
	if (dif > 4.25)
	{
		e.velocidad.y = -0.10;
	}
	if (dif <= 0.0f)
	{
		Vector2D v_inicial = e.velocidad;
		e.velocidad = v_inicial * (-1);
		e.posicion = e.posicion - dir * dif;
		return true;
	}
	return false;
}
void Interaccion::rebote(Esfera& e, Caja c) //Rebote de la pelota con el suelo del menu 2D
{
	rebote(e, c.suelo);
}
bool Interaccion::choque(Pelota& e, Bonus& b) //Colision de la pelota del mundo con los bonus
{

	float norma, dist;
	float dist1 = e.radio;
	dist = (e.pos - b.posicion).modulo();

	return (dist < dist1);
}