/*
 * tracking.h
 *
 *  Created on: Sep 6, 2018
 *      Author: lab
 */

#ifndef TRACKER_H_
#define TRACKER_H_

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <numeric>
#include "colors.cpp"

using namespace cv;
using namespace std;

// ROI_info: stores image, selected points, and number of points
// for cropping function
struct ROI_info
{
	Mat image;
	Point p[4];
	int numPoints;
	ROI_info(){
		for (int i = 0; i < 4; i++) {
			p[i] = Point(-1,-1);
		}
		numPoints = 0;
	}
};

// LINE_info: stores image, selected points, and number of points
// for the line used to calculate the pixel -> unit ratio
struct LINE_info
{
	Mat image;
	Point p[2];
	int numPoints;
	LINE_info(){
		for (int i = 0; i < 4; i++) {
			p[i] = Point(-1, -1);
		}
		numPoints = 0;
	}
};

int sensitivity;

Mat forward(VideoCapture* video, bool* vidFinished);
Mat backward(VideoCapture* video);
Mat3b getImageMean(const vector<Mat3b>& images);
Mat processImage(Mat firstImg, Mat refFrame, Mat ROI_mask, int sensitivity);
float getPixToUnitConv(Mat frame, float distT, string unitOI, LINE_info* line);
void onMouseLINE(int evt, int x, int y, int flags, void* param);
void onMouseROI(int evt, int x, int y, int flags, void* param);
void refreshImageROI(ROI_info* roi);
void refreshImageLINE(LINE_info* line);
Mat cropFloor(Mat frame, ROI_info* floor);
float mydistance(float ax, float ay, float bx, float by);
Mat squarize(Mat input, Point* p);
double round2p(double x);
void on_trackbar(int, void*);


#endif /* TRACKER_H_ */
