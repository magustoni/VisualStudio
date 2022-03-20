#include "TrackingViewer.hpp"

template<typename T>
inline cv::Point2f cvt(T pt, sl::float2 scale) {
    return cv::Point2f(pt.x * scale.x, pt.y * scale.y);
}

void render_2D(cv::Mat& left_display, sl::float2 img_scale, std::vector<sl::ObjectData>& objects, bool isTrackingON, sl::BODY_FORMAT body_format) {
	cv::Mat overlay = left_display.clone();
	cv::Rect roi_render(0, 0, left_display.size().width, left_display.size().height);

	// render skeleton joints and bones
	for (auto i = objects.rbegin(); i != objects.rend(); ++i) {
		sl::ObjectData& obj = (*i);
		if (renderObject(obj, isTrackingON)) {
			if (obj.keypoint_2d.size()) {
				cv::Scalar color = generateColorID_u(obj.id);
				if (body_format == sl::BODY_FORMAT::POSE_18) {
					// skeleton bones
					for (const auto& parts : SKELETON_BONES) {
						auto kp_a = cvt(obj.keypoint_2d[getIdx(parts.first)], img_scale);
						auto kp_b = cvt(obj.keypoint_2d[getIdx(parts.second)], img_scale);
						if (roi_render.contains(kp_a) && roi_render.contains(kp_b))
						{

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
							cv::line(left_display, kp_a, kp_b, color, 1);
#else
							cv::line(left_display, kp_a, kp_b, color, 1, cv::LINE_AA);
#endif
						}
					}
					auto hip_left = obj.keypoint_2d[getIdx(sl::BODY_PARTS::LEFT_HIP)];
					auto hip_right = obj.keypoint_2d[getIdx(sl::BODY_PARTS::RIGHT_HIP)];
					auto spine = (hip_left + hip_right) / 2;
					auto neck = obj.keypoint_2d[getIdx(sl::BODY_PARTS::NECK)];

					if (hip_left.x > 0 && hip_left.y > 0 && hip_right.x > 0 && hip_right.y > 0 && neck.x > 0 && neck.y > 0) {

						auto kp_a = cvt(spine, img_scale);
						auto kp_b = cvt(obj.keypoint_2d[getIdx(sl::BODY_PARTS::NECK)], img_scale);
						if (roi_render.contains(kp_a) && roi_render.contains(kp_b))
						{
#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
							cv::line(left_display, kp_a, kp_b, color, 1);
#else
							cv::line(left_display, kp_a, kp_b, color, 1, cv::LINE_AA);
#endif
						}
					}

					// skeleton joints
					for (auto& kp : obj.keypoint_2d) {
						cv::Point2f cv_kp = cvt(kp, img_scale);
						if (roi_render.contains(cv_kp))
							cv::circle(left_display, cv_kp, 3, color, -1);
					}
					cv::Point2f cv_kp = cvt(spine, img_scale);
					if (hip_left.x > 0 && hip_left.y > 0 && hip_right.x > 0 && hip_right.y > 0)
						cv::circle(left_display, cv_kp, 3, color, -1);
				}
				else if (body_format == sl::BODY_FORMAT::POSE_34) {
					// skeleton bones
					for (const auto& parts : sl::BODY_BONES_POSE_34) {
						auto kp_a = cvt(obj.keypoint_2d[getIdx(parts.first)], img_scale);
						auto kp_b = cvt(obj.keypoint_2d[getIdx(parts.second)], img_scale);
						if (roi_render.contains(kp_a) && roi_render.contains(kp_b))
						{

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
							cv::line(left_display, kp_a, kp_b, color, 1);
#else
							cv::line(left_display, kp_a, kp_b, color, 1, cv::LINE_AA);
#endif
						}
					}

					// skeleton joints
					for (auto& kp : obj.keypoint_2d) {
						cv::Point2f cv_kp = cvt(kp, img_scale);
						if (roi_render.contains(cv_kp))
							cv::circle(left_display, cv_kp, 3, color, -1);
					}
				}
			}

		}
	}
	// Here, overlay is as the left image, but with opaque masks on each detected objects
	cv::addWeighted(left_display, 0.9, overlay, 0.1, 0.0, left_display);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

template<typename T>
inline cv::Point3f cvt_3D(T pt, sl::float3 scale) {
	return cv::Point3f(pt.x * scale.x, pt.y * scale.y, pt.z * scale.z);
}

void render_3D(cv::Mat &left_display, sl::float3 img_scale, std::vector<sl::ObjectData>& objects, bool isTrackingON, sl::BODY_FORMAT body_format) {
	cv::Mat overlay = left_display.clone();
	cv::Rect roi_render(0, 0, left_display.size().width, left_display.size().height);

	// render skeleton joints and bones
	static int j = 0;
	static ofstream myFile;
	myFile.open("test.csv", std::ios_base::app);
	for (auto i = objects.rbegin(); i != objects.rend(); ++i) {
		sl::ObjectData& obj = (*i);
		sl::ObjectData& obj_3D = (*i);
		if (renderObject(obj_3D, isTrackingON)) {
			if (obj_3D.keypoint.size()) {
				cv::Scalar color = generateColorID_u(obj_3D.id);
				if (body_format == sl::BODY_FORMAT::POSE_18) {
					// skeleton bones

					// current date and time on the current system
					char fecha[1000];
					time_t t = time(NULL);
					struct tm* p = localtime(&t);
					strftime(fecha, 1000, "%A, %B %d %Y %H:%M:%S", p);
					myFile << fecha << ";";

					j++;
					myFile << j << ";";
					//cout << "--------------------Imprimo articulaciones segundo " << j << "\n";
					int k = 0;
					myFile << "Las 17 articulaciones medidas:" << ";";
					for (const auto& parts : SKELETON_BONES) {
						k++;
						auto kp_a = cvt_3D(obj_3D.keypoint[getIdx(parts.first)], img_scale);
						auto kp_b = cvt_3D(obj_3D.keypoint[getIdx(parts.second)], img_scale);

						//cout << "\tArticulacion kp_a(" << k << "): x = " << kp_a.x << "; y = " << kp_a.y << "\n";
						//cout << "\tArticulacion kp_b(" << k << "): x = " << kp_b.x << "; y = " << kp_b.y << "\n";
						if ((k == 1) || (k == 8) || (k == 10)) {
							myFile << kp_a.x << "," << kp_a.y << "," << kp_a.z << ";" << kp_b.x << "," << kp_b.y << "," << kp_b.z << ";";
						}
						else {
							myFile << kp_b.x << "," << kp_b.y << "," << kp_b.z << ";";
						}
					}

					auto hip_left = obj_3D.keypoint[getIdx(sl::BODY_PARTS::LEFT_HIP)];
					auto hip_right = obj_3D.keypoint[getIdx(sl::BODY_PARTS::RIGHT_HIP)];
					auto spine = (hip_left + hip_right) / 2;
					auto neck = obj.keypoint[getIdx(sl::BODY_PARTS::NECK)];

					if (hip_left.x > 0 && hip_left.y > 0 && hip_right.x > 0 && hip_right.y > 0 && neck.x > 0 && neck.y > 0) {
						k++;
						auto kp_a = cvt_3D(spine, img_scale);
						auto kp_b = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS::NECK)], img_scale);
						//cout << "\tArticulacion kp_a(" << k << "): x = " << kp_a.x << "; y = " << kp_a.y << "\n";
						//cout << "\tArticulacion kp_b(" << k << "): x = " << kp_b.x << "; y = " << kp_b.y << "\n";
						myFile << "Centro cadera" << ";";
						myFile << kp_a.x << "," << kp_a.y << "," << kp_a.z;
					}
					else {
						myFile << "Centro cadera" << ";" << "- , -";
					}

					//cout << "---Fin Impresion articulaciones segundo " << j << "---\n\n";
					myFile << endl;
					myFile.close();
				}
			}

		}
	}
}

void render_complete(cv::Mat &left_display, sl::float2 img_scale, sl::float3 img_scale_3D, std::vector<sl::ObjectData>& objects, bool isTrackingON, sl::BODY_FORMAT body_format, std::chrono::system_clock::time_point start){
	cv::Mat overlay = left_display.clone();
	cv::Rect roi_render(0, 0, left_display.size().width, left_display.size().height);

	static ofstream myFile;
	myFile.open("test.csv", std::ios_base::app);
	// render skeleton joints and bones
	static float j = 0;
	static int cont = 0;
	static float time_fps;
	time_t instante_inicial = time(0);
	static time_t now;
	static time_t fps;
	for (auto i = objects.rbegin(); i != objects.rend(); ++i) {
		sl::ObjectData& obj = (*i);
		sl::ObjectData& obj_3D = (*i);
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		//static std::time_t end_time = std::chrono::system_clock::to_time_t(end);

		myFile << elapsed_seconds.count() << ",";
		if (renderObject(obj_3D, isTrackingON)) {
			if (obj_3D.keypoint.size()) {
				cv::Scalar color = generateColorID_u(obj_3D.id);
				// current date and time on the current system
				char fecha[1000];
				/*time_t t = time(NULL);
				struct tm* p = localtime(&t);
				strftime(fecha, 1000, "%A, %B %d %Y %H:%M:%S", p);
				//j++;
				//time_fps = j / 100.0; //Ponlo bonito
				//myFile << to_string(time_fps) << ",";
				
				if (body_format == sl::BODY_FORMAT::POSE_18) {
					// skeleton bones
					
					////cout << "--------------------Imprimo articulaciones segundo " << j << "\n";
					int k = 0;
					for (const auto& parts : SKELETON_BONES) {
						k++;
						auto kp_a = cvt(obj.keypoint_2d[getIdx(parts.first)], img_scale);
						auto kp_b = cvt(obj.keypoint_2d[getIdx(parts.second)], img_scale);
						auto kp_a_3D = cvt_3D(obj_3D.keypoint[getIdx(parts.first)], img_scale_3D);
						auto kp_b_3D = cvt_3D(obj_3D.keypoint[getIdx(parts.second)], img_scale_3D);
						if (roi_render.contains(kp_a) && roi_render.contains(kp_b))
						{

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
							cv::line(left_display, kp_a, kp_b, color, 1);
#else
							cv::line(left_display, kp_a, kp_b, color, 1, cv::LINE_AA);
#endif
						}
						//cout << "\tArticulacion kp_a(" << k << "): x = " << kp_a.x << "; y = " << kp_a.y << "\n";
						//cout << "\tArticulacion kp_b(" << k << "): x = " << kp_b.x << "; y = " << kp_b.y << "\n";
						if ((k == 1) || (k == 8) || (k == 10)) {
							myFile << kp_a_3D.x << "," << kp_a_3D.y << "," << kp_a_3D.z << "," << kp_b_3D.x << "," << kp_b_3D.y << "," << kp_b_3D.z << ",";
						}
						else {
							myFile << kp_b_3D.x << "," << kp_b_3D.y << "," << kp_b_3D.z << ",";
						}
					}

					auto hip_left = obj_3D.keypoint[getIdx(sl::BODY_PARTS::LEFT_HIP)];
					auto hip_right = obj_3D.keypoint[getIdx(sl::BODY_PARTS::RIGHT_HIP)];
					auto spine = (hip_left + hip_right) / 2;
					auto neck = obj.keypoint[getIdx(sl::BODY_PARTS::NECK)];
					auto mid_shoulder = (obj_3D.keypoint[getIdx(sl::BODY_PARTS::RIGHT_SHOULDER)] + obj_3D.keypoint[getIdx(sl::BODY_PARTS::LEFT_SHOULDER)]) / 2;

					if (hip_left.x > 0 && hip_left.y > 0 && hip_right.x > 0 && hip_right.y > 0 && neck.x > 0 && neck.y > 0) {
						k++;
						auto kp_a = cvt(spine, img_scale);
						auto kp_b = cvt(obj.keypoint_2d[getIdx(sl::BODY_PARTS::NECK)], img_scale);

						auto kp_a_3D = cvt_3D(spine, img_scale_3D);
						auto kp_b_3D = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS::NECK)], img_scale_3D);
						myFile << kp_a_3D.x << "," << kp_a_3D.y << "," << kp_a_3D.z << ",";

						if (roi_render.contains(kp_a) && roi_render.contains(kp_b))
						{
#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
							cv::line(left_display, kp_a, kp_b, color, 1);
#else
							cv::line(left_display, kp_a, kp_b, color, 1, cv::LINE_AA);
#endif
						}
					}
					else {
						myFile << "-,-,-" << ",";
					}

					if (hip_left.x > 0 && hip_left.y > 0 && hip_right.x > 0 && hip_right.y > 0 && neck.x > 0 && neck.y > 0) {
						k++;
						myFile << mid_shoulder.x << "," << mid_shoulder.y << "," << mid_shoulder.z;
					}
					else {
						myFile << "-,-,-";
					}

					// skeleton joints
					for (auto& kp : obj.keypoint_2d) {
						cv::Point2f cv_kp = cvt(kp, img_scale);
						if (roi_render.contains(cv_kp))
							cv::circle(left_display, cv_kp, 3, color, -1);
					}
					cv::Point2f cv_kp = cvt(spine, img_scale);
					if (hip_left.x > 0 && hip_left.y > 0 && hip_right.x > 0 && hip_right.y > 0)
						cv::circle(left_display, cv_kp, 3, color, -1);
					//cout << "---Fin Impresion articulaciones segundo " << j << "---\n\n";
					myFile << endl;
					myFile.close();
				}
				else if (body_format == sl::BODY_FORMAT::POSE_34) {
					int k = 0;
					// skeleton bones
					for (const auto& parts : BODY_BONES_POSE_34) {
						k++;
						auto kp_a = cvt(obj.keypoint_2d[getIdx(parts.first)], img_scale);
						auto kp_b = cvt(obj.keypoint_2d[getIdx(parts.second)], img_scale);
						auto kp_a_3D = cvt_3D(obj_3D.keypoint[getIdx(parts.first)], img_scale_3D);
						auto kp_b_3D = cvt_3D(obj_3D.keypoint[getIdx(parts.second)], img_scale_3D);
						if (roi_render.contains(kp_a) && roi_render.contains(kp_b))
						{

#if (defined(CV_VERSION_EPOCH) && CV_VERSION_EPOCH == 2)
							cv::line(left_display, kp_a, kp_b, color, 1);
#else
							cv::line(left_display, kp_a, kp_b, color, 1, cv::LINE_AA);
#endif
						}
						/*if ((k == 1)) {
							myFile << kp_a_3D.x << "," << kp_a_3D.y << "," << kp_a_3D.z << "," << kp_b_3D.x << "," << kp_b_3D.y << "," << kp_b_3D.z << ",";
						}
						else {
							myFile << kp_b_3D.x << "," << kp_b_3D.y << "," << kp_b_3D.z << ",";
						}
					}
					auto kp_3D_1 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::HEAD)], img_scale_3D);
					myFile << kp_3D_1.x << "," << kp_3D_1.y << "," << kp_3D_1.z << ",";
					auto kp_3D_2 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::NECK)], img_scale_3D);
					myFile << kp_3D_2.x << "," << kp_3D_2.y << "," << kp_3D_2.z << ",";
					auto kp_3D_3 = (cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_CLAVICLE)], img_scale_3D) + cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_CLAVICLE)], img_scale_3D)) / 2;
					myFile << kp_3D_3.x << "," << kp_3D_3.y << "," << kp_3D_3.z << ",";
					auto kp_3D_4 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::CHEST_SPINE)], img_scale_3D);
					myFile << kp_3D_4.x << "," << kp_3D_4.y << "," << kp_3D_4.z << ",";
					auto kp_3D_5 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::PELVIS)], img_scale_3D);
					myFile << kp_3D_5.x << "," << kp_3D_5.y << "," << kp_3D_5.z << ",";
					auto kp_3D_6 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_SHOULDER)], img_scale_3D);
					myFile << kp_3D_6.x << "," << kp_3D_6.y << "," << kp_3D_6.z << ",";
					auto kp_3D_7 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_ELBOW)], img_scale_3D);
					myFile << kp_3D_7.x << "," << kp_3D_7.y << "," << kp_3D_7.z << ",";
					auto kp_3D_8 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_WRIST)], img_scale_3D);
					myFile << kp_3D_8.x << "," << kp_3D_8.y << "," << kp_3D_8.z << ",";
					auto kp_3D_9 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_SHOULDER)], img_scale_3D);
					myFile << kp_3D_9.x << "," << kp_3D_9.y << "," << kp_3D_9.z << ",";
					auto kp_3D_10 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_ELBOW)], img_scale_3D);
					myFile << kp_3D_10.x << "," << kp_3D_10.y << "," << kp_3D_10.z << ",";
					auto kp_3D_11 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_WRIST)], img_scale_3D);
					myFile << kp_3D_11.x << "," << kp_3D_11.y << "," << kp_3D_11.z << ",";
					auto kp_3D_12 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_HIP)], img_scale_3D);
					myFile << kp_3D_12.x << "," << kp_3D_12.y << "," << kp_3D_12.z << ",";
					auto kp_3D_13 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_KNEE)], img_scale_3D);
					myFile << kp_3D_13.x << "," << kp_3D_13.y << "," << kp_3D_13.z << ",";
					auto kp_3D_14 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_ANKLE)], img_scale_3D);
					myFile << kp_3D_14.x << "," << kp_3D_14.y << "," << kp_3D_14.z << ",";
					auto kp_3D_15 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::LEFT_FOOT)], img_scale_3D);
					myFile << kp_3D_15.x << "," << kp_3D_15.y << "," << kp_3D_15.z << ",";
					auto kp_3D_16 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_HIP)], img_scale_3D);
					myFile << kp_3D_16.x << "," << kp_3D_16.y << "," << kp_3D_16.z << ",";
					auto kp_3D_17 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_KNEE)], img_scale_3D);
					myFile << kp_3D_17.x << "," << kp_3D_17.y << "," << kp_3D_17.z << ",";
					auto kp_3D_18 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_ANKLE)], img_scale_3D);
					myFile << kp_3D_18.x << "," << kp_3D_18.y << "," << kp_3D_18.z << ",";
					auto kp_3D_19 = cvt_3D(obj.keypoint[getIdx(sl::BODY_PARTS_POSE_34::RIGHT_FOOT)], img_scale_3D);
					myFile << kp_3D_19.x << "," << kp_3D_19.y << "," << kp_3D_19.z;
					// skeleton joints
					for (auto& kp : obj.keypoint_2d) {
						cv::Point2f cv_kp = cvt(kp, img_scale);
						if (roi_render.contains(cv_kp))
							cv::circle(left_display, cv_kp, 3, color, -1);
					}
					myFile << endl;
					myFile.close();
				}
			}

		}
	}
	// Here, overlay is as the left image, but with opaque masks on each detected objects
	cv::addWeighted(left_display, 0.9, overlay, 0.1, 0.0, left_display);
}

*/