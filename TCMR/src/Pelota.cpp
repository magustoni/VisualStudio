#include "Pelota.h"
#include <stdio.h>
Pelota::Pelota()
{
	color.rojo = color.verde = color.azul = 255;
	pos.x = 1.0;
	pos.z = 2.0;
	pos.y = 8.0;
	vel.x = 0.0;  
	vel.y = 0.0;
	vel.z = 0.0;
	ac.x = 0;
	ac.z = 0.0;
	ac.y = 0.0;
	radio = 0.5;
	vel_nom = 3.0;
	mover = true;
}
void Pelota::setColor(unsigned char red, unsigned char green, unsigned char blue)
{
	color.set(red, green, blue);
}
void Pelota::dibuja()
{
	glColor3ub(color.rojo, color.verde, color.azul);
	glTranslatef(pos.x, pos.y, pos.z);
	glutSolidSphere(radio, 20, 20);
	glTranslatef(-pos.x, -pos.y, -pos.z);
}

void Pelota::set_pos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Pelota::mueve(float t)
{
	if (mover)
	{
		vel = vel + ac * t;
		pos = pos + vel * t + ac * (0.5 * t * t);
	
	}
}
void Pelota::teclado(unsigned char key)
{
	//if (key == 'W')
	//	vel.y = 1.0;
	//if (key == 'S')
	//	vel.y = -1.0;
	//if (key == 'D')
	//	vel.x = -1.0;
	//if (key == 'A')
	//	vel.x = 1.0;
	//if (key == 'Q')
	//	vel.z = -1.0;
	//if (key == 'E')
	//	vel.z = 1.0;
}

void Pelota::set_vel(float vx, float vy, float vz)
{
	vel.x = vx;
	vel.y = vy;
	vel.z = vz;
}

Vector3D Pelota::get_pos()
{
	return pos;
}