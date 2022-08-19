#ifndef QARGUSSLIDER_H
#define QARGUSSLIDER_H

#include <iostream>
#include <QCoreApplication>
#include <QMainWindow>
#include <QBoxLayout>
#include <QWidget>
#include <QSlider>
#include <QStyle>
#include <QPushButton>
#include <vector>

class QArgusSlider : public QWidget
{
	Q_OBJECT

	public:
		QArgusSlider(int);
		~QArgusSlider();

		void enableSlider(int);
		void disableSlider();

		bool isSliderDown();

		void setValue(int);
		int value();

		void testSlider();

	private:
		QVBoxLayout *totalBox;
		//QHBoxLayout *markerBox;
		//QHBoxLayout *sliderBox;
		QWidget *baseWidget;
		QSlider *argusSlider;

		std::vector<QPushButton *> buttonVec;

		//QPushButton *button1;

	private slots:
		void sliderValueChanged(int);
		void sliderWasReleased();

	public slots:
		void retractFive();
		void retractOne();
		void returnOne();
		void returnFive();
		void addMarker();

	signals:
		void valueChanged(int);
		void sliderReleased();
};

#endif