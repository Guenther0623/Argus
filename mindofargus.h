#ifndef MINDOFARGUS_H
#define MINDOFARGUS_H

#define _COLOR_BNW 1
#define _COLOR_BGR 2
#define _COLOR_RGB 3

#define _VIEW_NORM 1
#define _VIEW_SUBT 2
#define _VIEW_MASK 3
#define _VIEW_HEAT 4

#include <QObject>
#include <opencv2/highgui.hpp>
//#include <opencv2/videoio/videoio.hpp>
#include <iostream>
#include <string>

class MindOfArgus : public QObject
{
	Q_OBJECT

public:
	MindOfArgus();
	~MindOfArgus();

private:
	int viewMode;

	cv::Mat viewFrame;
	cv::Mat deffFrame;
	cv::Mat subtFrame;
	cv::Mat maskFrame;
	cv::Mat heatFrame;

	cv::VideoCapture video;
	std::string vidDir;

	double frameRate;
	int resoWidth;
	int resoHeight;
	int totalFrames;

	void videoChange();

public slots:
	void viewChanged_Deff();
	void viewChanged_Subt();
	void viewChanged_Mask();
	void viewChanged_Heat();

	void videoSync(QString);

private slots:
	void frameChanged(int);

signals:
	void sendSight(cv::Mat, int);
	void videoSynced(double, int, int, int);

};

#endif