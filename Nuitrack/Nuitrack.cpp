#include "nuitrack/Nuitrack.h"
#include <signal.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <chrono>

#define FRAMES 10000 //Numero de frames a capturar
#define MODE 1 //Modo de funcionamiento
//0 -> Modo analisis manual en .txt
//1- > Modo captura datos en .csv
#define PRINT false //Salida (solo modo 0)
//false -> Solo numero articulaciones captadas
//true -> Numero y posiciones de cada una

using namespace tdv::nuitrack;
using namespace std;
using namespace std::chrono;

//Variables globales
fstream fichero; //Fichero de salida
SkeletonTracker::Ptr skeletonTracker; //Modulo "tracker"
steady_clock::time_point t_init, t_now;

//Conjunto de articulaciones de interes
const vector<JointType> desired_joints = { JOINT_HEAD, JOINT_NECK, JOINT_LEFT_COLLAR, JOINT_TORSO, JOINT_WAIST, JOINT_LEFT_SHOULDER, 
JOINT_LEFT_ELBOW, JOINT_LEFT_WRIST, JOINT_RIGHT_SHOULDER, JOINT_RIGHT_ELBOW,  JOINT_RIGHT_WRIST, 
JOINT_RIGHT_HIP, JOINT_RIGHT_KNEE, JOINT_RIGHT_ANKLE, JOINT_LEFT_HIP, JOINT_LEFT_KNEE, JOINT_LEFT_ANKLE };

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

	if (MODE == 0) fichero << "Modo analisis manual" << endl << endl;
	if (MODE == 1)
	{
		fichero << "tiempo;";
		for (auto k : desired_joints) {
			fichero << "joint_position_" << name(k) << ".x;";
			fichero << "joint_position_" << name(k) << ".y;";
			fichero << "joint_position_" << name(k) << ".z;";
		}
		fichero << endl;
	}

	t_init = high_resolution_clock::now();

	//Bucle de captura
	for (int frame = 0; frame < FRAMES; frame++)
	{
		cout << "Procesando frame " << frame + 1 << endl;
		if (MODE == 0) fichero << "Frame " << frame + 1 << endl;
		//if (MODE == 1) fichero << frame + 1 << "\t\t";
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
		if (MODE == 1) fichero << endl;
	}

	//Liberar Nuitrack
	try { Nuitrack::release(); }
	catch (const Exception& e)
	{
		cerr << "Nuitrack release failed (ExceptionType: " << e.type() << ")" << endl;
		return 1;
	}

	cout << "Fin del programa Nuitrack" << endl;
	fichero.close();
	if (MODE == 0) system("Nuitrack.txt");
	if (MODE == 1) system("Nuitrack.csv");

	return 0;
}

const char* name(JointType joint)
{
	if (MODE == 0) {
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
	if (MODE == 1) {
		switch (joint) {
		case JOINT_HEAD: return "head";
		case JOINT_LEFT_ANKLE: return "left_ankle";
		case JOINT_LEFT_COLLAR: return "spine_top";
		case JOINT_LEFT_ELBOW: return "left_elbow";
		case JOINT_LEFT_FINGERTIP: return "Dedo Izq";
		case JOINT_LEFT_FOOT: return "Pie Izq";
		case JOINT_LEFT_HAND: return "Mano izq";
		case JOINT_LEFT_HIP: return "left_hip";
		case JOINT_LEFT_KNEE: return "left_knee";
		case JOINT_LEFT_SHOULDER: return "left_shoulder";
		case JOINT_LEFT_WRIST: return "left_wrist";
		case JOINT_NECK: return "neck";
		case JOINT_TORSO: return "spine_mid";
		case JOINT_WAIST: return "spine_bottom";
		case JOINT_RIGHT_ANKLE: return "right_ankle";
		case JOINT_RIGHT_COLLAR: return "Clavicula Der";
		case JOINT_RIGHT_ELBOW: return "right_elbow";
		case JOINT_RIGHT_FINGERTIP: return "Dedo Der";
		case JOINT_RIGHT_FOOT: return "Pie Der";
		case JOINT_RIGHT_HAND: return "Mano Der";
		case JOINT_RIGHT_HIP: return "right_hip";
		case JOINT_RIGHT_KNEE: return "right_knee";
		case JOINT_RIGHT_SHOULDER: return "right_shoulder";
		case JOINT_RIGHT_WRIST: return "right_wrist";
		default: return "NONE";
		}
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
		if(MODE == 0) fichero << "\t\t--------No se detectaron sujetos-------\n";
		return;
	}

	//Articulaciones
	int caught = 0;
	auto joints = userSkeletons[0].joints;

	if (MODE == 0) {
		for (int i = 0; i < joints.size(); i++)
		{
			if (joints[i].confidence >= 0.5) //El nivel de confianza indica si la articulacion ha sido detectada
			{
				if (PRINT) //PRINT sirve para elegir si imprimir las posiciones o no
					fichero << "\t\t" << name(joints[i].type) << ": Posicion[mm] ( " << (int)joints[i].real.x << ", " << (int)joints[i].real.y << ", " << (int)joints[i].real.z << " ) \t";
				if (belongs(i, desired_joints))
					caught++;
			}
			else if (PRINT && joints[i].type != JOINT_NONE) fichero << "\t\t" << name(joints[i].type) << ": No detectada \t\t\t\t";

			if (PRINT)
			{
				if (belongs(i, desired_joints))
					fichero << "<Deseada>" << endl;
				else
					fichero << endl;
			}
		}

		fichero << "Captadas " << caught << " / 20 articulaciones de interes" << endl << endl;
	}
	if (MODE == 1) {
		t_now = high_resolution_clock::now();
		fichero << float(duration_cast<milliseconds>(t_now - t_init).count()) / 1000 << ";";

		for (auto i : desired_joints)
				fichero << joints[i].real.x << ";" << joints[i].real.y << ";" << joints[i].real.z << ";";
	}
}
bool belongs(int index, const vector<JointType> v) {
	for (int i = 0; i < v.size(); i++)
		if (index == v[i]) return true;
	return false;
}
void init()
{
	//Apertura del fichero de salida
	if (MODE == 0)	fichero.open("Nuitrack.txt", fstream::out);
	if (MODE == 1)	fichero.open("Nuitrack.csv", fstream::out);

	//Configuracion Nuitrack
	Nuitrack::init();

	//Creacion del modulo de seguimiento
	skeletonTracker = SkeletonTracker::create();

	//Enlazar la callback para recibir los datos
	skeletonTracker->connectOnUpdate(onSkeletonUpdate);

	//Iniciar Nuitrack
	Nuitrack::run();
}