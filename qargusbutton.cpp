#include "qargusbutton.h"

QArgusButton::QArgusButton(QString s, int v, QWidget *parent)
	: QPushButton(parent)
{
	this->setText(s);
	val = v;
	state = false;

	connect(this, SIGNAL(released()), this, SLOT(sendValue()));
}

QArgusButton::~QArgusButton()
{
	
}

int QArgusButton::returnVal()
{
	return val;
}

void QArgusButton::setVal(int v)
{
	val = v;
}

void QArgusButton::sendValue()
{
	emit valReleased(val);
}