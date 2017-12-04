/*
 * BlobDetector.h
 *
 *  Created on: Dec 3, 2017
 *      Author: DMC srl
 */

#ifndef INCLUDE_BLOBDETECTOR_H_
#define INCLUDE_BLOBDETECTOR_H_

class BlobDetector {

	private:
		static const int THRESHOLD_VALUE = 5;
		static const int MIN_AREA_SIZE = 50;
		std::vector<std::vector<cv::Point> > blobs;

	public:
		BlobDetector();
		virtual ~BlobDetector();

		cv::Mat preProcess(const cv::Mat);
		std::vector<std::vector<cv::Point> > detectBlobs(const cv::Mat);
		cv::Mat drawBlob(const std::vector< std::vector< cv::Point> > contours, int rows, int cols);

};

#endif /* INCLUDE_BLOBDETECTOR_H_ */
