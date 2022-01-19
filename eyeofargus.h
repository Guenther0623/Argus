#ifndef EYEOFARGUS_H
#define EYEOFARGUS_H

#include <QLabel>
#include <QWidget>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//using namespace cv;

class EyeOfArgus : public QLabel
{
	Q_OBJECT

	public:
		EyeOfArgus(QWidget *parent = 0);
		~EyeOfArgus();

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