#include <QtWidgets>
#include <QLineEdit>
#include <iostream>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QPixmap>

#define _COLOR_BNW 1
#define _COLOR_BGR 2
#define _COLOR_RGB 3

#include "argus.h"

using namespace std;
using namespace cv;

Argus::Argus(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *mainGrid = new QGridLayout;

	argusMind = new MindOfArgus();

	mainGrid->addWidget(createTitle(), 0, 0, 1, 4);
	mainGrid->addWidget(createVideoOptions(), 1, 0, 1, 1);
	mainGrid->addWidget(createLogWindow(), 2, 0, 1, 1);
	mainGrid->addWidget(createVideoPlayer(), 1, 2, 2, 1);
	mainGrid->addWidget(createExperOptions(), 1, 3, 2, 1);
	//mainGrid->addWidget(createVideoAnalysis(), 2, 1);

	connect(argusEye, SIGNAL(clickReleased(QMouseEvent*)), this, SLOT(eyeClicked(QMouseEvent*)));
	connect(argusEye, SIGNAL(mouseMoved(QMouseEvent*)), this, SLOT(eyeMoved(QMouseEvent*)));
	connect(this, SIGNAL(sendSight(cv::Mat, int)), argusEye, SLOT(receiveSight(cv::Mat, int)));

	// Test eye presentation
	argusEye->showHomeScreen();
	//Mat newFrame = imread("eye.jpg");
	//cvtColor(newFrame, newFrame, CV_BGR2RGB);
	//argusEye->setPixmap(QPixmap::fromImage(QImage(newFrame.data, newFrame.cols, newFrame.rows, newFrame.step, QImage::Format_RGB888)));

	//cvtColor(newFrame, newFrame, CV_BGR2GRAY);
	//argusEye->setPixmap(QPixmap::fromImage(QImage(newFrame.data, newFrame.cols, newFrame.rows, newFrame.step, QImage::Format_Indexed8)));

	//Mat blur;
	//GaussianBlur(newFrame, blur, Size(3, 3), 0, 0);
	//Mat edges;
	//Canny(blur, edges, 100, 200, 3, false);
	//cvtColor(newFrame, newFrame, CV_BGR2GRAY);
	
	//emit sendSight(blur, _COLOR_BNW);

	
	connect(argusMind, SIGNAL(videoSynced(double, int, int, int)), this, SLOT(videoLoaded(double, int, int, int)));
	connect(this, SIGNAL(sendVideoQueue(QString)), argusMind, SLOT(videoSync(QString)));
	connect(argusMind, SIGNAL(sendSight(cv::Mat, int)), argusEye, SLOT(receiveSight(cv::Mat, int)));

	connect(this, SIGNAL(sendFrame(int)), argusMind, SLOT(frameChanged(int)));
	connect(argusMind, SIGNAL(updateGUI(int)), this, SLOT(guiUpdated(int)));
	connect(this, SIGNAL(sendStopSignal()), argusMind, SLOT(stopVideo()));
	//connect(this, SIGNAL())

	connect(this, SIGNAL(playVideo()), argusMind, SLOT(startVideo()));
	connect(this, SIGNAL(pauseVideo()), argusMind, SLOT(pauseVideo()));

	openField_ratNum = 1;

	setLayout(mainGrid);
}

Argus::~Argus()
{
	delete argusEye;

	delete vidIfoFrme;
	delete vidIfoReso;
	delete vidIfoTime;
	delete vidIfoName;

	delete fileLine;
}


/*
 *  createTitle
 *
 *  Creates the title box
 *
 */
QGroupBox *Argus::createTitle()
{
	QGroupBox *groupBox = new QGroupBox();
	groupBox->setStyleSheet("background-color: rgb(0, 128, 128)");

	QHBoxLayout *hbox = new QHBoxLayout;
	//QVBoxLayout *vbox = new QVBoxLayout;

	QLabel *title = new QLabel("Argus V0.2A");
	QFont font("Arial", 20, QFont::Bold);
	title->setAlignment(Qt::AlignCenter);
	title->setFont(font);

	hbox->setAlignment(Qt::AlignCenter);
	hbox->addWidget(title);

	//vbox->setAlignment(Qt::AlignCenter);
	//vbox->addLayout(hbox);

	groupBox->setLayout(hbox);

	return groupBox;
}

/*
 *  createTitle
 *
 *  Creates the box with instructions on
 *  to start the experiment of choice
 *
 */
QGroupBox *Argus::createVideoOptions()
{
	QGroupBox *groupBox = new QGroupBox(tr("Video Options Menu"));
	groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {border: 1px solid gray; border-radius: 5px; margin-top: 1ex; font-size: 20px; font-weight: bold} QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px}"));

	QFont fontTopTtls("Arial", 14, QFont::Bold);
	QFont fontSubTtls("Arial", 12);
	QFont fontbaseTxt("Arial", 10);

	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *hbox01 = new QHBoxLayout;
	QHBoxLayout *hbox02 = new QHBoxLayout;
	QHBoxLayout *hbox03 = new QHBoxLayout;
	QPushButton *buttonGrabVideo = new QPushButton(tr("..."));
	QPushButton *buttonLoadVideo = new QPushButton(tr("Load Video"));
	QLabel *fileLabel = new QLabel("Video File:");
	fileLabel->setFont(fontTopTtls);
	fileLine = new QLineEdit();
	fileLine->setFixedSize(200, 30);
	buttonGrabVideo->setFixedSize(25, 25);
	buttonLoadVideo->setFixedSize(150, 30);

	hbox01->addSpacing(5);
	hbox01->addWidget(fileLabel);
	hbox01->addStretch(100);

	hbox02->addStretch(20);
	hbox02->addWidget(fileLine);
	hbox02->addSpacing(5);
	hbox02->addWidget(buttonGrabVideo);
	hbox02->addStretch(20);

	hbox03->addStretch(5);
	hbox03->addWidget(buttonLoadVideo);
	hbox03->addStretch(5);

	QLabel *infoLabel = new QLabel("Video Info:");
	infoLabel->setFont(fontTopTtls);
	QLabel *vidLabName = new QLabel("Video Name:");
	vidLabName->setFont(fontSubTtls);
	vidIfoName = new QLabel("-");
	QLabel *vidLabReso = new QLabel("Resolution:");
	vidLabReso->setFont(fontSubTtls);
	vidIfoReso = new QLabel("-");
	QLabel *vidLabFrme = new QLabel("Frame Rate:");
	vidLabFrme->setFont(fontSubTtls);
	vidIfoFrme = new QLabel("-");
	QLabel *vidLabTime = new QLabel("Total Time:");
	vidLabTime->setFont(fontSubTtls);
	vidIfoTime = new QLabel("-");

	QHBoxLayout *hbox04 = new QHBoxLayout;
	QVBoxLayout *vbox01 = new QVBoxLayout;

	hbox04->addSpacing(5);
	hbox04->addWidget(infoLabel);
	hbox04->addStretch(100);

	QHBoxLayout *hb01 = new QHBoxLayout;
	QHBoxLayout *hb02 = new QHBoxLayout;
	QHBoxLayout *hb03 = new QHBoxLayout;
	QHBoxLayout *hb04 = new QHBoxLayout;
	QHBoxLayout *hb05 = new QHBoxLayout;
	QHBoxLayout *hb06 = new QHBoxLayout;
	QHBoxLayout *hb07 = new QHBoxLayout;
	QHBoxLayout *hb08 = new QHBoxLayout;

	hb01->addSpacing(20);
	hb01->addWidget(vidLabName);
	hb01->addStretch(100);
	hb02->addStretch(5);
	hb02->addWidget(vidIfoName);
	hb02->addStretch(5);

	hb03->addSpacing(20);
	hb03->addWidget(vidLabReso);
	hb03->addStretch(100);
	hb04->addStretch(5);
	hb04->addWidget(vidIfoReso);
	hb04->addStretch(5);

	hb05->addSpacing(20);
	hb05->addWidget(vidLabFrme);
	hb05->addStretch(100);
	hb06->addStretch(5);
	hb06->addWidget(vidIfoFrme);
	hb06->addStretch(5);

	hb07->addSpacing(20);
	hb07->addWidget(vidLabTime);
	hb07->addStretch(100);
	hb08->addStretch(5);
	hb08->addWidget(vidIfoTime);
	hb08->addStretch(5);

	vbox01->addSpacing(2);
	vbox01->addLayout(hb01);
	vbox01->addLayout(hb02);
	vbox01->addStretch(1);
	vbox01->addLayout(hb03);
	vbox01->addLayout(hb04);
	vbox01->addStretch(1);
	vbox01->addLayout(hb05);
	vbox01->addLayout(hb06);
	vbox01->addStretch(1);
	vbox01->addLayout(hb07);
	vbox01->addLayout(hb08);
	vbox01->addStretch(5);
	
	vbox->addLayout(hbox01);
	vbox->addLayout(hbox02);
	vbox->addLayout(hbox03);
	vbox->addSpacing(20);
	vbox->addLayout(hbox04);
	vbox->addLayout(vbox01);
	vbox->addStretch(10);

	connect(fileLine, SIGNAL(textChanged(QString)),
			this, SLOT(filePathChanged(QString)));
	connect(buttonGrabVideo, SIGNAL(released()),
			this, SLOT(locateVideo()));
	connect(buttonLoadVideo, SIGNAL(released()), 
			this, SLOT(loadVideo()));

	groupBox->setLayout(vbox);
	return groupBox;
}

QGroupBox *Argus::createLogWindow()
{
	QGroupBox *groupBox = new QGroupBox();

	return groupBox;
}

QGroupBox *Argus::createVideoPlayer()
{
	QGroupBox *groupBox = new QGroupBox();

	QVBoxLayout *vbox = new QVBoxLayout;
	QHBoxLayout *hbox01 = new QHBoxLayout;
	QHBoxLayout *hbox02 = new QHBoxLayout;
	QHBoxLayout *hbox03 = new QHBoxLayout;
	QHBoxLayout *hbox04 = new QHBoxLayout;

	argusEye = new EyeOfArgus();
	
	argusEye->setMouseTracking(true);
	argusEye->setFixedHeight(1080/2);
	argusEye->setFixedWidth(1920/2);
	argusEye->setStyleSheet("border: 1px solid black;");
	
	hbox01->addStretch(5);
	hbox01->addWidget(argusEye);
	hbox01->addStretch(5);

	QPushButton *backFive = new QPushButton("<<-");
	connect(backFive, SIGNAL(released()), this, SLOT(retractFive()));
	QPushButton *backOne = new QPushButton("<-");
	connect(backOne, SIGNAL(released()), this, SLOT(retractOne()));
	QPushButton *forwOne = new QPushButton("->");
	connect(forwOne, SIGNAL(released()), this, SLOT(returnOne()));
	QPushButton *forwFive = new QPushButton("->>");
	connect(forwFive, SIGNAL(released()), this, SLOT(returnFive()));
	QPushButton *playPause = new QPushButton("P / P");
	playPause->setCheckable(true);
	connect(playPause, SIGNAL(toggled(bool)), this, SLOT(videoPlayPause(bool)));
	QPushButton *stopNow = new QPushButton("Stop");
	connect(stopNow, SIGNAL(released()), this, SLOT(videoStop()));
	QVBoxLayout *vbox01 = new QVBoxLayout;
	vbox01->addWidget(playPause);
	vbox01->addWidget(stopNow);
	hbox02->addWidget(backFive);
	hbox02->addWidget(backOne);
	hbox02->addLayout(vbox01);
	hbox02->addWidget(forwOne);
	hbox02->addWidget(forwFive);

	QLabel *frameLabel = new QLabel("Frame:");
	qFrameSpiner = new QSpinBox();
	qFrameSpiner->setMinimum(1);
	qFrameSpiner->setMaximum(1);
	labelFrameMax = new QLabel(" \\ NA frames");
	qFrameSlider = new QSlider(Qt::Horizontal);
	qFrameSlider->setFixedSize(700, 20);
	qFrameSlider->setMinimum(1);
	qFrameSlider->setMaximum(130);
	qFrameSlider->setTickPosition(QSlider::TicksBelow);
	hbox03->addSpacing(10);
	hbox03->addWidget(qFrameSlider);
	hbox03->addStretch(10);
	hbox03->addWidget(frameLabel);
	hbox03->addWidget(qFrameSpiner);
	hbox03->addWidget(labelFrameMax);
	hbox03->addSpacing(10);

	int position = QStyle::sliderPositionFromValue(qFrameSlider->minimum(), qFrameSlider->maximum(), 
		65, qFrameSlider->width());
	QPainter painter(this);
	painter.drawLine(position, 0, position, qFrameSlider->height() + 5);
	update();
	//qFrameSlider->paintEvent(painter)

	connect(qFrameSlider, SIGNAL(valueChanged(int)), this, SLOT(qSliderChanged(int)));
	connect(qFrameSpiner, SIGNAL(valueChanged(int)), this, SLOT(qSpinerChanged(int)));

	QRadioButton *viewDeff = new QRadioButton("Default");
	QRadioButton *viewSubs = new QRadioButton("Subtracted");
	QRadioButton *viewMask = new QRadioButton("Masked");
	QRadioButton *viewHeat = new QRadioButton("Heatmap");
	viewDeff->setChecked(true);
	connect(viewDeff, SIGNAL(clicked()), argusMind, SLOT(viewChanged_Deff()));
	connect(viewSubs, SIGNAL(clicked()), argusMind, SLOT(viewChanged_Subt()));

	hbox04->addStretch(5);
	hbox04->addWidget(viewDeff);
	hbox04->addWidget(viewSubs);
	hbox04->addWidget(viewMask);
	hbox04->addWidget(viewHeat);
	hbox04->addStretch(5);

	vbox->addLayout(hbox01);
	vbox->addStretch(1);
	vbox->addLayout(hbox02);
	vbox->addStretch(1);
	vbox->addLayout(hbox03);
	vbox->addStretch(2);
	vbox->addLayout(hbox04);
	vbox->addStretch(5);

	groupBox->setLayout(vbox);

	return groupBox;
}

QGroupBox *Argus::createExperOptions()
{
	QGroupBox *groupBox = new QGroupBox(tr("Experiment Options Menu"));
	groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {border: 1px solid gray; border-radius: 5px; margin-top: 1ex; font-size: 20px; font-weight: bold} QGroupBox::title { subcontrol-origin: margin; subcontrol-position: top center; padding: 0 3px}"));

	QTabWidget *paramTabs = new QTabWidget;

	paramTabs->addTab(createExperiment_OpenField(), "Open-Field");
	paramTabs->addTab(createExperiment_PlusMaze(), "Ele. Plus-Maze");
	paramTabs->addTab(createExperiment_Default(), "Default");

	QHBoxLayout *hbox = new QHBoxLayout;

	hbox->addWidget(paramTabs);

	groupBox->setLayout(hbox);

	return groupBox;
}

QGroupBox *Argus::createExperiment_OpenField()
{
	QGroupBox *groupBox = new QGroupBox(tr("Open-Field Task Menu"));

	QHBoxLayout *hbox01 = new QHBoxLayout();
	QHBoxLayout *hbox02 = new QHBoxLayout();
	QVBoxLayout *vbox = new QVBoxLayout();

	QLabel *ratNumLab = new QLabel("Number of Experiments in Video:");
	QSpinBox *spinRatNum = new QSpinBox;
	spinRatNum->setRange(1, 4);
	spinRatNum->setSingleStep(1);
	spinRatNum->setValue(1);
	spinRatNum->setFixedSize(45, 25);

	hbox01->addSpacing(10);
	hbox01->addWidget(ratNumLab);
	hbox01->addSpacing(5);
	hbox01->addWidget(spinRatNum);
	hbox01->addSpacing(10);
	hbox01->addStretch(1);

	groupBox->setLayout(hbox01);

	connect(spinRatNum, SIGNAL(valueChanged(int)), this, SLOT(change_ratNumOpenField(int)));

	return groupBox;
}

QGroupBox *Argus::createExperiment_PlusMaze()
{
	QGroupBox *groupBox = new QGroupBox(tr("Elevated Plus-Maze Menu"));

	return groupBox;
}

QGroupBox *Argus::createExperiment_Default()
{
	QGroupBox *groupBox = new QGroupBox(tr("Default Experiment Menu"));

	return groupBox;
}

void Argus::filePathChanged(QString text)
{
	fileName = text;
}

void Argus::locateVideo()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mkv)"));
	fileLine->setText(fileName);
}

void Argus::loadVideo()
{
	QFile *fileID = new QFile(fileName);
	if (fileID->exists())
	{
		QFileInfo fileInfo(fileID->fileName());
		emit sendVideoQueue(fileInfo.fileName());
		vidIfoName->setText(fileInfo.fileName());
	}
	else
	{
		vidIfoName->setText("INVALID");
		vidIfoReso->setText("N/A");
		vidIfoFrme->setText("N/A");
		vidIfoTime->setText("N/A");
	}
}

void Argus::change_ratNumOpenField(int rn)
{
	openField_ratNum = rn;
}

void Argus::eyeClicked(QMouseEvent *ev)
{
	cout << "Argus Eye Clicked" << endl;
}

void Argus::eyeMoved(QMouseEvent *ev)
{
	int x = ev->x();
	int y = ev->y();
	cout << x << ", " << y << endl;
}
//PRIVATE SLOTS
//Exist only in this workspace
void Argus::retractFive()
{
	int curr = qFrameSlider->value();
	if (curr-5 <= 0)
	{
		qFrameSlider->setValue(1);
	}
	else
	{
		qFrameSlider->setValue(qFrameSlider->value() - 5);
	}
}

void Argus::retractOne()
{
	int curr = qFrameSlider->value();
	if (curr-1 <= 0)
	{
		qFrameSlider->setValue(1);
	}
	else
	{
		qFrameSlider->setValue(curr - 1);
	}
}

void Argus::returnOne()
{
	int curr = qFrameSlider->value();
	if (curr+1 >= qFrameSlider->maximum())
	{
		qFrameSlider->setValue(qFrameSlider->maximum());
	}
	else
	{
		qFrameSlider->setValue(curr + 1);
	}
}

void Argus::returnFive()
{
	int curr = qFrameSlider->value();
	if (curr+5 >= qFrameSlider->maximum())
	{
		qFrameSlider->setValue(qFrameSlider->maximum());
	}
	else
	{
		qFrameSlider->setValue(curr + 5);
	}
}

void Argus::videoPlayPause(bool isChecked)
{
	if(isChecked)
	{
		emit playVideo();
	}
	else
	{
		emit pauseVideo();
	}
}

void Argus::videoStop()
{
	qFrameSlider->setMaximum(1);
	qFrameSpiner->setMaximum(1);
	qFrameSlider->setValue(1);
	vidIfoName->setText("INVALID");
	vidIfoReso->setText("N/A");
	vidIfoFrme->setText("N/A");
	vidIfoTime->setText("N/A");
	labelFrameMax->setText(" \\ NA frames");
	fileLine->clear();

	argusEye->showHomeScreen();
	emit sendStopSignal();
}

void Argus::guiUpdated(int ff)
{
	if(qFrameSlider->value() != ff)
	{
		qFrameSlider->setValue(ff);
	}
}

void Argus::qSliderChanged(int vv)
{
	//qFrameSlider->setValue(vv);
	
	//qFrameSpiner->setValue(vv);
	if (qFrameSpiner->value() != vv)
	{
		qFrameSpiner->setValue(vv);
	}
	//std::cout << "Ran slider changed" << std::endl;
}

void Argus::qSpinerChanged(int vv)
{
	//qFrameSpiner->setValue(vv);
	if (qFrameSlider->value() != vv)
	{
		qFrameSlider->setValue(vv);
	}
	//std::cout << "Ran spinner changed" << std::endl;
	if (argusMind->isLoaded() & !argusMind->isPlaying())
	{	
		emit sendFrame(vv);
	}
}
// PUBLIC SLOTS
void Argus::videoLoaded(double fr, int tf, int rw, int rh)
{
	if (int(fr) == -1)
	{
		vidIfoName->setText("ERROR");
		vidIfoReso->setText("N/A");
		vidIfoFrme->setText("N/A");
		vidIfoTime->setText("N/A");
	}
	else
	{
		vidIfoFrme->setText(QString::fromStdString(std::to_string(int(fr))));
		string ss1 = std::to_string(rw) + " x " + std::to_string(rh);
		vidIfoReso->setText(QString::fromStdString(ss1));

		int time = int(tf/fr);
		int min = time / 60;
		int sec = time % 60;
		string ss2 = std::to_string(min) + ":" + std::to_string(sec);
		vidIfoTime->setText(QString::fromStdString(ss2));

		qFrameSlider->setMaximum(tf);
		string sst = " \\ " + std::to_string(tf) + " frames";
		labelFrameMax->setText(QString::fromStdString(sst));
		qFrameSpiner->setMaximum(tf);
		qFrameSpiner->setValue(1);
		qFrameSlider->setValue(1);
		//qFrameSlider->setEnabled(false);
	}
	cout << "Frame Rate: " << int(fr) << endl;
	cout << "Frame Count: " << tf << endl;

	
}

void Argus::closeEvent(QCloseEvent *event)
{
	int resBtn = QMessageBox::question(this, "Close Confirmation",
									"Are you sure you want to exit?\n",
									QMessageBox::Yes,
									QMessageBox::No);

	if(resBtn == QMessageBox::Yes)
		event->accept();
	else if(resBtn == QMessageBox::No)
		event->ignore();
}