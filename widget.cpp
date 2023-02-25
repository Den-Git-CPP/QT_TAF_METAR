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

    //    timer_show_weather = new QTimer (this);
    //    timer_show_weather->setInterval (15000); // интервал 15 сек
    //    connect (timer_show_weather, &QTimer::timeout, this,
    //    &Widget::Show_weather); timer_show_weather->start ();
}

Widget::~Widget () {}
QString Widget::forming_text_forecast ()
{
    QString _text_taf = "ПРОГНОЗ СОСТАВЛЕН: " + main_TAF->vec_taf.at (0).bulletin_time ();

    if (main_TAF->vec_taf.at (0).valid_time_from () != "") {
        _text_taf.append ("\nДЕЙСТВУЕТ С " + main_TAF->vec_taf.at (0).valid_time_from () + " ");
    }
    if (main_TAF->vec_taf.at (0).valid_time_to () != "") {
        _text_taf.append ("ПО " + main_TAF->vec_taf.at (0).valid_time_to ());
    }
    if (main_TAF->vec_taf.at (0).raw_text () != "") {
        _text_taf.append ("\n\n" + main_TAF->vec_taf.at (0).raw_text ());
    }

    QString _text_forecasts{ "" }, _text_forecast_tmp{ "" };
    for (auto forecast : main_TAF->vec_taf.at (0).forecasts) {
        if (forecast.fcst_time_from () != "") {
            _text_forecast_tmp.append ("\n\n-В период с " + forecast.fcst_time_from () + " ");
        }
        if (forecast.fcst_time_to () != "") {
            _text_forecast_tmp.append ("по " + forecast.fcst_time_to ());
        }
        if (forecast.change_indicator () != "") {
            _text_forecast_tmp.append ("\n    " + forecast.change_indicator () + " ");
        }
        if (forecast.time_becoming () != "") {
            _text_forecast_tmp.append ("начиная с " + forecast.time_becoming () + " ");
        }
        if (forecast.probability () != "") {
            _text_forecast_tmp.append ("\nс вероятностью" + forecast.probability ());
        }
        if (forecast.wind_dir_degrees () != "") {
            _text_forecast_tmp.append ("\n    Ветер: " + forecast.wind_dir_degrees () + "° ");
        }
        if (forecast.wind_speed_kt () != "") {
            _text_forecast_tmp.append (forecast.wind_speed_kt () + " м/с ");
        }
        if (forecast.wind_gust_kt () != "") {
            _text_forecast_tmp.append (" (порывы " + forecast.wind_gust_kt () + " м/с)");
        };
        if (forecast.wind_shear_hgt_ft_agl () != "") {
            _text_forecast_tmp.append ("\n    Сдвиг ветера на " + forecast.wind_shear_hgt_ft_agl () + "м. ");
        };
        if (forecast.wind_shear_dir_degrees () != "") {
            _text_forecast_tmp.append (forecast.wind_shear_dir_degrees () + "° ");
        };
        if (forecast.wind_shear_speed_kt () != "") {
            _text_forecast_tmp.append (forecast.wind_shear_speed_kt () + " м/с ");
        };
        // видимость
        if (forecast.visibility_statute_mi () != "") {
            _text_forecast_tmp.append ("\n    Видимость: " + forecast.visibility_statute_mi () + " м. ");
        };
        if (forecast.altim_in_hg () != "") {
            _text_forecast_tmp.append ("\n    Нижняя граница облачности:" + forecast.altim_in_hg () + " м. ");
        };
        if (forecast.vert_vis_ft () != "") {
            _text_forecast_tmp.append ("\n    Вертикальная видимость:" + forecast.vert_vis_ft () + " м. ");
        };
        if (forecast.wx_string () != "") {
            _text_forecast_tmp.append ("\n    " + forecast.wx_string () + " ");
        };
        if (forecast.not_decoded () != "") {
            // НЕ ВЫВОДИТЬ :_text_forecast_tmp.append ("\n Данные не расшифрованы:" + forecast.not_decoded () + " ");
        };
    }
    return _text_taf + _text_forecast_tmp;
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
