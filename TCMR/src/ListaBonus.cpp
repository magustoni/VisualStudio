#include"ListaBonus.h"
#include"Esfera.h"
#include"Interaccion.h"
#include"ETSIDI.h"

ListaBonus::ListaBonus()
{
	numero = 0;
	for (int i = 0; i < MAX_BONUS; i++)
		lista[i] = 0;
}

bool ListaBonus::agregar(Bonus* b, int tipo, Vector3D pos)
{
	for (int i = 0; i < numero; i++)
		if (b == lista[i])
			return false;

	if (numero < MAX_BONUS) { // último puesto sin rellenar 
		lista[numero++] = b;

		b->setTipo(tipo);
		b->setPos(pos);
	}
	else
		return false; // capacidad máxima alcanzada 

	return true;
	return false;
}

void ListaBonus::dibujar(float angulo)
{
	for (int i = 0; i < numero; i++) {
		lista[i]->Dibuja(angulo);
	}
}
void ListaBonus::eliminar(int index)
{
	if ((index < 0) || (index >= numero))
		return;
	delete lista[index];
	numero--;
	for (int i = index;i < numero;i++)
		lista[i] = lista[i + 1];
}

void ListaBonus::eliminar(Bonus* e)//elimina el bonus que corresponda
{
	for (int i = 0;i < numero;i++)
		if (lista[i] == e)
		{
			eliminar(i);
			return;
		}
}
Bonus* ListaBonus::colision(Pelota* e)
{
	for (int i = 0;i < numero;i++)
	{
		if (Interaccion::choque(*e, *(lista[i]))) {//revisa si se produce choque en cada bonus
			return lista[i];
		}
	}
	return 0; //no hay colisión
}
void ListaBonus::destruirContenido() {
	for (int i = 0; i < numero; i++) // destrucción de Bonus contenidos 
		delete lista[i];

	numero = 0; // inicializa lista
}