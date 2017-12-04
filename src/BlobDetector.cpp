/*
 * ComputerVisionProcessor.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: DMC srl
 */

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>

#include "BlobDetector.h"

using namespace std;
using namespace cv;

BlobDetector::BlobDetector() {

}

BlobDetector::~BlobDetector() {

}

Mat BlobDetector::preProcess(const Mat input){
    Mat output(input.rows, input.cols, CV_8UC1);

	if(input.channels() > 1)
		cvtColor(input, output, CV_BGR2GRAY);

	else
	    Mat(input.rows, input.cols, CV_8UC1, input.data).copyTo(output);

	normalize(output, output, 0, 255, NORM_MINMAX, CV_8UC1);
	equalizeHist(output, output);

	return output;
}

vector<vector<Point> > BlobDetector::detectBlobs(const Mat input){

    Mat thresholded(input.rows, input.cols, CV_8UC1);
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    int counter = 0;

    if( input.rows == 0 || input.cols == 0 || input.data == NULL){
    	cout << "matrice vuota" << endl;
    	return blobs;
    }
    threshold(input, thresholded, BlobDetector::THRESHOLD_VALUE, 255, THRESH_BINARY_INV);

	imshow("thresjhr", thresholded);

    findContours( thresholded, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    blobs.clear();
    while(counter < contours.size()){
    	if(contourArea(contours[counter]) > BlobDetector::MIN_AREA_SIZE){
    	    this->blobs.push_back(contours[counter]);
    	}
	    counter++;
   	}

    return blobs;
}

Mat BlobDetector::drawBlob(const vector<vector<Point> > contours, int rows, int cols){
	Mat drawing = Mat::zeros( Size(cols, rows), CV_8UC1 );

	for( int i = 0; i< contours.size(); i++ ){
	   Scalar color = Scalar(255);
	   drawContours( drawing, contours, i, color, 1, 8, NULL, 0, Point() );
	}

	return drawing;
}
