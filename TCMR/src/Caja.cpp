#include "Caja.h"
#define COLOR 50,50,50
Caja::Caja()
{
	suelo.setColor(COLOR);
	suelo.setPos(-20.0f, 0, 20.0f, 0, 5);
	pared.setColor(COLOR+20);
	pared.setPos(-20.0f, -2.5f, 20.0f, -2.5f, 5);
	estante.setColor(COLOR);
	estante.setPos(-20.0f, 6, 20.0f, 6, 5);
	parede.setColor(COLOR+20);
	parede.setPos(-20.0f, 5.5, 20.0f, 5.5, 5);
}


void Caja::dibuja(int a)
{
	switch (a)
	{
	case 0:
		suelo.dibuja();
		pared.dibuja();
		break;
	case 1:
		estante.dibuja();
		parede.dibuja();
		break;
	}
}