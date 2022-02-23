#include "nuitrack/Nuitrack.h"
#include <signal.h>
#include <iomanip>
#include <iostream>

using namespace tdv::nuitrack;
FILE* fichero = fopen("C:/Users/mateo/Desktop/Nuitrack.txt", "w");

const char* name(JointType joint) {
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
	case JOINT_TORSO: return "Torso\t\t";
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

// Callback for the hand data update event
void onHandUpdate(HandTrackerData::Ptr handData)
{
	if (!handData)
	{
		// No hand data
		std::cout << "No hand data" << std::endl;
		return;
	}

	auto userHands = handData->getUsersHands();
	if (userHands.empty())
	{
		// No user hands
		return;
	}

	auto rightHand = userHands[0].rightHand;
	if (!rightHand)
	{
		// No right hand
		std::cout << "Right hand of the first user is not found" << std::endl;
		return;
	}

	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Right hand position: "
		"x = " << rightHand->xReal << ", "
		"y = " << rightHand->yReal << ", "
		"z = " << rightHand->zReal << std::endl;
}
void onSkeletonUpdate(SkeletonData::Ptr skeletonData)
{
	//No se recibio correctamente el puntero
	if (!skeletonData) {
		std::cout << "No skeleton data" << std::endl;
		return;
	}

	//Obtener esqueletos
	auto userSkeletons = skeletonData->getSkeletons();
	//No hay esqueletos
	if (userSkeletons.empty())
	{
		fprintf(fichero, ", \t\t\t\t--------No se detectaron sujetos-------\n");
		return;
	}

	//Articulaciones
	auto joints = userSkeletons[0].joints;
	std::cout << joints[0].real.x << std::endl;
	fprintf(fichero, "\n");

	for (int i = 0; i < joints.size(); i++)
	{
		if (joints[i].type != JOINT_NONE)
			fprintf(fichero, "\t%s: Posicion[mm] ( %d, %d, %d )\n",
				name(joints[i].type), (int)joints[i].real.x, (int)joints[i].real.y, (int)joints[i].real.z);
	}
	fprintf(fichero, "\n");
}

bool finished;
void signalHandler(int signal)
{
	if (signal == SIGINT)
		finished = true;
}

int main(int argc, char* argv[])
{
	signal(SIGINT, &signalHandler);
	std::string configPath = "";
	if (argc > 1)
		configPath = argv[1];

	//Configuracion Nuitrack
	std::cout << "Configurando camara" << std::endl;
	try { Nuitrack::init(configPath); }
	catch (const Exception& e) {
		std::cerr << "Can not initialize Nuitrack (ExceptionType: " << e.type() << ")" << std::endl;
		return EXIT_FAILURE;
	}

	//Creacion del modulo de seguimiento
	//auto handTracker = HandTracker::create();
	auto skeletonTracker = SkeletonTracker::create();

	//Enlazar la callback para recibir los datos
	//handTracker->connectOnUpdate(onHandUpdate);
	skeletonTracker->connectOnUpdate(onSkeletonUpdate);

	//Iniciar Nuitrack
	try { Nuitrack::run(); }
	catch (const Exception& e)
	{
		std::cerr << "Can not start Nuitrack (ExceptionType: " << e.type() << ")" << std::endl;
		return EXIT_FAILURE;
	}

	int errorCode = EXIT_SUCCESS;
	//Bucle de captura
	for (int frame = 0; frame < 500; frame++)
	{
		std::cout << "Procesando frame " << frame + 1 << std::endl;
		fprintf(fichero, "Frame %d", frame + 1);
		//Esperar datos
		try { Nuitrack::waitUpdate(skeletonTracker); }
		catch (LicenseNotAcquiredException& e)
		{
			std::cerr << "LicenseNotAcquired exception (ExceptionType: " << e.type() << ")" << std::endl;
			errorCode = EXIT_FAILURE;
			break;
		}
		catch (const Exception& e)
		{
			std::cerr << "Nuitrack update failed (ExceptionType: " << e.type() << ")" << std::endl;
			errorCode = EXIT_FAILURE;
		}
	}

	//Liberar Nuitrack
	try { Nuitrack::release(); }
	catch (const Exception& e)
	{
		std::cerr << "Nuitrack release failed (ExceptionType: " << e.type() << ")" << std::endl;
		errorCode = EXIT_FAILURE;
	}
	std::cout << "Fin del programa Nuitrack" << std::endl;
	return errorCode;
}