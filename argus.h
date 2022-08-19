#ifndef ARGUS_H
#define ARGUS_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QLabel>
#include <QtGui>
#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QLCDNumber>
#include <QLineEdit>
#include <QtWidgets>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "eyeofargus.h"
#include "mindofargus.h"
#include "qargusslider.h"
#include "qstatewatcher.h"
#include "headofargus.h"
#include "qargusbutton.h"

class QGroupBox;
class QTextEdit;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class Argus : public QWidget
{
	Q_OBJECT

	public:
		Argus(QWidget *parent = 0);
		~Argus();

	private:
		bool forceClosing;

		int openField_ratNum;
		int openField_referenceMode;
		int openField_referenceNumb;
		double openField_BoxX;
		double openField_BoxY;
		int openField_BoxU;
		int openField_TaskDur, openField_IgnoreDur;

		QGroupBox *createTitle();
		QGroupBox *createVideoOptions();
		QGroupBox *createLogWindow();
		QGroupBox *createVideoPlayer();
		QGroupBox *createExperOptions();

		QGroupBox *createExperiment_OpenField();
		QGroupBox *createExperiment_PlusMaze();
		QGroupBox *createExperiment_Default();

		QGraphicsScene *gScene;

		QPushButton *initOF;
		QPushButton *startOF;
		QPushButton *resuOF;

		QArgusSlider *argusSlider;

		QLineEdit *fileLine;
		QString fileName;

		QLabel *vidIfoFrme;
		QLabel *vidIfoName;
		QLabel *vidIfoTime;
		QLabel *vidIfoReso;

		QLabel *labelFrameMax;
		//QSlider *qFrameSlider;
		QSpinBox *qFrameSpiner;

		QLabel *fieldLabel01;
		QLabel *fieldLabel11;
		QLabel *fieldLabel21;
		QLabel *fieldLabel31;
		QLabel *fieldLabel02;
		QLabel *fieldLabel12;
		QLabel *fieldLabel22;
		QLabel *fieldLabel32;
		QLabel *fieldLabel03;
		QLabel *fieldLabel13;
		QLabel *fieldLabel23;
		QLabel *fieldLabel33;
		QLabel *fieldLabel04;
		QLabel *fieldLabel14;
		QLabel *fieldLabel24;
		QLabel *fieldLabel34;

		QLineEdit *qReff_Line;
		QLineEdit *sensLine;
		QLineEdit *blurLine;

		QComboBox *colorSel01;
		QArgusButton *selectROI01;
		QArgusButton *assignROI01;
		QArgusButton *deleteROI01;
		QComboBox *colorSel02;
		QArgusButton *selectROI02;
		QArgusButton *assignROI02;
		QArgusButton *deleteROI02;
		QComboBox *colorSel03;
		QArgusButton *selectROI03;
		QArgusButton *assignROI03;
		QArgusButton *deleteROI03;
		QComboBox *colorSel04;
		QArgusButton *selectROI04;
		QArgusButton *assignROI04;
		QArgusButton *deleteROI04;

		QLineEdit *lineOFXDim;
		QLineEdit *lineOFYDim;

		QLineEdit *frameStROI01;
		QLineEdit *frameEdROI01;
		QArgusButton *selectROI11;
		QArgusButton *assignROI11;
		QArgusButton *deleteROI11;
		QLineEdit *frameStROI02;
		QLineEdit *frameEdROI02;
		QArgusButton *selectROI12;
		QArgusButton *assignROI12;
		QArgusButton *deleteROI12;
		QLineEdit *frameStROI03;
		QLineEdit *frameEdROI03;
		QArgusButton *selectROI13;
		QArgusButton *assignROI13;
		QArgusButton *deleteROI13;
		QLineEdit *frameStROI04;
		QLineEdit *frameEdROI04;
		QArgusButton *selectROI14;
		QArgusButton *assignROI14;
		QArgusButton *deleteROI14;

		//EyeOfArgus *argusEye;
		MindOfArgus *argusMind;
		HeadOfArgus *argusHead;

		QStateWatcher *stateMachine_OF01;
		QStateWatcher *stateMachine_OF02;
		QStateWatcher *stateMachine_OF03;
		QStateWatcher *stateMachine_OF04;

		void closeEvent(QCloseEvent *event);

	private slots:
		void locateVideo();
		void loadVideo();
		void filePathChanged(QString);

		void blurSliderChanged(int);
		void sensSliderChanged(int);

		//void retractFive();
		//void retractOne();
		//void returnOne();
		//void returnFive();

		void eyeClicked(QMouseEvent *ev);
		void eyeMoved(QMouseEvent *ev);
		
		void change_ratNumOpenField(int);

		void videoPlayPause(bool);
		void videoStop();

		void OF_selectROI(int);
		void OF_selectTOI(int);
		void OF_saveROI(int);
		void OF_saveTOI(int);
		void OF_removeROI(int);
		void OF_removeTOI(int);
		void OF_ColorChanged01(int);
		void OF_ColorChanged02(int);
		void OF_InitAnalysis();
		void OF_BeginAnalysis();
		void OF_ResuAnalysis();
		void OF_XChanged(QString);
		void OF_YChanged(QString);
		void OF_taskDurChanged(QString);
		void OF_ignoreDurChanged(QString);

		void boxUnitChanged_CM();
		void boxUnitChanged_IN();
		void qReff_StarterClicked();
		void qReff_AverageClicked();
		void qReff_CustomFClicked();
		void qReff_AssignReference();

	public slots:
		void videoLoaded(double, int, int, int);
		void guiUpdated(int);
		void openField_expSet(int, bool);
		void OF_TrackerFrameAssigned(int, int);
		void videoStopped();
		void userReassignTOI(int);

		void pingOF_objectLost();

	signals:
		void sendVideoQueue(QString);
		void sendSight(cv::Mat, int);
		void sendFrame(int);

		void playVideo();
		void pauseVideo();
		void sendStopSignal();

		void OF_StartROI(int, int);
		void OF_StartTOI(int, int);
		void OF_CancelROI(int);
		void OF_CancelTOI(int);
		void OF_SaveROI(int);
		void OF_SaveTOI(int);
		void OF_RemoveROI(int);
		void OF_RemoveTOI(int);
		void OF_roiSetColor(int, int);
		void OF_setReference(int);
		void OF_sensChanged(int);
		void OF_blurChanged(int);

		void initNow_OF();
		void startNow_OF();
		void resuNow_OF();

		void assignOF_BoxDims(double, double, int);
		void assignOF_TaskDur(int, int);
};

#endif