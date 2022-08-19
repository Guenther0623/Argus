#ifndef HEADOFARGUS_H
#define HEADOFARGUS_H

#include "eyeofargus.h"
#include "mindofargus.h"
#include "qargusslider.h"

#include <QtWidgets>
#include <QLineEdit>
#include <iostream>
#include <QBoxLayout>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QPixmap>
#include <QThread>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>

#include <iostream>

class HeadOfArgus : public QGroupBox
{
	Q_OBJECT
	QThread workerThread;

	public:
		HeadOfArgus(QWidget *parent = 0);
		~HeadOfArgus();

		bool isLoaded();
		int getCurrentFrame() {return currentFrame;};
		int getCurrentFrameRate() {return argusMind->getCurrentFrameRate();};

	private:
		QVBoxLayout *argusHeadLayout();
		void startVideo();
		void pauseVideo();

		int roiNumPoints, roiMaxNumber;
		int toiNumPoints, toiMaxNumber;

		bool roiSelector, toiSelector;
		int roiSelected, toiSelected, usrNumPoints;

		bool loaded, playing, paused, procing;
		bool processing;
		bool waitingForUser;
		bool *toiSaved, *roiSaved;
		int totalFrames, currentFrame;
		EyeOfArgus *argusEye;
		MindOfArgus *argusMind;

		QArgusSlider *argusSlider;

		QPushButton *backFive;
		QPushButton *forwFive;
		QPushButton *backOne;
		QPushButton *forwOne;
		QPushButton *stopNow;
		QPushButton *playPause;

		//QArgusWorker *argusWorker;

		QSpinBox *qFrameSpiner;
		QLabel *labelFrameMax;

		double interTimer;
		QTimer *playTimer;

	public slots:
		void videoSync(QString);
		void guiUpdated(int);
		void setRefImage(int);
		void sensitivityChanged(int);
		void blurFactorChanged(int);
		void startROISelector(int, int);
		void startTOISelector(int, int);
		void cancelROISelector(int);
		void cancelTOISelector(int);
		void saveROISelector(int);
		void saveTOISelector(int);
		void removeROISaved(int);
		void removeTOISaved(int);
		void roiSetColor(int, int);
		void receiveOF_BoxDims(double, double, int);
		void receiveOF_TaskDur(int, int);

		void pingOF_objectLost();

		void analysisStopped();

		void eyeClicked(QMouseEvent*);
		void eyeMoved(QMouseEvent*);

	private slots:
		void videoSyncCompleted(double, int, int, int);
		void videoPlayPause();
		void videoStop();
		void qSliderChanged(int);
		void qSliderReleased();
		void qSpinerChanged(int);
		void goNextFrame();
		void openField_expSet(int, bool);
		void trackerInfo_Send(int, int);
		void ping_initOpenField();
		void ping_startOpenField();
		void ping_resuOpenField();
		void analysisFinished();
		void sendRequest_TOIReassignment(int, bool*);

		void viewChanged_Norm();
		void viewChanged_Base();
		void viewChanged_Reff();
		void viewChanged_Diff();
		void viewChanged_Subt();

	signals:
		void sendVideoString(QString);
		void videoSynced(double, int, int, int);
		void sendFrame(int);
		void nextFrame();
		void startVideoNow();
		void pauseVideoNow();
		void stopVideoNow();

		void assignRefImage(int);
		void roiSelectStart(int, int);
		void toiSelectStart(int, int);
		void roiSelectSave(int);
		void toiSelectSave(int);
		void roiSelectCancel(int);
		void toiSelectCancel(int);
		void roiSelectRemove(int);
		void toiSelectRemove(int);
		void roiSelectColor(int, int);
		void setOF_BoxDims(double, double, int);
		void setOF_TaskDur(int, int);

		void sendViewChange_Norm();
		void sendViewChange_Base();
		void sendViewChange_Reff();
		void sendViewChange_Diff();
		void sendViewChange_Subt();

		void signalOF_objectLost();

		void compileData();

		void ping_reguestTOIReassignment(int);
		void openField_expChange(int, bool);
		void trackerInfo_Sent(int, int);
		void initNow_OF();
		void startNow_OF();
		void resuNow_OF();
};

#endif