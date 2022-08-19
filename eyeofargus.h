#ifndef EYEOFARGUS_H
#define EYEOFARGUS_H

#include <QLabel>
#include <QWidget>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//using namespace cv;

class argusROI
{
	public:
		argusROI(int numP){
			p = new cv::Point[numP];
			for (int i = 0; i < numP; i++) {
				p[i] = cv::Point(-1, -1);
			}
			numPoints = 0;
		};
		~argusROI();

		cv::Point *p;
		int numPoints;
};

class retinaROI
{
	public:
		retinaROI(){
			p = new cv::Point[2];
			for (int i = 0; i < 2; i++) {
				p[i] = cv::Point(-1, -1);
			}
			numPoints = 0;
		};
		~retinaROI();

		cv::Point *p;
		int numPoints;
};

class EyeOfArgus : public QLabel
{
	Q_OBJECT

	public:
		EyeOfArgus(QWidget *parent = 0);
		~EyeOfArgus();

		void showHomeScreen();

	private:

	protected:
		void mouseMoveEvent(QMouseEvent *ev);
		void mouseReleaseEvent(QMouseEvent *ev);

	public slots:
		void receiveSight(cv::Mat, int);

	signals:
		void mouseMoved(QMouseEvent*);
		void clickReleased(QMouseEvent*);
};



#endif