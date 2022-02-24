#include <assert.h>
#include <iostream>
#include <fstream>
#include <k4a/k4a.hpp>
#include <k4abt.hpp>

#define FRAMES 20 //Numero de frames a capturar
#define MODE 1 //Modo de funcionamiento
//0 -> Modo analisis manual en .txt
//1- > Modo captura datos en .xls
#define PRINT false //Salida (solo modo 0)
//false -> Solo numero articulaciones captadas
//true -> Numero y posiciones de cada una
#define GPU false //Activar procesamiento en GPU

using namespace std;

//Variables globales
k4a::device device; //Dispositivo asociado a la camara
k4a::capture sensor_capture; //Capturas de imagen
k4abt::tracker tracker; //Modulo "tracker"
k4abt::frame body_frame; //Frame del cuerpo
k4abt_body_t body; //Objeto cuerpo
uint32_t num_bodies; //Numero de cuerpos detectados
fstream fichero; //Fichero de salida

//Conjunto de articulaciones de interes
const vector<int> desired_joints = { 1,2,3,4,5,6,7,11,12,13,14,18,19,20,21,22,23,24,25,26 };

//Funciones
const char* name(int i); //Devuelve el nombre de la articulacion segun su numero
bool belongs(int index, const vector<int> v); //Devuelve si la articulacion pertenece al conjunto de deseadas
int print_body_information(k4abt_body_t body); //Gestiona lal informacion de las capturas
void init(); //Inicializacion de lo relacionado con la camara


int main()
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
		fichero << "Frame\t\t";
		for (auto k : desired_joints) {
			fichero << name(k) << " X\t";
			fichero << name(k) << " Y\t";
			fichero << name(k) << " Z\t";
		}
		fichero << endl;
	}

	//Bucle de captura
	for (int frame = 0; frame < FRAMES; frame++)
	{
		cout << "Procesando frame " << frame + 1 << endl;
		//Obtener captura
		device.get_capture(&sensor_capture, chrono::milliseconds(K4A_WAIT_INFINITE));
		//Introducirla en el tracker
		tracker.enqueue_capture(sensor_capture);
		//Obtener reslutados
		body_frame = tracker.pop_result();
		//Numero de cuerpos detectados
		num_bodies = body_frame.get_num_bodies();

		if (MODE == 0) fichero << "Frame " << frame + 1 << endl;
		if (MODE == 1) fichero << frame + 1 << "\t\t";

		if (num_bodies == 0) {
			if (MODE == 0)
				fichero << "\t\t--------No se detectaron sujetos-------\n";
		}
		else {
			body = body_frame.get_body(0);
			if (MODE == 0) fichero << "Captadas " << print_body_information(body) << " / 20 articulaciones de interes" << endl << endl;
			if (MODE == 1) print_body_information(body);
		}

	}
	cout << "Fin del programa Kinect" << endl;

	fichero.close();
	if (MODE == 0) system("Kinect.txt");
	if (MODE == 1) system("Kinect.xls");

	return 0;
}

const char* name(int i) {
	if (MODE == 0) {
		switch (i) {
		case 0: return "Centro Cadera\t";
		case 1: return "Cintura\t\t";
		case 2: return "Esternon\t";
		case 3: return "Cuello\t\t";
		case 4: return "Clavicula Izq\t";
		case 5: return "Hombro Izq\t";
		case 6: return "Codo Izq\t";
		case 7: return "Muneca Izq\t";
		case 8: return "Mano Izq\t";
		case 9: return "Palma Izq\t";
		case 10: return "Pulgar Izq\t";
		case 11: return "Clavicula Der\t";
		case 12: return "Hombro Der\t";
		case 13: return "Codo Der\t";
		case 14: return "Muneca Der\t";
		case 15: return "Mano Der\t";
		case 16: return "Palma Der\t";
		case 17: return "Pulgar Der\t";
		case 18: return "Cadera Izq\t";
		case 19: return "Rodilla Izq\t";
		case 20: return "Tobillo Izq\t";
		case 21: return "Pie Izq\t\t";
		case 22: return "Cadera Der\t";
		case 23: return "Rodilla Der\t";
		case 24: return "Tobillo Der\t";
		case 25: return "Pie Der\t\t";
		case 26: return "Cabeza\t\t";
		case 27: return "Nariz\t\t";
		case 28: return "Ojo Izq\t\t";
		case 29: return "Oreja Izq\t";
		case 30: return "Ojo Der\t\t";
		case 31: return "Oreja Der\t";
		default: return "NONE\t\t";
		}
	}
	if (MODE == 1) {
		switch (i) {
		case 0: return "Centro Cadera";
		case 1: return "Cintura";
		case 2: return "Esternon";
		case 3: return "Cuello";
		case 4: return "Clavicula Izq";
		case 5: return "Hombro Izq";
		case 6: return "Codo Izq";
		case 7: return "Muneca Izq";
		case 8: return "Mano Izq";
		case 9: return "Palma Izq";
		case 10: return "Pulgar Izq";
		case 11: return "Clavicula Der";
		case 12: return "Hombro Der";
		case 13: return "Codo Der";
		case 14: return "Muneca Der";
		case 15: return "Mano Der";
		case 16: return "Palma Der";
		case 17: return "Pulgar Der";
		case 18: return "Cadera Izq";
		case 19: return "Rodilla Izq";
		case 20: return "Tobillo Izq";
		case 21: return "Pie Izq";
		case 22: return "Cadera Der";
		case 23: return "Rodilla Der";
		case 24: return "Tobillo Der";
		case 25: return "Pie Der";
		case 26: return "Cabeza";
		case 27: return "Nariz";
		case 28: return "Ojo Izq";
		case 29: return "Oreja Izq";
		case 30: return "Ojo Der";
		case 31: return "Oreja Der";
		default: return "NONE";
		}
	}
}
bool belongs(int index, const vector<int> v) {
	for (int i = 0; i < v.size(); i++)
		if (index == v[i]) return true;
	return false;
}
int print_body_information(k4abt_body_t body)
{
	int caught = 0; //Numero de articulaciones de interes captadas

	if (MODE == 0) {
		for (int i = 0; i < (int)K4ABT_JOINT_COUNT; i++)
		{
			k4a_float3_t position = body.skeleton.joints[i].position;
			if (body.skeleton.joints[i].confidence_level >= K4ABT_JOINT_CONFIDENCE_MEDIUM){ //El nivel de confianza indica si la articulacion ha sido detectada
				if (PRINT) //PRINT sirve para elegir si imprimir las posiciones o no
					fichero << "\t\t" << name(i) << ": Posicion[mm] ( " << (int)position.v[0] << ", " << (int)position.v[1] << ", " << (int)position.v[2] << " ) \t";
				if (belongs(i, desired_joints))
					caught++;
			}
			else if (PRINT) fichero << "\t\t" << name(i) << ": No detectada \t\t\t\t";

			if (PRINT) {
				if (belongs(i, desired_joints))
					fichero << "<Deseada>" << endl;
				else
					fichero << endl;
			}
		}
	}
	if (MODE == 1) {
		for (int i = 0; i < (int)K4ABT_JOINT_COUNT; i++)
		{
			k4a_float3_t position = body.skeleton.joints[i].position;
			if (belongs(i, desired_joints))	{
				if (body.skeleton.joints[i].confidence_level >= K4ABT_JOINT_CONFIDENCE_MEDIUM) //El nivel de confianza indica si la articulacion ha sido detectada
					fichero << position.v[0] << "\t" << position.v[1] << "\t" << position.v[2] << "\t";
				else fichero << 0 << "\t" << 0 << "\t" << 0 << "\t";
			}
		}
		fichero << endl;
	}
	return caught;
}
void init() {
	//Configuracion de la camara
	k4a_device_configuration_t device_config = K4A_DEVICE_CONFIG_INIT_DISABLE_ALL;
	device_config.depth_mode = K4A_DEPTH_MODE_NFOV_2X2BINNED;
	device = k4a::device::open(0);
	device.start_cameras(&device_config);

	//Inicializacion del objeto "tracker"
	k4a::calibration sensor_calibration = device.get_calibration(device_config.depth_mode, device_config.color_resolution);
	if (!GPU) {
		k4abt_tracker_configuration_t tracker_config;
		tracker_config.processing_mode = K4ABT_TRACKER_PROCESSING_MODE_CPU;
		tracker = k4abt::tracker::create(sensor_calibration, tracker_config);
	}
	else tracker = k4abt::tracker::create(sensor_calibration);

	//Apertura del fichero de salida
	if (MODE == 0)	fichero.open("Kinect.txt", fstream::out);
	if (MODE == 1)	fichero.open("Kinect.xls", fstream::out);
}