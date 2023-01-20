#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QTimer>
#include <QTime>

class lb_weather : public QWidget
{
    Q_OBJECT
public:
    explicit lb_weather(QWidget *parent = nullptr);

signals:
private:
    QIcon *icon=nullptr;
    QTimer* timer_close_weather =nullptr;
    QString name_airport{""};

};

