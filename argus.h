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

		QGroupBox *createTitle();
		QGroupBox *createVideoOptions();
		QGroupBox *createLogWindow();
		QGroupBox *createVideoPlayer();
		QGroupBox *createExperOptions();

		QGroupBox *createExperiment_OpenField();
		QGroupBox *createExperiment_PlusMaze();
		QGroupBox *createExperiment_Default();

		QLineEdit *fileLine;
		QString fileName;

		QLabel *vidIfoFrme;
		QLabel *vidIfoName;
		QLabel *vidIfoTime;
		QLabel *vidIfoReso;

		QLabel *labelFrameMax;
		QSlider *qFrameSlider;
		QSpinBox *qFrameSpiner;

		EyeOfArgus *argusEye;
		MindOfArgus *argusMind;

		void closeEvent(QCloseEvent *event);

	private slots:
		void locateVideo();
		void loadVideo();
		void filePathChanged(QString);

		void qSliderChanged(int);
		void qSpinerChanged(int);

		void eyeClicked(QMouseEvent *ev);
		void eyeMoved(QMouseEvent *ev);
		
		void change_ratNumOpenField(int);

	public slots:
		void videoLoaded(double, int, int, int);

	signals:
		void sendVideoQueue(QString);
		void sendSight(cv::Mat, int);
};

#endif //MAINWINDOW_H