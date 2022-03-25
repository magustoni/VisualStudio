///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2021, STEREOLABS.
//
// All rights reserved.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////

#ifdef _SL_JETSON_
const bool isJetson = true;
#else
const bool isJetson = false;
#endif

#include <sl/Camera.hpp>
//#include "GLViewer.hpp"
#include "TrackingViewer.hpp"
#include <math.h>
#include <iostream>
#include <fstream>
#include <chrono>

#define INPUT 0 // 0 -> video | 1 -> .svo
#define CONFIDENCE 40 //Minima confianza admitida (0-100)

using namespace std;
using namespace sl;
using namespace std::chrono;

template<typename T>
inline cv::Point3f cvt_3D(T pt, sl::float3 scale) {
	return cv::Point3f(pt.x * scale.x, pt.y * scale.y, pt.z * scale.z);
}

bool quit = false; //Termina el bucle cuando pasa a true
void print(string msg_prefix, ERROR_CODE err_code = ERROR_CODE::SUCCESS, string msg_suffix = ""); //Imprime mensaje en caso de error


int main(int argc, char** argv)
{
	////////////////////////////////////////////////////////////////////////////////CONFIG INICIALES////////////////////////////////////////////////////////////////////////////////

	//Modulos y variables de configuracion
	fstream file; //Fichero de salida
	Camera zed; //Objeto camara
	Objects bodies; //Objeto cuerpos
	InitParameters init_parameters; //Parametros camara
	PositionalTrackingParameters positional_tracking_parameters; //Parametros tracking
	ObjectDetectionRuntimeParameters objectTracker_parameters_rt; //Parametros runtime
	ObjectDetectionParameters obj_det_params; //Parametros deteccion objetos
	ERROR_CODE returned_state; //Codigo de error|exito
	steady_clock::time_point t_init, t_now; //Medicion de tiempo

	//Apertura del fichero
	file.open("release/ZED.csv", fstream::out);

	//Parametros ZED
	init_parameters.camera_resolution = RESOLUTION::VGA; //Resolucion
	init_parameters.camera_fps = 100; //FPS
	init_parameters.depth_mode = DEPTH_MODE::PERFORMANCE; //Modo profundidad
	init_parameters.coordinate_system = COORDINATE_SYSTEM::IMAGE; //Sistema coordenadas

	if (INPUT) init_parameters.input.setFromSVOFile("input.svo"); //Entrada desde fichero
	init_parameters.sensors_required = TRUE;

	//Inicializacion ZED
	returned_state = zed.open(init_parameters);
	if (returned_state != ERROR_CODE::SUCCESS) {
		print("Open Camera", returned_state, "\nExit program.");
		zed.close();
		return EXIT_FAILURE;
	}
	returned_state = zed.enablePositionalTracking(positional_tracking_parameters);
	if (returned_state != ERROR_CODE::SUCCESS) {
		print("enable Positional Tracking", returned_state, "\nExit program.");
		zed.close();
		return EXIT_FAILURE;
	}

	//Modulo deteccion objetos
	objectTracker_parameters_rt.detection_confidence_threshold = CONFIDENCE; //Minima confianza admitida (0-100) 
	obj_det_params.enable_tracking = true; //Habilitar tracking
	obj_det_params.enable_body_fitting = false; //Suavizar movimientos esqueleto
	obj_det_params.body_format = BODY_FORMAT::POSE_34; //Num articulaciones
	obj_det_params.detection_model = DETECTION_MODEL::HUMAN_BODY_ACCURATE; //Modelo de deteccion
	returned_state = zed.enableObjectDetection(obj_det_params);
	if (returned_state != ERROR_CODE::SUCCESS) {
		print("enable Object Detection", returned_state, "\nExit program.");
		zed.close();
		return EXIT_FAILURE;
	}

	//Configuraciones varias (ni idea)
	auto camera_config = zed.getCameraInformation().camera_configuration;
	Resolution display_resolution(min((int)camera_config.resolution.width, 1280), min((int)camera_config.resolution.height, 720));
	cv::Mat image_left_ocv(display_resolution.height, display_resolution.width, CV_8UC4, 1);
	Mat image_left(display_resolution, MAT_TYPE::U8_C4, image_left_ocv.data, image_left_ocv.step);
	sl::float2 img_scale(display_resolution.width / (float)camera_config.resolution.width, display_resolution.height / (float)camera_config.resolution.height);
	sl::float3 img_scale_3D(display_resolution.width / (float)camera_config.resolution.width, display_resolution.height / (float)camera_config.resolution.height);
	Resolution pc_resolution(min((int)camera_config.resolution.width, 720), min((int)camera_config.resolution.height, 404));
	auto camera_parameters = zed.getCameraInformation(pc_resolution).camera_configuration.calibration_parameters.left_cam;
	Mat point_cloud(pc_resolution, MAT_TYPE::F32_C4, MEM::GPU);
	Pose cam_pose;
	cam_pose.pose_data.setIdentity();

	// Visor OpenGL
	GLViewer viewer;
	viewer.init(argc, argv, camera_parameters, obj_det_params.enable_tracking, obj_det_params.body_format);
	bool gl_viewer_available = true;

	/* Camara fija
	Plane floor_plane; // floor plane handle
	Transform reset_from_floor_plane; // camera transform once floor plane is detected
	bool need_floor_plane = positional_tracking_parameters.set_as_static;
	*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Variables de calculo
	cv::Point3f articulacion;
	cv::Point3f cadera, rodilla, tobillo;
	cv::Point3f femur, tibia;
	float angulo;

	//Cabecera fichero
	file << "tiempo;head.x;head.y;head.z;neck.x;neck.y;neck.z;spine_top.x;spine_top.y;spine_top.z;spine_mid.x;spine_mid.y;spine_mid.z;spine_bottom.x;spine_bottom.y;spine_bottom.z;left_shoulder.x;left_shoulder.y;left_shoulder.z;left_elbow.x;left_elbow.y;left_elbow.z;left_hand.x;left_hand.y;left_hand.z;right_shoulder.x;right_shoulder.y;right_shoulder.z;right_elbow.x;right_elbow.y;right_elbow.z;right_hand.x;right_hand.y;right_hand.z;right_hip.x;right_hip.y;right_hip.z;right_knee.x;right_knee.y;right_knee.z;right_ankle.x;right_ankle.y;right_ankle.z;left_hip.x;left_hip.y;left_hip.z;left_knee.x;left_knee.y;left_knee.z;left_ankle.x;left_ankle.y;left_ankle.z;left_angle;right_angle" << endl;
	//file << "tiempo;joint_position_head.x;joint_position_head.y;joint_position_head.z;joint_position_neck.x;joint_position_neck.y;joint_position_neck.z;joint_position_spine_top.x;joint_position_spine_top.y;joint_position_spine_top.z;joint_position_spine_mid.x;joint_position_spine_mid.y;joint_position_spine_mid.z;joint_position_spine_bottom.x;joint_position_spine_bottom.y;joint_position_spine_bottom.z;joint_position_left_shoulder.x;joint_position_left_shoulder.y;joint_position_left_shoulder.z;joint_position_left_elbow.x;joint_position_left_elbow.y;joint_position_left_elbow.z;joint_position_left_hand.x;joint_position_left_hand.y;joint_position_left_hand.z;joint_position_right_shoulder.x;joint_position_right_shoulder.y;joint_position_right_shoulder.z;joint_position_right_elbow.x;joint_position_right_elbow.y;joint_position_right_elbow.z;joint_position_right_hand.x;joint_position_right_hand.y;joint_position_right_hand.z;joint_position_right_hip.x;joint_position_right_hip.y;joint_position_right_hip.z;joint_position_right_knee.x;joint_position_right_knee.y;joint_position_right_knee.z;joint_position_right_ankle.x;joint_position_right_ankle.y;joint_position_right_ankle.z;joint_position_left_hip.x;joint_position_left_hip.y;joint_position_left_hip.z;joint_position_left_knee.x;joint_position_left_knee.y;joint_position_left_knee.z;joint_position_left_ankle.x;joint_position_left_ankle.y;joint_position_left_ankle.z" << endl;
	t_init = high_resolution_clock::now();

	//Bucle principal
	int frame = 0;
	while (!quit)//(gl_viewer_available && !quit)
	{
		//Obtencion imagenes
		if (zed.grab() == ERROR_CODE::SUCCESS) {
			cout << "Working on frame " << ++frame << endl;

			/* Camara fija
			if (need_floor_plane) {
				if (zed.findFloorPlane(floor_plane, reset_from_floor_plane) == ERROR_CODE::SUCCESS) {
					need_floor_plane = false;
					viewer.setFloorPlaneEquation(floor_plane.getPlaneEquation());
				}
			}
			*/

			//Mediciones
			zed.retrieveObjects(bodies, objectTracker_parameters_rt);
			zed.retrieveImage(image_left, VIEW::LEFT, MEM::CPU, display_resolution);
			zed.retrieveMeasure(point_cloud, MEASURE::XYZRGBA, MEM::GPU, pc_resolution);
			zed.getPosition(cam_pose, REFERENCE_FRAME::WORLD);

			// Visor OpenGL
			viewer.updateData(point_cloud, bodies.object_list, cam_pose.pose_data);
			gl_viewer_available = viewer.isAvailable();
			
			//Terminar al finalizar video input
			if (INPUT && zed.getSVOPosition() == zed.getSVONumberOfFrames()) quit = true;

			//Renderizar imagenes
			render_2D(image_left_ocv, img_scale, bodies.object_list, obj_det_params.enable_tracking, obj_det_params.body_format);

			//Imprimir archivo
			t_now = high_resolution_clock::now();
			file << float(duration_cast<milliseconds>(t_now - t_init).count()) / 1000 << ";"; //Conteo de tiempo

			if (!bodies.object_list.empty()) //Si se detectaron esqueletos
			{
				sl::ObjectData& obj = *bodies.object_list.rbegin(); //Solo el primer esqueleto detectado

				//Cabeza
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::HEAD)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Cuello
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::NECK)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Columna superior
				articulacion = (cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_CLAVICLE)], img_scale_3D) + cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_CLAVICLE)], img_scale_3D)) / 2;
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Columna media
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::CHEST_SPINE)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Columna baja
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::PELVIS)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Hombro izq
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_SHOULDER)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Codo izq
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_ELBOW)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Muñeca izq
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_WRIST)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Hombro der
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_SHOULDER)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Codo der
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_ELBOW)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Muñeca der
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_WRIST)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Cadera der
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_HIP)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Rodilla der
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_KNEE)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Tobillo der
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_ANKLE)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Cadera izq
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_HIP)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Rodilla izq
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_KNEE)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";"; 
				//Tobillo izq
				articulacion = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_ANKLE)], img_scale_3D);
				file << articulacion.x << ";" << articulacion.y << ";" << articulacion.z << ";";

				//Angulo rodilla izq
				cadera = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_HIP)], img_scale_3D);
				rodilla = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_KNEE)], img_scale_3D);
				tobillo = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_ANKLE)], img_scale_3D);
				femur = rodilla - cadera;
				tibia = tobillo - rodilla;
				
				angulo = 180 * acos((femur.x * tibia.x + femur.y * tibia.y + femur.z * tibia.z) / (sqrt(pow(femur.x, 2) + pow(femur.y, 2) + pow(femur.z, 2)) * sqrt(pow(tibia.x, 2) + pow(tibia.y, 2) + pow(tibia.z, 2)))) / 3.14159 ;
				file << angulo << ";";

				//Angulo rodilla der
				cadera = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_HIP)], img_scale_3D);
				rodilla = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_KNEE)], img_scale_3D);
				tobillo = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_ANKLE)], img_scale_3D);
				femur = rodilla - cadera;
				tibia = tobillo - rodilla;

				angulo = 180 * acos((femur.x * tibia.x + femur.y * tibia.y + femur.z * tibia.z) / (sqrt(pow(femur.x, 2) + pow(femur.y, 2) + pow(femur.z, 2)) * sqrt(pow(tibia.x, 2) + pow(tibia.y, 2) + pow(tibia.z, 2)))) / 3.14159;
				file << angulo;
			}

			file << endl;

			//Visor imagen real
			cv::imshow("ZED 2D View", image_left_ocv);
		}
	}

	//Liberar objetos y modulos
	viewer.exit();
	image_left.free();
	point_cloud.free();
	//floor_plane.clear();
	bodies.object_list.clear();
	zed.disableObjectDetection();
	zed.disablePositionalTracking();
	zed.close();
	file.close();

	return EXIT_SUCCESS;
}

void print(string msg_prefix, ERROR_CODE err_code, string msg_suffix) {
	if (err_code != ERROR_CODE::SUCCESS)
		cout << "[Error]";
	cout << " " << msg_prefix << " ";
	if (err_code != ERROR_CODE::SUCCESS) {
		cout << " | " << toString(err_code) << " : ";
		cout << toVerbose(err_code);
	}
	if (!msg_suffix.empty())
		cout << " " << msg_suffix;
	cout << endl;
}
