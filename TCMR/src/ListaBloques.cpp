#include "ListaBloques.h"
#include "Interaccion.h"
#include "freeglut.h"
ListaBloques::ListaBloques() {
	numero = 0;
	for (int i = 0; i < MAX_BLOQUES; i++)
		lista[i] = 0;
}
bool ListaBloques::agregar(Bloque* b, int tipo, int rotacion, Int3D pos) {

	for (int i = 0; i < numero; i++)
		if (b == lista[i])
			return false;

	if (numero < MAX_BLOQUES) { // último puesto sin rellenar 
		lista[numero++] = b; 
		
		b->set_tipo(tipo);
		b->set_Rot(rotacion);
		b->set_Pos(pos);
	}
	else
		return false; // capacidad máxima alcanzada 

	return true;
}
void ListaBloques::dibujar(bool wire) {
	for (int i = 0; i < numero; i++)
		lista[i]->dibujar(wire);
}
void ListaBloques::destruirContenido() {
	for (int i = 0; i < numero; i++) // destrucción de Bloques contenidos 
		delete lista[i];
	numero = 0; // inicializa lista
}

void ListaBloques::cambiar_bloque(bool permiso, int tipo, int rotacion, int pos)
{
	if ((lista[pos]->get_tipo() != 10 and lista[pos]->get_tipo() != 11 and lista[pos]->get_tipo() != 12 and lista[pos]->get_tipo() != 13) or permiso) {
		lista[pos]->cambiar(tipo, rotacion);
	}
}
int ListaBloques::pos_lista(Int3D pos) {
	for (int i = 0; i < numero; i++)
		if (lista[i]->get_pos() == pos)
			return i;
}
Bloque ListaBloques::inicio() {
	for (int i = 0; i < numero; i++)
		if (lista[i]->get_tipo()==10)
			return *lista[i];
}
Bloque ListaBloques :: meta() {
	for (int i = 0; i < numero; i++)
		if (lista[i]->get_tipo()==11 or lista[i]->get_tipo() == 12)
			return *lista[i];
}
