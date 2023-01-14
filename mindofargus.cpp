#include "mindofargus.h"

#define _GREEN		0
#define _BLUE		1
#define _RED		2
#define _YELLOW		3
#define _BLACK		4

#define _UNIT_UNSET		9
#define _UNIT_CM		10
#define _UNIT_IN		11

#define _COLOR_GREEN	cv::Scalar(0, 255, 0)
#define _COLOR_BLUE		cv::Scalar(255, 0, 0)
#define _COLOR_RED		cv::Scalar(0, 0, 255)
#define _COLOR_YELLOW	cv::Scalar(0, 255, 255)
#define _COLOR_BLACK	cv::Scalar(0, 0, 0)

#define _COLOR_BNW	1
#define _COLOR_BGR	2
#define _COLOR_RGB	3

#define _VIEW_NORM	0
#define _VIEW_BASE	1
#define _VIEW_REFR	2
#define _VIEW_DIFF	3
#define _VIEW_SUBT	4

#define _CROP_NORM	0
#define _CROP_MASK	1

MindOfArgus::MindOfArgus()
{
	cv::Ptr<cv::Tracker> tracker;
	cv::getBuildInformation();

	dimX = -1;
	dimY = -1;
	dimMode = _UNIT_UNSET;
	taskDur = 0;

	viewMode = _VIEW_NORM;
	loaded = false;
	playing = false;
	playingCopy = false;
	processing = false;
	paused = false;
	initialized = false;

	resetting = false;

	available = true;

	waitingForUser = false;
	userStopped = false;

	refSet = false;

	toiSelector = false;
	roiSelector = false;

	sensitivity = 45;
	blurFactor = 3;

	roiNumPoints = 4;
	roiMaxNumber = 4;
	roiSelected = -1;
	toiNumPoints = 2;
	toiMaxNumber = 4;
	toiSelected = -1;
	usrNumPoints = 0;

	maskBlending = 0.15;

	resizeRatio = 1;
	xOffset = 0;
	yOffset = 0;

	pointer = new cv::Point(-1, -1);
	roiPointer = new cv::Point(-1, -1);
	toiPointer = new cv::Point(-1, -1);

	totalDistance = new float[roiMaxNumber];
	currentVelocity = new float[roiMaxNumber];
	aveVelocity = new double[roiMaxNumber];
	procFrames = new int[roiMaxNumber];

	loggerFile = new std::ofstream[roiMaxNumber];
	loggerName = new std::stringstream[roiMaxNumber];

	roiSaved = new bool[roiMaxNumber];
	region = new cv::Point*[roiMaxNumber];
	colorROI = new cv::Scalar[roiMaxNumber];
	for (int i = 0; i < roiMaxNumber; i++)
	{

		roiSaved[i] = false;
		colorROI[i] = cv::Scalar(0, 0, 0);
		region[i] = new cv::Point[roiNumPoints];
		mouseInfo[i].reserve(100000);

		for (int j = 0; j < roiNumPoints; j++)
			region[i][j] = cv::Point(-1, -1);

		totalDistance[i] = 0;
		currentVelocity[i] = 0;
		procFrames[i] = 0;
		aveVelocity[i] = 0;
	}

	toiSaved = new bool[toiMaxNumber];
	toiStart = new int[toiMaxNumber];
	tracki = new cv::Point*[toiMaxNumber];
	processCenter = new cv::Point[toiMaxNumber];
	currentPoint = new cv::Point[toiMaxNumber];
	previousPoint = new cv::Point[toiMaxNumber];

	for (int i = 0; i < toiMaxNumber; i ++)
	{
		toiSaved[i] = false;
		toiStart[i] = -1;
		tracki[i] = new cv::Point[toiNumPoints];
		processCenter[i].x = -1;
		processCenter[i].y = -1;
		currentPoint[i].x = -1;
		currentPoint[i].y = -1;
		previousPoint[i].x = -1;
		previousPoint[i].y = -1;

		for (int j = 0; j < toiNumPoints; j++)
			tracki[i][j] = cv::Point(-1, -1);

	}

	argusTimer = new QTimer();
	connect(argusTimer, SIGNAL(timeout()), this, SLOT(nextFrame()));
}

MindOfArgus::~MindOfArgus()
{

}

bool MindOfArgus::isPlaying()
{
	return playing;
}

bool MindOfArgus::isProcessing()
{
	return processing;
}

bool MindOfArgus::isLoaded()
{
	return loaded;
}

bool MindOfArgus::isPaused()
{
	return paused;
}

int MindOfArgus::getCurrentFrame()
{
	return currFrame;
}

int MindOfArgus::getCurrentSensitivity()
{
	return sensitivity;
}

int MindOfArgus::getCurrentBlurFactor()
{
	return blurFactor;
}

void MindOfArgus::applyImageProcessing()
{
	cv::cvtColor(baseFrame, diffFrame, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(diffFrame, diffFrame, cv::Size(blurFactor, blurFactor), 0);
	cv::dilate(diffFrame, diffFrame, 2);
	cv::absdiff(diffFrame, refFrame, diffFrame);
	cv::threshold(diffFrame, subtFrame, sensitivity, 255, cv::THRESH_BINARY);
}

void MindOfArgus::processSpecificImage(cv::Mat& image)
{
	cv::Mat& tImage = const_cast<cv::Mat&>(image);
	cv::cvtColor(tImage, tImage, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(tImage, tImage, cv::Size(blurFactor, blurFactor), 0);
	cv::dilate(tImage, tImage, 2);
	cv::absdiff(tImage, refFrame, tImage);
	cv::threshold(tImage, tImage, sensitivity, 255, cv::THRESH_BINARY);
}

void MindOfArgus::applySelectorMask()
{
	if (roiSelector)
	{
		if (usrNumPoints > 0 && usrNumPoints < roiNumPoints)
		{
			cv::Point *tempP = new cv::Point[usrNumPoints+1];
			for (int i = 0; i < usrNumPoints; i++)
				tempP[i] = region[roiSelected][i];
			tempP[usrNumPoints] = cv::Point(pointer->x, pointer->y);

			fillConvexPoly(viewFrame, tempP, usrNumPoints+1, colorROI[roiSelected]);
			delete tempP;
		}
		else if (usrNumPoints == 4)
		{
			fillConvexPoly(viewFrame, region[roiSelected], usrNumPoints, colorROI[roiSelected]);
		}

		if (pointer->x != -1)
		{
			circle(viewFrame, *pointer, 10, colorROI[roiSelected], cv::FILLED);
		}
	}
	else if (toiSelector)
	{
		if (usrNumPoints > 0 && usrNumPoints < toiNumPoints)
		{
			cv::Point tempP1 = cv::Point(tracki[toiSelected][0]);
			cv::Point tempP2 = cv::Point(pointer->x, pointer->y);

			rectangle(viewFrame, tempP1, tempP2, colorROI[toiSelected]);
			//delete tempP;
		}
		else if (usrNumPoints == toiNumPoints)
		{
			rectangle(viewFrame, tracki[toiSelected][0], tracki[toiSelected][1], colorROI[toiSelected]);
		}

		if (pointer->x != -1)
		{
			circle(viewFrame, *pointer, 15, _COLOR_BLACK, cv::FILLED);
			circle(viewFrame, *pointer, 10, colorROI[toiSelected], cv::FILLED);
		}
	}
}

void MindOfArgus::applyAllSavedMask()
{
	cv::Mat cloned;
	cv::Mat result;
	baseFrame.copyTo(cloned);

	bool wasMasked = false;

	for (int i = 0; i < roiMaxNumber; i++)
	{
		if (roiSaved[i])
		{
			fillConvexPoly(cloned, region[i], roiNumPoints, colorROI[i]);
			wasMasked = true;
		}
		//addWeighted(baseFrame, 0.75, cloned, 0.25, 0, viewFrame);
		//cv::imshow("test2", viewFrame);
		//cv::imshow("test1", cloned);
	}

	if (wasMasked)
		addWeighted(baseFrame, 1-maskBlending, cloned, maskBlending, 0, viewFrame);

	for (int i = 0; i < toiMaxNumber; i++)
	{
		if (toiSaved[i])
		{
			cv::Point p1 = cv::Point(tracki[i][0].x, tracki[i][0].y);
			cv::Point p2 = cv::Point(tracki[i][1].x, tracki[i][1].y);
			rectangle(viewFrame, p1, p2, _COLOR_BLACK, 4);
			rectangle(viewFrame, p1, p2, colorROI[i], 2);
		}
	}
}

void MindOfArgus::applyProcessingMask()
{
	for (int i = 0; i < roiMaxNumber; i++)
	{
		if (processCenter[i].x > 0 && processCenter[i].y >0)
		{
			circle(viewFrame, processCenter[i], 4, colorROI[i], -1);
		}
	}
}

void MindOfArgus::startVideo()
{
	if (loaded & !playing & !paused)
	{
		playing = true;
		video.set(cv::CAP_PROP_POS_FRAMES, 1);
		currFrame = 1;
		argusTimer->setInterval(interTimer);
		argusTimer->start();
	}
	else if (loaded & !playing & paused)
	{
		playing = true;
		paused = false;
		argusTimer->start();
	}
}

void MindOfArgus::pauseVideo()
{
	playing = false;
	paused = true;
	argusTimer->stop();
}

void MindOfArgus::stopVideo()
{
	viewMode = _VIEW_NORM;

	toiSelector = false;
	roiSelector = false;
	roiNumPoints = 0;
	toiNumPoints = 0;
	usrNumPoints = 0;

	resizeRatio = 1;

	pointer = new cv::Point(-1, -1);

	for (int i = 0; i < roiMaxNumber; i++)
	{
		if(loggerFile[i].is_open())
			loggerFile[i].close();
	}

	video.release();
	
	this->resetAll();
	while(resetting)
	{

	}
	playing = false;
	paused = false;
	processing = false;
	loaded = false;

	//this->showHomeScreen();
	//emit updateGUI(-1);
}

void MindOfArgus::videoChange()
{
	std::cout << "hello" << std::endl;
}

//Public SLOTS for QT
void MindOfArgus::viewChanged_Norm()
{
	viewMode = _VIEW_NORM;
	if (loaded)
		this->sendCurrentView();
}

void MindOfArgus::viewChanged_Base()
{
	viewMode = _VIEW_BASE;
	if (loaded)
		this->sendCurrentView();
}

void MindOfArgus::viewChanged_Reff()
{
	viewMode = _VIEW_REFR;
	if (loaded)
		this->sendCurrentView();
}
	
void MindOfArgus::viewChanged_Diff()
{
	viewMode = _VIEW_DIFF;
	if (loaded)
		this->sendCurrentView();
}

void MindOfArgus::viewChanged_Subt()
{
	viewMode = _VIEW_SUBT;
	if (loaded)
		this->sendCurrentView();
}

void MindOfArgus::sensitivityChanged(int val)
{
	sensitivity = val;
	if (loaded && refSet)
	{
		this->applyImageProcessing();
		this->sendCurrentView();
	}
}

void MindOfArgus::blurFactorChanged(int val)
{
	blurFactor = val;
	if (loaded && refSet)
	{
		this->applyImageProcessing();
		this->sendCurrentView();
	}
}

void MindOfArgus::videoSync(QString qstr)
{
	vidDir = qstr.toStdString();
	video.open(vidDir);

	if (video.isOpened())
	{
		loaded = true;
		frameRate = video.get(cv::CAP_PROP_FPS);
		totalFrames = int(video.get(cv::CAP_PROP_FRAME_COUNT));
		resoHeight = int(video.get(cv::CAP_PROP_FRAME_HEIGHT));
		resoWidth = int(video.get(cv::CAP_PROP_FRAME_WIDTH));
		currFrame = 1;

		if (resoWidth == 1280 && resoHeight == 1024)
		{
			xOffset = (1920/2) - (1280/2);
			yOffset = (1080/2) - (1024/2);
			resizeRatio = 2;
		}	
		else if (resoWidth == 1920 && resoHeight == 1080)
		{
			xOffset = 0;
			yOffset = 0;
			resizeRatio = 2;
		}
		//resizeRatio = resoHeight/540 + (resoHeight%540 != 0);
		video.read(baseFrame);
		baseFrame.copyTo(viewFrame);
		baseFrame.copyTo(refFrame);
		cv::cvtColor(refFrame, refFrame, cv::COLOR_BGR2GRAY);
		//baseFrame.copyTo(diffFrame);
		interTimer = (1/frameRate)*1000;
		emit sendSight(baseFrame, _COLOR_BGR);
	}
	else
	{
		frameRate = -1;
		totalFrames = -1;
		resoHeight = -1;
		resoWidth = -1;
	}

	emit videoSynced(frameRate, totalFrames, resoWidth, resoHeight);
}

void MindOfArgus::frameChanged(int frameNum)
{
	if (frameNum != (currFrame + 1))
	{
		video.set(cv::CAP_PROP_POS_FRAMES, frameNum);
	}
	video.set(cv::CAP_PROP_POS_FRAMES, frameNum);
	video.read(baseFrame);
	std::cout<<"video frame changed?"<<std::endl;
	this->sendCurrentView();
	currFrame = frameNum;
}

void MindOfArgus::nextFrame()
{
	video >> baseFrame;

	this->sendCurrentView();
	currFrame++;
	if(currFrame > totalFrames)
	{
		//argusTimer->stop();
		playing = false;
	}
	std::cout<<"video next frame loop?"<<std::endl;
	emit updateGUI(currFrame);

}

void MindOfArgus::playVideoLoop()
{
	if(loaded)
	{
		int stFr = currFrame;
		playing = true;
		while(playing & !processing)
		{
			nextFrame();
			std::cout<<"video playing loop?"<<std::endl;
			if (currFrame >= totalFrames)
				playing = false;
		}
	}
}

void MindOfArgus::pauseVideoLoop()
{
	if(loaded)
	{
		playing = false;
	}
}

void MindOfArgus::setRefImage(int frMode)
{
	int numFramesToAverage = 100;
	int frameDivider = 1; 
	//If 1, use whole video. If 2, then only uses first half of video, etc.

	int customFrames[numFramesToAverage] = {201, 1650, 1805, 2550, 2580, 3310, 3350, 3410, 3490, 3505, 
		6910, 6960, 6980, 7000, 7035, 7165, 7250, 7270, 7300, 7320, 
		7350, 7375, 7385, 7555, 8130, 8195, 12860, 12900, 12990, 13035, 
		13055, 17095, 17110, 17135, 17155, 17195, 17225, 17260, 17305, 17325, 
		17330, 17335, 20220, 20245, 20340, 20360, 20590, 20995, 22440, 22790};
	bool useManualFrames = false;

	if (frMode < 0)
	{
		int frameJump = ((totalFrames/frameDivider)-1) / numFramesToAverage;
		int frameNow = video.get(cv::CAP_PROP_POS_FRAMES);

		QProgressDialog *progBar = new QProgressDialog("Calculating Average Reference Frame", "Cancel", 0, totalFrames);
		progBar->setWindowModality(Qt::WindowModal);

		// Put in average reference image algorithm here, when possible
		video.set(cv::CAP_PROP_POS_FRAMES, 1);
		double alpha = 0.02;
		cv::Mat tempSrc;
		video.read(tempSrc);
		cv::Mat tempDst = cv::Mat::zeros(tempSrc.size(), CV_32FC3); //tempSrc.clone();
		available = false;

		if (useManualFrames)
		{
			//int frameJump = ((totalFrames/frameDivider)-1) / numFramesToAverage;
			int frameNow = video.get(cv::CAP_PROP_POS_FRAMES);

			for (int i = 1; i < numFramesToAverage; i++)
			{
				video.set(cv::CAP_PROP_POS_FRAMES, customFrames[i]);
				video.read(tempSrc);
				cv::accumulateWeighted(tempSrc, tempDst, alpha);

				if (progBar->wasCanceled())
					break;

				progBar->setValue(i);
				std::cout<<"i = "<<i<<std::endl;
			}
			available = true;
			cv::Mat finalRes;
			cv::convertScaleAbs(tempDst, finalRes);
			cv::cvtColor(finalRes, refFrame, cv::COLOR_BGR2GRAY);
			video.set(cv::CAP_PROP_POS_FRAMES, frameNow);

			delete progBar;
		}
		else
		{
			
			for (int i = 1+frameJump; i < totalFrames/frameDivider; i += frameJump)
			{
				video.set(cv::CAP_PROP_POS_FRAMES, i);
				video.read(tempSrc);
				//cv::cvtColor(temp, temp, cv::COLOR_BGR2GRAY);
				cv::accumulateWeighted(tempSrc, tempDst, alpha);
			
				if (progBar->wasCanceled())
					break;

				progBar->setValue(i);
				std::cout<<"i = "<<i<<std::endl;
			}
			available = true;
			cv::Mat finalRes;
			cv::convertScaleAbs(tempDst, finalRes);
			cv::cvtColor(finalRes, refFrame, cv::COLOR_BGR2GRAY);
			video.set(cv::CAP_PROP_POS_FRAMES, frameNow);

			delete progBar;
		}
	}
	else if (frMode > 0)
	{
		if (frMode != currFrame)
		{
			int tf = currFrame;
			video.set(cv::CAP_PROP_POS_FRAMES, frMode);
			video.read(refFrame);
			cv::cvtColor(refFrame, refFrame, cv::COLOR_BGR2GRAY);
			video.set(cv::CAP_PROP_POS_FRAMES, tf);
		}
		else
		{
			baseFrame.copyTo(refFrame);
			cv::cvtColor(refFrame, refFrame, cv::COLOR_BGR2GRAY);
		}

		//cv::imshow("test", refFrame);
	}
	refSet = true;
	this->applyImageProcessing();
	std::cout<<"Sender:: new ref assigned"<<std::endl;
	this->sendCurrentView();
}

void MindOfArgus::startROISelector(int roiNumber, int colorSelect)
{
	toiSelector = false;
	roiSelector = true;
	roiSaved[roiNumber] = false;
	roiSelected = roiNumber;
	usrNumPoints = 0;

	switch (colorSelect)
	{
		case _GREEN:
			colorROI[roiNumber] = _COLOR_GREEN;
			break;
		case _RED:
			colorROI[roiNumber] = _COLOR_RED;
			break;
		case _BLUE:
			colorROI[roiNumber] = _COLOR_BLUE;
			break;
		case _YELLOW:
			colorROI[roiNumber] = _COLOR_YELLOW;
			break;
	}
}

void MindOfArgus::saveROISelector(int roiNumber)
{
	bool notFinished = false;
	if (loaded)
	{
		for (int i = 0; i < roiNumPoints; i++)
		{
			if(region[roiNumber][i].x == -1)
			{
				notFinished = true;
				break;
			}
		}

		if (!notFinished)
		{
			roiSaved[roiNumber] = true;
			roiSelector = false;
			roiSelected = -1;
			usrNumPoints = 0;
			if (toiSaved[roiNumber])
				emit openField_expChange(roiNumber, true);
			
			std::cout<<"Sender:: New ROI Assigned"<<std::endl;
			this->sendCurrentView();
		}
		else
		{
			emit openField_expChange(roiNumber, false);
			std::cout << "ERROR: ROI has not been saved, it is not done being initialized" << std::endl;
		}
	}
	else
	{
		std::cout<< "ERROR: ROI has not been saved. No video currently loaded." << std::endl;
	}
}

void MindOfArgus::cancelROISelector(int roiNumber)
{
	if (roiSelector)
	{
		roiSelector = false;
		roiSelected = -1;
		//roiNumPoints = 0;
		usrNumPoints = 0;

		pointer->x = -1;
		pointer->y = -1; //= new cv::Point(-1, -1);
		if (!roiSaved[roiNumber])
		{
			region[roiNumber] = new cv::Point[roiNumPoints]{cv::Point(-1, -1)};
		}
		std::cout<<"Sender:: New ROI Canceled"<<std::endl;
		this->sendCurrentView();
	}
}

void MindOfArgus::removeROISaved(int roiNumber)
{
	if (roiSaved[roiNumber])
	{
		region[roiNumber] = new cv::Point[roiNumPoints];
		for (int i = 0; i < roiNumPoints; i++)
			region[roiNumber][i] = cv::Point(-1, -1);

		roiSaved[roiNumber] = false;
		emit openField_expChange(roiNumber, false);
		std::cout<<"Sender:: New ROI Removed"<<std::endl;
		this->sendCurrentView();
	}
}

void MindOfArgus::roiSetColor(int roiNumber, int colorSelect)
{
	switch (colorSelect)
	{
		case _GREEN:
			colorROI[roiNumber] = _COLOR_GREEN;
			break;
		case _RED:
			colorROI[roiNumber] = _COLOR_RED;
			break;
		case _BLUE:
			colorROI[roiNumber] = _COLOR_BLUE;
			break;
		case _YELLOW:
			colorROI[roiNumber] = _COLOR_YELLOW;
			break;
	}

	if (loaded)
	{
		std::cout<<"Sender:: ROI Color Changed"<<std::endl;
		this->sendCurrentView();
	}
}

void MindOfArgus::startTOISelector(int toiNumber, int colorSelect)
{
	roiSelector = false;
	toiSelector = true;
	toiSelected = toiNumber;
	usrNumPoints = 0;

	switch (colorSelect)
	{
		case _GREEN:
			colorROI[toiNumber] = _COLOR_GREEN;
			break;
		case _RED:
			colorROI[toiNumber] = _COLOR_RED;
			break;
		case _BLUE:
			colorROI[toiNumber] = _COLOR_BLUE;
			break;
		case _YELLOW:
			colorROI[toiNumber] = _COLOR_YELLOW;
			break;
	}

	//if (waitingForUser)
	//	waitingForUser = false;
}

void MindOfArgus::saveTOISelector(int toiNumber)
{
	bool notFinished = false;
	if (loaded)
	{
		for (int i = 0; i < toiNumPoints; i++)
		{
			if(tracki[toiNumber][i].x == -1)
			{
				notFinished = true;
				break;
			}
		}

		if (!notFinished)
		{
			toiSaved[toiNumber] = true;
			toiSelector = false;
			toiSelected = -1;
			usrNumPoints = 0;
			if (roiSaved[toiNumber])
				emit openField_expChange(toiNumber, true);
			
			toiStart[toiNumber] = currFrame;
			emit trackerInfo_Frame(currFrame, toiNumber);
			this->sendCurrentView();
			if (waitingForUser)
				waitingForUser = false;
		}
		else
		{
			emit openField_expChange(toiNumber, false);
			std::cout << "ERROR: TOI has not been saved, it is not done being initialized" << std::endl;
		}
	}
	else
	{
		std::cout<< "ERROR: TOI has not been saved. No video currently loaded." << std::endl;
	}
}

void MindOfArgus::cancelTOISelector(int toiNumber)
{
	if (toiSelector)
	{
		toiSelector = false;
		toiSelected = -1;
		usrNumPoints = 0;

		pointer->x = -1;
		pointer->y = -1; //= new cv::Point(-1, -1);
		if (!toiSaved[toiNumber])
		{
			tracki[toiNumber] = new cv::Point[toiNumPoints];
			for (int i = 0; i < toiNumPoints; i++)
				tracki[toiNumber][i] = cv::Point(-1, -1);
		}
		this->sendCurrentView();
	}
}

void MindOfArgus::removeTOISaved(int toiNumber)
{
	if (toiSaved[toiNumber])
	{
		toiStart[toiNumber] = -1;
		emit trackerInfo_Frame(-1, toiNumber);
		tracki[toiNumber] = new cv::Point[toiNumPoints];
		for (int i = 0; i < toiNumPoints; i++)
			tracki[toiNumber][i] = cv::Point(-1, -1);

		toiSaved[toiNumber] = false;
		emit openField_expChange(toiNumber, false);
		this->sendCurrentView();
	}
}

void MindOfArgus::receiveOF_BoxDims(double bx, double by, int unitMode)
{
	dimX = bx;
	dimY = by;
	dimMode = unitMode;
}

void MindOfArgus::receiveOF_TaskDur(int tdur, int idur)
{
	taskDur = tdur;
	ignoreDur = idur;
	std::cout<<"hello??"<<std::endl;
	std::cout<<taskDur<<", "<<ignoreDur<<std::endl;
}

void MindOfArgus::receivePM_BoxDims(double bx, double by, int unitMode)			// added by Riddhi
{
	dimX = bx;
	dimY = by;
	dimMode = unitMode;
}

void MindOfArgus::receivePM_TaskDur(int tdur, int idur)							// added by Riddhi
{
	taskDur = tdur;
	ignoreDur = idur;
	std::cout<<"hello??"<<std::endl;
	std::cout<<taskDur<<", "<<ignoreDur<<std::endl;
}


void MindOfArgus::resetAll()
{
	resetting = true;

	toiSelector = false;
	roiSelector = false;

	refSet = false;

	roiNumPoints = 4;
	roiMaxNumber = 4;
	roiSelected = -1;
	toiNumPoints = 2;
	toiMaxNumber = 4;
	toiSelected = -1;
	usrNumPoints = 0;

	for (int i = 0; i < roiMaxNumber; i++)
	{
		roiSaved[i] = false;
		region[i] = new cv::Point[roiNumPoints];
		for (int j = 0; j < roiNumPoints; j++)
			region[i][j] = cv::Point(-1, -1);

		emit openField_expChange(i, false);
	}

	for (int i = 0; i < toiMaxNumber; i ++)
	{
		toiSaved[i] = false;
		toiStart[i] = -1;
		tracki[i] = new cv::Point[toiNumPoints];
		for (int j = 0; j < toiNumPoints; j++)
			tracki[i][j] = cv::Point(-1, -1);
	}

	resetting = false;
}

void MindOfArgus::exp_initOF()
{
	if (dimMode == _UNIT_UNSET)
	{
		std::cout<<"ERROR: Dimensions appear to be unset"<<std::endl;
		return;
	}
	else if (dimX < 0 || dimY < 0)
	{
		std::cout<<"ERROR: Dimensions values are invalid and can not be used"<<std::endl;
		return;
	}
	else if (taskDur <= 0 || ignoreDur < 0)
	{
		std::cout<<"ERROR: Task Length Metrics not assigned"<<std::endl;
		return;
	}
	//loggerName = "testResults.txt";
	//loggerFile.open(loggerName);

	minStart = totalFrames;
	minIndex = 0;
	for(int i = 0; i < roiMaxNumber; i++)
	{
		if(toiSaved[i])
		{
			if(i > minIndex)
				minIndex = i;

			if(toiStart[i] < minStart)
				minStart = toiStart[i];
		}
	}
	minIndex++;
	std::cout << "minStart is:"<<minStart<<std::endl;

	trackObj = new cv::Ptr<cv::Tracker>[minIndex];
	cv::Rect bbox[minIndex];
	isGood = new bool[minIndex];

	for(int i = 0; i < minIndex; i++)
	{
		processCenter[i].x = -1;
		processCenter[i].y = -1;
		currentPoint[i].x = -1;
		currentPoint[i].y = -1;
		previousPoint[i].x = -1;
		previousPoint[i].y = -1;



		//if (assert(loggerName[i].str().empty()))
		if (loggerName[i].str().empty())
			loggerName[i] << "textFile_" << i<<".txt";
		
		loggerFile[i].open(loggerName[i].str());
		loggerFile[i]<<"STARTING OPEN-FIELD ANALYSIS"<<std::endl<<std::endl;

		totalDistance[i] = 0;
		currentVelocity[i] = 0;
		aveVelocity[i] = 0;
		procFrames[i] = 0;

		isGood[i] = true;
		//isGood[i] = true;
		video.set(cv::CAP_PROP_POS_FRAMES, toiStart[i]);
		//cv::Mat tempA;
		//video.read(tempA);
		cv::Mat tempA;
		cv::Mat tempT;
		cv::Mat tempC;
		video.read(tempA);
		cv::Mat tempF = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
		fillConvexPoly(tempF, region[i], roiNumPoints, cv::Scalar(255));
		//this->processSpecificImage(tempA);
		
		tempA.copyTo(tempT, tempF);
		refFrame.copyTo(tempC, tempF);
		cv::cvtColor(tempT, tempT, cv::COLOR_BGR2GRAY);
		cv::GaussianBlur(tempT, tempT, cv::Size(blurFactor, blurFactor), 0);
		cv::dilate(tempT, tempT, 2);
		cv::absdiff(tempT, tempC, tempT);
		cv::threshold(tempT, tempT, sensitivity, 255, cv::THRESH_BINARY);
		//cv::imshow("TempT01", tempT);
		cv::cvtColor(tempT, tempT, cv::COLOR_GRAY2BGR);
		//cv::imshow("tempT02", tempT);
		//cv::waitKey(0);

		bbox[i] = cv::Rect(tracki[i][0], tracki[i][1]);
		//if (i == 0)
		trackObj[i] = cv::TrackerKCF::create();
		//trackObj[i]->init(tempA, bbox[i]);
		trackObj[i]->init(tempT, bbox[i]);

		mouseInfo[i].clear();
		mouseInfo[i].reserve(totalFrames - toiStart[i]);
	}

	initialized = true;
	std::cout <<"OpenField initiated successfully"<<std::endl;

}

void MindOfArgus::exp_startOF()
{
	if (!initialized)
	{
		std::cout<<"ERROR: Please successfully initialize the experiment first"<<std::endl;
		return;
	}
	video.set(cv::CAP_PROP_POS_FRAMES, minStart);
	currFrame = minStart;
	processing = true;
	playing = true;
	//bool isGood[minIndex];
	//isGood = new bool[minIndex];
	bool allGood = true;
	cv::Rect bbox[minIndex];

	available = false;

	while(processing)
	{

		if (playing)
		{
			cv::Mat prevFrame;
			baseFrame.copyTo(prevFrame);
			video >> baseFrame;
			currFrame++;
			if (currFrame >= (totalFrames))
			{
				playing = false;
				processing = false;
				break;
			}

			cv::Mat baseTemp, prevTemp;
			cv::cvtColor(baseFrame, baseTemp, cv::COLOR_BGR2GRAY);
			cv::cvtColor(prevFrame, prevTemp, cv::COLOR_BGR2GRAY);
			double normDiff = cv::norm(baseTemp, prevTemp, cv::NORM_L1);
			double isEqualCutoff = 1000000;
			bool isEqual = false;
			if (normDiff < isEqualCutoff)
				isEqual = true;
			

			this->applyImageProcessing();

			for (int i = 0; i < minIndex; i++)
			{
					//isGood[i] = true;
				if (currFrame > toiStart[i])
				{
					bbox[i] = cv::Rect(tracki[i][0], tracki[i][1]);	
					cv::Mat maskV = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
					fillConvexPoly(maskV, region[i], roiNumPoints, cv::Scalar(255));
					//cv::imshow("maskV", maskV);
					cv::Mat analysisMat;
					subtFrame.copyTo(analysisMat, maskV);
					cv::cvtColor(analysisMat, analysisMat, cv::COLOR_GRAY2BGR);
					
					//cv::imshow("analysisMat", analysisMat);
					//cv::waitKey(0);
					isGood[i] = trackObj[i]->update(analysisMat, bbox[i]);
			
					std::cout << currFrame << std::endl;

					if (isGood[i])
					{
						tracki[i][0] = bbox[i].tl();
						tracki[i][1] = bbox[i].br();
						cv::Mat roiMask = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
						fillConvexPoly(roiMask, region[i], roiNumPoints, cv::Scalar(255));
						cv::Mat tempT;
						subtFrame.copyTo(tempT, roiMask);

						cv::Mat bbxMask = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
						rectangle(bbxMask, bbox[i].tl(), bbox[i].br(), cv::Scalar(255), -1);
						cv::Mat momentFrame;
						tempT.copyTo(momentFrame, bbxMask);
						//cv::imshow("test", momentFrame);
						//cv::waitKey(0);
						std::cout << "moment frame generated"<<std::endl;

						cv::Moments mo = cv::moments(momentFrame, true);
						//prevPointNm[i] = Point(processCenter[i].x, processCenter[i].y);
						processCenter[i].x = mo.m10 / mo.m00;
						processCenter[i].y = mo.m01 / mo.m00;

						std::cout<<"pc_x:="<<processCenter[i].x<<std::endl;
						std::cout<<"pc_y:="<<processCenter[i].y<<std::endl;
						std::cout<<"moment center calculated"<<std::endl;

						if (processCenter[i].x <= 0 || processCenter[i].y <= 0)
						{
							if(allGood)
								allGood = false;
							isGood[i] = false;
							loggerFile[i]<<"#Mouse lost, requesting reassignment"<<std::endl; 
						}
						else
						{
							if (currentPoint[i].x > 0 && currentPoint[i].y > 0)
							{
								previousPoint[i].x = currentPoint[i].x;
								previousPoint[i].y = currentPoint[i].y;
							}
							currentPoint[i] = processCenter[i];
							//std::cout << currentPoint[i].x << ", " << currentPoint[i].y << std::endl;							
							squareFrame = squarizeImage(baseFrame, region[i], currentPoint[i]);
							//std::cout << currentPoint[i].x << ", " << currentPoint[i].y << std::endl;							
							
							//if (previousPoint[i].x >= 0)
							//	cv::circle(squareFrame, previousPoint[i], 4, _COLOR_BLUE, -1);
							//cv::circle(squareFrame, currentPoint[i], 4, _COLOR_RED, -1);

							//cv::imshow("squared", squareFrame);
							//cv::waitKey(0);

							double dist = 0.0;
							if (previousPoint[i].x > 0 && previousPoint[i].y > 0)
							{
								dist = sqrt(pow((currentPoint[i].x - previousPoint[i].x)*(dimX/squareFrame.cols), 2) + pow((currentPoint[i].y - previousPoint[i].y)*(dimY/squareFrame.rows), 2));
								totalDistance[i] = totalDistance[i] + dist;
								currentVelocity[i] = (dist * frameRate);
								procFrames[i]++;
							}
							else
							{
								//totalDistance[i] = 0.0;
								currentVelocity[i] = -1;
								//avgVelocity[i] = 0;
								procFrames[i]++;
							}
							//mouseInfo[i].push_back(mouse(processCenter[i].x, processCenter[i].y, currentPoint[i].x, currentPoint[i].ycurrFrame, isEqual));

							if (procFrames[i] == 1)
							{
								std::string tempStr01 = "#Mouse ID:" + std::to_string(i);
								loggerFile[i]<<tempStr01<<std::endl;

								std::string tempStr02 = "#FPS:" + std::to_string(frameRate);
								loggerFile[i]<<tempStr02<<std::endl;

								std::string tempStr03 = "#X-Pixels:" + std::to_string(squareFrame.cols);
								loggerFile[i]<<tempStr03<<std::endl;

								std::string tempStr04 = "#Y-Pixels:" + std::to_string(squareFrame.rows);
								loggerFile[i]<<tempStr04<<std::endl;

								std::string tempStr05 = "#X-Value:" + std::to_string(dimX);
								loggerFile[i]<<tempStr05<<std::endl;

								std::string tempStr06 = "#Y-Value:" + std::to_string(dimY);
								loggerFile[i]<<tempStr06<<std::endl;

								std::string tempStr07;
								if (dimMode == _UNIT_UNSET)
									tempStr07 = "#Units: Unknown";
								else if (dimMode == _UNIT_CM)
									tempStr07 = "#Units: Centimeters";
								else if (dimMode == _UNIT_IN)
									tempStr07 = "#Units: Inches";
								loggerFile[i]<<tempStr07<<std::endl<<std::endl;
							}
							std::string comm = std::to_string(currentPoint[i].x) + ", " + std::to_string(currentPoint[i].y) + ", " + std::to_string(dist) + ", " + std::to_string(totalDistance[i]) + ", " + std::to_string(currentVelocity[i]) + ", " + std::to_string(currFrame) + ", " + std::to_string(isEqual);
							loggerFile[i]<<comm<<std::endl;

							//previousPoint[i].x = currentPoint[i].x;
							//previousPoint[i].y = currentPoint[i].y;
						}
					}
					else if (!isGood[i] || !allGood)
					{
						std::cout<<"object lost" << std::endl;
						tracki[i][0] = cv::Point(-1, -1);
						tracki[i][1] = cv::Point(-1, -1);
						allGood = false;
						isGood[i] = false;
					}
				}

			}
			emit updateGUI(currFrame);
			this->sendCurrentView();
			if (userStopped)
			{
				processing = false;
			}

			if (!allGood)
			{
				errFound = currFrame;
				playing = false;
				processing = false;
			}
			if (currFrame >= (totalFrames))
			{
				playing = false;
				processing = false;
			}
		}
		//std::cout<<"processing loop"<<std::endl;
	}
	//this->sendCurrentView();
	if (!allGood)
		emit objectWasLost();

	available = true;
}

void MindOfArgus::exp_resuOF()
{
	std::cout<<"resume called"<<std::endl;
	bool allGood = true;
	cv::Rect bbox[minIndex];
	playing = true;

	available = false;

	for(int i = 0; i < roiMaxNumber; i++)
	{
		if (!isGood[i])
		{	
			processCenter[i].x = -1;
			processCenter[i].y = -1;
			isGood[i] = true;
			video.set(cv::CAP_PROP_POS_FRAMES, toiStart[i]);
						
			cv::Mat tempA, tempT, tempC;
			video.read(tempA);
			cv::Mat tempF = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
			fillConvexPoly(tempF, region[i], roiNumPoints, cv::Scalar(255));
	
			tempA.copyTo(tempT, tempF);
			refFrame.copyTo(tempC, tempF);
			cv::cvtColor(tempT, tempT, cv::COLOR_BGR2GRAY);
			cv::GaussianBlur(tempT, tempT, cv::Size(blurFactor, blurFactor), 0);
			cv::dilate(tempT, tempT, 2);
			cv::absdiff(tempT, tempC, tempT);
			cv::threshold(tempT, tempT, sensitivity, 255, cv::THRESH_BINARY);
			cv::cvtColor(tempT, tempT, cv::COLOR_GRAY2BGR);
		
			bbox[i] = cv::Rect(tracki[i][0], tracki[i][1]);
			trackObj[i] = cv::TrackerKCF::create();
			trackObj[i]->init(tempT, bbox[i]);
		}
	}

	video.set(cv::CAP_PROP_POS_FRAMES, errFound);
	currFrame = errFound;
	processing = true;
	playing = true;
	//bool isGood[minIndex];
	//isGood = new bool[minIndex];

	available = false;

	while(processing)
	{

		if (playing)
		{
			cv::Mat prevFrame;
			baseFrame.copyTo(prevFrame);
			video >> baseFrame;
			currFrame++;
			if (currFrame >= (totalFrames))
			{
				playing = false;
				processing = false;
				break;
			}

			cv::Mat baseTemp, prevTemp;
			cv::cvtColor(baseFrame, baseTemp, cv::COLOR_BGR2GRAY);
			cv::cvtColor(prevFrame, prevTemp, cv::COLOR_BGR2GRAY);
			double normDiff = cv::norm(baseTemp, prevTemp, cv::NORM_L1);
			double isEqualCutoff = 1000000;
			bool isEqual = false;
			if (normDiff < isEqualCutoff)
				isEqual = true;

			this->applyImageProcessing();
						
			for (int i = 0; i < minIndex; i++)
			{
					//isGood[i] = true;
				if (currFrame > toiStart[i])
				{
					bbox[i] = cv::Rect(tracki[i][0], tracki[i][1]);	
					cv::Mat maskV = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
					fillConvexPoly(maskV, region[i], roiNumPoints, cv::Scalar(255));
					//cv::imshow("maskV", maskV);
					cv::Mat analysisMat;
					subtFrame.copyTo(analysisMat, maskV);
					cv::cvtColor(analysisMat, analysisMat, cv::COLOR_GRAY2BGR);
					
					//cv::imshow("analysisMat", analysisMat);
					//cv::waitKey(0);
					isGood[i] = trackObj[i]->update(analysisMat, bbox[i]);
			
					std::cout << currFrame << std::endl;

					if (isGood[i])
					{
						tracki[i][0] = bbox[i].tl();
						tracki[i][1] = bbox[i].br();
						cv::Mat roiMask = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
						fillConvexPoly(roiMask, region[i], roiNumPoints, cv::Scalar(255));
						cv::Mat tempT;
						subtFrame.copyTo(tempT, roiMask);

						cv::Mat bbxMask = cv::Mat::zeros(baseFrame.rows, baseFrame.cols, CV_8U);
						rectangle(bbxMask, bbox[i].tl(), bbox[i].br(), cv::Scalar(255), -1);
						cv::Mat momentFrame;
						tempT.copyTo(momentFrame, bbxMask);
						std::cout << "moment frame generated"<<std::endl;

						cv::Moments mo = cv::moments(momentFrame, true);
						//prevPointNm[i] = Point(processCenter[i].x, processCenter[i].y);
						processCenter[i].x = mo.m10 / mo.m00;
						processCenter[i].y = mo.m01 / mo.m00;

						std::cout<<"pc_x:="<<processCenter[i].x<<std::endl;
						std::cout<<"pc_y:="<<processCenter[i].y<<std::endl;
						std::cout<<"moment center calculated"<<std::endl;

						if (processCenter[i].x <= 0 || processCenter[i].y <= 0)
						{
							if(allGood)
								allGood = false;
							isGood[i] = false;
							loggerFile[i]<<"#Mouse lost, requesting reassignment"<<std::endl; 
						}
						else
						{
							if (currentPoint[i].x > 0 && currentPoint[i].y > 0)
							{
								previousPoint[i].x = currentPoint[i].x;
								previousPoint[i].y = currentPoint[i].y;
							}
							currentPoint[i] = processCenter[i];
							//std::cout << currentPoint[i].x << ", " << currentPoint[i].y << std::endl;							
							squareFrame = squarizeImage(baseFrame, region[i], currentPoint[i]);
							//std::cout << currentPoint[i].x << ", " << currentPoint[i].y << std::endl;							
							
							//if (previousPoint[i].x >= 0)
							//	cv::circle(squareFrame, previousPoint[i], 4, _COLOR_BLUE, -1);
							//cv::circle(squareFrame, currentPoint[i], 4, _COLOR_RED, -1);

							//cv::imshow("squared", squareFrame);
							//cv::waitKey(0);

							double dist = 0.0;
							if (previousPoint[i].x > 0 && previousPoint[i].y > 0)
							{
								dist = sqrt(pow((currentPoint[i].x - previousPoint[i].x)*(dimX/squareFrame.cols), 2) + pow((currentPoint[i].y - previousPoint[i].y)*(dimY/squareFrame.rows), 2));
								totalDistance[i] = totalDistance[i] + dist;
								currentVelocity[i] = (dist * frameRate);
								procFrames[i]++;
							}
							else
							{
								//totalDistance[i] = 0.0;
								currentVelocity[i] = -1;
								//avgVelocity[i] = 0;
								procFrames[i]++;
							}
							//mouseInfo[i].push_back(mouse(processCenter[i].x, processCenter[i].y, currentPoint[i].x, currentPoint[i].ycurrFrame, isEqual));

							if (procFrames[i] == 1)
							{
								std::string tempStr01 = "#Mouse ID:" + std::to_string(i);
								loggerFile[i]<<tempStr01<<std::endl;

								std::string tempStr02 = "#FPS:" + std::to_string(frameRate);
								loggerFile[i]<<tempStr02<<std::endl;

								std::string tempStr03 = "#X-Pixels:" + std::to_string(squareFrame.cols);
								loggerFile[i]<<tempStr03<<std::endl;

								std::string tempStr04 = "#Y-Pixels:" + std::to_string(squareFrame.rows);
								loggerFile[i]<<tempStr04<<std::endl;

								std::string tempStr05 = "#X-Value:" + std::to_string(dimX);
								loggerFile[i]<<tempStr05<<std::endl;

								std::string tempStr06 = "#Y-Value:" + std::to_string(dimY);
								loggerFile[i]<<tempStr06<<std::endl;

								std::string tempStr07;
								if (dimMode == _UNIT_UNSET)
									tempStr07 = "#Units: Unknown";
								else if (dimMode == _UNIT_CM)
									tempStr07 = "#Units: Centimeters";
								else if (dimMode == _UNIT_IN)
									tempStr07 = "#Units: Inches";
								loggerFile[i]<<tempStr07<<std::endl<<std::endl<<std::endl;
							}
							std::string comm = std::to_string(currentPoint[i].x) + ", " + std::to_string(currentPoint[i].y) + ", " + std::to_string(dist) + ", " + std::to_string(totalDistance[i]) + ", " + std::to_string(currentVelocity[i]) + ", " + std::to_string(currFrame) + ", " + std::to_string(isEqual);
							loggerFile[i]<<comm<<std::endl;

							//previousPoint[i].x = currentPoint[i].x;
							//previousPoint[i].y = currentPoint[i].y;
						}
					}
					else if (!isGood[i] || !allGood)
					{
						std::cout<<"object lost" << std::endl;
						tracki[i][0] = cv::Point(-1, -1);
						tracki[i][1] = cv::Point(-1, -1);
						allGood = false;
						isGood[i] = false;
					}
				}

			}
			emit updateGUI(currFrame);
			this->sendCurrentView();
			std::cout<<"Sender:: Main Processing Loop"<<std::endl;
			if (userStopped)
			{
				processing = false;
			}

			if (!allGood)
			{
				errFound = currFrame;
				playing = false;
				processing = false;
			}
		}
	}

	if (!allGood)
		emit objectWasLost();

	available = true;
}

void MindOfArgus::ping_startOpenField()
{

}

void MindOfArgus::ping_startPlusMaze()			// Added by Riddhi
{

}

cv::Mat MindOfArgus::processImage(cv::Mat image, cv::Mat reference, cv::Mat roiMask, int sensitivity)
{
	cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(image, image, cv::Size(blurFactor, blurFactor), 0);
	cv::dilate(image, image, 2);
	cv::absdiff(image, reference, diffFrame);

	cv::Mat output;
	diffFrame.copyTo(output, roiMask);
	cv::threshold(output, subtFrame, sensitivity, 255, cv::THRESH_BINARY);

	return subtFrame;
}

cv::Mat MindOfArgus::squarizeImage(cv::Mat image, cv::Point* p, cv::Point& r)
{
	cv::Mat birdsEyeTransform(2, 4, CV_32FC1);
	cv::Point2f inPoints[4];
	//for (int i = 0; i < 4; i++)
	//	inPoints[i] = cv::Point2f(p[i]);

	for (int i = 0; i < 4; i++)
	{
		inPoints[i] = p[i];
	}
	cv::Point p_tl = p[0];
	cv::Point p_br = p[3];

	cv::Point p_tr = p[1]; //cv::Point(p_br.x, p_tl.y);
	cv::Point p_bl = p[3]; //cv::Point(p_tl.x, p_br.y);

	//inPoints[0] = p_tl;
	//inPoints[1] = p_tr;
	//inPoints[2] = p_br;
	//inPoints[3] = p_bl; 

	long int diffWA_x = (p_tr.x - p_tl.x);
	long int diffWA_y = (p_tr.y - p_tl.y);
	diffWA_x = diffWA_x * diffWA_x;
	diffWA_y = diffWA_y * diffWA_y;
	long int diffWB_x = (p_br.x - p_bl.x);
	long int diffWB_y = (p_br.y - p_bl.x);
	diffWB_x = diffWB_x * diffWB_x;
	diffWB_y = diffWB_y * diffWB_y;

	long int diffWA_t = diffWA_x + diffWA_y;
	long int diffWB_t = diffWB_x + diffWB_y;

	long int diffHA_x = (p_tr.x - p_br.x);
	long int diffHA_y = (p_tr.y - p_br.y);
	diffHA_x = diffHA_x * diffHA_x;
	diffHA_y = diffHA_y * diffHA_y;
	long int diffHB_x = (p_tl.x - p_bl.x);
	long int diffHB_y = (p_tl.y - p_bl.x);
	diffHB_x = diffHB_x * diffHB_x;
	diffHB_y = diffHB_y * diffHB_y;

	long int diffHA_t = diffHA_x + diffHA_y;
	long int diffHB_t = diffHB_x + diffHB_y;

	int widthA = sqrt(diffWA_t);
	int widthB = sqrt(diffWB_t);
	int heightA = sqrt(diffHA_t);
	int heightB = sqrt(diffHB_t);

	int widthFinal = std::max(widthA, widthB);
	int heightFinal = std::max(heightA, heightB);

	cv::Point2f outPoints[4];
	outPoints[0] = cv::Point2f(0, 0);
	outPoints[1] = cv::Point2f(widthFinal-1, 0);
	outPoints[2] = cv::Point2f(widthFinal-1, heightFinal-1);
	outPoints[3] = cv::Point2f(0, heightFinal-1);

	birdsEyeTransform = cv::getPerspectiveTransform(inPoints, outPoints);

	cv::Mat birdsEyeOut;
	cv::warpPerspective(image, birdsEyeOut, birdsEyeTransform, cv::Size(widthFinal, heightFinal));
	
	std::vector<cv::Point2f> inPoint, outPoint;
	inPoint.push_back(cv::Point2f(r.x, r.y));

	cv::perspectiveTransform(inPoint, outPoint, birdsEyeTransform);

	r.x = outPoint[0].x;
	r.y = outPoint[0].y;

	return birdsEyeOut;
}

//void MindOfArgus::getConversionFactors(int numFactors)
//{
//	for (int i = 0; i < numFactors; i++)
//	{
//
//	}
//}

void MindOfArgus::eyeClicked(QMouseEvent *ev)
{
	if (roiSelector)
	{
		if (usrNumPoints < roiNumPoints)
		{
			region[roiSelected][usrNumPoints] = cv::Point(ev->x()*resizeRatio - xOffset, ev->y()*resizeRatio - yOffset);
			usrNumPoints++;
		}
		this->sendCurrentView();
	}
	else if (toiSelector)
	{
		if (usrNumPoints < toiNumPoints)
		{
			tracki[toiSelected][usrNumPoints] = cv::Point(ev->x()*resizeRatio - xOffset, ev->y()*resizeRatio - yOffset);
			usrNumPoints++;
		}
		this->sendCurrentView();
	}

}

void MindOfArgus::eyeMoved(QMouseEvent *ev)
{
	if (roiSelector || toiSelector)
	{
		if (ev->x() != 0 && ev->y() != 0)
		{
			pointer = new cv::Point(ev->x()*resizeRatio - xOffset, ev->y()*resizeRatio - yOffset);
			this->sendCurrentView();
		}
	}
	int x = ev->x();
	int y = ev->y();
}

void MindOfArgus::sendCurrentView()
{
	if (!loaded)
		return;

	baseFrame.copyTo(viewFrame);
	this->applyAllSavedMask();
	this->applySelectorMask();
	if (processing)
		this->applyProcessingMask();
	//{
		//this->applyProcessingMask();
		//cv::imshow("test", viewFrame);
		//cv::waitKey(0);
	//}
	//cv::resize(viewFrame, viewFrame, cv::Size(1920/resizeRatio, 1080/resizeRatio), 0, 0, cv::INTER_LINEAR);

	switch (viewMode)
	{
		case _VIEW_NORM:
			//std::cout<<"attempting to send image NORM"<<std::endl;
			emit sendSight(viewFrame, _COLOR_BGR);
			//std::cout<<"image sent NORM"<<std::endl;
			break;

		case _VIEW_BASE:
			emit sendSight(baseFrame, _COLOR_BGR);
			break;

		case _VIEW_REFR:
			emit sendSight(refFrame, _COLOR_BGR);
			break;

		case _VIEW_DIFF:
			emit sendSight(diffFrame, _COLOR_BNW);
			break;

		case _VIEW_SUBT:
			emit sendSight(subtFrame, _COLOR_BNW);
			break;
	}
}