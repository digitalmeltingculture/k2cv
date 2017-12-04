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
#include "BlobDetector.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv){
	KinectHandler* handler = NULL;
	BlobDetector* blobDetector = NULL;

	Mat inputFrame, preprocessedFrame;

	signal(SIGINT, KinectHandler::signalHandler);

	handler = new KinectHandler();
	blobDetector = new BlobDetector();

	if( !handler->init() )
		return 0;

	int key = -1;
	while(!KinectHandler::exitCondition){
		//handler->update();
		inputFrame = handler->convertDepth2Cv(handler->update());

	    if( inputFrame.rows == 0 || inputFrame.cols == 0 || inputFrame.data == NULL){
	    	cout << "matrice vuota" << endl;
	    	continue;
	    }

	    preprocessedFrame = blobDetector->preProcess(inputFrame);

		vector<vector<Point> >blobs = blobDetector->detectBlobs(preprocessedFrame);

		Mat drawing = blobDetector->drawBlob(blobs, KinectHandler::DEPTH_HEIGHT, KinectHandler::DEPTH_WIDTH );
		imshow("asd", inputFrame);
		imshow("asd2", preprocessedFrame);
		imshow("qwr", drawing);

		key = waitKey(60);
	}

	handler->release();
}
