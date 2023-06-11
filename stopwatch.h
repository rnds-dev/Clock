#pragma once
#include <qwidget.h>

#include <qlabel.h>
#include <qtimer.h>

class stopwatch : public QWidget {
	Q_OBJECT;

public:
	stopwatch(QWidget* parent = 0);

private:
	QList<QLabel*>* timeList = new QList<QLabel*>();
	QTimer* tmr;
	int all = 0;
	QString hs, ms, ss;

	void start();
	void pause();
	void stop();

	void control();
	void stopwatchStart();

	QString normalise(int input) { return QString("%1").arg(input, 2, 10, QChar('0')); };
};

