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

		int plusMaze_ratNum;
		int plusMaze_referenceMode;
		int plusMaze_referenceNumb;
		double plusMaze_BoxX;
		double plusMaze_BoxY;
		int plusMaze_BoxU;
		int plusMaze_TaskDur, plusMaze_IgnoreDur;

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

		QPushButton *initPM;	// Added by Riddhi
		QPushButton *startPM;	// Added by Riddhi
		QPushButton *resuPM;	// Added by Riddhi

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
		QArgusButton *selectOpenROI01;		// added by Riddhi - for plus maze
		QArgusButton *assignOpenROI01;		// added by Riddhi - for plus maze
		QArgusButton *deleteOpenROI01;		// added by Riddhi - for plus maze
		QArgusButton *selectClosedROI01;	// added by Riddhi - for plus maze
		QArgusButton *assignClosedROI01;	// added by Riddhi - for plus maze
		QArgusButton *deleteClosedROI01;	// added by Riddhi - for plus maze
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
		QArgusButton *selectOpenROI11;		// added by Riddhi - for plus maze (tracker)
		QArgusButton *assignOpenROI11;		// added by Riddhi - for plus maze (tracker)
		QArgusButton *deleteOpenROI11;		// added by Riddhi - for plus maze (tracker)
		QArgusButton *selectClosedROI11;	// added by Riddhi - for plus maze (tracker)
		QArgusButton *assignClosedROI11;	// added by Riddhi - for plus maze (tracker)
		QArgusButton *deleteClosedROI11;	// added by Riddhi - for plus maze (tracker)
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

		QStateWatcher *stateMachine_PM01;	// added by Riddhi - for plus maze
		QStateWatcher *stateMachine_PM02;	// added by Riddhi - for plus maze


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

		void PM_selectROI(int);				// Added by Riddhi
		void PM_selectTOI(int);				// Added by Riddhi
		void PM_saveROI(int);				// Added by Riddhi
		void PM_saveTOI(int);				// Added by Riddhi
		void PM_removeROI(int);				// Added by Riddhi
		void PM_removeTOI(int);				// Added by Riddhi
		void PM_ColorChanged01(int);		// Added by Riddhi
		void PM_ColorChanged02(int);		// Added by Riddhi
		void PM_InitAnalysis();				// Added by Riddhi
		void PM_BeginAnalysis();			// Added by Riddhi
		void PM_ResuAnalysis();				// Added by Riddhi
		void PM_XChanged(QString);			// Added by Riddhi
		void PM_YChanged(QString);			// Added by Riddhi
		void PM_taskDurChanged(QString);	// Added by Riddhi
		void PM_ignoreDurChanged(QString);	// Added by Riddhi

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

		void plusMaze_expSet(int, bool);			// Added by Riddhi	

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

		void PM_StartROI(int, int);			// added by Riddhi
		void PM_StartTOI(int, int);			// added by Riddhi
		void PM_CancelROI(int);				// added by Riddhi
		void PM_CancelTOI(int);				// added by Riddhi
		void PM_SaveROI(int);				// added by Riddhi
		void PM_SaveTOI(int);				// added by Riddhi
		void PM_RemoveROI(int);				// added by Riddhi
		void PM_RemoveTOI(int);				// added by Riddhi
		void PM_roiSetColor(int, int);		// added by Riddhi
		void PM_setReference(int);			// added by Riddhi
		void PM_sensChanged(int);			// added by Riddhi
		void PM_blurChanged(int);			// added by Riddhi

		void initNow_PM();					// added by Riddhi
		void startNow_PM();					// added by Riddhi
		void resuNow_PM();					// added by Riddhi

		void assignPM_BoxDims(double, double, int);		// added by Riddhi
		void assignPM_TaskDur(int, int);				// added by Riddhi
};

#endif