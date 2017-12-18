/*
 * KinectHandler.h
 *
 *  Created on: Dec 3, 2017
 *      Author: kaleidocity
 */

#ifndef KINECTHANDLER_H
#define KINECTHANDLER_H

class KinectHandler{

	private:
		libfreenect2::Freenect2 freenect2;
		libfreenect2::Freenect2Device *dev;
		libfreenect2::PacketPipeline *pipeline;
		libfreenect2::SyncMultiFrameListener *listener;

		std::string serial;

		bool protonect_shutdown;

		static const int DEPTH_WIDTH = 512;
		static const int DEPTH_HEIGHT = 424;

		const std::string ERROR_NO_DEVICE			= "Error: No device connected!";
		const std::string ERROR_CANT_OPEN_DEVICE	= "Error: Failure opening device!";
		const std::string ERROR_INIT_LISTENER		= "Error: listener init error!";
		const std::string ERROR_STREAM				= "Error: startStreams error!";
		const std::string ERROR_TIMEOUT_MSG			= "Error: Kinect Timeout!";
	public:
		//Attributes
		static int exitCondition;

		//Methods
		KinectHandler();

		int init();
		libfreenect2::Frame* update();
		int release();

		cv::Mat convertDepth2Cv(const libfreenect2::Frame*);

		static void signalHandler(int);
};

#endif
