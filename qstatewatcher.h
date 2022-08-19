#ifndef QSTATEWATCHER_H
#define QSTATEWATCHER_H

#include <QLabel>
#include <QWidget>
#include <string>

class QStateWatcher : public QLabel
{
	Q_OBJECT

	public:
		QStateWatcher(QString, QString, QString, QString, QString, int, int, QWidget *parent = 0);
		~QStateWatcher();

		int getState();
		void changeState(int);

	private:
		int currState;
		int numStates;

		QImage imageActiveGood;
		QImage imageActiveWait;
		QImage imageActiveStop;
		QImage imageInactiveOf;
		QImage imageInactiveOn;

		int valueActiveGood;
		int valueActiveWait;
		int valueActiveStop;
		int valueInactiveOf;
		int valueInactiveOn;

	public slots:
		void changeStateSLOT(int);
};

#endif