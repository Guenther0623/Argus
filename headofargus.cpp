#include "headofargus.h"

#define _GREEN		0
#define _BLUE		1
#define _RED		2
#define _YELLOW		3
#define _BLACK		4

#define _COLOR_GREEN	cv::Scalar(0, 255, 0)
#define _COLOR_BLUE		cv::Scalar(255, 0, 0)
#define _COLOR_RED		cv::Scalar(0, 0, 255)
#define _COLOR_YELLOW	cv::Scalar(0, 255, 255)
#define _COLOR_BLACK	cv::Scalar(0, 0, 0)

#define _COLOR_BNW	1
#define _COLOR_BGR	2
#define _COLOR_RGB	3

#define _VIEW_NORM	0
#define _VIEW_BASE	1
#define _VIEW_REFR	2
#define _VIEW_DIFF	3
#define _VIEW_SUBT	4

#define _CROP_NORM	0
#define _CROP_MASK	1

HeadOfArgus::HeadOfArgus(QWidget *parent)
	: QGroupBox(parent)
{
	argusMind = new MindOfArgus();
	playTimer = new QTimer;

	loaded = false;
	//argusWorker = new QArgusWorker(this);

	setLayout(argusHeadLayout());
	argusEye->showHomeScreen();

	argusMind->moveToThread(&workerThread);
	connect(&workerThread, SIGNAL(finished()), argusMind, SLOT(deleteLater()));

	qRegisterMetaType< cv::Mat >("cv::Mat");
	connect(argusEye, SIGNAL(clickReleased(QMouseEvent*)), 
		argusMind, SLOT(eyeClicked(QMouseEvent*)));
	connect(argusEye, SIGNAL(mouseMoved(QMouseEvent*)),
		argusMind, SLOT(eyeMoved(QMouseEvent*)));
	connect(argusMind, SIGNAL(sendSight(cv::Mat, int)),
		argusEye, SLOT(receiveSight(cv::Mat, int)));

	connect(this, SIGNAL(sendVideoString(QString)),
		argusMind, SLOT(videoSync(QString)));
	connect(argusMind, SIGNAL(videoSynced(double, int, int, int)),
		this, SLOT(videoSyncCompleted(double, int, int, int)));

	connect(argusMind, SIGNAL(openField_expChange(int, bool)), this, SLOT(openField_expSet(int, bool)));
	connect(argusMind, SIGNAL(trackerInfo_Frame(int, int)), this, SLOT(trackerInfo_Send(int, int)));
	connect(this, SIGNAL(initNow_OF()), argusMind, SLOT(exp_initOF()));
	connect(this, SIGNAL(startNow_OF()), argusMind, SLOT(exp_startOF()));
	connect(this, SIGNAL(resuNow_OF()), argusMind, SLOT(exp_resuOF()));

	connect(argusMind, SIGNAL(pong_endOpenField()), this, SLOT(analysisFinished()));
	connect(argusMind, SIGNAL(request_TOIReassignment(int, bool*)), this, SLOT(sendRequest_TOIReassignment(int, bool*)));

	connect(playTimer, SIGNAL(timeout()), this, SLOT(goNextFrame()));
	connect(this, SIGNAL(nextFrame()), argusMind, SLOT(nextFrame()));
	connect(this, SIGNAL(startVideoNow()), argusMind, SLOT(playVideoLoop()));
	connect(argusMind, SIGNAL(updateGUI(int)), this, SLOT(guiUpdated(int)));

	connect(this, SIGNAL(stopVideoNow()), argusMind, SLOT(stopVideo()));

	connect(this, SIGNAL(assignRefImage(int)), argusMind, SLOT(setRefImage(int)));

	connect(this, SIGNAL(roiSelectStart(int, int)), argusMind, SLOT(startROISelector(int, int)));
	connect(this, SIGNAL(roiSelectSave(int)), argusMind, SLOT(saveROISelector(int)));
	connect(this, SIGNAL(roiSelectCancel(int)), argusMind, SLOT(cancelROISelector(int)));
	connect(this, SIGNAL(roiSelectRemove(int)), argusMind, SLOT(removeROISaved(int)));
	connect(this, SIGNAL(toiSelectStart(int, int)), argusMind, SLOT(startTOISelector(int, int)));
	connect(this, SIGNAL(toiSelectSave(int)), argusMind, SLOT(saveTOISelector(int)));
	connect(this, SIGNAL(toiSelectCancel(int)), argusMind, SLOT(cancelTOISelector(int)));
	connect(this, SIGNAL(toiSelectRemove(int)), argusMind, SLOT(removeTOISaved(int)));
	connect(this, SIGNAL(roiSelectColor(int, int)), argusMind, SLOT(roiSetColor(int, int)));
	//connect(this, SIGNAL(sendBoxDims(double, double, int)), argusMind, SLOT(saveBoxDims(double, double, int)));
	//connect(this, SIGNAL(sendTaskDur(int)), argusMind, SLOT(saveTaskDur(int)));

	connect(this, SIGNAL(setOF_BoxDims(double, double, int)), argusMind, SLOT(receiveOF_BoxDims(double, double, int)));
	connect(this, SIGNAL(setOF_TaskDur(int, int)), argusMind, SLOT(receiveOF_TaskDur(int, int)));

	totalFrames = -1;
	currentFrame = -1;

	roiNumPoints = 4;
	roiMaxNumber = 4;
	roiSelected = -1;
	toiNumPoints = 2;
	toiMaxNumber = 4;
	toiSelected = -1;
	usrNumPoints = 0;
	roiSelector = false;
	toiSelector = false;

	loaded = false;
	playing = false;
	processing = false;
	paused = false;

	waitingForUser = false;

	toiSaved = new bool[toiMaxNumber];
	for(int i = 0; i < toiMaxNumber; i++)
	{
		toiSaved[i] = false;
	}

	roiSaved = new bool[roiMaxNumber];
	for(int i = 0; i < roiMaxNumber; i++)
	{
		roiSaved[i] = false;
	}
	workerThread.start();
}

HeadOfArgus::~HeadOfArgus()
{
	workerThread.quit();
	workerThread.wait();
}

void HeadOfArgus::sendRequest_TOIReassignment(int idx, bool* isWaiting)
{
	emit ping_reguestTOIReassignment(idx);
}

QVBoxLayout *HeadOfArgus::argusHeadLayout()
{
	QVBoxLayout *vboxF = new QVBoxLayout;

	QHBoxLayout *hbox01 = new QHBoxLayout;
	QHBoxLayout *hbox03 = new QHBoxLayout;
	QHBoxLayout *hbox04 = new QHBoxLayout;

	argusEye = new EyeOfArgus(this);
	argusEye->setMouseTracking(true);
	argusEye->setFixedHeight(1080/2);
	argusEye->setFixedWidth(1920/2);
	argusEye->setStyleSheet("border: 1px solid black;");

	hbox01->addStretch(5);
	hbox01->addWidget(argusEye);
	hbox01->addStretch(5);

	argusSlider = new QArgusSlider(700);

	QHBoxLayout *hbox02 = new QHBoxLayout;
	QVBoxLayout *vbox01 = new QVBoxLayout;

	backFive = new QPushButton("<<-");
	forwFive = new QPushButton("->>");
	backOne = new QPushButton("<-");
	forwOne = new QPushButton("->");
	stopNow = new QPushButton("Stop");
	playPause = new QPushButton("P/P");
	playPause->setCheckable(true);

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

	hbox03->addSpacing(10);
	hbox03->addWidget(argusSlider);
	hbox03->addWidget(frameLabel);
	hbox03->addWidget(qFrameSpiner);
	hbox03->addWidget(labelFrameMax);
	hbox03->addSpacing(10);

	QRadioButton *viewNorm = new QRadioButton("Default");
	QRadioButton *viewBase = new QRadioButton("Unedited");
	QRadioButton *viewReff = new QRadioButton("Reference");
	QRadioButton *viewDiff = new QRadioButton("Difference");
	QRadioButton *viewSubt = new QRadioButton("Thresholded");
	viewNorm->setChecked(true);

	hbox04->addStretch(5);
	hbox04->addWidget(viewNorm);
	hbox04->addWidget(viewBase);
	hbox04->addWidget(viewReff);
	hbox04->addWidget(viewDiff);
	hbox04->addWidget(viewSubt);
	hbox04->addStretch(5);

	connect(backFive, SIGNAL(released()), argusSlider, SLOT(retractFive()));
	connect(backOne, SIGNAL(released()), argusSlider, SLOT(retractOne()));
	connect(forwOne, SIGNAL(released()), argusSlider, SLOT(returnOne()));
	connect(forwFive, SIGNAL(released()), argusSlider, SLOT(returnFive()));
	connect(stopNow, SIGNAL(released()), this, SLOT(videoStop()));
	connect(playPause, SIGNAL(released()), this, SLOT(videoPlayPause()));

	connect(viewNorm, SIGNAL(clicked()), this, SLOT(viewChanged_Norm()));
	connect(this, SIGNAL(sendViewChange_Norm()), argusMind, SLOT(viewChanged_Norm()));
	connect(viewBase, SIGNAL(clicked()), this, SLOT(viewChanged_Base()));
	connect(this, SIGNAL(sendViewChange_Base()), argusMind, SLOT(viewChanged_Base()));
	connect(viewReff, SIGNAL(clicked()), this, SLOT(viewChanged_Reff()));
	connect(this, SIGNAL(sendViewChange_Reff()), argusMind, SLOT(viewChanged_Reff()));
	connect(viewDiff, SIGNAL(clicked()), this, SLOT(viewChanged_Diff()));
	connect(this, SIGNAL(sendViewChange_Diff()), argusMind, SLOT(viewChanged_Diff()));
	connect(viewSubt, SIGNAL(clicked()), this, SLOT(viewChanged_Subt()));
	connect(this, SIGNAL(sendViewChange_Subt()), argusMind, SLOT(viewChanged_Subt()));

	connect(this, SIGNAL(sendFrame(int)), argusMind, SLOT(frameChanged(int)));

	connect(argusMind, SIGNAL(objectWasLost()), this, SLOT(pingOF_objectLost()));

	connect(argusSlider, SIGNAL(valueChanged(int)), this, SLOT(qSliderChanged(int)));
	connect(argusSlider, SIGNAL(sliderReleased()), this, SLOT(qSliderReleased()));
	connect(qFrameSpiner, SIGNAL(valueChanged(int)), this, SLOT(qSpinerChanged(int)));

	vboxF->addLayout(hbox01);
	vboxF->addStretch(1);
	vboxF->addLayout(hbox02);
	vboxF->addStretch(1);
	vboxF->addLayout(hbox03);
	vboxF->addStretch(1);
	vboxF->addLayout(hbox04);
	vboxF->addStretch(5);

	return vboxF;
}

void HeadOfArgus::startVideo()
{
	if (argusMind->isLoaded())
	{
		if (!argusMind->isProcessing())
		{
			std::cout<<"yuppers"<<std::endl;
			emit startVideoNow();
		}
		else
		{
			argusMind->playing = true;
		}
	}
}

void HeadOfArgus::pauseVideo()
{
	if(argusMind->isLoaded() & !argusMind->isPaused())
	{
		argusMind->playing = false;
	}
}

bool HeadOfArgus::isLoaded()
{
	return loaded;
}

//---------------//
//  PUBLIC SLOTS //
//---------------//
void HeadOfArgus::videoSync(QString qstr)
{
	emit sendVideoString(qstr);
}

void HeadOfArgus::guiUpdated(int fr)
{
	argusSlider->setValue(fr);
}

void HeadOfArgus::setRefImage(int fr)
{
	emit assignRefImage(fr);
}

void HeadOfArgus::blurFactorChanged(int vv)
{
	argusMind->blurFactor = vv;
}

void HeadOfArgus::sensitivityChanged(int vv)
{
	argusMind->sensitivity = vv;
}

void HeadOfArgus::startROISelector(int roiIdx, int clrIdx)
{
	roiSelector = true;
	toiSelector = false;
	roiSelected = roiIdx;
	usrNumPoints = 0;

	emit roiSelectStart(roiIdx, clrIdx);
}

void HeadOfArgus::startTOISelector(int toiIdx, int clrIdx)
{
	roiSelector = false;
	toiSelector = true;
	toiSelected = toiIdx;
	usrNumPoints = 0;

	emit toiSelectStart(toiIdx, clrIdx);
}

void HeadOfArgus::saveROISelector(int roiIdx)
{
	emit roiSelectSave(roiIdx);
}

void HeadOfArgus::saveTOISelector(int toiIdx)
{
	emit toiSelectSave(toiIdx);
}

void HeadOfArgus::cancelROISelector(int roiIdx)
{
	emit roiSelectCancel(roiIdx);
}

void HeadOfArgus::cancelTOISelector(int toiIdx)
{
	emit toiSelectCancel(toiIdx);
}

void HeadOfArgus::removeROISaved(int roiIdx)
{
	emit roiSelectRemove(roiIdx);
}

void HeadOfArgus::removeTOISaved(int toiIdx)
{
	emit toiSelectRemove(toiIdx);
}

void HeadOfArgus::roiSetColor(int roiIdx, int clrIdx)
{
	emit roiSelectColor(roiIdx, clrIdx);
}

void HeadOfArgus::receiveOF_BoxDims(double bx, double by, int unitMode)
{
	emit setOF_BoxDims(bx, by, unitMode);
}

void HeadOfArgus::receiveOF_TaskDur(int tdur, int idur)
{
	emit setOF_TaskDur(tdur, idur);
}

void HeadOfArgus::eyeClicked(QMouseEvent *ev)
{
	if (roiSelector)
	{
		if (argusMind->usrNumPoints < argusMind->roiNumPoints)
		{
			argusMind->region[roiSelected][argusMind->usrNumPoints] = cv::Point(ev->x()*argusMind->resizeRatio, ev->y()*argusMind->resizeRatio);
			argusMind->usrNumPoints++;
		}
		if (!argusMind->processing)
			argusMind->sendCurrentView();
	}
	else if (toiSelector)
	{
		if (argusMind->usrNumPoints < argusMind->toiNumPoints)
		{
			argusMind->tracki[toiSelected][argusMind->usrNumPoints] = cv::Point(ev->x()*argusMind->resizeRatio, ev->y()*argusMind->resizeRatio);
			argusMind->usrNumPoints++;
		}
		if (!argusMind->processing)
			argusMind->sendCurrentView();
	}

	std::cout << "Argus Eye Clicked" << std::endl;
}

void HeadOfArgus::eyeMoved(QMouseEvent *ev)
{
	if (roiSelector)
	{
		//std::cout<<"Pointer assigned"<<std::endl;
		if (ev->x() != 0 && ev->y() != 0)
		{
			argusMind->pointer = new cv::Point(ev->x()*argusMind->resizeRatio, ev->y()*argusMind->resizeRatio);
			if (!waitingForUser)
				argusMind->sendCurrentView();
		}
	}
	else if(toiSelector)
	{
		if(ev->x() != 0 && ev->y() != 0)
		{
			argusMind->toiPointer = new cv::Point(ev->x()*argusMind->resizeRatio, ev->y()*argusMind->resizeRatio);
			if (!waitingForUser)
				argusMind->sendCurrentView();
		}
	}
}

void HeadOfArgus::ping_initOpenField()
{
	emit initNow_OF();
}

void HeadOfArgus::ping_startOpenField()
{
	procing = true;
	playing = true;
	emit startNow_OF();

	backFive->setEnabled(false);
	forwFive->setEnabled(false);
	backOne->setEnabled(false);
	forwOne->setEnabled(false);

	playPause->setChecked(true);
}

void HeadOfArgus::ping_resuOpenField()
{
	emit resuNow_OF();
}

//---------------//
// PRIVATE SLOTS //
//---------------//
void HeadOfArgus::videoPlayPause()
{
	if(playPause->isChecked())
	{
		startVideo();
	}
	else
	{
		pauseVideo();
	}
}

void HeadOfArgus::videoStop()
{
	//argusSlider->disableSlider();
	//qFrameSpiner->setMaximum(1);
	//labelFrameMax->setText(" \\ NA frames");

	if (argusMind->processing)
	{
		argusMind->playing = false;
		int resBtn = QMessageBox::question(this, "Finish Analysis",
									"Video currently being processed. Would you like to stop and save your data?\n",
									QMessageBox::Yes,
									QMessageBox::No);

		if(resBtn == QMessageBox::Yes)
		{
			argusMind->processing = false;

			//emit stopVideoNow();
			while(!argusMind->available)
			{
				
				//std::cout<<argusMind->playing<<", "<<argusMind->processing<<", "<<argusMind->available<<std::endl;
				//std::cout<<"waiting for argusMind to finish current loop"<<std::endl;
			}
			emit stopVideoNow();
			while(argusMind->isLoaded())
			{
				//std::cout<<"Argus is loaded"<<std::endl;
			}
			std::cout<<"Stopped while processing"<<std::endl;
			backFive->setEnabled(true);
			forwFive->setEnabled(true);
			backOne->setEnabled(true);
			forwOne->setEnabled(true);

			playPause->setChecked(false);
			argusSlider->disableSlider();
			qFrameSpiner->setMaximum(1);
			labelFrameMax->setText(" \\ NA frames");
			argusEye->showHomeScreen();
			//emit compileData();
		}
		else if(resBtn == QMessageBox::No)
		{
			argusMind->playing = true;
		}
		
	}
	else
	{
		argusMind->playing = false;
		argusMind->processing = false;
		emit stopVideoNow();

		while(!argusMind->available)
		{
			std::cout<<"waiting for argusMind to finish current loop"<<std::endl;
		}
		//while(!workerThread.finished()){
		//	std::cout<<"waiting for mind to finish current loop"<<std::endl;
		//}
		//workerThread.wait();
		std::cout<<"stopping no processing"<<std::endl;
		backFive->setEnabled(true);
		forwFive->setEnabled(true);
		backOne->setEnabled(true);
		forwOne->setEnabled(true);

		playPause->setChecked(false);
	
		argusSlider->disableSlider();
		qFrameSpiner->setMaximum(1);
		labelFrameMax->setText(" \\ NA frames");
		argusEye->showHomeScreen();
	}

	
}

void HeadOfArgus::goNextFrame()
{
	if (currentFrame < totalFrames-1)
	{
		currentFrame++;
		argusSlider->setValue(currentFrame);
		emit nextFrame();
	}
}

void HeadOfArgus::analysisStopped()
{
	backFive->setEnabled(true);
	forwFive->setEnabled(true);
	backOne->setEnabled(true);
	forwOne->setEnabled(true);
}

void HeadOfArgus::viewChanged_Norm()
{
	if (argusMind->playing)
		argusMind->viewMode = _VIEW_NORM;
	else
		emit sendViewChange_Norm();
}

void HeadOfArgus::viewChanged_Base()
{
	if (argusMind->playing)
		argusMind->viewMode = _VIEW_BASE;
	else
		emit sendViewChange_Base();
}

void HeadOfArgus::viewChanged_Reff()
{
	if (argusMind->playing)
		argusMind->viewMode = _VIEW_REFR;
	else
		emit sendViewChange_Reff();
}

void HeadOfArgus::viewChanged_Diff()
{
	if (argusMind->playing)
		argusMind->viewMode = _VIEW_DIFF;
	else
		emit sendViewChange_Diff();
}

void HeadOfArgus::viewChanged_Subt()
{
	if (argusMind->playing)
		argusMind->viewMode = _VIEW_SUBT;
	else
		emit sendViewChange_Subt();
}

void HeadOfArgus::videoSyncCompleted(double fr, int tf, int rw, int rh)
{
	loaded = true;
	totalFrames = tf;
	currentFrame = 1;
	argusSlider->enableSlider(tf);
	qFrameSpiner->setMaximum(tf);
	qFrameSpiner->setValue(1);
	argusSlider->setValue(1);
	emit videoSynced(fr, tf, rw, rh);
	interTimer = (1/fr)*1000;
	std::cout<<"done"<<std::endl;
}

void HeadOfArgus::analysisFinished()
{
	backFive->setEnabled(true);
	forwFive->setEnabled(true);
	backOne->setEnabled(true);
	forwOne->setEnabled(true);

	playPause->setChecked(false);

	playing = false;
	procing = false;
}

void HeadOfArgus::pingOF_objectLost()
{
	emit signalOF_objectLost();
}

void HeadOfArgus::trackerInfo_Send(int fr, int tr)
{
	std::cout<<"tried"<<std::endl;
	emit trackerInfo_Sent(fr, tr);
}

void HeadOfArgus::openField_expSet(int expID, bool flagSet)
{
	emit openField_expChange(expID, flagSet);
}

void HeadOfArgus::qSliderChanged(int vv)
{
	//qFrameSlider->setValue(vv);
	if(!argusSlider->isSliderDown())
	{
		qFrameSpiner->setValue(vv);
		if (argusSlider->value() != vv)
		{
			argusSlider->setValue(vv);
		}
	}
	//std::cout << "Ran slider changed" << std::endl;
}

void HeadOfArgus::qSliderReleased()
{
	int vv = argusSlider->value();
	qFrameSpiner->setValue(vv);
	if (argusSlider->value() != vv)
	{
		argusSlider->setValue(vv);
	}
}

void HeadOfArgus::qSpinerChanged(int vv)
{
	qFrameSpiner->setValue(vv);
	if (argusSlider->value() != vv)
	{
		argusSlider->setValue(vv);
	}
	//std::cout << "Ran spinner changed" << std::endl;
	if (argusMind->isLoaded() & !argusMind->isPlaying() & argusMind->available)
	{
		currentFrame=vv;
		std::cout<<"frame changed in head: "<<vv<<std::endl;
		emit sendFrame(vv);
	}
}