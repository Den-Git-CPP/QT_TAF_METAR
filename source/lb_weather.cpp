#include "./include/lb_weather.h"

lb_weather::lb_weather (QWidget* parent) : QWidget (parent)
{

    this->resize (100, 100);
    this->setWindowTitle ("Погода в аэропорту");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon = new QIcon (":/resource/meteo.ico");
    this->setWindowIcon (*icon); // Значок для окна
    label_name_airport = new QLabel (this);
    label_name_airport->setStyleSheet ("QLabel {"
                                       "font-size: 18px; "
                                       "font-weight: bold;"
                                       "color: darkBlue"
                                       "}");

    label_forecast = new QLabel (this);
    label_forecast->setStyleSheet ("QLabel {"
                                   "font-size: 14px; "
                                   "font-weight: bold;"
                                   "}");

    label_forecast->setTextInteractionFlags (Qt::TextSelectableByMouse);
    label_forecast->setFocusPolicy (Qt::StrongFocus);

    QVBoxLayout* vbox = new QVBoxLayout (this);

    vbox->setAlignment (Qt::AlignTop);
    vbox->setContentsMargins (5, 1, 5, 0);
    vbox->addWidget (label_name_airport, 1, Qt::AlignTop);
    vbox->addSpacing (1);
    vbox->addWidget (label_forecast, 1, Qt::AlignTop);
    vbox->addStretch (5);
    this->setLayout (vbox);

    this->move (100, 100);
}

lb_weather::~lb_weather () {}

void lb_weather::set_name_airport (QString name_airport_)
{
    label_name_airport->setText ("АЭРОПОРТ: " + name_airport_);
    this->setWindowTitle ("Погода в аэропорту " + name_airport_);
}

void lb_weather::set_text_forecast (QString text_forecast_)
{
    label_forecast->setText (text_forecast_);
}

void lb_weather::start_close_timer ()
{
    timer_close_weather = new QTimer (this);
    timer_close_weather->setInterval (120000); // Qtimer 1000 ->1сек
    timer_close_weather->setSingleShot (true);

    connect (timer_close_weather, &QTimer::timeout, [=] {
        this->close ();
        qDebug () << "Close weather" << QTime::currentTime ().toString ();
    });

    timer_close_weather->start ();
}
