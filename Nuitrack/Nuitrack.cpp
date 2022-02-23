#include "nuitrack/Nuitrack.h"
#include <signal.h>
#include <iomanip>
#include <iostream>
#include <Windows.h>

#define FRAMES 100 //Numero de frames a capturar
#define PRINT false 
//false -> Solo numero articulaciones captadas
//true -> Numero y posiciones de cada una
using namespace tdv::nuitrack;
using namespace std;

//Variables globales
FILE* fichero;
SkeletonTracker::Ptr skeletonTracker;

//Conjunto de articulaciones de interes
const vector<JointType> desired_joints = { JOINT_HEAD, JOINT_NECK, JOINT_LEFT_COLLAR, JOINT_RIGHT_COLLAR, JOINT_TORSO, JOINT_WAIST, JOINT_LEFT_SHOULDER,
JOINT_LEFT_ELBOW, JOINT_LEFT_WRIST, JOINT_RIGHT_SHOULDER, JOINT_RIGHT_ELBOW,  JOINT_RIGHT_WRIST, JOINT_LEFT_HIP,
JOINT_LEFT_KNEE, JOINT_LEFT_ANKLE, JOINT_LEFT_FOOT, JOINT_RIGHT_HIP, JOINT_RIGHT_KNEE, JOINT_RIGHT_ANKLE, JOINT_RIGHT_FOOT };

//Funciones
const char* name(JointType joint); //Devuelve el nombre de la articulacion segun su tipo
void onSkeletonUpdate(SkeletonData::Ptr skeletonData); //Callback para actualizacion de datos
bool belongs(int index, const vector<JointType> v); //Devuelve si la articulacion pertenece al conjunto de deseadas
void init(); //Inicializacion de lo relacionado con la camara

int main(int argc, char* argv[])
{
	cout << "Configurando sensor, espere por favor..." << endl;
	try { init(); }
	catch (const exception& e)
	{
		cerr << "Failed with exception:" << endl
			<< "    " << e.what() << endl;
		return 1;
	}

	cout << "La captura comenzara en 3..." << endl;
	Sleep(1000);
	cout << "2..." << endl;
	Sleep(1000);
	cout << "1..." << endl;
	Sleep(1000);

	//Bucle de captura
	for (int frame = 0; frame < FRAMES; frame++)
	{
		cout << "Procesando frame " << frame + 1 << endl;
		fprintf(fichero, "Frame %d\n", frame + 1);
		//Esperar datos
		try { Nuitrack::waitUpdate(skeletonTracker); }
		catch (LicenseNotAcquiredException& e)
		{
			cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << endl;
			return 1;
		}
		catch (const Exception& e)
		{
			cerr << "Nuitrack update failed (ExceptionType: " << e.type() << ")" << endl;
			return 1;
		}
	}

	//Liberar Nuitrack
	try { Nuitrack::release(); }
	catch (const Exception& e)
	{
		cerr << "Nuitrack release failed (ExceptionType: " << e.type() << ")" << endl;
		return 1;
	}

	cout << "Fin del programa Nuitrack" << endl;
	fclose(fichero);
	system("Nuitrack.txt");

	return 0;
}

const char* name(JointType joint)
{
	switch (joint) {
	case JOINT_HEAD: return "Cabeza\t\t";
	case JOINT_LEFT_ANKLE: return "Tobillo Izq\t";
	case JOINT_LEFT_COLLAR: return "Clavicula Izq\t";
	case JOINT_LEFT_ELBOW: return "Codo Izq\t";
	case JOINT_LEFT_FINGERTIP: return "Dedo Izq\t";
	case JOINT_LEFT_FOOT: return "Pie Izq\t\t";
	case JOINT_LEFT_HAND: return "Mano Izq\t";
	case JOINT_LEFT_HIP: return "Cadera Izq\t";
	case JOINT_LEFT_KNEE: return "Rodilla Izq\t";
	case JOINT_LEFT_SHOULDER: return "Hombro Izq\t";
	case JOINT_LEFT_WRIST: return "Muñeca Izq\t";
	case JOINT_NECK: return "Cuello\t\t";
	case JOINT_TORSO: return "Esternon\t";
	case JOINT_WAIST: return "Cintura\t\t";
	case JOINT_RIGHT_ANKLE: return "Tobillo Der\t";
	case JOINT_RIGHT_COLLAR: return "Clavicula Der\t";
	case JOINT_RIGHT_ELBOW: return "Codo Der\t";
	case JOINT_RIGHT_FINGERTIP: return "Dedo Der\t";
	case JOINT_RIGHT_FOOT: return "Pie Der\t\t";
	case JOINT_RIGHT_HAND: return "Mano Der\t";
	case JOINT_RIGHT_HIP: return "Cadera Der\t";
	case JOINT_RIGHT_KNEE: return "Rodilla Der\t";
	case JOINT_RIGHT_SHOULDER: return "Hombro Der\t";
	case JOINT_RIGHT_WRIST: return "Muñeca Der\t";
	default: return "NONE\t\t";
	}
}
void onSkeletonUpdate(SkeletonData::Ptr skeletonData)
{
	//No se recibio correctamente el puntero
	if (!skeletonData) {
		cout << "\t\t--------No se detectaron sujetos-------\n" << endl;
		return;
	}

	//Obtener esqueletos
	auto userSkeletons = skeletonData->getSkeletons();
	//No hay esqueletos
	if (userSkeletons.empty())
	{
		fprintf(fichero, "\t\t--------No se detectaron sujetos-------\n");
		return;
	}

	//Articulaciones
	int caught = 0;
	auto joints = userSkeletons[0].joints;

	for (int i = 0; i < joints.size(); i++)
	{
		if (joints[i].confidence >= 0.5) //El nivel de confianza indica si la articulacion ha sido detectada
		{
			if (PRINT) //PRINT sirve para elegir si imprimir las posiciones o no
				fprintf(fichero, "\t\t%s: Posicion[mm] ( %d, %d, %d ) \t", name(joints[i].type), (int)joints[i].real.x, (int)joints[i].real.y, (int)joints[i].real.z);
			if (belongs(i, desired_joints))
				caught++;
		}
		else if (PRINT && joints[i].type != JOINT_NONE) fprintf(fichero, "\t\t%s: No detectada \t\t\t\t", name(joints[i].type));

		if (PRINT)
		{
			if (belongs(i, desired_joints))
				fprintf(fichero, "<Deseada>\n");
			else
				fprintf(fichero, "\n");
		}
	}

	fprintf(fichero, "Captadas %d/20 articulaciones de interes\n\n", caught);
}
bool belongs(int index, const vector<JointType> v) {
	for (int i = 0; i < v.size(); i++)
		if (index == v[i]) return true;
	return false;
}
void init()
{
	//Apertura del fichero de salida
	fichero = fopen("Nuitrack.txt", "w");

	//Configuracion Nuitrack
	Nuitrack::init();

	//Creacion del modulo de seguimiento
	skeletonTracker = SkeletonTracker::create();

	//Enlazar la callback para recibir los datos
	skeletonTracker->connectOnUpdate(onSkeletonUpdate);

	//Iniciar Nuitrack
	Nuitrack::run();
}