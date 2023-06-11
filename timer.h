
#pragma once
#include <qwidget.h>
#include <qlineedit.h>
#include <qtimer.h>

class timer : public QWidget
{
	Q_OBJECT;
public:
	timer(QWidget* parent = 0);

private:
	QList<QLineEdit*>* timeList = new QList<QLineEdit*>();
	QTimer* tmr;
	int all = 0;
	QString hs, ms, ss;

	void editTime(int index, char type);
	void control();
	void tstop();
	void timerStart();

	QString normalise(int input) { return QString("%1").arg(input, 2, 10, QChar('0')); };

};

