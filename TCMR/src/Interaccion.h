#pragma once
#include "Bloque.h"
#include "Pelota.h"
#include "Esfera.h"
#include "Caja.h"
#include "Pared.h"
#include "ListaBloques.h"
#include"Bonus.h"

class Interaccion
{
public:
	static bool Rebote(ListaBloques l, Pelota& p, float t, Vector3D);
	static bool rebote(Esfera& e, Pared p);
	static void rebote(Esfera& e, Caja c);
	static bool choque(Pelota& e, Bonus& b);
};