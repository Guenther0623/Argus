#include "qstatewatcher.h"

#define _STATE_WAIT		0
#define _STATE_GOOD		1
#define _STATE_STOP		2
#define _STATE_OFF		-1
#define _STATE_ON		-2

QStateWatcher::QStateWatcher(QString activeGood,
					QString activeWait,
					QString activeStop,
					QString inactiveOf,
					QString inactiveOn,
					int ww, 
					int hh,
					QWidget *parent)
	: QLabel(parent)
{
	this->setFixedSize(ww, hh);
	int w = ww;
	int h = hh;

	imageActiveGood = QImage(activeGood).scaled(w, h, Qt::KeepAspectRatio);
	imageActiveWait = QImage(activeWait).scaled(w, h, Qt::KeepAspectRatio);
	imageActiveStop = QImage(activeStop).scaled(w, h, Qt::KeepAspectRatio);
	imageInactiveOf = QImage(inactiveOf).scaled(w, h, Qt::KeepAspectRatio);
	imageInactiveOn = QImage(inactiveOn).scaled(w, h, Qt::KeepAspectRatio);

	valueActiveGood = _STATE_GOOD;
	valueActiveWait = _STATE_WAIT;
	valueActiveStop = _STATE_STOP;
	valueInactiveOf = _STATE_OFF;
	valueInactiveOn = _STATE_ON;

	currState = -1;
	this->setPixmap(QPixmap::fromImage(imageInactiveOf));
}

QStateWatcher::~QStateWatcher()
{

}

int QStateWatcher::getState()
{
	return currState;
}

void QStateWatcher::changeState(int state)
{
	if (state != currState)
	{
		switch(state)
		{
			case _STATE_ON:
				this->setPixmap(QPixmap::fromImage(imageInactiveOn));
				break;

			case _STATE_OFF:
				this->setPixmap(QPixmap::fromImage(imageInactiveOf));
				break;

			case _STATE_WAIT:
				this->setPixmap(QPixmap::fromImage(imageActiveWait));
				break;

			case _STATE_GOOD:
				this->setPixmap(QPixmap::fromImage(imageActiveGood));
				break;

			case _STATE_STOP:
				this->setPixmap(QPixmap::fromImage(imageActiveStop));
				break;
		}
		currState = state;
	}
}

//PUBLIC SLOTS
void QStateWatcher::changeStateSLOT(int state)
{
	if (state != currState)
	{
		switch(state)
		{
			case _STATE_ON:
				this->setPixmap(QPixmap::fromImage(imageInactiveOn));
				break;

			case _STATE_OFF:
				this->setPixmap(QPixmap::fromImage(imageInactiveOf));
				break;

			case _STATE_WAIT:
				this->setPixmap(QPixmap::fromImage(imageActiveWait));
				break;

			case _STATE_GOOD:
				this->setPixmap(QPixmap::fromImage(imageActiveGood));
				break;

			case _STATE_STOP:
				this->setPixmap(QPixmap::fromImage(imageActiveStop));
				break;		
		}
		currState = state;
	}
	
}