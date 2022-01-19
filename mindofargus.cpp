#include "mindofargus.h"


MindOfArgus::MindOfArgus()
{
	viewMode = _VIEW_NORM;
}

MindOfArgus::~MindOfArgus()
{

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
		frameRate = video.get(CV_CAP_PROP_FPS);
		totalFrames = int(video.get(CV_CAP_PROP_FRAME_COUNT));
		resoHeight = int(video.get(CV_CAP_PROP_FRAME_HEIGHT));
		resoWidth = int(video.get(CV_CAP_PROP_FRAME_WIDTH));
		video.read(viewFrame);
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
	video.set(CV_CAP_PROP_POS_FRAMES, frameNum);
	cv::Mat temp;
	video.read(temp);

	switch (viewMode)
	{
		case _VIEW_NORM:
			emit sendSight(temp, _COLOR_BGR);
			break;

		case _VIEW_SUBT:
			emit sendSight(temp, _COLOR_BNW);
			break;

		case _VIEW_MASK:
			emit sendSight(temp, _COLOR_BNW);
			break;

		case _VIEW_HEAT:
			emit sendSight(temp, _COLOR_BGR);
			break;
	}
}