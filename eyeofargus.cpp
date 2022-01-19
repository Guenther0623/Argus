#include "eyeofargus.h"

#define _COLOR_BNW 1
#define _COLOR_BGR 2
#define _COLOR_RGB 3

EyeOfArgus::EyeOfArgus(QWidget *parent)
	: QLabel(parent)
{

}

EyeOfArgus::~EyeOfArgus()
{
	
}

void EyeOfArgus::receiveSight(cv::Mat viewFrame, int colorMode)
{
	if (viewFrame.rows > 1080/2)
	{
		cv::resize(viewFrame, viewFrame, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_LINEAR);
	}	

	switch(colorMode)
	{
		case _COLOR_BNW:
			this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_Indexed8)));
			break;
		case _COLOR_BGR:
			cvtColor(viewFrame, viewFrame, CV_BGR2RGB);
			std::cout << "Cols of image: " << viewFrame.cols << std::endl << "Rows of image: " << viewFrame.rows << std::endl;
			this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_RGB888)));
			break;
		case _COLOR_RGB:
			this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_RGB888)));
			break;
	}
	this->setAlignment(Qt::AlignCenter);
}

//EyeOfArgus custom

/* 
**
** All over-written signals used in custom EyeOfArgus
**
** 		Over-written signals are from inherited 
**		QLabel parent class
*/
void EyeOfArgus::mouseMoveEvent(QMouseEvent *ev)
{
	emit mouseMoved(ev);
}

void EyeOfArgus::mouseReleaseEvent(QMouseEvent *ev)
{
	emit clickReleased(ev);
}