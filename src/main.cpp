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

int main(int argc, char** argv){
	KinectHandler* handler = NULL;

	Mat cvDepthFrame;
	libfreenect2::Frame* freenectDepthFrame = NULL;

	signal(SIGINT, KinectHandler::signalHandler);

	handler = new KinectHandler();

	if( !handler->init() )
		return 0;

	int key = -1;
	while(!KinectHandler::exitCondition){

		if( (freenectDepthFrame = handler->update()) == NULL){
	    	cout << "Main Error: Can't update Frame!" << endl;
			KinectHandler::exitCondition = 1;
		}
		else{
			cvDepthFrame = handler->convertDepth2Cv(freenectDepthFrame);

			if( cvDepthFrame.rows == 0 || cvDepthFrame.cols == 0 || cvDepthFrame.data == NULL){
				cout << "Main Error: No frame read!" << endl;
				KinectHandler::exitCondition = 1;
			}
			else{
				imshow("asd", cvDepthFrame);
				key = waitKey(60);
			}
		}
	}

	handler->release();
}
