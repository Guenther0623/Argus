/*
 * tracking.cpp
 *
 *  Created on: Jan 17, 2018
 *      Author: Bobbie Isaly, Alexandra Isaly
 *
 *  Instructions:
 *  	When first starting the program:
 *  		- N: to skip forward frames until you reach a good frame to select the rat from
 *  		- ESC: when ready to select the rat and draw a square box around the rat
 *  		  starting with the top left corner
 *  		- ENTER: after drawing the bounding box to let it run
 *  	When the program is running through the tracking loop:
 *  		- ESC: to end the video tracking at any time
 *  		- b: to reselect a new region of interest if the tracking has messed up
 *  	When tracking has been detected as a failure and you need to select a new ROI:
 *  		- f: to finish the program if the trial is finished
 *  		- N: to skip forward frames until you reach a good frame to select the rat in
 *  		- ESC: when ready to select the rat and draw a bounding box around the rat
 *  		  starting with the top left corner
 *  		- Y: to indicate a new track (if the rat was manually moved)
 *  		- N: to indicate the same track
 *  		- ENTER: after drawing the square, repeat above loop steps
 *
 */

//#include <opencv2/core/utility.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>

#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include "tracker.h"

using namespace cv;
using namespace std;

// Convert to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

#define _INSTRUCTION_BG_COLOR Scalar(30,5,0)

double dot_product(Point a, Point b) {
	return ((a.x*b.x)+(a.y*b.y));
}

int main(int argc, char **argv)
{
	/***********************************************************
	 *							SETUP
	 ***********************************************************/
	// Declarations
	bool vidFinished = false;
	bool newROI = false;
	bool first = true;
	bool first2 = true;
	Mat frame, momentFrame, refFrame, initFrame, tempOutFrame, outFrame, firstFrame;
	Mat heatMap, heatMapGray, transFrame, ROI_mask, dummyMask, fixedFrameG;
	Mat fixedFrame, lineTravel;
	Rect2d bbox;
	Ptr<Tracker> tracker = TrackerKCF::create();
	Point center;
	Point prevCenter = Point(-1,-1);
	Point prevCenterL = Point(-1,-1);
	float mouseDistance = 0.0;
	float velocity = 0.0;
	ROI_info floor = ROI_info();
	LINE_info lineII = LINE_info();
	float xRatio, yRatio;
	Mat lineDistance;
	colorList color;
	int switchNum = 0;

	int minVel = 1000;
	int maxVel = -1;
	//int medVel;
	int aveVel;

	string units = "centimeters";
	float xDistOI = 78.75;
	float yDistOI = 42; //as of now this is in centimeters
	float currDist;

	//vector<float> totVels;
	//vector<float> totPosX;
	//vector<float> totPosY;

	int idx = 0;

	// Read in file name
	string fileName = "";
	string labelName = "";
	if(argc <= 1)
	{
		cout << endl << "Enter the video filename" << endl;
		cin >> fileName;
	}
	else {
		fileName = argv[1];
	}

	//fileName = "video.avi";

	cout << endl << "Enter output file label" << endl;
	cin >> labelName;

	string textFileName = labelName + ".txt";

	ofstream textFile(textFileName.c_str());
	//textFile.open(textFileName);

	textFile << labelName << endl;
	textFile << "Info Order:" << endl << "1) x-Position" << endl << "2) y-Position" << endl;
	textFile << "3) current-Distance" << endl << "4) total-Distance" << endl << "5) current-Velocity" << endl << endl;


	string delimiter = ".";
	string name = fileName.substr(0, fileName.find(delimiter));

    // Read video
    VideoCapture video(fileName);

    // Exit if video is not opened
    if(!video.isOpened())
    {
        cout << "Could not read video file" << endl;
        return 1;
    }

    /***********************************************************
	 *					GET REFERENCE FRAME
	 ***********************************************************/
    // Read the frame and save the first frame as refFrame
    // WARNING: assumes frame 0 is the background to compare with,
    // if frame 0 is not the empty experiment, user must create a
    // custom background during ROI selection
    video.read(frame);
    firstFrame = frame.clone();
    refFrame = frame.clone();
    Mat background = refFrame.clone();
    cvtColor(refFrame, refFrame, CV_BGR2GRAY);

    //get FPS
    int fps = video.get(CAP_PROP_FPS);

    // Create mask
	//Mat mask = cropFloor(frame, &floor);
	Mat mask = Mat::zeros(frame.rows, frame.cols, CV_8U);
	mask = Scalar(255);

    //Mat mask = frame.clone();
    lineII.image = frame.clone();

	float pixUnitRatio = getPixToUnitConv(frame, xDistOI, units, &lineII);

	destroyWindow("Corner Select");

	// Create line image with correct size
	lineTravel = Mat::zeros(firstFrame.size(), CV_8UC3);

	// Create the heatMap as the correct size
	heatMapGray = Mat::zeros(firstFrame.size(), CV_8UC1);

	// Initialize heat map frame counts to 0
	int cols = frame.cols;
	int rows = frame.rows;
	vector< vector<int> > frameCounts;
	frameCounts.resize(cols, vector<int>(rows, 0));


    /***********************************************************
	 *					SEARCH FOR START FRAME
	 *					    SELECT ROI
	 ***********************************************************/
    // Get to first frame to start video analysis
    Mat instructions = Mat::zeros(250,450,CV_8UC3);
	instructions.setTo(_INSTRUCTION_BG_COLOR);
	putText(instructions, "CALIBRATION", Point(10,95), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Press 'n' for next or 'p' for previous frame", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Press 'c' to create a custom background image", Point(10,140), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Press ESC to start ROI selection", Point(10,165), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	imshow("Instructions", instructions);
	moveWindow("Instructions", 20, 25);

	imshow("Video Frame", frame);
	moveWindow("Video Frame", 525, 25);

	sensitivity = 18; // starting value
	namedWindow("Sensitivity Slider", CV_WINDOW_NORMAL);
    char thresh_trackbar[50];
    sprintf(thresh_trackbar, "Lower = More sensitive");
	createTrackbar(thresh_trackbar, "Sensitivity Slider", &sensitivity, 50, on_trackbar);
	on_trackbar( sensitivity, 0 );

	while (!vidFinished) {

		// Mask of all ones to pass to processImage
		dummyMask = Mat(frame.size(), CV_8UC1, Scalar(255));

		// Process image
		outFrame = processImage(frame.clone(), refFrame, dummyMask, sensitivity);

		// Refresh current frame
		imshow("Video Frame", frame);

		// Wait for key press
		int k = waitKey(0);

		// If ESC pressed
		if(k == 27)
		{
			destroyWindow("Instructions");
			Mat sel_instructions = Mat::zeros(250,450,CV_8UC3);
			sel_instructions.setTo(_INSTRUCTION_BG_COLOR);
			putText(sel_instructions, "Draw ROI starting at top left corner around rat", Point(10,100), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(sel_instructions, "Press ENTER when done", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			imshow("Selector Instructions", sel_instructions);
			moveWindow("Selector Instructions", 20, 25);

			// Select bounding box
			bbox = selectROI(outFrame, false);

			// Display bounding box.
			rectangle(outFrame, bbox, Scalar( 255, 0, 0 ), 2, 1 );

			// Initialize tracker
			tracker->init(outFrame, bbox);
			cout << "Checkpoint A" << endl;
			moveWindow("ROI Selector", 350, 300);
			cout << "Checkpoint B" << endl;

			// Close SelectROI window
			destroyWindow("ROI selector");
			destroyWindow("Selector Instructions");

			// Start video analysis
			break;
		}

		// Skip 25 frames if 'n' pressed
		else if (k == 110)
		{
			frame = forward(&video, &vidFinished);
		}

		// Rewind 25 frames if 'p' pressed
		else if (k == 112 || k == 80)
		{
			frame = backward(&video);
		}

		// If 'c' pressed
		else if (k == 99)
		{
			bool selectImages = true;
			vector<Mat3b> images;

			destroyWindow("Instructions");
			Mat bg_instructions = Mat::zeros(250,450,CV_8UC3);
			bg_instructions.setTo(_INSTRUCTION_BG_COLOR);
			putText(bg_instructions, "SELECT CUSTOM BACKGROUND IMAGES", Point(10,90), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(bg_instructions, "Press 'n' for next or 'p' for previous frame", Point(10,115), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(bg_instructions, "Navigate to a variety of frames and press space", Point(10,140), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(bg_instructions, "or press 'a' to auto-calculate a background", Point(10,160), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(bg_instructions, "When finished, press ESC to return to ROI selection", Point(10,185), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			imshow("Custom Background Instructions", bg_instructions);
			moveWindow("Custom Background Instructions", 20, 25);


			while(selectImages) {
				imshow("Video Frame", frame);
				k = waitKey(0);
				// If 'n' pressed, skip 25 frames
				if (k == 110)
				{
					frame = forward(&video, &vidFinished);
					if (vidFinished) {
						break;
					}
				}

				// If 'p' pressed, reverse 25 frames
				else if (k == 112)
				{
					frame = backward(&video);
				}

				// If 'ESC' pressed, exit custom
				else if (k == 27)
				{
					selectImages = false;
					// reset to first frame
					video.set(CAP_PROP_POS_FRAMES, 0);
					video.read(frame);
					destroyWindow("Custom Background Instructions");
					imshow("Instructions", instructions);
				}

				// If 'space' pressed, add image to mean calculations
				else if (k == 32)
				{
					images.push_back(frame.clone());
				}

				// If 'a' pressed, auto calculate
				else if (k == 97)
				{
					int vidLength = video.get(CAP_PROP_FRAME_COUNT);
					for (int i = 0; i < 30; i++)
					{
						video.set(CAP_PROP_POS_FRAMES, rand() % (vidLength/2)); // from 0 to vidLength/2
						video.read(frame);
						images.push_back(frame.clone());
					}
					for (int i = 0; i < 30; i++)
					{
						video.set(CAP_PROP_POS_FRAMES, rand() % (vidLength/2) + (vidLength/2)); // from vidLength/2 to vidLength
						video.read(frame);
						images.push_back(frame.clone());
					}
					// auto exit
					selectImages = false;
					video.set(CAP_PROP_POS_FRAMES, 0);
					video.read(frame);
					destroyWindow("Custom Background Instructions");
					imshow("Instructions", instructions);
				}
			}

			// If custom images chosen, calculate custom background image
			if (images.size() > 0)
			{
				Mat3b meanImage = getImageMean(images);
				refFrame = (Mat)meanImage;
				background = refFrame.clone();
				cvtColor(refFrame, refFrame, CV_BGR2GRAY);
				imshow("Background", background);
			}

		}

	}

	/***********************************************************
	 *						MAIN LOOP LOGIC
	 ***********************************************************/

	cout << "Checkpoint C" << endl;
	//int totFrames = video.get(CAP_PROP_FRAME_COUNT);
    // While there is a frame left in the video file, read the frame
    while(!vidFinished) {
    	bool frame_read = false;
    	int ct = 0;

    	while(!frame_read && ct < 5){ // try 5 times to read next frame before exiting
    		ct++;
    		frame_read = video.read(frame);
    	}
    	if(!frame_read) {
    		vidFinished = true;
    		break;
    	}

		// If last frame, video is finished (will not get more frames)
		if (video.get(CAP_PROP_POS_FRAMES) >= video.get(CAP_PROP_FRAME_COUNT)-1) {
			vidFinished = true;
			waitKey(0);
			break;
		}

		cout << "Checkpoint D" <<  endl;
    	// Find new ROI
    	if (newROI) {
    		cout << "Checkpoint L1" << endl;
			instructions.setTo(_INSTRUCTION_BG_COLOR);
			putText(instructions, "TRACKING LOST - NEW ROI SELECTION", Point(10,75), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(instructions, "Press 'f' if the video is finished", Point(10,100), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(instructions, "Otherwise, press 'n' for the next frame", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(instructions, "Press ESC to start ROI selection", Point(10,145), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			imshow("Instructions", instructions);

    		//Reset flag
    		newROI = false;

    		// Have user pick a new ROI
			while(1) {
				// Process image
				outFrame = processImage(frame, refFrame, dummyMask, sensitivity);

				// Display frame.
				imshow("Video Frame", frame);
				imshow("Absolute Difference", outFrame);

				int k = waitKey(0);

				// If 'n' pressed, skip 25 frames
				if (k == 110)
				{
					frame = forward(&video, &vidFinished);
					if (vidFinished) {
						break;
					}
				}

				// If 'p' pressed, reverse 25 frames
				else if (k == 112)
				{
					frame = backward(&video);
				}

				// Select new ROI if ESC pressed
				if (k == 27) {
					Mat sel_instructions = Mat::zeros(250,450,CV_8UC3);
					sel_instructions.setTo(_INSTRUCTION_BG_COLOR);
					putText(sel_instructions, "Press 'y' if this is a new track, 'n' if not", Point(10,100), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
					putText(sel_instructions, "Draw ROI starting at top left corner around rat", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
					putText(sel_instructions, "Press ENTER when done", Point(10,140), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
					imshow("Selector Instructions", sel_instructions);
					moveWindow("Selector Instructions", 20, 25);

					int k2 = waitKey(0);

					if (k2 == 89 || k2 == 121) { // Y
						color.next();
						switchNum++;

						// Change prevCenter to -1 so we don't have
						// a huge jump in distance calculation
						prevCenter.x = -1;
						prevCenter.y = -1;
						prevCenterL.x = -1;
						prevCenterL.y = -1;

						// Save as new point in center for calculations
						//centers[center_count] = Point(-1,-1);
						//center_count++;
					}
					// Select bounding box
					bbox = selectROI(outFrame, false);

					// Display bounding box.
					rectangle(outFrame, bbox, Scalar( 255, 0, 0 ), 2, 1 );

					// Initialize tracker
					tracker = TrackerKCF::create();
					tracker->init(outFrame, bbox);
					moveWindow("ROI Selector", 350, 300);

					// Close ROI window
					destroyWindow("ROI selector");
					destroyWindow("Selector Instructions");

					// Continue the video analysis
					break;
				}

				// End the loop, video is finished
				else if (k == 102) {
					vidFinished = true;
					break;
				}

				cout << "Checkpoint L2" << endl;
			}
    	}

    	// Video Processing
    	else {
        	cout << "Checkpoint E" << endl;

			instructions.setTo(_INSTRUCTION_BG_COLOR);
			putText(instructions, "TRACKING IN PROGRESS", Point(10,110), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(instructions, "Press ESC to end the video tracking at any time", Point(10,130), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
			putText(instructions, "Press 'b' to select a new region of interest", Point(10,150), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));

			// Process Image with floorCrop mask
			outFrame = processImage(frame.clone(), refFrame, mask, sensitivity);

			// Copy outFrame image
			tempOutFrame = outFrame.clone();
			// Convert from BGR to GRAY
			cvtColor(tempOutFrame, tempOutFrame, CV_BGR2GRAY);

			// Update the tracking result
			bool ok = tracker->update(outFrame, bbox);

			cout << "Checkpoint 5" << endl;
			if(ok){
				// Look through all pixels in the bounding box
				for(int i = bbox.tl().x; i < bbox.br().x; i++) {
					if (i < 0) {
						continue;
					}
					for (int j = bbox.tl().y; j < bbox.br().y; j++) {
						// Ignore coordinates not in screen space
						if (j < 0) {
							continue;
						}
						// Look at which pixels are not black in the rectangle and set those to 1
						if (tempOutFrame.at<uchar>(j, i) != 0) {
							frameCounts[i][j] += 1;
						}
					}
				}

				// Create ROI mask for moments
				cout << "Checkpoint 3" << endl;
				ROI_mask = Mat::zeros(outFrame.rows, outFrame.cols, CV_8U);
				rectangle(ROI_mask, bbox.tl(), bbox.br(), Scalar(255), -1);
				cout << "Checkpoint 4" << endl;

				// Initialize moments
				momentFrame = Mat::zeros(tempOutFrame.rows, tempOutFrame.cols, CV_8U);

				// Apply mask
				tempOutFrame.copyTo(momentFrame, ROI_mask);

				// Investigate hull ..?
//				vector<vector<Point> > contours;
//				vector<Vec4i> hierarchy;
//				vector<Point> hull;
//				findContours(tempOutFrame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);
//				vector<Point> max;
//				if (contours.size() > 0) {
//					vector<Point> max = contours[0];
//					for (uint i = 0; i < contours.size(); i++) {
//						if (contourArea(contours[i]) > contourArea(max)) {
//							max = contours[i];
//						}
//					}
//					convexHull(max, hull);
//					for (uint i = 2; i < hull.size()-2; i++) {
//						int dot = dot_product(hull[i] - hull[i-2], hull[i] - hull[i+2]);
//						if (dot > 0) {
//							circle(frame, hull[i], 2, Scalar(0, 255, 255), -1);
//						}
//					}
//				}

				// Compute weighted center of contour
				Moments mu = moments(momentFrame, true);
				center.x = mu.m10 / mu.m00;
				center.y = mu.m01 / mu.m00;
				if (center.x <= 0 || center.y <= 0) {
					prevCenter.x = -1;
					prevCenter.y = -1;
					prevCenterL.x = -1;
					prevCenterL.y = -1;
					newROI = true;
				}

				else
				{
					// Draw line from previous center to new center on image
					// before making floor rectangular
					if (prevCenterL.x != -1 && prevCenterL.y != -1)
					{
						line(lineTravel, center, prevCenterL, color.getColor(), 1);
					}

					prevCenterL.x = center.x;
					prevCenterL.y = center.y;

					// Tracking success : Draw the tracked object
					rectangle(frame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
					rectangle(outFrame, bbox, Scalar( 255, 0, 0 ), 2, 1 );
					circle(frame, center, 4, Scalar( 255, 0, 0 ), -1);
					circle(outFrame, center, 4, Scalar( 255, 0, 0 ), -1);

					// Fix perspective to calculate distance
					//fixedFrameG = squarize(momentFrame, floor.p);
					fixedFrameG = momentFrame.clone();
					cvtColor(fixedFrameG, fixedFrame, COLOR_GRAY2BGR);

					// Compute center of contour of transformed image
					Moments mu2 = moments(fixedFrameG, true);
					center.x = mu2.m10 / mu2.m00;
					center.y = mu2.m01 / mu2.m00;
					//cout << "Checkpoint 1" << endl;

					//totPosX[idx] = center.x;
					//totPosY[idx] = center.y;
					//cout << "Checkpoint 2" << endl;

					if (center.x == 0 || center.y == 0)
					{
						prevCenter.x = -1;
						prevCenter.y = -1;
						newROI = true;
						continue;
					}
					circle(fixedFrame, center, 4, Scalar(255, 0, 0), -1);

					// Draw line from previous center to new center on fixed image
					if (prevCenter.x != -1 && prevCenter.y != -1) {
						line(fixedFrame, center, prevCenter, color.getColor());
					}

					xRatio = xDistOI / fixedFrame.cols;     // Using 2 ft as real box size
					yRatio = yDistOI / fixedFrame.rows;

					// Update distance
					float prevDistance = mouseDistance;
					if (prevCenter.x != -1 && prevCenter.y != -1) {
						currDist = 0;
						currDist = mydistance(center.x * xRatio, center.y * yRatio, prevCenter.x * xRatio, prevCenter.y * yRatio);
						mouseDistance += mydistance(center.x * xRatio, center.y * yRatio, prevCenter.x * xRatio, prevCenter.y * yRatio);
						velocity = (mouseDistance - prevDistance) / video.get(CV_CAP_PROP_FPS);
					}
					else{
						velocity = -1;
					}
					cout << "Checkpoint 6" << endl;

					if (velocity != -1){
						aveVel += velocity;
						idx++;

						if (velocity < minVel)
							minVel = velocity;

						if (velocity > maxVel)
							maxVel = velocity;
					}

					textFile << center.x << ", " << center.y << ", " << currDist << ", " << mouseDistance << ", " << velocity << endl;
					//totVels[idx] = velocity;
					// Move current center to last
					prevCenter.x = center.x;
					prevCenter.y = center.y;

					cout << center.x << ", " << center.y << ", " << velocity << endl;


				}

			}
			else
			{
				// Tracking failure
				cout << "Lost object" << endl;
				newROI = true;
			}

			ostringstream ss;
//			ss << velocity;
//			string v(ss.str());
//			ss << mouseDistance;
//			string m(ss.str());
//			ss << switchNum;
//			string st(ss.str());
//			const string info = "Velocity: " + v + " feet/s | Distance: " + m + " feet | Switch: " + st;
//			putText(frame, info, Point(10,lineDistance.rows - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255));

			ss.str( std::string() );
			ss.clear();
			// Display the image
			imshow("Video Frame", frame);

			namedWindow("Absolute Difference", CV_WINDOW_NORMAL);
			imshow("Absolute Difference", outFrame);
			double newHeight = (outFrame.rows * 450.0) / outFrame.cols;
			if (first) {
				first = false;
				resizeWindow("Absolute Difference", 450, (int)newHeight);
				moveWindow("Absolute Difference", 20, 350);
			}

			imshow("Instructions", instructions);

			// Displaying distance on image
			lineDistance = lineTravel.clone();

			ss << mouseDistance;
			string s(ss.str());
			const string text = "Distance: " + s + " " + units;
			putText(lineDistance, text, Point(10,lineDistance.rows - 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,255,255));
			namedWindow("Line", CV_WINDOW_NORMAL);
			imshow("Line", lineDistance);
			newHeight = (lineDistance.rows * 450.0) / lineDistance.cols;
			if (first2) {
				first2 = false;
				resizeWindow("Line", 450, (int)newHeight);
				moveWindow("Line", 20, 700);
			}

			int k = waitKey(1);
			// Exit if ESC pressed
			if(k == 27) {
				break;
			}
			// Pick a new ROI if 'b' pressed
			else if(k == 98) {
				newROI = true;
			}
    	}
    }

	/***********************************************************
	 *					END OF PROGRAM LOGIC
	 *					   CREATE HEAT MAP
	 ***********************************************************/

    int maxFrameCount = 0;
    float ratio = 0;

    // Find the maximum frame count in the matrix
    for (int i = 0; i < rows; i++){
    	for (int j = 0; j < cols; j++){
    		if (frameCounts[j][i] > maxFrameCount) {
    			maxFrameCount = frameCounts[j][i];
    		}
    	}
    }

    // Calculate the ratio of the max frame count with max pixel coloring
    ratio = maxFrameCount / 255;

    // Create a gray image based on the frame counts divided by the ratio calculated
    for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			int val = frameCounts[j][i] / ratio;
			if(val > 255) {
				val = 255;
			}
			heatMapGray.at<uchar>(i, j) = val;
		}
	}

    // Drawing heatmap scale
    int BAR_WIDTH = 30;

    // Create mat to work with
    Mat scale = Mat::zeros(300, 100, CV_8UC1);
    Mat scaleColor = Mat(300, 100, CV_8UC3, Scalar(255,255,255));
    // Draw gradient
    for (int c = 255; c >= 0; c--) {
    	rectangle(scale, Point(0, 300-c-24), Point(BAR_WIDTH, 300-c-24), c, -1);
    }
    applyColorMap(scale, scaleColor, COLORMAP_JET);
    // Draw surrounding white background
    rectangle(scaleColor, Point(0, 0), Point(99, 19), Scalar(255,255,255), -1);
    rectangle(scaleColor, Point(0, 277), Point(99, 299), Scalar(255,255,255), -1);
	rectangle(scaleColor, Point(BAR_WIDTH+1, 0), Point(99, 299), Scalar(255,255,255), -1);

	// Calculate scale values
	double scaleMax = maxFrameCount / double(fps);
	double maxRounded = round2p(scaleMax);
	ostringstream ss;
	ss << maxRounded;
	string m(ss.str());
	const string max = "" + m;

	line(scaleColor, Point(0, 20), Point(BAR_WIDTH+4, 20), Scalar(0,0,0), 1);
	putText(scaleColor, max, Point(BAR_WIDTH+8, 20), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
	line(scaleColor, Point(0, 276), Point(BAR_WIDTH+4, 276), Scalar(0,0,0), 1);
	putText(scaleColor, "0", Point(BAR_WIDTH+8, 276), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
	putText(scaleColor, "in seconds", Point(5, 292), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
	ss.str( std::string() );
	ss.clear();

	double interval = scaleMax / 4.0;
	double tick = scaleMax;
	for (int i = 1; i < 4; i++) {
		tick = tick - interval;
		tick = round2p(tick);
		ss << tick;
		string m(ss.str());
		const string label = "" + m;
		line(scaleColor, Point(0,(i*64)+20), Point(BAR_WIDTH+4, (i*64)+20), Scalar(0,0,0), 1);
		putText(scaleColor, label, Point(BAR_WIDTH+8, (i*64)+20), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0));
		ss.str( std::string() );
		ss.clear();
	}
	imshow("Scale", scaleColor);

    // Crop out walls
    Mat destImg;
    heatMapGray.copyTo(destImg, mask);

    // Apply a color map to the gray image created above
    applyColorMap(destImg, heatMap, COLORMAP_JET);

    // Next, go through BGR heatMap image
    // Anywhere we detect a pixel with BGR code of <128, 0, 0>,
    // Change the pixel to value to BGR code of <0, 0, 0>
    Mat heatMap2 = heatMap.clone();

    for (int i = 0; i < rows; i++){
    	for (int j = 0; j < cols; j++){
    		if (heatMap2.at<Vec3b>(i, j)[0] == 128 && heatMap2.at<Vec3b>(i, j)[1] == 0 && heatMap2.at<Vec3b>(i, j)[2] == 0){
    			heatMap2.at<Vec3b>(i, j)[0] = 0;
    		}
    	}
    }

    // Next image, lets put heat map on top of initial (background)
    // Anywhere we detect a pixel with BGR code of <128, 0, 0>,
    // change the pixel value to BGR code of that pixel in original frame
    // Draw path of rat on top of heatmap
    initFrame = background.clone();
    Mat heatMap3 = heatMap.clone();

    for (int i = 0; i < rows; i++){
    	for(int j = 0; j < cols; j++){
    		if (heatMap3.at<Vec3b>(i, j)[0] == 128 && heatMap3.at<Vec3b>(i,j)[1] == 0 && heatMap3.at<Vec3b>(i,j)[2] == 0){
    			heatMap3.at<Vec3b>(i, j)[0] = initFrame.at<Vec3b>(i, j)[0];
    			heatMap3.at<Vec3b>(i, j)[1] = initFrame.at<Vec3b>(i, j)[1];
    			heatMap3.at<Vec3b>(i, j)[2] = initFrame.at<Vec3b>(i, j)[2];
    		}
    	}
    }


    Mat heatMapLine = heatMap.clone();
    for (int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			if (heatMapLine.at<Vec3b>(i, j)[0] == 128 && heatMapLine.at<Vec3b>(i,j)[1] == 0 && heatMapLine.at<Vec3b>(i,j)[2] == 0){
				heatMapLine.at<Vec3b>(i, j)[0] = initFrame.at<Vec3b>(i, j)[0];
				heatMapLine.at<Vec3b>(i, j)[1] = initFrame.at<Vec3b>(i, j)[1];
				heatMapLine.at<Vec3b>(i, j)[2] = initFrame.at<Vec3b>(i, j)[2];
			}
			if (!(lineTravel.at<Vec3b>(i, j)[0] == 0 && lineTravel.at<Vec3b>(i, j)[1] == 0 && lineTravel.at<Vec3b>(i, j)[2] == 0)) {
				heatMapLine.at<Vec3b>(i, j)[0] = lineTravel.at<Vec3b>(i, j)[0];
				heatMapLine.at<Vec3b>(i, j)[1] = lineTravel.at<Vec3b>(i, j)[1];
				heatMapLine.at<Vec3b>(i, j)[2] = lineTravel.at<Vec3b>(i, j)[2];
			}
		}
	}

    // Add area around image Point p[4]
    Mat heatMapSquare = squarize(heatMapLine, floor.p);


    // Hey Bobbie, look!! I can still code too!!    ^^^^^ -Dylan
    // Wow, Dylan. Great moves! Keep it up. Proud of you. -Michelle Obama

    // Close the open windows **this was causing a crash for some reason
	destroyWindow("Video Frame");
	destroyWindow("Absolute Difference");
	destroyWindow("Fixed Frame");

    // Display the heat map
    imshow("HeatMap", heatMap);
    imshow("HeatMap2", heatMap2);
    imshow("HeatMap3", heatMap3);
    imshow("HeatMapLine", heatMapLine);
    imshow("HeatMapSqr", heatMapSquare);

	instructions.setTo(_INSTRUCTION_BG_COLOR);
	putText(instructions, "Press ESC to end the program", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	imshow("Instructions", instructions);


    string heatMapFileName = name + "_heatmap1.jpg";
    string heatMap2FileName = name + "_heatmap2.jpg";
    string heatMap3FileName = name + "_heatmap3.jpg";
    string heatMapLineFileName = name + "_heatmapline.jpg";
    string heatmapsqrFileName = name + "_heatmapsqr.jpg";
    string lineFileName = name + "_line.jpg";
    string lineDistFileName = name + "_lineDist.jpg";
    string scaleName = name + "_scale.jpg";

    string fixedFrameName = name + "_fixedFrame.jpg";

    imwrite(heatMapFileName, heatMap);
    imwrite(heatMap2FileName, heatMap2);
    imwrite(heatMap3FileName, heatMap3);
    imwrite(heatMapLineFileName, heatMapLine);
    imwrite(heatmapsqrFileName, heatMapSquare);
    imwrite(lineFileName, lineTravel);
    imwrite(lineDistFileName, lineDistance);
    imwrite(scaleName, scaleColor);

    imwrite(fixedFrameName, fixedFrame);

    aveVel = aveVel / idx;

    textFile << endl << endl;
    textFile << "Total Distance: " << mouseDistance << " " << units << endl;
    textFile << "Min Vel: " << minVel << " " << units << " / second" << endl;
    textFile << "Max Vel: " << maxVel << " " << units << " / second" << endl;
    textFile << "Average Velocity: " << aveVel << " " << units << " / second" << endl;

    textFile.close();

    while(1){
    	// Exit if ESC pressed
		int k = waitKey(0);
		if(k == 27)
		{
			destroyWindow("HeatMap");
			destroyWindow("HeatMap2");
			destroyWindow("HeatMap3");
			destroyWindow("HeatMapLine");
			destroyWindow("Line");
			destroyWindow("Instructions");
			destroyWindow("Scale");
			break;
		}
    }
}


/*
 * forward
 * Skip 25 frames in given video
 *
 * @param VideoCapture* video
 * @param bool* vidFinished - tracks state of video
 *
 * @return frame
 */
Mat forward(VideoCapture* video, bool* vidFinished) {
	Mat frame;
	video->read(frame);
	// this is so ugly im sorry
	int current = video->get(CAP_PROP_POS_FRAMES);
	int total = video->get(CAP_PROP_FRAME_COUNT);
	if ((current+35) >= (total-1)) {
		*vidFinished = true;
		return frame;
	}
	else {
		for(int i = 0; i < 25; i++) {
			video->read(frame);
		}
	}
	return frame;
}


/*
 * backward
 * Rewind 25 frames in given video
 *
 * @param VideoCapture* video
 *
 * @return frame
 */
Mat backward(VideoCapture* video) {
	Mat frame;
	int current_frame = video->get(CAP_PROP_POS_FRAMES);
	if (current_frame - 25 > 0)
	{
		video->set(CAP_PROP_POS_FRAMES, current_frame - 25) ;
	}
	else
	{
		video->set(CAP_PROP_POS_FRAMES, 0);
	}
	video->read(frame);
	return frame;
}


/*
 *	getImageMean
 * 	Averages the images vector to create background estimation
 *
 * 	@param const vector<Mat3b>& images - vector of user-added frames
 *
 * 	@return m - the mean image of images in vector
 */
Mat3b getImageMean(const vector<Mat3b>& images)
{
    if (images.empty()) return Mat3b();

    // Create a 0 initialized image to use as accumulator
    Mat m(images[0].rows, images[0].cols, CV_64FC3);
    m.setTo(Scalar(0,0,0,0));

    // Use a temp image to hold the conversion of each input image to CV_64FC3
    // This will be allocated just the first time, since all your images have
    // the same size.
    Mat temp;
    for (uint i = 0; i < images.size(); ++i)
    {
        // Convert the input images to CV_64FC3 ...
        images[i].convertTo(temp, CV_64FC3);

        // ... so you can accumulate
        m += temp;
    }

    // Convert back to CV_8UC3 type, applying the division to get the actual mean
    m.convertTo(m, CV_8U, 1. / images.size());
    return m;
}


/*
 *	processImage
 * 	Processes the image with correct blurs, thresholds, color conversions, etc
 * 	Compares to the reference frame
 *
 * 	@param Mat firstImg - current frame we are on
 * 	@param Mat refFrame - reference frame that was found in beginning
 *
 * 	@return Mat - the Mat image after processing
 */
Mat processImage(Mat firstImg, Mat refFrame, Mat ROI_mask, int sensitivity) {
	Mat outFrame;

	// Convert the color to gray
	cvtColor(firstImg, firstImg, CV_BGR2GRAY);

	// Blur the image to reduce noise
	GaussianBlur(firstImg, firstImg, Size(3, 3), 3, 3);

	// Dilate image
	dilate(firstImg, firstImg, 2);

	// Absolute diff image
	absdiff(firstImg, refFrame, outFrame);

	Mat outFrame_copy;
	// Apply ROI mask
	cout << "Checkpoint F" << endl;
	outFrame.copyTo(outFrame_copy, ROI_mask);
	cout << "Checkpoint G" << endl;

	// Threshold image so gray turns black
	threshold(outFrame_copy, outFrame_copy, sensitivity, 255, THRESH_BINARY);

	// Convert from gray to BGR
	cvtColor(outFrame_copy, outFrame_copy, CV_GRAY2BGR);

	return outFrame_copy.clone();
}


/*
 * 	onMouse
 *
 * 	@param evt int
 * 	@param x int
 * 	@param y int
 * 	@param flags int
 * 	@param param void*
 */
void onMouseROI(int evt, int x, int y, int flags, void* param) {

	    // First dereference param and create new roi
	    // pointing to this address
		ROI_info* roi = (ROI_info*)param;

		// Switch statement for different mouse actions
		// Display new image between two points if moving
		// mouse, but set new point if clicked
		switch(evt)
		{
			case CV_EVENT_LBUTTONDOWN:
				if(roi->numPoints < 4)
				{
					roi->p[roi->numPoints] = Point(x, y);
					roi->numPoints++;
				}
				break;

			case CV_EVENT_RBUTTONDOWN:
				for(int i = 0; i < 4; i++)
					roi->p[i] = Point(-1, -1);
				roi->numPoints = 0;
				break;

			case CV_EVENT_MOUSEMOVE:
				if(roi->numPoints < 4 && roi->numPoints != 0)
					roi->p[roi->numPoints] = Point(x, y);
				break;

			default:
				break;
		}

		refreshImageROI(roi);
}

void onMouseLINE(int evt, int x, int y, int flags, void* param) {
	LINE_info* lineT = (LINE_info*)param;

	switch(evt)
	{
		case CV_EVENT_LBUTTONDOWN:
			if(lineT->numPoints < 2)
			{
				lineT->p[lineT->numPoints] = Point(x, y);
				lineT->numPoints++;
			}
			break;

		case CV_EVENT_RBUTTONDOWN:
			for(int i = 0; i < 2; i++)
				lineT->p[i] = Point(-1, -1);
			lineT->numPoints = 0;
			break;

		case CV_EVENT_MOUSEMOVE:
			if(lineT->numPoints < 2 && lineT->numPoints != 0)
				lineT->p[lineT->numPoints] = Point(x, y);
			break;

		default:
			break;
	}

	refreshImageLINE(lineT);
}

void refreshImageLINE(LINE_info* lineT) {
	Mat cloned = lineT->image.clone();
	Mat display;
	int count = 0;

	Point polyPnts[1][2];

	if(lineT->p[0].x == -1)
		display = cloned.clone();
	else
	{
		while(lineT->p[count].x != -1 && count < 2)
		{
			circle(cloned, lineT->p[count], 3, Scalar(0, 255, 0), 1);
			polyPnts[0][count] = lineT->p[count];
			count++;
		}

		const Point* ppt[1] = {polyPnts[0]};
		int npt[] = {count};

		fillPoly(cloned, ppt, npt, 1, Scalar(0, 255, 0));
		addWeighted(lineT->image, 0.75, cloned, 0.25, 0, display);
		imshow("Corner Select", display);
	}
}


/*
 * 	refreshImage
 *
 * 	@param roi ROI_info*
 */
void refreshImageROI(ROI_info* roi) {
	Mat cloned = roi->image.clone();
	Mat display;
	int count = 0;

	Point polyPnts[1][4];

	if(roi->p[0].x == -1)
		display = cloned.clone();
	else
	{
		while(roi->p[count].x != -1 && count < 4)
		{
			circle(cloned, roi->p[count], 3, Scalar(0, 255, 0), 1);
			polyPnts[0][count] = roi->p[count];
			count++;
		}

		const Point* ppt[1] = {polyPnts[0]};
		int npt[] = {count};

		fillPoly(cloned, ppt, npt, 1, Scalar(0, 255, 0));

		addWeighted(roi->image, .75, cloned, .25, 0, display);

		imshow("Floor Select", display);
	}
}

float getPixToUnitConv(Mat frame, float distT, string unitOI, LINE_info* lineT) {
	Mat ptp = frame.clone();

	Mat instructions = Mat::zeros(250, 450, CV_8UC3);
	instructions.setTo(_INSTRUCTION_BG_COLOR);
	string welcomeText = "WELCOME - PIXEL TO " + unitOI + " CONVERTER";
	putText(instructions, welcomeText, Point(10, 100), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240, 240, 240));
	putText(instructions, "Select top two corners of the Y-Maze", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Start with the left-most corner", Point(10, 130), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240, 240, 240));
	putText(instructions, "Press any key when done to continue or press ESC to redo", Point(10, 100), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240, 240, 240));
	imshow("Welcome", instructions);
	moveWindow("Welcome", 20, 25);

	imshow("Corner Select", ptp);
	moveWindow("Corner Select", 525, 25);
	setMouseCallback("Corner Select", onMouseLINE, (void*)lineT);

	waitKey(0);
	destroyWindow("Welcome");

	Mat mask = Mat::zeros(frame.rows, frame.cols, CV_8U);
	Point ptArr[4] = {
		lineT->p[0],
		lineT->p[1],
	};

	fillConvexPoly(mask, ptArr, 4, Scalar(255));

	float distC = sqrt(pow(lineT->p[1].x - lineT->p[0].x, 2) + pow(lineT->p[1].y - lineT->p[0].y, 2));

	return (distT / distC);
}

/*
 * 	cropFloor
 *
 * 	@param frame Mat*
 */
Mat cropFloor(Mat frame, ROI_info* floor) {
	Mat crop_floor = frame.clone();
	floor->image = crop_floor;

	// Display instructions
	Mat instructions = Mat::zeros(250,450,CV_8UC3);
	instructions.setTo(_INSTRUCTION_BG_COLOR);
	putText(instructions, "WELCOME - FLOOR SELECT", Point(10,100), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Select corner points of the floor space", Point(10,120), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Start from the top left and continue clockwise", Point(10,140), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	putText(instructions, "Press any key to continue", Point(10,160), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(240,240,240));
	imshow("Welcome", instructions);
	moveWindow("Welcome", 20, 25);

	imshow("Floor Select", crop_floor);
	moveWindow("Floor Select", 525, 25);
	setMouseCallback("Floor Select", onMouseROI, (void*)floor);

	waitKey(0);
	destroyWindow("Welcome");

	// Create and return the floor mask
	Mat mask = Mat::zeros(frame.rows, frame.cols, CV_8U);
	Point ptArr[4] = {
		floor->p[0],
		floor->p[1],
		floor->p[2],
		floor->p[3]
	};
	fillConvexPoly( mask, ptArr, 4, Scalar(255) );

	return mask;

}


/*
 * 	squarize
 *
 * 	@param input Mat
 * 	@param p Point*
 */
Mat squarize(Mat input, Point* p) {
	Mat birdsEyeMatrix(2, 4, CV_32FC1);
	Mat birdsEye, birdsWithFrame;
	Point2f inPoints[4];
	inPoints[0] = Point2f(p[0]);
	inPoints[1] = Point2f(p[1]);
	inPoints[2] = Point2f(p[2]);
	inPoints[3] = Point2f(p[3]);

	Point p_tl = p[0];
	Point p_tr = p[1];
	Point p_br = p[2];
	Point p_bl = p[3];

	//line(input, p_tl, p_tr, Scalar(255, 255, 0), 3);
	//line(input, p_tl, p_bl, Scalar(0, 255, 0), 3);
	//line(input, p_bl, p_br, Scalar(255, 255, 255), 3);
	//line(input, p_br, p_tr, Scalar(0, 255, 255), 3);

	long int diffWA_x = (p_tr.x - p_tl.x);
	diffWA_x = diffWA_x * diffWA_x;
	long int diffWB_x = (p_br.x - p_bl.x);
	diffWB_x = diffWB_x * diffWB_x;

	long int  diffWA_y = (p_tr.y - p_tl.y);
	diffWA_y = diffWA_y * diffWA_y;
	long int diffWB_y = (p_br.y - p_bl.y);
	diffWB_y = diffWB_y * diffWB_y;

	long int diffWA_t = diffWA_x + diffWA_y;
	long int diffWB_t = diffWB_x + diffWB_y;
	int widthA = sqrt(diffWA_t);
	int widthB = sqrt(diffWB_t);

	////////////////////////////////////////////
	long int diffHA_x = (p_tr.x - p_br.x);
	diffHA_x = diffHA_x * diffHA_x;
	long int diffHB_x = (p_tl.x - p_bl.x);
	diffHB_x = diffHB_x * diffHB_x;

	long int diffHA_y = (p_tr.y - p_br.y);
	diffHA_y = diffHA_y - diffHA_y;
	long int diffHB_y = (p_tl.y - p_bl.y);
	diffHB_y = diffHB_y * diffHB_y;

	long int diffHA_t = diffHA_x + diffHA_y;
	long int diffHB_t = diffHB_x + diffHB_y;
	int heightA = sqrt(diffHA_t);
	int heightB = sqrt(diffHB_t);

	///////////////////////////////////////////

	int heightFinal = max(heightA, heightB);
	int widthFinal = max(widthA, widthB);

	//cout << "Height: "<<heightFinal<<endl;
	//cout << "Width: "<<widthFinal<<endl;

	Point2f outPoints[4];
	outPoints[0] = Point2f(0, 0);
	outPoints[1] = Point2f(widthFinal-1, 0);
	outPoints[2] = Point2f(widthFinal-1, heightFinal-1);
	outPoints[3] = Point2f(0, heightFinal-1);

	birdsEyeMatrix = getPerspectiveTransform(inPoints, outPoints);
	warpPerspective(input, birdsEye, birdsEyeMatrix, Size(widthFinal, heightFinal));

	return birdsEye;
}


/*
 * 	mydistance
 *
 * 	@param ax float
 * 	@param ay float
 * 	@param bx float
 * 	@param by float
 */
float mydistance(float ax, float ay, float bx, float by) {

	float dist = sqrt(pow(ax - bx, 2) + pow(ay - by, 2));

	// Ignore value that is negligible to reduce noise
	if (dist < 0.01) {
		dist = 0.0;
	}

	return dist;
}


/*
 * 	round2p
 *
 * 	@param x double
 */
double round2p(double x) {
	int xi = int(x*100);
	if (xi % 100 >= 50)
		return (ceil(x*100))/100;
	else
		return (floor(x*100))/100;
}

/*
 * 	on_trackbar
 *
 * 	@param  int
 * 	@param  void*
 */
void on_trackbar(int, void*)
{
	return; //nothing?
}
