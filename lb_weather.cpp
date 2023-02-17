#include "lb_weather.h"

lb_weather::lb_weather (QWidget* parent) : QWidget (parent)
{
    this->resize (300, 80);
    this->setWindowTitle ("Погода в аэропорту");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon = new QIcon (":/resource/avia.png");
    this->setWindowIcon (*icon); // Значок для окна

    label          = new QLabel ();
    label_forecast = new QLabel ();
    label->setText (name_airport);
    label_forecast->setText ("Погода:" + Forecast_on_airport);

    QVBoxLayout* vbox = new QVBoxLayout ();
    vbox->addWidget (label);
    vbox->addWidget (label_forecast);

    this->setLayout (vbox);

    qDebug () << "Show weather" << QTime::currentTime ().toString (); /*  */
    timer_close_weather = new QTimer (this);
    timer_close_weather->setInterval (10000); // интервал 60 сек
    timer_close_weather->setSingleShot (true);

    connect (timer_close_weather, &QTimer::timeout, [=] {
        this->close ();
        qDebug () << "Close weather" << QTime::currentTime ().toString ();
    });

    timer_close_weather->start ();
}

void lb_weather::set_name_airport (QString name_airport_) { name_airport = name_airport_; }
