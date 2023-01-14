#include "lb_weather.h"

lb_weather::lb_weather(QWidget *parent) : QWidget(parent)
{
    this->resize(180,70);
    this->setWindowTitle("Погода в аэропорту");
    this->setWindowFlags(Qt::Window
                         |Qt::WindowCloseButtonHint);

    icon=new QIcon (":/resource/avia.png");
    this->setWindowIcon(*icon); // Значок для окна

    QLabel *label = new QLabel();
    label->setText("Погода в аэропорту.");

    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(label);
    this->setLayout(vbox);

}

