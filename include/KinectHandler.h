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

	public:
		//Attributes
		static const int DEPTH_WIDTH = 512;
		static const int DEPTH_HEIGHT = 424;

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
