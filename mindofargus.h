#ifndef MINDOFARGUS_H
#define MINDOFARGUS_H

#include <QObject>
#include <QMouseEvent>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <opencv2/core/utility.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/tracking/tracking.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>
#include <opencv2/core/ocl.hpp>
#include <QProgressDialog>
#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <cmath>
#include <string>
#include <QTimer>
#include <vector>
#include <algorithm>
#include <atomic>

#define _UNIT_UNSET		9
#define _UNIT_CM		10
#define _UNIT_IN		11

struct mouse
{
	int rawX;			// Raw x pixel value before squarizing and cropping plane
	int rawY;			// Raw y pixel value before squarizing and cropping plane
	int corrX;			// Corrected x pixel value inside the squarized and cropped image
	int corrY;			// Corrected y pixel value inside the squarized and cropped image
	double distX;		// Distance traveled across x axis in pixels within the corrected plane
	double distY;		// Distance traveled across y axis in pixels within the corrected plane
	double currDist; 	// Distance traveled across both axes (in pixels of corrected plane) in this current frame from previous frame
	double totlDist; 	// Total distance traveled across both axes within corrected plane between all frames processed so far
	int currFrame;		// The current frame from the video that is being analyzed
	int consFrame;		// The current frame count that has been analyzed
	bool isDup;			// Bool flag that represents whether this frame is an exact duplicate of the previous frame
	uint8_t unitMode;	// Low int value representing unit mode (in list of defines)

	mouse(int rx, int ry, int cx, int cy, double dx, double dy, double cd, double td, int ff, int cf, bool dd, uint8_t um){
		rawX = rx;
		rawY = ry;
		corrX = cx;
		corrY = cy;
		distX = dx;
		distY = dy;
		currDist = cd;
		totlDist = td;
		currFrame = ff;
		consFrame = cf;

		isDup = dd;
		unitMode = um;
	}
	mouse(){
		rawX = 0;
		rawY = 0;
		corrX = 0;
		corrY = 0;
		distX = 0.0;
		distY = 0.0;
		currDist = 0.0;
		totlDist = 0.0;
		currFrame = -1;
		consFrame = -1;

		isDup = false;
		unitMode = _UNIT_UNSET;
	}
};

class MindOfArgus : public QObject
{
	Q_OBJECT

public:
	MindOfArgus();
	~MindOfArgus();

	bool isLoaded();
	bool isPlaying();
	bool isProcessing();
	bool isPaused();

	std::ofstream *loggerFile;
	std::stringstream *loggerName;

	cv::Point **region;
	cv::Point **tracki;

	cv::Scalar *colorROI;

	cv::Point *toiPointer;
	cv::Point *roiPointer;
	cv::Point *pointer;

	int roiNumPoints, toiNumPoints, usrNumPoints;

	float *totalDistance;
	float *currentVelocity;
	double *aveVelocity;
	int *procFrames;

	std::atomic<bool> playingCopy;

	std::atomic<bool> playing;
	std::atomic<bool> processing;
	std::atomic<bool> available;
	bool waitingForUser;
	bool userStopped;
	bool resetting;
	bool initialized;

	int viewMode;
	int blurFactor;
	int sensitivity;

	int minStart, minIndex;
	int errFound;

	int resizeRatio;

	int getCurrentFrame();
	int getCurrentFrameRate() {return frameRate;};
	int getCurrentSensitivity();
	int getCurrentBlurFactor();

	void sendCurrentView();

	void resetAll();

private:
	int currFrame;
	
	int roiMaxNumber;
	int toiMaxNumber;

	int roiSelected;
	int toiSelected;

	int roiColor;
	//cv::Scalar *colorTOI;

	double maskBlending;
	double dimX, dimY;
	int dimMode;
	int taskDur, ignoreDur;

	bool loaded;
	bool paused;
	bool toiSelector;
	bool *toiSaved;
	bool roiSelector;
	bool *roiSaved;
	bool refSet;

	int xOffset, yOffset;

	bool *isGood;

	int *toiStart;

	cv::Mat baseFrame;
	cv::Mat viewFrame;

	cv::Mat diffFrame;
	cv::Mat diffMaskd;
	cv::Mat subtFrame;
	cv::Mat subtMaskd;
	cv::Mat heatFrame;
	cv::Mat heatMaskd;
	cv::Mat refFrame;
	cv::Mat squareFrame;

	cv::Point *processCenter;
	cv::Point *currentPoint;
	cv::Point *previousPoint;

	QTimer *argusTimer;

	cv::VideoCapture video;
	std::string vidDir;

	cv::Ptr<cv::Tracker> *trackObj;

	double frameRate;
	double interTimer;
	int resoWidth;
	int resoHeight;
	int totalFrames;

	void videoChange();
	void applySelectorMask();
	void applyAllSavedMask();
	void applyProcessingMask();
	void applyImageProcessing();
	void processSpecificImage(cv::Mat&);

	cv::Mat processImage(cv::Mat, cv::Mat, cv::Mat, int);
	cv::Mat squarizeImage(cv::Mat, cv::Point*, cv::Point&);

	std::vector<mouse> mouseInfo[4];

	//void startVideo();
	//void stopVideo();

public slots:
	void viewChanged_Norm();
	void viewChanged_Base();
	void viewChanged_Reff();
	void viewChanged_Diff();
	void viewChanged_Subt();

	void sensitivityChanged(int);
	void blurFactorChanged(int);

	void videoSync(QString);

	void frameChanged(int);

	void startVideo();
	void pauseVideo();
	void stopVideo();
	void playVideoLoop();
	void pauseVideoLoop();

	void startROISelector(int, int);
	void saveROISelector(int);
	void cancelROISelector(int);
	void removeROISaved(int);
	void roiSetColor(int, int);
	void startTOISelector(int, int);
	void saveTOISelector(int);
	void cancelTOISelector(int);
	void removeTOISaved(int);
	void receiveOF_BoxDims(double, double, int);
	void receiveOF_TaskDur(int, int);
	void receivePM_BoxDims(double, double, int);		// added by Riddhi
	void receivePM_TaskDur(int, int);					// added by Riddhi

	//void getConversionFactor(int);

	void setRefImage(int);

	void ping_startOpenField();
	void ping_startPlusMaze();		// added by Riddhi
	void exp_initOF();
	void exp_startOF();
	void exp_resuOF();
	//void request_TOIReassigned(int, bool);

	void eyeClicked(QMouseEvent *ev);
	void eyeMoved(QMouseEvent *ev);

private slots:
	void nextFrame();

signals:
	void sendSight(cv::Mat, int);
	void videoSynced(double, int, int, int);

	void updateGUI(int);
	void openField_expChange(int, bool);
	void trackerInfo_Frame(int, int);

	void trackersLost(bool*);
	void objectWasLost();

	void pong_endOpenField();

	void request_TOIReassignment(int, bool*);

};

#endif
