#include "./include/widget_show_weather.h"

Widget_Show_Weather::Widget_Show_Weather (QWidget* parent) : QWidget (parent)
{

    this->resize (100, 100);
    this->setWindowTitle ("Погода в аэропорту");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon = new QIcon (":/resource/meteo.ico");
    this->setWindowIcon (*icon);                     // Значок для окна
    label_name_airport = new QLabel ("aaaaa", this); // название аэропорта
    label_name_airport->setStyleSheet ("QLabel {"
                                       "font-size: 18px; "
                                       "font-weight: bold;"
                                       "color: darkBlue"
                                       "}");
    /*
     * METAR
     */
    label_text_raw_METAR = new QLabel ("aaaaa", this); // raw- текст прогноза
    label_text_raw_METAR->setStyleSheet ("QLabel {"
                                         "font-size: 15px; "
                                         "font-weight: bold;"
                                         "color: royalblue"
                                         "}");

    label_text_METAR = new QLabel ("aaaaa", this); // текст прогноза
    label_text_METAR->setStyleSheet ("QLabel {"
                                     "font-size: 14px; "
                                     "font-weight: bold;"
                                     "}");

    /*
     * TAF
     */
    label_text_raw_TAF = new QLabel ("aaaaa", this); // raw- текст прогноза
    label_text_raw_TAF->setStyleSheet ("QLabel {"
                                       "font-size: 15px; "
                                       "font-weight: bold;"
                                       "color: royalblue"
                                       "}");

    label_text_TAF = new QLabel ("aaaaa", this); // текст прогноза
    label_text_TAF->setStyleSheet ("QLabel {"
                                   "font-size: 14px; "
                                   "font-weight: bold;"
                                   "}");

    label_text_raw_METAR->setTextInteractionFlags (Qt::TextSelectableByMouse);
    label_text_raw_METAR->setFocusPolicy (Qt::StrongFocus);
    label_text_METAR->setTextInteractionFlags (Qt::TextSelectableByMouse);
    label_text_METAR->setFocusPolicy (Qt::StrongFocus);

    label_text_raw_TAF->setTextInteractionFlags (Qt::TextSelectableByMouse);
    label_text_raw_TAF->setFocusPolicy (Qt::StrongFocus);
    label_text_TAF->setTextInteractionFlags (Qt::TextSelectableByMouse);
    label_text_TAF->setFocusPolicy (Qt::StrongFocus);

    QVBoxLayout* vbox = new QVBoxLayout (this);

    vbox->setAlignment (Qt::AlignTop);
    vbox->addWidget (label_name_airport);
    // METAR

    vbox->addWidget (label_text_raw_METAR);
    vbox->addWidget (label_text_METAR);

    // TAF
    vbox->addSpacing (-10);
    vbox->addWidget (label_text_raw_TAF);
    vbox->addSpacing (-20);
    vbox->addWidget (label_text_TAF);

    this->setLayout (vbox);
    this->move (100, 100);

    // Timer
    timer_close_weather = new QTimer (this);
    timer_close_weather->setInterval (120000); // Qtimer 1000 ->1сек
    timer_close_weather->setSingleShot (true);

    connect (timer_close_weather, &QTimer::timeout, [=] {
        close ();
    });
}

Widget_Show_Weather::~Widget_Show_Weather () {}
void Widget_Show_Weather::start_close_timer ()
{

    timer_close_weather->start ();
}
