#include "eyeofargus.h"

#define _COLOR_BNW 1
#define _COLOR_BGR 2
#define _COLOR_RGB 3

#define _GREEN	0
#define _BLUE	1
#define _RED	2
#define _YELLOW	3

EyeOfArgus::EyeOfArgus(QWidget *parent)
	: QLabel(parent)
{

}

EyeOfArgus::~EyeOfArgus()
{
	
}

void EyeOfArgus::showHomeScreen()
{
	cv::Mat newFrame = cv::imread("eye.jpg");
	cv::Mat blur;
	GaussianBlur(newFrame, blur, cv::Size(3, 3), 0, 0);
	std::cout<<"Argus Eye: Sending home screen"<<std::endl;
	receiveSight(blur,_COLOR_BNW);
}

void EyeOfArgus::receiveSight(cv::Mat viewFrame, int colorMode)
{
	if (viewFrame.rows == 1080)
	{
		cv::resize(viewFrame, viewFrame, cv::Size(1920/2, 1080/2), 0, 0, cv::INTER_LINEAR);
	}
	if (viewFrame.rows == 1024)
	{
		cv::resize(viewFrame, viewFrame, cv::Size(1280/2, 1024/2), 0, 0, cv::INTER_LINEAR);
	}
	//std::cout<<"Eye: chk01"<<std::endl;
	switch(colorMode)
	{
		case _COLOR_BNW:
			//cvtColor(viewFrame, viewFrame, CV_BGR2GRAY);
			//this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_Indexed8)));
			//std::cout<<"Eye: chk02.1"<<std::endl;
			this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_Grayscale8)));
			//this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_Grayscale16)));
			//std::cout<<"Eye: chk03.1"<<std::endl;
			break;
		case _COLOR_BGR:
			//std::cout<<"Eye: chk02.2"<<std::endl;
			cvtColor(viewFrame, viewFrame, cv::COLOR_BGR2RGB);
			//std::cout << "Cols of image: " << viewFrame.cols << std::endl << "Rows of image: " << viewFrame.rows << std::endl;
			this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_RGB888)));
			//std::cout<<"Eye: chk03.2"<<std::endl;
			break;
		case _COLOR_RGB:
			//std::cout<<"Eye: chk02.3"<<std::endl;
			this->setPixmap(QPixmap::fromImage(QImage(viewFrame.data, viewFrame.cols, viewFrame.rows, viewFrame.step, QImage::Format_RGB888)));
			//std::cout<<"Eye: chk03.3"<<std::endl;
			break;
	}
	this->setAlignment(Qt::AlignCenter);
	std::cout<<"Eye assigned a frame"<<std::endl;
	
	//this->update();
	//this->repaint();
	//std::cout<<"Eye: chk04"<<std::endl;
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
