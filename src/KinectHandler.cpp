/*
 * KinectHandler.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: DMC srl
 */

#include <iostream>
#include <string>
#include <signal.h>

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>

#include "KinectHandler.h"

using namespace std;
using namespace cv;

int KinectHandler::exitCondition = 0;

KinectHandler::KinectHandler(){

	this->dev 			= NULL;
	this->pipeline 		= NULL;
	this->listener 		= NULL;

	KinectHandler::protonect_shutdown = false;
}

int KinectHandler::init(){
	int types = 0;

	if(freenect2.enumerateDevices() == 0){
	   cout << KinectHandler::ERROR_NO_DEVICE << endl;
	   return 0;
	}

	std::string serial(freenect2.getDefaultDeviceSerialNumber());

	if(this->pipeline == NULL){
		dev = freenect2.openDevice(serial);
	}
	else{
		dev = freenect2.openDevice(serial, pipeline);
	}

	if(dev == NULL){
		cout << ERROR_CANT_OPEN_DEVICE <<endl;
		return 0;
	}

	types |= libfreenect2::Frame::Color;
	types |= libfreenect2::Frame::Depth | libfreenect2::Frame::Ir;

	if( !(listener = new libfreenect2::SyncMultiFrameListener(types) ) ){
		cout << ERROR_INIT_LISTENER <<endl;
		return 0;
	}

	dev->setIrAndDepthFrameListener(listener);
	dev->setColorFrameListener(listener);

    if (!dev->startStreams(1, 1)){
		cout << ERROR_STREAM <<endl;
    	return 0;
    }

	cout<<"device serial: "<< dev->getSerialNumber()<<endl;
	cout<<"device firmware: "<< dev->getFirmwareVersion()<<endl;
	cout<<"KinectHandler: init completed successfully! "<< endl;

	return 1;
}

libfreenect2::Frame* KinectHandler::update(){
	libfreenect2::FrameMap frames;
	libfreenect2::Frame *depth = NULL, *rgb, *ir;

	if(! listener->waitForNewFrame(frames, 3*1000) ){
		cout << KinectHandler::ERROR_TIMEOUT_MSG << endl;
		return NULL;
	}

	rgb		= frames[libfreenect2::Frame::Color];
	ir		= frames[libfreenect2::Frame::Ir];
	depth	= frames[libfreenect2::Frame::Depth];

	listener->release(frames);

	return depth;
}

Mat KinectHandler::convertDepth2Cv(const libfreenect2::Frame* inputFrame){
	double min, max, diff;

	Mat outputFrame;

    Mat(KinectHandler::DEPTH_HEIGHT, KinectHandler::DEPTH_WIDTH, CV_32FC1, inputFrame->data).copyTo(outputFrame);

    cv::minMaxLoc(outputFrame, &min, &max);

    diff = abs(max-min);

    if(diff < 1 )
    	diff = 1;
    outputFrame.convertTo( outputFrame, CV_8UC1, 255.0/diff, -min*255.0/diff);

	return outputFrame;
}

int KinectHandler::release(){
	protonect_shutdown = true;

	dev->stop();
	dev->close();

	return 1;
}

void KinectHandler::signalHandler(int signo){
	switch(signo){
		case SIGINT:
			KinectHandler::exitCondition = 1;
			break;
	}
}
