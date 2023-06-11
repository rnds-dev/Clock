#include "stopwatch.h"
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <Windows.h>

//#define LIGHTTHEME

QString normalise(int input);

stopwatch::stopwatch(QWidget* parent) {
	QFont timeFont("Montserrat SemiBold", 35), btnFont("Montserrat Medium", 15);
	QString style = (
#ifdef LIGHTTHEME
		"background-color:#eeeeee;"
		"color: #202020;"
#endif
#ifndef LIGHTTHEME
		"background-color:#202020;"
		"color: #eeeeee;"
#endif 
		"border-radius: 0;");

	QGridLayout* grid = new QGridLayout(this);
	QList controls = { "Start", "Pause", "Stop" };
	tmr = new QTimer();

	for (int i = 0; i < 3; i++) {
		QLabel* tm = new QLabel("00");
		tm->setFont(timeFont);
		tm->setStyleSheet(style);
		tm->setAlignment(Qt::AlignCenter);
		tm->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		timeList->append(tm);
		grid->addWidget(tm, 1, i);

		QPushButton* controlbtn = new QPushButton(controls[i]);
		controlbtn->setFont(btnFont);
		controlbtn->setStyleSheet(style);
		controlbtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		grid->addWidget(controlbtn, 3, i);

		connect(controlbtn, &QPushButton::clicked, this, &stopwatch::control);

	}

	grid->setSpacing(0);
	grid->setContentsMargins(0, 0, 0, 0);
	setLayout(grid);
};


void stopwatch::control() {
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	QString buttonText = buttonSender->text();

	if (buttonText == "Start") {
		if (!tmr->isActive()) {
			hs = timeList->at(0)->text();
			ms = timeList->at(1)->text();
			ss = timeList->at(2)->text();

			all = (hs.toInt() * 60 * 60 + ms.toInt() * 60 + ss.toInt());

			connect(tmr, &QTimer::timeout, this, &stopwatch::stopwatchStart);
			tmr->start(1000);
		}
	}
	else {
		tmr->stop();
		tmr->disconnect();
		if (buttonText == "Stop") {
			timeList->at(0)->setText("00");
			timeList->at(1)->setText("00");
			timeList->at(2)->setText("00");
		}
	}
};

void stopwatch::stopwatchStart() {

	all++;
	timeList->at(0)->setText(normalise(all / 3600));
	timeList->at(1)->setText(normalise((all / 60) % 60));
	timeList->at(2)->setText(normalise(all % 60));

};

QString normalise(int input) {
	return QString("%1").arg(input, 2, 10, QChar('0'));
};
