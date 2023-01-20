#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{   this->resize(180,70);
    this->setWindowTitle("Запрос погоды");
    this->setWindowFlags(Qt::Window
                         |Qt::WindowCloseButtonHint);

    icon=new QIcon (":/resource/avia.png");
    this->setWindowIcon(*icon); // Значок для окна

    label = new QLabel();
    ft=     new QFont("Arial", 12, QFont::Bold); // Устанавливаем размер шрифта
    pa=     new QPalette();
    pa->setColor(QPalette::WindowText,Qt::darkBlue); // Устанавливаем цвет шрифта

    label->setFont(*ft);
    label->setPalette(*pa);
    label->setAlignment(Qt::AlignCenter);
    label->setText("Проводим запрос погоды\n по аэропортам.");

    bt_UUWW= new QPushButton(tr("Запрос Внуково"),this);
    bt_UUDD= new QPushButton(tr("Запрос Домодедово"),this);
    bt_UUEE= new QPushButton(tr("Запрос Шереметьево"),this);

    vbox= new QVBoxLayout();
    vbox->addWidget(label);
    vbox->addWidget(bt_UUWW);
    vbox->addWidget(bt_UUDD);
    vbox->addWidget(bt_UUEE);

    this->setLayout(vbox);

    timer_show_weather =new QTimer(this);
    timer_show_weather->setInterval(6000);// интервал 6 сек
    connect(timer_show_weather,&QTimer::timeout,this,&Widget::Show_weather);
    timer_show_weather->start();

}

Widget::~Widget()
{
  //  delete weather;
}

void Widget::Show_weather()

{   weather= new lb_weather();// класс запроса погоды
    weather->show();

}
