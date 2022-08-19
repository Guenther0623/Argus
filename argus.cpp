#include <QtWidgets>
#include <QLineEdit>
#include <iostream>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QPixmap>

#define _COLOR_BNW		1
#define _COLOR_BGR		2
#define _COLOR_RGB		3

#define _UNIT_CM		10
#define _UNIT_IN		11

#define _REF_START		0
#define _REF_AVERG		1
#define _REF_CUSTM		2

#define _STATE_WAIT		0
#define _STATE_GOOD		1
#define _STATE_STOP		2
#define _STATE_OFF		-1
#define _STATE_ON		-2

#include "argus.h"

using namespace std;
using namespace cv;

Argus::Argus(QWidget *parent)
	: QWidget(parent)
{
	openField_BoxX = -1;
	openField_BoxY = -1;
	openField_BoxU = _UNIT_CM;
	openField_TaskDur = -1;

	QGridLayout *mainGrid = new QGridLayout;

	argusMind = new MindOfArgus();
	argusHead = new HeadOfArgus();

	//QGroupBox *ggTemp = createVideoPlayer();
	mainGrid->addWidget(createTitle(), 0, 0, 1, 4);
	mainGrid->addWidget(createVideoOptions(), 1, 0, 1, 1);
	mainGrid->addWidget(createLogWindow(), 2, 0, 1, 1);
	mainGrid->addWidget(argusHead, 1, 2, 2, 1);
	mainGrid->addWidget(createExperOptions(), 1, 3, 2, 1);

	connect(argusHead, SIGNAL(openField_expChange(int, bool)), this, SLOT(openField_expSet(int, bool)));
	connect(argusHead, SIGNAL(videoSynced(double, int, int, int)), this, SLOT(videoLoaded(double, int, int, int)));
	connect(this, SIGNAL(sendVideoQueue(QString)), argusHead, SLOT(videoSync(QString)));

	connect(argusHead, SIGNAL(stopVideoNow()), this, SLOT(videoStopped()));
	
	connect(this, SIGNAL(OF_StartROI(int, int)), argusHead, SLOT(startROISelector(int, int)));
	connect(this, SIGNAL(OF_StartTOI(int, int)), argusHead, SLOT(startTOISelector(int, int)));
	connect(this, SIGNAL(OF_CancelROI(int)), argusHead, SLOT(cancelROISelector(int)));
	connect(this, SIGNAL(OF_CancelTOI(int)), argusHead, SLOT(cancelTOISelector(int)));
	connect(this, SIGNAL(OF_SaveROI(int)), argusHead, SLOT(saveROISelector(int)));
	connect(this, SIGNAL(OF_SaveTOI(int)), argusHead, SLOT(saveTOISelector(int)));
	connect(this, SIGNAL(OF_RemoveROI(int)), argusHead, SLOT(removeROISaved(int)));
	connect(this, SIGNAL(OF_RemoveTOI(int)), argusHead, SLOT(removeTOISaved(int)));
	connect(this, SIGNAL(OF_roiSetColor(int, int)), argusHead, SLOT(roiSetColor(int, int)));
	connect(this, SIGNAL(OF_setReference(int)), argusHead, SLOT(setRefImage(int)));

	connect(argusHead, SIGNAL(ping_requestTOIReassignment(int)), this, SLOT(userReassignTOI(int)));
	connect(this, SIGNAL(initNow_OF()), argusHead, SLOT(ping_initOpenField()));
	connect(this, SIGNAL(startNow_OF()), argusHead, SLOT(ping_startOpenField()));
	connect(this, SIGNAL(resuNow_OF()), argusHead, SLOT(ping_resuOpenField()));
	connect(this, SIGNAL(assignOF_BoxDims(double, double, int)), argusHead, SLOT(receiveOF_BoxDims(double, double, int)));
	connect(this, SIGNAL(assignOF_TaskDur(int, int)), argusHead, SLOT(receiveOF_TaskDur(int, int)));

	connect(argusHead, SIGNAL(trackerInfo_Sent(int, int)), this, SLOT(OF_TrackerFrameAssigned(int, int)));

	connect(argusHead, SIGNAL(signalOF_objectLost()), this, SLOT(pingOF_objectLost()));

	openField_ratNum = 1;

	setLayout(mainGrid);
}

Argus::~Argus()
{
	//delete argusEye;

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

	QHBoxLayout *hboxOF_01 = new QHBoxLayout();
	QHBoxLayout *hboxOF_11 = new QHBoxLayout();
	QHBoxLayout *hboxOF_02 = new QHBoxLayout();
	QHBoxLayout *hboxOF_12 = new QHBoxLayout();
	QHBoxLayout *hboxOF_03 = new QHBoxLayout();
	QHBoxLayout *hboxOF_13 = new QHBoxLayout();
	QHBoxLayout *hboxOF_04 = new QHBoxLayout();
	QHBoxLayout *hboxOF_14 = new QHBoxLayout();

	QVBoxLayout *vbox = new QVBoxLayout();

	QLabel *ratNumLab = new QLabel("Number of Experiments in Video:");
	QSpinBox *spinRatNum = new QSpinBox;
	spinRatNum->setRange(1, 4);
	spinRatNum->setSingleStep(1);
	spinRatNum->setValue(1);
	spinRatNum->setFixedSize(45, 25);

	QLabel *durLabel = new QLabel("Length of Analysis:");
	QLineEdit *durLine = new QLineEdit();
	durLine->setValidator(new QIntValidator(0, 200, this));
	QLabel *durMLabel = new QLabel("minutes (m)");
	QLabel *ignLabel = new QLabel("Length of Habituation:");
	QLineEdit *ignLine = new QLineEdit();
	ignLine->setValidator(new QIntValidator(0, 200, this));
	QLabel *ignMLabel = new QLabel("minutes (m)");

	QHBoxLayout *hboxDur = new QHBoxLayout();
	hboxDur->addSpacing(5);
	hboxDur->addWidget(durLabel);
	hboxDur->addSpacing(5);
	hboxDur->addWidget(durLine);
	hboxDur->addSpacing(2);
	hboxDur->addWidget(durMLabel);
	hboxDur->addStretch(1);
	QHBoxLayout *hboxIgn = new QHBoxLayout();
	hboxIgn->addSpacing(5);
	hboxIgn->addWidget(ignLabel);
	hboxIgn->addSpacing(5);
	hboxIgn->addWidget(ignLine);
	hboxIgn->addSpacing(2);
	hboxIgn->addWidget(ignMLabel);
	hboxIgn->addStretch(1);

	connect(durLine, SIGNAL(textChanged(QString)), this, SLOT(OF_taskDurChanged(QString)));
	connect(ignLine, SIGNAL(textChanged(QString)), this, SLOT(OF_ignoreDurChanged(QString)));

	QString stateMachineGOOD = QString("SL_Icon_Green.png");
	QString stateMachineSTOP = QString("SL_Icon_Red.png");
	QString stateMachineWAIT = QString("SL_Icon_Blue.png");
	QString stateMachineIOFF = QString("SL_Icon_AllOff.png");
	QString stateMachineIONN = QString("SL_Icon_AllOn.png");
	stateMachine_OF01 = new QStateWatcher(stateMachineGOOD, stateMachineWAIT, stateMachineSTOP, stateMachineIOFF, stateMachineIONN, 20, 50);
	stateMachine_OF02 = new QStateWatcher(stateMachineGOOD, stateMachineWAIT, stateMachineSTOP, stateMachineIOFF, stateMachineIONN, 20, 50);
	stateMachine_OF03 = new QStateWatcher(stateMachineGOOD, stateMachineWAIT, stateMachineSTOP, stateMachineIOFF, stateMachineIONN, 20, 50);
	stateMachine_OF04 = new QStateWatcher(stateMachineGOOD, stateMachineWAIT, stateMachineSTOP, stateMachineIOFF, stateMachineIONN, 20, 50);
	stateMachine_OF01->changeState(_STATE_WAIT);

	fieldLabel01 = new QLabel("ROI 01:");
	fieldLabel11 = new QLabel("Tracker:");
	fieldLabel21 = new QLabel("Start:");
	fieldLabel31 = new QLabel("End:");
	fieldLabel02 = new QLabel("ROI 02:");
	fieldLabel12 = new QLabel("Tracker:");
	fieldLabel22 = new QLabel("Start:");
	fieldLabel32 = new QLabel("End:");
	fieldLabel03 = new QLabel("ROI 03:");
	fieldLabel13 = new QLabel("Tracker:");
	fieldLabel23 = new QLabel("Start:");
	fieldLabel33 = new QLabel("End:");
	fieldLabel04 = new QLabel("ROI 04:");
	fieldLabel14 = new QLabel("Tracker:");
	fieldLabel24 = new QLabel("Start:");
	fieldLabel34 = new QLabel("End:");

	colorSel01 = new QComboBox();
	colorSel02 = new QComboBox();
	colorSel03 = new QComboBox();
	colorSel04 = new QComboBox();

	colorSel01->addItem(QIcon("icon_green_small.png"), "Green");
	colorSel01->addItem(QIcon("icon_blue_small.png"), "Blue");
	colorSel01->addItem(QIcon("icon_red_small.png"), "Red");
	colorSel01->addItem(QIcon("icon_yellow_small.png"), "Yellow");
	colorSel02->addItem(QIcon("icon_green_small.png"), "Green");
	colorSel02->addItem(QIcon("icon_blue_small.png"), "Blue");
	colorSel02->addItem(QIcon("icon_red_small.png"), "Red");
	colorSel02->addItem(QIcon("icon_yellow_small.png"), "Yellow");
	colorSel03->addItem(QIcon("icon_green_small.png"), "Green");
	colorSel03->addItem(QIcon("icon_blue_small.png"), "Blue");
	colorSel03->addItem(QIcon("icon_red_small.png"), "Red");
	colorSel03->addItem(QIcon("icon_yellow_small.png"), "Yellow");
	colorSel04->addItem(QIcon("icon_green_small.png"), "Green");
	colorSel04->addItem(QIcon("icon_blue_small.png"), "Blue");
	colorSel04->addItem(QIcon("icon_red_small.png"), "Red");
	colorSel04->addItem(QIcon("icon_yellow_small.png"), "Yellow");
	colorSel01->setCurrentIndex(0);
	colorSel02->setCurrentIndex(1);
	colorSel03->setCurrentIndex(2);
	colorSel04->setCurrentIndex(3);

	selectROI01 = new QArgusButton("Select", 0);
	selectROI01->setCheckable(true);
	assignROI01 = new QArgusButton("Assign", 0);
	deleteROI01 = new QArgusButton("Remove", 0);
	selectROI02 = new QArgusButton("Select", 1);
	selectROI02->setCheckable(true);
	assignROI02 = new QArgusButton("Assign", 1);
	deleteROI02 = new QArgusButton("Remove", 1);
	selectROI03 = new QArgusButton("Select", 2);
	selectROI03->setCheckable(true);
	assignROI03 = new QArgusButton("Assign", 2);
	deleteROI03 = new QArgusButton("Remove", 2);
	selectROI04 = new QArgusButton("Select", 3);
	selectROI04->setCheckable(true);
	assignROI04 = new QArgusButton("Assign", 3);
	deleteROI04 = new QArgusButton("Remove", 3);

	selectROI11 = new QArgusButton("Select", 0);
	selectROI11->setCheckable(true);
	assignROI11 = new QArgusButton("Assign", 0);
	deleteROI11 = new QArgusButton("Remove", 0);
	selectROI12 = new QArgusButton("Select", 1);
	selectROI12->setCheckable(true);
	assignROI12 = new QArgusButton("Assign", 1);
	deleteROI12 = new QArgusButton("Remove", 1);
	selectROI13 = new QArgusButton("Select", 2);
	selectROI13->setCheckable(true);
	assignROI13 = new QArgusButton("Assign", 2);
	deleteROI13 = new QArgusButton("Remove", 2);
	selectROI14 = new QArgusButton("Select", 3);
	selectROI14->setCheckable(true);
	assignROI14 = new QArgusButton("Assign", 3);
	deleteROI14 = new QArgusButton("Remove", 3);

	frameStROI01 = new QLineEdit();
	frameStROI01->setPlaceholderText("-1");
	frameStROI01->setReadOnly(true);
	frameEdROI01 = new QLineEdit();
	frameEdROI01->setReadOnly(true);
	frameStROI02 = new QLineEdit();
	frameStROI02->setPlaceholderText("-1");
	frameStROI02->setReadOnly(true);
	frameStROI02->setEnabled(false);
	frameEdROI02 = new QLineEdit();
	frameEdROI02->setReadOnly(true);
	frameEdROI02->setEnabled(false);
	frameStROI03 = new QLineEdit();
	frameStROI03->setPlaceholderText("-1");
	frameStROI03->setReadOnly(true);
	frameStROI03->setEnabled(false);
	frameEdROI03 = new QLineEdit();
	frameEdROI03->setReadOnly(true);
	frameEdROI03->setEnabled(false);
	frameStROI04 = new QLineEdit();
	frameStROI04->setPlaceholderText("-1");
	frameStROI04->setReadOnly(true);
	frameStROI04->setEnabled(false);
	frameEdROI04 = new QLineEdit();
	frameEdROI04->setReadOnly(true);
	frameEdROI04->setEnabled(false);

	colorSel02->setEnabled(false);
	fieldLabel02->setEnabled(false);
	fieldLabel12->setEnabled(false);
	fieldLabel22->setEnabled(false);
	fieldLabel32->setEnabled(false);
	selectROI02->setEnabled(false);
	assignROI02->setEnabled(false);
	deleteROI02->setEnabled(false);
	selectROI12->setEnabled(false);
	assignROI12->setEnabled(false);
	deleteROI12->setEnabled(false);
	colorSel03->setEnabled(false);
	fieldLabel03->setEnabled(false);
	fieldLabel13->setEnabled(false);
	fieldLabel23->setEnabled(false);
	fieldLabel33->setEnabled(false);
	selectROI03->setEnabled(false);
	assignROI03->setEnabled(false);
	deleteROI03->setEnabled(false);
	selectROI13->setEnabled(false);
	assignROI13->setEnabled(false);
	deleteROI13->setEnabled(false);
	colorSel04->setEnabled(false);
	fieldLabel04->setEnabled(false);
	fieldLabel14->setEnabled(false);
	fieldLabel24->setEnabled(false);
	fieldLabel34->setEnabled(false);
	selectROI04->setEnabled(false);
	assignROI04->setEnabled(false);
	deleteROI04->setEnabled(false);
	selectROI14->setEnabled(false);
	assignROI14->setEnabled(false);
	deleteROI14->setEnabled(false);

	QVBoxLayout *vertBoxAll = new QVBoxLayout();
	QHBoxLayout *horiBox01 = new QHBoxLayout();
	QHBoxLayout *horiBox02 = new QHBoxLayout();
	QHBoxLayout *horiBox03 = new QHBoxLayout();

	QLabel *labelBoxT = new QLabel("Box Size Settings:");
	QLabel *labelBoxX = new QLabel("X-Dimension");
	QLabel *labelBoxY = new QLabel("Y-Dimension");
	QLabel *labelBoxUnit = new QLabel("Dimension Units:");
	QRadioButton *boxUnitCM = new QRadioButton("Centimeters (cm)");
	QRadioButton *boxUnitIN = new QRadioButton("Inches (in)");
	QButtonGroup *dimRadioGroup = new QButtonGroup;
	dimRadioGroup->addButton(boxUnitCM);
	dimRadioGroup->addButton(boxUnitIN);
	lineOFXDim = new QLineEdit();
	lineOFXDim->setValidator(new QDoubleValidator(0, 1000, 2));
	lineOFYDim = new QLineEdit();
	lineOFYDim->setValidator(new QDoubleValidator(0, 1000, 2));

	initOF = new QPushButton("Initialize");
	startOF = new QPushButton("Start");
	startOF->setEnabled(false);
	resuOF = new QPushButton("Resume");
	resuOF->setEnabled(false);

	horiBox01->addWidget(labelBoxT);
	horiBox02->addSpacing(25);
	horiBox02->addWidget(labelBoxX);
	horiBox02->addWidget(lineOFXDim);
	horiBox02->addSpacing(10);
	horiBox02->addWidget(labelBoxY);
	horiBox02->addWidget(lineOFYDim);
	horiBox03->addSpacing(25);
	horiBox03->addWidget(labelBoxUnit);
	horiBox03->addWidget(boxUnitCM);
	horiBox03->addWidget(boxUnitIN);

	vertBoxAll->addLayout(horiBox01);
	vertBoxAll->addSpacing(5);
	vertBoxAll->addLayout(horiBox02);
	vertBoxAll->addSpacing(10);
	vertBoxAll->addLayout(horiBox03);
	boxUnitCM->setChecked(true);


	QHBoxLayout *hboxOF_ctrl = new QHBoxLayout();
	hboxOF_ctrl->addWidget(initOF);
	hboxOF_ctrl->addWidget(startOF);
	hboxOF_ctrl->addWidget(resuOF);

	//hboxOF_01->addWidget(stateMachine_OF01);
	//stateMachine_OF01->setFixedSize(50, 125);
	//stateMachine_OF01->changeState(2);
	hboxOF_01->addSpacing(15);
	hboxOF_01->addWidget(fieldLabel01);
	hboxOF_01->addSpacing(10);
	hboxOF_01->addWidget(selectROI01);
	hboxOF_01->addSpacing(5);
	hboxOF_01->addWidget(assignROI01);
	hboxOF_01->addSpacing(5);
	hboxOF_01->addWidget(deleteROI01);
	hboxOF_01->addSpacing(10);
	hboxOF_01->addWidget(colorSel01);
	hboxOF_01->addSpacing(10);

	hboxOF_11->addSpacing(25);
	hboxOF_11->addWidget(fieldLabel11);
	hboxOF_11->addSpacing(10);
	hboxOF_11->addWidget(selectROI11);
	hboxOF_11->addSpacing(5);
	hboxOF_11->addWidget(assignROI11);
	hboxOF_11->addSpacing(5);
	hboxOF_11->addWidget(deleteROI11);
	hboxOF_11->addSpacing(10);
	hboxOF_11->addWidget(fieldLabel21);
	hboxOF_11->addSpacing(5);
	hboxOF_11->addWidget(frameStROI01);
	hboxOF_11->addSpacing(5);
	hboxOF_11->addWidget(fieldLabel31);
	hboxOF_11->addSpacing(5);
	hboxOF_11->addWidget(frameEdROI01);
	hboxOF_11->addSpacing(10);

	QHBoxLayout *hbox1 = new QHBoxLayout();
	QVBoxLayout *vbox1 = new QVBoxLayout();
	vbox1->addLayout(hboxOF_01);
	vbox1->addLayout(hboxOF_11);
	hbox1->addSpacing(5);
	hbox1->addWidget(stateMachine_OF01);
	hbox1->addSpacing(5);
	hbox1->addLayout(vbox1);

	hboxOF_02->addSpacing(15);
	hboxOF_02->addWidget(fieldLabel02);
	hboxOF_02->addSpacing(10);
	hboxOF_02->addWidget(selectROI02);
	hboxOF_02->addSpacing(5);
	hboxOF_02->addWidget(assignROI02);
	hboxOF_02->addSpacing(5);
	hboxOF_02->addWidget(deleteROI02);
	hboxOF_02->addSpacing(10);
	hboxOF_02->addWidget(colorSel02);
	hboxOF_02->addSpacing(10);

	hboxOF_12->addSpacing(25);
	hboxOF_12->addWidget(fieldLabel12);
	hboxOF_12->addSpacing(10);
	hboxOF_12->addWidget(selectROI12);
	hboxOF_12->addSpacing(5);
	hboxOF_12->addWidget(assignROI12);
	hboxOF_12->addSpacing(5);
	hboxOF_12->addWidget(deleteROI12);
	hboxOF_12->addSpacing(10);
	hboxOF_12->addWidget(fieldLabel22);
	hboxOF_12->addSpacing(5);
	hboxOF_12->addWidget(frameStROI02);
	hboxOF_12->addSpacing(5);
	hboxOF_12->addWidget(fieldLabel32);
	hboxOF_12->addSpacing(5);
	hboxOF_12->addWidget(frameEdROI02);
	hboxOF_12->addSpacing(10);

	QHBoxLayout *hbox2 = new QHBoxLayout();
	QVBoxLayout *vbox2 = new QVBoxLayout();
	vbox2->addLayout(hboxOF_02);
	vbox2->addLayout(hboxOF_12);
	hbox2->addSpacing(5);
	hbox2->addWidget(stateMachine_OF02);
	hbox2->addSpacing(5);
	hbox2->addLayout(vbox2);

	//vboxOF_2->addLayout(hboxOF_02);
	//vboxOF_2->addLayout(hboxOF_12);

	hboxOF_03->addSpacing(15);
	hboxOF_03->addWidget(fieldLabel03);
	hboxOF_03->addSpacing(10);
	hboxOF_03->addWidget(selectROI03);
	hboxOF_03->addSpacing(5);
	hboxOF_03->addWidget(assignROI03);
	hboxOF_03->addSpacing(5);
	hboxOF_03->addWidget(deleteROI03);
	hboxOF_03->addSpacing(10);
	hboxOF_03->addWidget(colorSel03);
	hboxOF_03->addSpacing(10);

	hboxOF_13->addSpacing(25);
	hboxOF_13->addWidget(fieldLabel13);
	hboxOF_13->addSpacing(10);
	hboxOF_13->addWidget(selectROI13);
	hboxOF_13->addSpacing(5);
	hboxOF_13->addWidget(assignROI13);
	hboxOF_13->addSpacing(5);
	hboxOF_13->addWidget(deleteROI13);
	hboxOF_13->addSpacing(10);
	hboxOF_13->addWidget(fieldLabel23);
	hboxOF_13->addSpacing(5);
	hboxOF_13->addWidget(frameStROI03);
	hboxOF_13->addSpacing(5);
	hboxOF_13->addWidget(fieldLabel33);
	hboxOF_13->addSpacing(5);
	hboxOF_13->addWidget(frameEdROI03);
	hboxOF_13->addSpacing(10);

	QHBoxLayout *hbox3 = new QHBoxLayout();
	QVBoxLayout *vbox3 = new QVBoxLayout();
	vbox3->addLayout(hboxOF_03);
	vbox3->addLayout(hboxOF_13);
	hbox3->addSpacing(5);
	hbox3->addWidget(stateMachine_OF03);
	hbox3->addSpacing(5);
	hbox3->addLayout(vbox3);

	//vboxOF_3->addLayout(hboxOF_03);
	//vboxOF_3->addLayout(hboxOF_13);

	hboxOF_04->addSpacing(15);
	hboxOF_04->addWidget(fieldLabel04);
	hboxOF_04->addSpacing(10);
	hboxOF_04->addWidget(selectROI04);
	hboxOF_04->addSpacing(5);
	hboxOF_04->addWidget(assignROI04);
	hboxOF_04->addSpacing(5);
	hboxOF_04->addWidget(deleteROI04);
	hboxOF_04->addSpacing(10);
	hboxOF_04->addWidget(colorSel04);
	hboxOF_04->addSpacing(10);

	hboxOF_14->addSpacing(25);
	hboxOF_14->addWidget(fieldLabel14);
	hboxOF_14->addSpacing(10);
	hboxOF_14->addWidget(selectROI14);
	hboxOF_14->addSpacing(5);
	hboxOF_14->addWidget(assignROI14);
	hboxOF_14->addSpacing(5);
	hboxOF_14->addWidget(deleteROI14);
	hboxOF_14->addSpacing(10);
	hboxOF_14->addWidget(fieldLabel24);
	hboxOF_14->addSpacing(5);
	hboxOF_14->addWidget(frameStROI04);
	hboxOF_14->addSpacing(5);
	hboxOF_14->addWidget(fieldLabel34);
	hboxOF_14->addSpacing(5);
	hboxOF_14->addWidget(frameEdROI04);
	hboxOF_14->addSpacing(10);

	QHBoxLayout *hbox4 = new QHBoxLayout();
	QVBoxLayout *vbox4 = new QVBoxLayout();
	vbox4->addLayout(hboxOF_04);
	vbox4->addLayout(hboxOF_14);
	hbox4->addSpacing(5);
	hbox4->addWidget(stateMachine_OF04);
	hbox4->addSpacing(5);
	hbox4->addLayout(vbox4);

	//vboxOF_4->addLayout(hboxOF_04);
	//vboxOF_4->addLayout(hboxOF_14);

	hbox01->addSpacing(5);
	hbox01->addWidget(ratNumLab);
	hbox01->addSpacing(5);
	hbox01->addWidget(spinRatNum);
	hbox01->addStretch(1);

	QLabel *qReff_Label = new QLabel("Reference Frame Options:");
	QRadioButton *qReff_Str = new QRadioButton("First");
	QRadioButton *qReff_Ave = new QRadioButton("Average");
	QRadioButton *qReff_Cus = new QRadioButton("Custom");
	QButtonGroup *refRadioGroup = new QButtonGroup();
	refRadioGroup->addButton(qReff_Str);
	refRadioGroup->addButton(qReff_Ave);
	refRadioGroup->addButton(qReff_Cus);
	QPushButton *assignRef = new QPushButton("Set Reference");
	QLabel *qReff_Frame = new QLabel("Frame:");
	qReff_Str->setChecked(true);
	qReff_Line = new QLineEdit();
	qReff_Line->setReadOnly(true);
	qReff_Line->setText("1");

	QHBoxLayout *hbox_Ref = new QHBoxLayout();
	QVBoxLayout *vbox_Ref = new QVBoxLayout();
	QHBoxLayout *hvbox_ref01 = new QHBoxLayout();
	QHBoxLayout *hvbox_ref02 = new QHBoxLayout();

	hvbox_ref01->addWidget(qReff_Str);
	hvbox_ref01->addWidget(qReff_Ave);
	hvbox_ref01->addWidget(qReff_Cus);
	hvbox_ref02->addSpacing(15);
	hvbox_ref02->addWidget(assignRef);
	hvbox_ref02->addSpacing(10);
	hvbox_ref02->addWidget(qReff_Frame);
	hvbox_ref02->addWidget(qReff_Line);
	hvbox_ref02->addSpacing(15);
	vbox_Ref->addLayout(hvbox_ref01);
	vbox_Ref->addLayout(hvbox_ref02);
	hbox_Ref->addWidget(qReff_Label);
	hbox_Ref->addLayout(vbox_Ref);

	QSlider *blurSlider = new QSlider(Qt::Horizontal);
	blurSlider->setMinimum(1);
	blurSlider->setMaximum(9);
	blurSlider->setSingleStep(2);
	blurSlider->setValue(argusMind->getCurrentBlurFactor());
	blurLine = new QLineEdit(QString::number(argusMind->getCurrentBlurFactor()));
	blurLine->setReadOnly(true);
	QLabel *blurLabel = new QLabel("Blurring Size:");
	QSlider *sensSlider = new QSlider(Qt::Horizontal);
	sensSlider->setMinimum(1);
	sensSlider->setMaximum(50);
	sensSlider->setValue(argusMind->getCurrentSensitivity());
	sensLine = new QLineEdit(QString::number(argusMind->getCurrentSensitivity()));
	sensLine->setReadOnly(true);
	QLabel *sensLabel = new QLabel("Threshold Limit:");
	QGridLayout *sliderGrid = new QGridLayout();

	sliderGrid->addWidget(blurLabel, 0, 0, 1, 1);
	sliderGrid->addWidget(blurLine, 0, 1, 1, 1);
	sliderGrid->addWidget(blurSlider, 0, 2, 1, 1);
	sliderGrid->addWidget(sensLabel, 1, 0, 1, 1);
	sliderGrid->addWidget(sensLine, 1, 1, 1, 1);
	sliderGrid->addWidget(sensSlider, 1, 2, 1, 1);

	sliderGrid->setColumnStretch(0, 1);
	sliderGrid->setColumnStretch(1, 1);
	sliderGrid->setColumnStretch(2, 4);

	connect(blurSlider, SIGNAL(valueChanged(int)), this, SLOT(blurSliderChanged(int)));
	connect(this, SIGNAL(OF_blurChanged(int)), argusHead, SLOT(blurFactorChanged(int)));
	connect(sensSlider, SIGNAL(valueChanged(int)), this, SLOT(sensSliderChanged(int)));
	connect(this, SIGNAL(OF_sensChanged(int)), argusHead, SLOT(sensitivityChanged(int)));

	vbox->addSpacing(30);
	vbox->addLayout(hbox01);
	vbox->addLayout(hboxDur);
	vbox->addLayout(hboxIgn);
	vbox->addSpacing(15);
	vbox->addLayout(hbox1);
	vbox->addSpacing(15);
	vbox->addLayout(hbox2);
	vbox->addSpacing(15);
	vbox->addLayout(hbox3);
	vbox->addSpacing(15);
	vbox->addLayout(hbox4);
	vbox->addSpacing(25);
	vbox->addLayout(vertBoxAll);
	vbox->addSpacing(15);
	vbox->addLayout(hbox_Ref);
	vbox->addSpacing(25);
	vbox->addLayout(sliderGrid);
	vbox->addSpacing(25); 
	vbox->addLayout(hboxOF_ctrl);
	vbox->addStretch(100);

	connect(qReff_Str, SIGNAL(clicked()), this, SLOT(qReff_StarterClicked()));
	connect(qReff_Ave, SIGNAL(clicked()), this, SLOT(qReff_AverageClicked()));
	connect(qReff_Cus, SIGNAL(clicked()), this, SLOT(qReff_CustomFClicked()));
	connect(assignRef, SIGNAL(released()), this, SLOT(qReff_AssignReference()));

	groupBox->setLayout(vbox);

	connect(spinRatNum, SIGNAL(valueChanged(int)), this, SLOT(change_ratNumOpenField(int)));
	//connect(assignROI01, SIGNAL(clicked()), this, SLOT(OF_SaveROI01()));
	connect(assignROI01, SIGNAL(valReleased(int)), this, SLOT(OF_saveROI(int)));
	connect(assignROI02, SIGNAL(valReleased(int)), this, SLOT(OF_saveROI(int)));
	connect(assignROI03, SIGNAL(valReleased(int)), this, SLOT(OF_saveROI(int)));
	connect(assignROI04, SIGNAL(valReleased(int)), this, SLOT(OF_saveROI(int)));
	connect(selectROI01, SIGNAL(valReleased(int)), this, SLOT(OF_selectROI(int)));
	connect(selectROI02, SIGNAL(valReleased(int)), this, SLOT(OF_selectROI(int)));
	connect(selectROI03, SIGNAL(valReleased(int)), this, SLOT(OF_selectROI(int)));
	connect(selectROI04, SIGNAL(valReleased(int)), this, SLOT(OF_selectROI(int)));
	connect(deleteROI01, SIGNAL(valReleased(int)), this, SLOT(OF_removeROI(int)));
	connect(deleteROI02, SIGNAL(valReleased(int)), this, SLOT(OF_removeROI(int)));
	connect(deleteROI03, SIGNAL(valReleased(int)), this, SLOT(OF_removeROI(int)));
	connect(deleteROI04, SIGNAL(valReleased(int)), this, SLOT(OF_removeROI(int)));

	connect(assignROI11, SIGNAL(valReleased(int)), this, SLOT(OF_saveTOI(int)));
	connect(assignROI12, SIGNAL(valReleased(int)), this, SLOT(OF_saveTOI(int)));
	connect(assignROI13, SIGNAL(valReleased(int)), this, SLOT(OF_saveTOI(int)));
	connect(assignROI14, SIGNAL(valReleased(int)), this, SLOT(OF_saveTOI(int)));
	connect(selectROI11, SIGNAL(valReleased(int)), this, SLOT(OF_selectTOI(int)));
	connect(selectROI12, SIGNAL(valReleased(int)), this, SLOT(OF_selectTOI(int)));
	connect(selectROI13, SIGNAL(valReleased(int)), this, SLOT(OF_selectTOI(int)));
	connect(selectROI14, SIGNAL(valReleased(int)), this, SLOT(OF_selectTOI(int)));
	connect(deleteROI11, SIGNAL(valReleased(int)), this, SLOT(OF_removeTOI(int)));
	connect(deleteROI12, SIGNAL(valReleased(int)), this, SLOT(OF_removeTOI(int)));
	connect(deleteROI13, SIGNAL(valReleased(int)), this, SLOT(OF_removeTOI(int)));
	connect(deleteROI14, SIGNAL(valReleased(int)), this, SLOT(OF_removeTOI(int)));

	connect(lineOFXDim, SIGNAL(textChanged(QString)), this, SLOT(OF_XChanged(QString)));
	connect(lineOFYDim, SIGNAL(textChanged(QString)), this, SLOT(OF_YChanged(QString)));

	connect(boxUnitCM, SIGNAL(clicked()), this, SLOT(boxUnitChanged_CM()));
	connect(boxUnitIN, SIGNAL(clicked()), this, SLOT(boxUnitChanged_IN()));

	connect(initOF, SIGNAL(clicked()), this, SLOT(OF_InitAnalysis()));
	connect(startOF, SIGNAL(clicked()), this, SLOT(OF_BeginAnalysis()));
	connect(resuOF, SIGNAL(clicked()), this, SLOT(OF_ResuAnalysis()));

	connect(colorSel01, SIGNAL(currentIndexChanged(int)), this, SLOT(OF_ColorChanged01(int)));

	return groupBox;
}

void Argus::OF_saveROI(int v)
{
	emit OF_SaveROI(v);

	switch (v)
	{
		case 0:
			if (selectROI01->isChecked())
				selectROI01->setChecked(false);
			break;
		case 1:
			if (selectROI02->isChecked())
				selectROI02->setChecked(false);
			break;
		case 2:
			if (selectROI03->isChecked())
				selectROI03->setChecked(false);
			break;
		case 3:
			if (selectROI04->isChecked())
				selectROI04->setChecked(false);
			break;
	}
}

void Argus::OF_saveTOI(int v)
{
	emit OF_SaveTOI(v);

	switch (v)
	{
		case 0:
			if (selectROI11->isChecked())
				selectROI11->setChecked(false);
			break;
		case 1:
			if (selectROI12->isChecked())
				selectROI12->setChecked(false);
			break;
		case 2:
			if (selectROI13->isChecked())
				selectROI13->setChecked(false);
			break;
		case 3:
			if (selectROI14->isChecked())
				selectROI14->setChecked(false);
			break;
	}
}

void Argus::OF_selectROI(int v)
{
	//Assuming that selectROI check states are working properly
	if (!argusHead->isLoaded())
		return;

	switch(v)
	{
		case 0:
			if (selectROI01->isChecked())
				emit OF_StartROI(v, colorSel01->currentIndex());
			else
				emit OF_CancelROI(v);
			break;

		case 1:
			if (selectROI02->isChecked())
				emit OF_StartROI(v, colorSel02->currentIndex());
			else
				emit OF_CancelROI(v);
			break;

		case 2:
			if (selectROI03->isChecked())
				emit OF_StartROI(v, colorSel03->currentIndex());
			else
				emit OF_CancelROI(v);
			break;

		case 3:
			if (selectROI04->isChecked())
				emit OF_StartROI(v, colorSel04->currentIndex());
			else
				emit OF_CancelROI(v);
			break;
	}
}

void Argus::OF_selectTOI(int v)
{
	if(!argusHead->isLoaded())
		return;

	switch(v)
	{
		case 0:
			if (selectROI11->isChecked())
				emit OF_StartTOI(v, colorSel01->currentIndex());
			else
				emit OF_CancelTOI(v);
			break;

		case 1:
			if (selectROI12->isChecked())
				emit OF_StartTOI(v, colorSel02->currentIndex());
			else
				emit OF_CancelTOI(v);
			break;

		case 2:
			if (selectROI13->isChecked())
				emit OF_StartTOI(v, colorSel03->currentIndex());
			else
				emit OF_CancelTOI(v);
			break;

		case 3:
			if (selectROI14->isChecked())
				emit OF_StartTOI(v, colorSel04->currentIndex());
			else
				emit OF_CancelTOI(v);
			break;
	}
}

void Argus::OF_removeROI(int v)
{
	emit OF_RemoveROI(v);
}

void Argus::OF_removeTOI(int v)
{
	emit OF_RemoveTOI(v);
}

void Argus::OF_XChanged(QString txt)
{
	txt.remove(QChar(','));
	openField_BoxX = txt.toDouble();
	std::cout<<openField_BoxX<<std::endl;
}

void Argus::OF_YChanged(QString txt)
{
	txt.remove(QChar(','));
	openField_BoxY = txt.toDouble();
}

void Argus::OF_taskDurChanged(QString txt)
{
	openField_TaskDur = txt.toInt();
	//std::cout << openField_TaskDur << std::endl;
}

void Argus::OF_ignoreDurChanged(QString txt)
{
	openField_IgnoreDur = txt.toInt();
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

void Argus::boxUnitChanged_CM()
{
	openField_BoxU = _UNIT_CM;
}

void Argus::boxUnitChanged_IN()
{
	openField_BoxU = _UNIT_IN;
}

void Argus::qReff_StarterClicked()
{
	openField_referenceMode = _REF_START;
}

void Argus::qReff_AverageClicked()
{
	openField_referenceMode = _REF_AVERG;
}

void Argus::qReff_CustomFClicked()
{
	openField_referenceMode = _REF_CUSTM;
}

void Argus::qReff_AssignReference()
{
	switch(openField_referenceMode)
	{
		case _REF_START:
			emit OF_setReference(1);
			break;
		case _REF_AVERG:
			qReff_Line->setText(QString("Average"));
			emit OF_setReference(-1);
			break;
		case _REF_CUSTM:
			openField_referenceNumb = argusHead->getCurrentFrame();
			qReff_Line->setText(QString::number(openField_referenceNumb));
			emit OF_setReference(openField_referenceNumb);
			break;
	}
}

void Argus::blurSliderChanged(int val)
{
	if (val > 1 && val%2 == 0)
		val = val - 1;
	blurLine->setText(QString::number(val));
	emit OF_blurChanged(val);
}

void Argus::sensSliderChanged(int val)
{
	sensLine->setText(QString::number(val));
	emit OF_sensChanged(val);
}

void Argus::locateVideo()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open Video File"), "", tr("Video Files (*.mkv *.mp4)"));
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

void Argus::videoStopped()
{
	vidIfoName->setText("INVALID");
	vidIfoReso->setText("N/A");
	vidIfoFrme->setText("N/A");
	vidIfoTime->setText("N/A");
	fileLine->clear();

	if (selectROI01->isChecked())
	{
		selectROI01->setChecked(false);
		emit OF_CancelROI(1);
	}
}

void Argus::change_ratNumOpenField(int rn)
{
	openField_ratNum = rn;
	switch(openField_ratNum)
	{	
		case 1:
			if (colorSel02->isEnabled())
			{
				stateMachine_OF02->changeState(_STATE_OFF);
				colorSel02->setEnabled(false);
				selectROI02->setEnabled(false);
				assignROI02->setEnabled(false);
				deleteROI02->setEnabled(false);
				selectROI12->setEnabled(false);
				assignROI12->setEnabled(false);
				deleteROI12->setEnabled(false);
				fieldLabel02->setEnabled(false);
				fieldLabel12->setEnabled(false);
				fieldLabel22->setEnabled(false);
				frameStROI02->setEnabled(false);
				fieldLabel32->setEnabled(false);
				frameEdROI02->setEnabled(false);
			}
			if (colorSel03->isEnabled())
			{
				stateMachine_OF03->changeState(_STATE_OFF);
				colorSel03->setEnabled(false);
				selectROI03->setEnabled(false);
				assignROI03->setEnabled(false);
				deleteROI03->setEnabled(false);
				selectROI13->setEnabled(false);
				assignROI13->setEnabled(false);
				deleteROI13->setEnabled(false);
				fieldLabel03->setEnabled(false);
				fieldLabel13->setEnabled(false);
				fieldLabel23->setEnabled(false);
				frameStROI03->setEnabled(false);
				fieldLabel33->setEnabled(false);
				frameEdROI03->setEnabled(false);
			}
			if (colorSel04->isEnabled())
			{
				stateMachine_OF04->changeState(_STATE_OFF);
				colorSel04->setEnabled(false);
				selectROI04->setEnabled(false);
				assignROI04->setEnabled(false);
				deleteROI04->setEnabled(false);
				selectROI14->setEnabled(false);
				assignROI14->setEnabled(false);
				deleteROI14->setEnabled(false);
				fieldLabel04->setEnabled(false);
				fieldLabel14->setEnabled(false);
				fieldLabel24->setEnabled(false);
				frameStROI04->setEnabled(false);
				fieldLabel34->setEnabled(false);
				frameEdROI04->setEnabled(false);
			}
			break;
		case 2:
			if (!colorSel02->isEnabled())
			{
				stateMachine_OF02->changeState(_STATE_WAIT);
				colorSel02->setEnabled(true);
				selectROI02->setEnabled(true);
				assignROI02->setEnabled(true);
				deleteROI02->setEnabled(true);
				selectROI12->setEnabled(true);
				assignROI12->setEnabled(true);
				deleteROI12->setEnabled(true);
				fieldLabel02->setEnabled(true);
				fieldLabel12->setEnabled(true);
				fieldLabel22->setEnabled(true);
				frameStROI02->setEnabled(true);
				fieldLabel32->setEnabled(true);
				frameEdROI02->setEnabled(true);
			}
			if (colorSel03->isEnabled())
			{
				stateMachine_OF03->changeState(_STATE_OFF);
				colorSel03->setEnabled(false);
				selectROI03->setEnabled(false);
				assignROI03->setEnabled(false);
				deleteROI03->setEnabled(false);
				selectROI13->setEnabled(false);
				assignROI13->setEnabled(false);
				deleteROI13->setEnabled(false);
				fieldLabel03->setEnabled(false);
				fieldLabel13->setEnabled(false);
				fieldLabel23->setEnabled(false);
				frameStROI03->setEnabled(false);
				fieldLabel33->setEnabled(false);
				frameEdROI03->setEnabled(false);
			}
			if (colorSel04->isEnabled())
			{
				stateMachine_OF04->changeState(_STATE_OFF);
				colorSel04->setEnabled(false);
				selectROI04->setEnabled(false);
				assignROI04->setEnabled(false);
				deleteROI04->setEnabled(false);
				selectROI14->setEnabled(false);
				assignROI14->setEnabled(false);
				deleteROI14->setEnabled(false);
				fieldLabel04->setEnabled(false);
				fieldLabel14->setEnabled(false);
				fieldLabel24->setEnabled(false);
				frameStROI04->setEnabled(false);
				fieldLabel34->setEnabled(false);
				frameEdROI04->setEnabled(false);
			}
			break;
		case 3:
			if (!colorSel02->isEnabled())
			{
				stateMachine_OF02->changeState(_STATE_WAIT);
				colorSel02->setEnabled(true);
				selectROI02->setEnabled(true);
				assignROI02->setEnabled(true);
				deleteROI02->setEnabled(true);
				selectROI12->setEnabled(true);
				assignROI12->setEnabled(true);
				deleteROI12->setEnabled(true);
				fieldLabel02->setEnabled(true);
				fieldLabel12->setEnabled(true);
				fieldLabel22->setEnabled(true);
				frameStROI02->setEnabled(true);
				fieldLabel32->setEnabled(true);
				frameEdROI02->setEnabled(true);
			}
			if (!colorSel03->isEnabled())
			{
				stateMachine_OF03->changeState(_STATE_WAIT);
				colorSel03->setEnabled(true);
				selectROI03->setEnabled(true);
				assignROI03->setEnabled(true);
				deleteROI03->setEnabled(true);
				selectROI13->setEnabled(true);
				assignROI13->setEnabled(true);
				deleteROI13->setEnabled(true);
				fieldLabel03->setEnabled(true);
				fieldLabel13->setEnabled(true);
				fieldLabel23->setEnabled(true);
				frameStROI03->setEnabled(true);
				fieldLabel33->setEnabled(true);
				frameEdROI03->setEnabled(true);
			}
			if (colorSel04->isEnabled())
			{
				stateMachine_OF04->changeState(_STATE_OFF);
				colorSel04->setEnabled(false);
				selectROI04->setEnabled(false);
				assignROI04->setEnabled(false);
				deleteROI04->setEnabled(false);
				selectROI14->setEnabled(false);
				assignROI14->setEnabled(false);
				deleteROI14->setEnabled(false);
				fieldLabel04->setEnabled(false);
				fieldLabel14->setEnabled(false);
				fieldLabel24->setEnabled(false);
				frameStROI04->setEnabled(false);
				fieldLabel34->setEnabled(false);
				frameEdROI04->setEnabled(false);				
			}
			break;
		case 4:
			if (!colorSel02->isEnabled())
			{
				stateMachine_OF02->changeState(_STATE_WAIT);
				colorSel02->setEnabled(true);
				selectROI02->setEnabled(true);
				assignROI02->setEnabled(true);
				deleteROI02->setEnabled(true);
				selectROI12->setEnabled(true);
				assignROI12->setEnabled(true);
				deleteROI12->setEnabled(true);
				fieldLabel02->setEnabled(true);
				fieldLabel12->setEnabled(true);
				fieldLabel22->setEnabled(true);
				frameStROI02->setEnabled(true);
				fieldLabel32->setEnabled(true);
				frameEdROI02->setEnabled(true);
			}
			if (!colorSel03->isEnabled())
			{
				stateMachine_OF03->changeState(_STATE_WAIT);
				colorSel03->setEnabled(true);
				selectROI03->setEnabled(true);
				assignROI03->setEnabled(true);
				deleteROI03->setEnabled(true);
				selectROI13->setEnabled(true);
				assignROI13->setEnabled(true);
				deleteROI13->setEnabled(true);
				fieldLabel03->setEnabled(true);
				fieldLabel13->setEnabled(true);
				fieldLabel23->setEnabled(true);
				frameStROI03->setEnabled(true);
				fieldLabel33->setEnabled(true);
				frameEdROI03->setEnabled(true);
			}
			if (!colorSel04->isEnabled())
			{
				stateMachine_OF04->changeState(_STATE_WAIT);
				colorSel04->setEnabled(true);
				selectROI04->setEnabled(true);
				assignROI04->setEnabled(true);
				deleteROI04->setEnabled(true);
				selectROI14->setEnabled(true);
				assignROI14->setEnabled(true);
				deleteROI14->setEnabled(true);
				fieldLabel04->setEnabled(true);
				fieldLabel14->setEnabled(true);
				fieldLabel24->setEnabled(true);
				frameStROI04->setEnabled(true);
				fieldLabel34->setEnabled(true);
				frameEdROI04->setEnabled(true);
			}
			break;
	} 
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
	argusSlider->disableSlider();
	//qFrameSlider->setMaximum(1);
	qFrameSpiner->setMaximum(1);
	//qFrameSlider->setValue(1);
	vidIfoName->setText("INVALID");
	vidIfoReso->setText("N/A");
	vidIfoFrme->setText("N/A");
	vidIfoTime->setText("N/A");
	//labelFrameMax->setText(" \\ NA frames");
	fileLine->clear();

	if (selectROI01->isChecked())
	{
		selectROI01->setChecked(false);
		emit OF_CancelROI(1);
	}

	//argusEye->showHomeScreen();
	emit sendStopSignal();
}

void Argus::guiUpdated(int ff)
{
	if(argusSlider->value() != ff)
	{
		argusSlider->setValue(ff);
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

		//qFrameSlider->setMaximum(tf);
		//argusSlider->enableSlider(tf);
		string sst = " \\ " + std::to_string(tf) + " frames";
		//labelFrameMax->setText(QString::fromStdString(sst));
		//qFrameSpiner->setMaximum(tf);
		//qFrameSpiner->setValue(1);
		//argusSlider->setValue(1);
		//qFrameSlider->setEnabled(false);
	}
	cout << "Frame Rate: " << int(fr) << endl;
	cout << "Frame Count: " << tf << endl;
}

void Argus::OF_ColorChanged01(int idx)
{
	emit OF_roiSetColor(0, idx);
}

void Argus::OF_ColorChanged02(int idx)
{
	emit OF_roiSetColor(1, idx);
}

void Argus::userReassignTOI(int idx)
{
	switch(idx)
	{
		case 0:
			stateMachine_OF02->changeState(_STATE_OFF);
			colorSel02->setEnabled(false);
			selectROI02->setEnabled(false);
			assignROI02->setEnabled(false);
			deleteROI02->setEnabled(false);
			selectROI12->setEnabled(false);
			assignROI12->setEnabled(false);
			deleteROI12->setEnabled(false);
			fieldLabel02->setEnabled(false);
			fieldLabel12->setEnabled(false);
			fieldLabel22->setEnabled(false);
			frameStROI02->setEnabled(false);
			stateMachine_OF03->changeState(_STATE_OFF);
			colorSel03->setEnabled(false);
			selectROI03->setEnabled(false);
			assignROI03->setEnabled(false);
			deleteROI03->setEnabled(false);
			selectROI13->setEnabled(false);
			assignROI13->setEnabled(false);
			deleteROI13->setEnabled(false);
			fieldLabel03->setEnabled(false);
			fieldLabel13->setEnabled(false);
			fieldLabel23->setEnabled(false);
			frameStROI03->setEnabled(false);
			stateMachine_OF04->changeState(_STATE_OFF);
			colorSel04->setEnabled(false);
			selectROI04->setEnabled(false);
			assignROI04->setEnabled(false);
			deleteROI04->setEnabled(false);
			selectROI14->setEnabled(false);
			assignROI14->setEnabled(false);
			deleteROI14->setEnabled(false);
			fieldLabel04->setEnabled(false);
			fieldLabel14->setEnabled(false);
			fieldLabel24->setEnabled(false);
			frameStROI04->setEnabled(false);
			break;

	}
}

void Argus::OF_TrackerFrameAssigned(int fr, int tr)
{
	//std::cout << fr << std::endl;
	switch(tr)
	{
		case 0:
			frameStROI01->setText(QString::number(fr));
			break;
		case 1:
			frameStROI02->setText(QString::number(fr));
			break;
		case 2:
			frameStROI03->setText(QString::number(fr));
			break;
		case 3:
			frameStROI04->setText(QString::number(fr));
			break;
	}
}

void Argus::openField_expSet(int expID, bool flagSet)
{
	std::cout << "hello" << flagSet << "__" << expID << std::endl;
	switch (expID)
	{
		case 0:
			if (flagSet)
			{
				std::cout << "true flag found 1" << std::endl;
				if (colorSel01->isEnabled())
					stateMachine_OF01->changeState(_STATE_GOOD);
				else
					stateMachine_OF01->changeState(_STATE_OFF);
			}
			else
			{
				if (colorSel01->isEnabled())
					stateMachine_OF01->changeState(_STATE_STOP);
				else
					stateMachine_OF01->changeState(_STATE_OFF);
			}
			break;

		case 1:
			if (flagSet)
			{
				std::cout << "true flag found 2" << std::endl;
				if (colorSel02->isEnabled())
					stateMachine_OF02->changeState(_STATE_GOOD);
				else
					stateMachine_OF02->changeState(_STATE_OFF);
			}
			else
			{
				if (colorSel02->isEnabled())
					stateMachine_OF02->changeState(_STATE_STOP);
				else
					stateMachine_OF02->changeState(_STATE_OFF);
			}
			break;

		case 2:
			if (flagSet)
			{
				std::cout << "true flag found 3" << std::endl;
				if (colorSel03->isEnabled())
					stateMachine_OF03->changeState(_STATE_GOOD);
				else
					stateMachine_OF03->changeState(_STATE_OFF);
			}
			else
			{
				if (colorSel03->isEnabled())
					stateMachine_OF03->changeState(_STATE_STOP);
				else
					stateMachine_OF03->changeState(_STATE_OFF);
			}
			break;
		case 3:
			if (flagSet)
			{
				std::cout << "true flag found 3" << std::endl;
				if (colorSel04->isEnabled())
					stateMachine_OF04->changeState(_STATE_GOOD);
				else
					stateMachine_OF04->changeState(_STATE_OFF);
			}
			else
			{
				if (colorSel04->isEnabled())
					stateMachine_OF04->changeState(_STATE_STOP);
				else
					stateMachine_OF04->changeState(_STATE_OFF);
			}
			break;
	}
}

void Argus::OF_InitAnalysis()
{
	// FIrst we should check that all valid stateMachines are good
	if (!argusHead->isLoaded())
	{
		std::cout << "ERROR: No video loaded" << std::endl;
		return;
	}
	bool stateSet = true;
	if (stateMachine_OF01->getState() != _STATE_OFF && stateMachine_OF01->getState() != _STATE_ON)
		if (stateMachine_OF01->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF02->getState() != _STATE_OFF && stateMachine_OF02->getState() != _STATE_ON)
		if (stateMachine_OF02->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF03->getState() != _STATE_OFF && stateMachine_OF03->getState() != _STATE_ON)
		if (stateMachine_OF03->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF04->getState() != _STATE_OFF && stateMachine_OF04->getState() != _STATE_ON)
		if (stateMachine_OF04->getState() != _STATE_GOOD)
			stateSet = false;

	if (openField_BoxX < 0 || openField_BoxY < 0)
		stateSet = false;

	if (openField_TaskDur <= 0)
		stateSet = false;

	if (stateSet)
	{
		emit assignOF_BoxDims(openField_BoxX, openField_BoxY, openField_BoxU);
		emit assignOF_TaskDur(openField_TaskDur, openField_IgnoreDur);
		int endFrame = frameStROI01->text().toInt() + argusHead->getCurrentFrameRate() * (60*(openField_TaskDur+openField_IgnoreDur));
		frameEdROI01->setText(QString::number(endFrame));
		//QString textTemp = vidIfoReso->text();
		//int fr = argusMind->gettextTemp.toInt();
		//int addedFr = v * 60 * 

		emit initNow_OF();// DO stuff
		startOF->setEnabled(true);
	}
	else
	{
		std::cout << "ERROR: Needed ROIs and trackers not initialized" << std::endl;
		return;
	}
}

void Argus::OF_BeginAnalysis()
{
	// FIrst we should check that all valid stateMachines are good
	if (!argusHead->isLoaded())
	{
		std::cout << "ERROR: No video loaded" << std::endl;
		return;
	}
	bool stateSet = true;
	if (stateMachine_OF01->getState() != _STATE_OFF && stateMachine_OF01->getState() != _STATE_ON)
		if (stateMachine_OF01->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF02->getState() != _STATE_OFF && stateMachine_OF02->getState() != _STATE_ON)
		if (stateMachine_OF02->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF03->getState() != _STATE_OFF && stateMachine_OF03->getState() != _STATE_ON)
		if (stateMachine_OF03->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF04->getState() != _STATE_OFF && stateMachine_OF04->getState() != _STATE_ON)
		if (stateMachine_OF04->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateSet)
	{
		emit startNow_OF();// DO stuff
		startOF->setEnabled(false);
		//resuOF->setEnabled(false);
	}
	else
	{
		std::cout << "ERROR: Needed ROIs and trackers not initialized" << std::endl;
		return;
	}
}

void Argus::OF_ResuAnalysis()
{
	// FIrst we should check that all valid stateMachines are good
	if (!argusHead->isLoaded())
	{
		std::cout << "ERROR: No video loaded" << std::endl;
		return;
	}
	bool stateSet = true;
	if (stateMachine_OF01->getState() != _STATE_OFF && stateMachine_OF01->getState() != _STATE_ON)
		if (stateMachine_OF01->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF02->getState() != _STATE_OFF && stateMachine_OF02->getState() != _STATE_ON)
		if (stateMachine_OF02->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF03->getState() != _STATE_OFF && stateMachine_OF03->getState() != _STATE_ON)
		if (stateMachine_OF03->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateMachine_OF04->getState() != _STATE_OFF && stateMachine_OF04->getState() != _STATE_ON)
		if (stateMachine_OF04->getState() != _STATE_GOOD)
			stateSet = false;

	if (stateSet)
	{
		emit resuNow_OF();// DO stuff
		resuOF->setEnabled(false);
	}
	else
	{
		std::cout << "ERROR: Needed ROIs and trackers not initialized" << std::endl;
		return;
	}
}

void Argus::pingOF_objectLost()
{
	resuOF->setEnabled(true);
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