#include "widget.h"

Widget::Widget (QWidget* parent) : QWidget (parent)
{
    this->resize (180, 70);
    this->setWindowTitle ("Запрос погоды");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon = new QIcon (":/resource/avia.png");
    this->setWindowIcon (*icon); // Значок для окна

    label = new QLabel (this);
    ft    = new QFont ("Arial", 12, QFont::Bold); // Устанавливаем размер шрифта
    pa    = new QPalette ();
    pa->setColor (QPalette::WindowText,
      Qt::darkBlue); // Устанавливаем цвет шрифта

    label->setFont (*ft);
    label->setPalette (*pa);
    label->setAlignment (Qt::AlignCenter);
    label->setText ("Проводим запрос погоды\n по аэропортам.");

    downloader = new Downloader (this); // Инициализируем Downloader
    main_TAF   = new MainTAF (this);
    xmlparser  = new XMLParser (this->main_TAF);
    weather    = new lb_weather (this); // класс запроса погоды

    bt_UUWW = new QPushButton (tr ("Запрос Внуково"), this);
    connect (bt_UUWW, &QPushButton::clicked, downloader, [=] () {
        downloader->set_name_airport ("UUWW");
        downloader->getData ();
    });

    connect (bt_UUWW, &QPushButton::clicked, weather, [=] () {
        weather->start_close_timer ();
    });

    bt_UUDD = new QPushButton (tr ("Запрос Домодедово"), this);
    connect (bt_UUDD, &QPushButton::clicked, downloader, [=] () {
        downloader->set_name_airport ("UUDD");
        downloader->getData ();
    });

    connect (bt_UUDD, &QPushButton::clicked, weather, [=] () {
        weather->start_close_timer ();
    });

    bt_UUEE = new QPushButton (tr ("Запрос Шереметьево"), this);
    connect (bt_UUEE, &QPushButton::clicked, downloader, [=] () {
        downloader->set_name_airport ("UUEE");
        downloader->getData ();
    });
    connect (bt_UUEE, &QPushButton::clicked, weather, [=] () {
        weather->start_close_timer ();
    });

    connect (downloader, &Downloader::onReady, xmlparser, [=] () {
        main_TAF->vec_taf.clear ();

        xmlparser->set_dir_file_with_xml (downloader->get_dir_file_with_xml_for_parser ());
        xmlparser->Read_XML ();
        // qDebug () << "Reading is completed";
        // qDebug () << main_TAF->Title->request_index () << "\t" <<

        //  формируется строка прогноза

        weather->set_name_airport (main_TAF->vec_taf.at (0).station_id ());
        weather->set_text_forecast (forming_text_forecast ());
        // показываем Label
        weather->show ();

        // qDebug () << "Show weather" << QTime::currentTime ().toString (); /*  */
    });

    vbox = new QVBoxLayout (this);
    vbox->addWidget (label);
    vbox->addWidget (bt_UUWW);
    vbox->addWidget (bt_UUDD);
    vbox->addWidget (bt_UUEE);

    this->setLayout (vbox);

    timer_show_weather = new QTimer (this);
    timer_show_weather->setInterval (15000); // интервал 15 сек
    connect (timer_show_weather, &QTimer::timeout, this, &Widget::Show_weather);
    timer_show_weather->start ();
}

Widget::~Widget () {}

QString Widget::forming_text_forecast ()
{
    QString _text_taf = "Время составления прогноза: " + main_TAF->vec_taf.at (0).bulletin_time () + "\nДействует c "
                      + main_TAF->vec_taf.at (0).valid_time_from () + +" по " + main_TAF->vec_taf.at (0).valid_time_to () + "\n"
                      + main_TAF->vec_taf.at (0).raw_text ();
    QString _text_forecasts{ "" };
    for (auto forecast : main_TAF->vec_taf.at (0).forecasts) {
        // forecast.
    }

    return _text_taf + "\n" + _text_forecasts;
}

void Widget::Show_weather ()
{
    switch (position_selection) {
        case 1:
            emit this->bt_UUWW->clicked ();
            position_selection++;
            break;
        case 2:
            emit this->bt_UUDD->clicked ();
            position_selection++;
            break;
        case 3:
            emit this->bt_UUEE->clicked ();
            position_selection = 1;
            break;
    }
}
