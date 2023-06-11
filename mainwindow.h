#pragma once
#include <qwidget.h>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qboxlayout.h>
#include <qtabwidget.h>

#include "timer.h"
#include "stopwatch.h"

class change : public QWidget
{
	Q_OBJECT;
public:


	change(QWidget* parent = 0) {

		stw = new stopwatch;
		tm = new timer;

		QFont btnFont("Montserrat Light", 12);
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

		QWidget* container = new QWidget();
		container->setStyleSheet("background: #202020");

		QTabWidget* tabs = new QTabWidget(container);

		tabs->insertTab(0, stw, "Stopwatch");
		tabs->insertTab(1, tm, "Timer");

		tabs->setStyleSheet(
			"QTabBar::tab { background: #202020; color: white; padding: 5px; } "
			"QTabBar::tab:selected { background: #303030; } "
			"QTabWidget::pane { border: 0; alighnment: center; position: absolute;} "
			"QTabWidget::tab-bar {alighnment: center;}"
			"QWidget { background: #202020; } "
		);

		tabs->setContentsMargins(0, 0, 0, 0);

		allWin = new QVBoxLayout(container);
		allWin->setSpacing(0);
		allWin->setContentsMargins(0, 0, 0, 0);
		allWin->addWidget(tabs);
		//setLayout(allWin);

		container->resize(500, 300);
		container->show();
	};

private:
	QVBoxLayout* allWin;
	QWidget* stw, * tm;
	
	/*
	
	bool isTimer;

	void changeType() {
		if (isTimer) {
			stw->show();
			allWin->replaceWidget(tm, stw);
			tm->hide();
		}
		else {
			tm->show();
			allWin->replaceWidget(stw, tm);
			stw->hide();
		}
		isTimer = !isTimer;
	};
	*/
};
