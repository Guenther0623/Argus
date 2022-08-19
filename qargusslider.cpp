#include "qargusslider.h"

QArgusSlider::QArgusSlider(int width)
{
	totalBox = new QVBoxLayout(this);
	//markerBox = new QHBoxLayout();
	//sliderBox = new QHBoxLayout();
	totalBox->addSpacing(50);
	
	argusSlider = new QSlider(Qt::Horizontal);
	argusSlider->setFixedSize(width, 20);
	argusSlider->setMinimum(1);
	argusSlider->setMaximum(1);
	argusSlider->setTickPosition(QSlider::TicksBelow);
	connect(argusSlider, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged(int)));
	connect(argusSlider, SIGNAL(sliderReleased()), this, SLOT(sliderWasReleased()));

	totalBox->addWidget(argusSlider);

	//markerBox->addSpacing(20);
	//sliderBox->addWidget(argusSlider);
	//baseWidget = new QWidget();
	//QPushButton *button1 = new QPushButton(this);
	//button1->move(100, 5);
	//button1->resize(30, 30);

	
	//markerBox->addWidget(baseWidget);
	//baseWidget->resize(700, 20);
	//button1->resize(20, 15);
	//button1->move(10, 10);
	//sliderBox->addWidget(argusSlider);

}

QArgusSlider::~QArgusSlider()
{

}

int QArgusSlider::value()
{
	return argusSlider->value();
}

void QArgusSlider::setValue(int val)
{
	argusSlider->setValue(val);
}

bool QArgusSlider::isSliderDown()
{
	return argusSlider->isSliderDown();
}

void QArgusSlider::testSlider()
{
	argusSlider->setMaximum(1000);
	argusSlider->setValue(1);

}

void QArgusSlider::enableSlider(int lim)
{
	argusSlider->setMaximum(lim);
	argusSlider->setValue(1);
}

void QArgusSlider::disableSlider()
{
	argusSlider->setValue(1);
	argusSlider->setMaximum(1);
}

//PUBLIC SLOTS

//retractFive
void QArgusSlider::retractFive()
{
	int curr = argusSlider->value();
	if (curr-5 <= 0)
	{
		argusSlider->setValue(1);
	}
	else
	{
		argusSlider->setValue(argusSlider->value() - 5);
	}
}

void QArgusSlider::retractOne()
{
	int curr = argusSlider->value();
	if (curr-1 <= 0)
	{
		argusSlider->setValue(1);
	}
	else
	{
		argusSlider->setValue(curr - 1);
	}
}

void QArgusSlider::returnOne()
{
	int curr = argusSlider->value();
	if (curr+1 >= argusSlider->maximum())
	{
		argusSlider->setValue(argusSlider->maximum());
	}
	else
	{
		argusSlider->setValue(curr + 1);
	}
}

void QArgusSlider::returnFive()
{
	int curr = argusSlider->value();
	if (curr+5 >= argusSlider->maximum())
	{
		argusSlider->setValue(argusSlider->maximum());
	}
	else
	{
		argusSlider->setValue(curr + 5);
	}
}

void QArgusSlider::addMarker()
{
	std::cout << "addMarker routine entered\n" << std::endl;
	int curV = argusSlider->value();
	int maxV = argusSlider->maximum();
	int minV = argusSlider->minimum();
	int wdth = argusSlider->width();

	int pos = QStyle::sliderPositionFromValue(minV, maxV, curV, wdth);
	std::cout << "position determined to be:" << pos << std::endl;

	QPushButton *newButton = new QPushButton(this);

	newButton->move(pos, 5);
	newButton->resize(30, 20);
	newButton->show();
}

//PRIVATE SLOTS

//sliderValueChanged
// slot that receives the internal signal from qSlider's valueChanged signal, 
// and then emits its own valueChanged signal. 
// qSlider(SIGNAL_valueChanged) -> qArgusSlider(SLOT_sliderValueChanged) -> 
// qArgusSlider(SIGNAL_valueChanged) -> argus(SLOT_qSliderChanged)
void QArgusSlider::sliderValueChanged(int val)
{
	emit valueChanged(val);
}

void QArgusSlider::sliderWasReleased()
{
	emit sliderReleased();
}