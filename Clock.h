#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Clock.h"

class Clock : public QMainWindow
{
    Q_OBJECT

public:
    Clock(QWidget *parent = Q_NULLPTR);

private:
    Ui::ClockClass ui;
};
