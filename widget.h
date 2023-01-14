#pragma once

#include <QWidget>
#include <QLabel>
#include <QPalette>
#include <QColor>
#include <QIcon>
#include <QVBoxLayout>
#include <QTimer>
#include <QTime>
#include <QDebug>

#include "lb_weather.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QLabel *label=nullptr;
    QVBoxLayout *vbox=nullptr;

    QFont *ft=nullptr;
    QPalette *pa=nullptr;
    QIcon *icon=nullptr;

    lb_weather *weather=nullptr;
    QTimer* timer_show_weather =nullptr;
    QTimer* timer_close_weather =nullptr;

    void Show_weather();
};
