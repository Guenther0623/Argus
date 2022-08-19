#ifndef QARGUSBUTTON_H
#define QARGUSBUTTON_H

#include <iostream>
#include <QCoreApplication>
#include <QMainWindow>
#include <QBoxLayout>
#include <QWidget>
#include <QSlider>
#include <QStyle>
#include <QPushButton>
#include <vector>

class QArgusButton : public QPushButton
{
	Q_OBJECT

	public:
		QArgusButton(QString, int, QWidget *parent = 0);
		~QArgusButton();
		void setVal(int);
		int returnVal();

	private:
		int val;
		bool state;

	private slots:
		void sendValue();

	signals:
		void valReleased(int);
};

#endif