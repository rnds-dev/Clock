
#include "timer.h"
#include <qgridlayout.h>
#include <qpushbutton.h>
#include <Windows.h>

//#define LIGHTTHEME

QString normalise(int input);

timer::timer(QWidget* parent) {
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
		QPushButton* plus = new QPushButton("+");
		plus->setStyleSheet(style + "text-align: bottom;");
		plus->setFont(btnFont);
		plus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		grid->addWidget(plus, 0, i);
		connect(plus, &QPushButton::clicked, [this, i] {editTime(i, '+'); });

		QLineEdit* tm = new QLineEdit("00");
		tm->setFont(timeFont);
		tm->setStyleSheet(style);
		tm->setAlignment(Qt::AlignCenter);
		timeList->append(tm);
		grid->addWidget(tm, 1, i);

		QPushButton* minus = new QPushButton("-");
		minus->setStyleSheet(style + "text-align: top;");
		minus->setFont(btnFont);
		minus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		grid->addWidget(minus, 2, i);
		connect(minus, &QPushButton::clicked, [this, i] {editTime(i, '-'); });

		QPushButton* control = new QPushButton(controls[i]);
		control->setFont(btnFont);
		control->setStyleSheet(style);
		control->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		grid->addWidget(control, 3, i);
		connect(control, &QPushButton::clicked, this, &timer::control);

	}

	grid->setSpacing(0);
	grid->setContentsMargins(0, 0, 0, 0);
	setLayout(grid);
};

void timer::editTime(int index, char type) {
	if (!tmr->isActive()) {
		int get = timeList->at(index)->text().toInt();
		timeList->at(index)->setText(normalise(type == '+' ? (++get % 60) : (60 + (--get)) % 60));
	}
};

void timer::tstop() {
	tmr->stop(); tmr->disconnect();
}

void timer::control() {
	QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
	QString buttonText = buttonSender->text();

	if (buttonText == "Start") {
		if (!tmr->isActive()) {
			hs = timeList->at(0)->text();
			ms = timeList->at(1)->text();
			ss = timeList->at(2)->text();

			all = (hs.toInt() * 60 * 60 + ms.toInt() * 60 + ss.toInt());

			connect(tmr, &QTimer::timeout, this, &timer::timerStart);
			tmr->start(1000);
		}
	}
	else {
		tstop();
		if (buttonText == "Stop") {
			timeList->at(0)->setText(hs);
			timeList->at(1)->setText(ms);
			timeList->at(2)->setText(ss);
		}
	}
};

void timer::timerStart() {

	if (all < 1) tstop();
	all--;
	timeList->at(0)->setText(normalise(all / 3600));
	timeList->at(1)->setText(normalise((all / 60) % 60));
	timeList->at(2)->setText(normalise(all % 60));

};
