#include "lb_weather.h"

lb_weather::lb_weather (QWidget* parent) : QWidget (parent)
{
    this->resize (300, 80);
    this->setWindowTitle ("Погода в аэропорту");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon = new QIcon (":/resource/avia.png");
    this->setWindowIcon (*icon); // Значок для окна
                                 // style

    label_name_airport = new QLabel (this);
    label_forecast     = new QLabel ("Погода:", this);

    QVBoxLayout* vbox = new QVBoxLayout (this);
    vbox->addWidget (label_name_airport);
    vbox->addWidget (label_forecast);
    this->setLayout (vbox);
}

lb_weather::~lb_weather () {}

void lb_weather::set_name_airport (QString name_airport_) { label_name_airport->setText (name_airport_); }

void lb_weather::set_text_forecast (QString text_forecast_) { label_forecast->setText ("Погода:" + text_forecast_); }

void lb_weather::start_close_timer ()
{
    timer_close_weather = new QTimer (this);
    timer_close_weather->setInterval (10000); // интервал 10 сек
    timer_close_weather->setSingleShot (true);

    connect (timer_close_weather, &QTimer::timeout, [=] {
        this->close ();
        qDebug () << "Close weather" << QTime::currentTime ().toString ();
    });

    timer_close_weather->start ();
}
