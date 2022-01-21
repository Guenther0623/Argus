#include "mindofargus.h"


MindOfArgus::MindOfArgus()
{
	viewMode = _VIEW_NORM;
	loaded = false;
	playing = false;
	processing = false;
	paused = false;

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

void MindOfArgus::startVideo()
{
	if (loaded & !playing & !paused)
	{
		playing = true;
		video.set(CV_CAP_PROP_POS_FRAMES, 1);
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
	playing = false;
	paused = false;
	loaded = false;
	processing = false;

	video.release();
	//this->showHomeScreen();
	//emit updateGUI(-1);
}

void MindOfArgus::videoChange()
{
	std::cout << "hello" << std::endl;
}

//Public SLOTS for QT
void MindOfArgus::viewChanged_Deff()
{
	viewMode = _VIEW_NORM;
}

void MindOfArgus::viewChanged_Subt()
{
	viewMode = _VIEW_SUBT;
}
	
void MindOfArgus::viewChanged_Mask()
{
	viewMode = _VIEW_MASK;
}

void MindOfArgus::viewChanged_Heat()
{
	viewMode = _VIEW_HEAT;
}

void MindOfArgus::videoSync(QString qstr)
{
	vidDir = qstr.toStdString();
	video.open(vidDir);

	if (video.isOpened())
	{
		loaded = true;
		frameRate = video.get(CV_CAP_PROP_FPS);
		totalFrames = int(video.get(CV_CAP_PROP_FRAME_COUNT));
		resoHeight = int(video.get(CV_CAP_PROP_FRAME_HEIGHT));
		resoWidth = int(video.get(CV_CAP_PROP_FRAME_WIDTH));
		video.read(viewFrame);
		interTimer = (1/frameRate)*1000;
		emit sendSight(viewFrame, _COLOR_BGR);
	}
	else
	{
		frameRate = -1;
		totalFrames = -1;
		resoHeight = -1;
		resoWidth = -1;
	}

	std::cout << "Frame Rate inside of ArgusMind: " << frameRate << std::endl;
	std::cout << "Frame Count inside of ArgusMind: " << totalFrames << std::endl;


	emit videoSynced(frameRate, totalFrames, resoWidth, resoHeight);
}

void MindOfArgus::frameChanged(int frameNum)
{
	if (frameNum != (currFrame + 1))
	{
		video.set(CV_CAP_PROP_POS_FRAMES, frameNum);
	}
	video.set(CV_CAP_PROP_POS_FRAMES, frameNum);
	video.read(viewFrame);

	switch (viewMode)
	{
		case _VIEW_NORM:
			emit sendSight(viewFrame, _COLOR_BGR);
			break;

		case _VIEW_SUBT:
			emit sendSight(viewFrame, _COLOR_BNW);
			break;

		case _VIEW_MASK:
			emit sendSight(viewFrame, _COLOR_BNW);
			break;

		case _VIEW_HEAT:
			emit sendSight(viewFrame, _COLOR_BGR);
			break;
	}
	currFrame = frameNum;
}

void MindOfArgus::nextFrame()
{
	video >> viewFrame;
	switch (viewMode)
	{
		case _VIEW_NORM:
			emit sendSight(viewFrame, _COLOR_BGR);
			break;

		case _VIEW_SUBT:
			cv::GaussianBlur(viewFrame, viewFrame, cv::Size(3, 3), 0, 0);
			//cv::Canny(viewFrame, viewFrame, 100, 200, 3, false);
			//std::cout << viewFrame.rows << " " << viewFrame.cols << std::endl;
			emit sendSight(viewFrame, _COLOR_BNW);
			break;

		case _VIEW_MASK:
			emit sendSight(viewFrame, _COLOR_BNW);
			break;

		case _VIEW_HEAT:
			emit sendSight(viewFrame, _COLOR_BGR);
			break;
	}
	currFrame++;
	if(currFrame > totalFrames)
	{
		argusTimer->stop();
		playing = false;
	}
	emit updateGUI(currFrame);
}