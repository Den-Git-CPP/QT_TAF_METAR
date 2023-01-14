#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>

class lb_weather : public QWidget
{
    Q_OBJECT
public:
    explicit lb_weather(QWidget *parent = nullptr);

signals:
private:
    QIcon *icon=nullptr;
};

