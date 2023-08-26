#include "./include/widget.h"

Widget::Widget (QWidget* parent) : QWidget (parent)
{
    this->resize (180, 70);
    this->setWindowTitle ("Запрос погоды");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon1 = new QIcon ("./resource/meteo.ico");
    this->setWindowIcon (*icon1); // Значок для окна

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
    taf        = std::make_shared<TAF> ();
    metar      = std::make_shared<METAR> ();
    xmlparser  = new XMLParser (this);
    weather    = new lb_weather (this); // класс запроса погоды

    bt_UUWW = new QPushButton (tr ("Запрос Внуково"), this);
    connect (bt_UUWW, &QPushButton::clicked, downloader, [=] () {
        downloader->set_name_airport ("UUWW");
        downloader->getDataForecast ();
    });

    connect (bt_UUWW, &QPushButton::clicked, weather, [=] () {
        weather->start_close_timer ();
    });

    bt_UUDD = new QPushButton (tr ("Запрос Домодедово"), this);
    connect (bt_UUDD, &QPushButton::clicked, downloader, [=] () {
        downloader->set_name_airport ("UUDD");
        downloader->getDataForecast ();
    });

    connect (bt_UUDD, &QPushButton::clicked, weather, [=] () {
        weather->start_close_timer ();
    });

    bt_UUEE = new QPushButton (tr ("Запрос Шереметьево"), this);
    connect (bt_UUEE, &QPushButton::clicked, downloader, [=] () {
        downloader->set_name_airport ("UUEE");
        downloader->getDataForecast ();
    });
    connect (bt_UUEE, &QPushButton::clicked, weather, [=] () {
        weather->start_close_timer ();
    });

    connect (downloader, &Downloader::onReady, xmlparser, [=] () {
        xmlparser->set_vec_buf_xml (downloader->get_vec_buf_xml ());
        // xmlparser->set_vec_buf_xml (downloader)->get_vec_buf_xml ();
        //  xmlparser->create_shr_ptr_forecast ();

        // taf->v_forecasttaf.resize (1); // БЕРЕМ ТОЛЬКО ПЕРВЫЙ ЭЛЕМЕНТ

        //  формируется строка прогноза
        // weather->set_name_airport (taf->v_forecasttaf.at (0)->station_id ());
        // weather->set_text_forecast (forming_text_forecast ());
        //  показываем Label
        // weather->show ();
        // qDebug () << "Show weather" << QTime::currentTime ().toString ();
    });

    vbox = new QVBoxLayout (this);
    vbox->addWidget (label);
    vbox->addWidget (bt_UUWW);
    vbox->addWidget (bt_UUDD);
    vbox->addWidget (bt_UUEE);

    this->setLayout (vbox);

    timer_show_weather = new QTimer (this);
    timer_show_weather->setInterval (600000); // интервал 10 мин
    connect (timer_show_weather, &QTimer::timeout, this, &Widget::Show_weather);
    timer_show_weather->start ();
}

Widget::~Widget () {}
QString Widget::forming_text_forecast ()
{
    QString _text_taf = "ПРОГНОЗ СОСТАВЛЕН: " + taf->v_forecasttaf.at (0)->bulletin_time ();
    if (taf->v_forecasttaf.at (0)->valid_time_from () != "") {
        _text_taf.append ("\nДЕЙСТВУЕТ С " + taf->v_forecasttaf.at (0)->valid_time_from () + " ");
    }
    if (taf->v_forecasttaf.at (0)->valid_time_to () != "") {
        _text_taf.append ("ПО " + taf->v_forecasttaf.at (0)->valid_time_to ());
    }
    if (taf->v_forecasttaf.at (0)->raw_text () != "") {
        _text_taf.append ("\n\n" + taf->v_forecasttaf.at (0)->raw_text ());
    }

    QString _text_forecasts{ "" };
    for (auto forecast : taf->v_forecasttaf.at (0)->v_forecasts) {
        if (forecast->fcst_time_from () != "") {
            _text_forecasts.append ("\n\n-В период с " + forecast->fcst_time_from () + " ");
        }
        if (forecast->fcst_time_to () != "") {
            _text_forecasts.append ("по " + forecast->fcst_time_to ());
        }
        if (forecast->change_indicator () != "") {
            _text_forecasts.append ("\n    " + forecast->change_indicator () + " ");
        }
        if (forecast->time_becoming () != "") {
            _text_forecasts.append ("начиная с " + forecast->time_becoming () + " ");
        }
        if (forecast->probability () != "") {
            _text_forecasts.append ("\nс вероятностью" + forecast->probability ());
        }
        if (forecast->wind_dir_degrees () != "") {
            _text_forecasts.append ("\n    Ветер: " + forecast->wind_dir_degrees () + "° ");
        }
        if (forecast->wind_speed_kt () != "") {
            _text_forecasts.append (forecast->wind_speed_kt () + " м/с ");
        }
        if (forecast->wind_gust_kt () != "") {
            _text_forecasts.append (" (порывы " + forecast->wind_gust_kt () + " м/с)");
        };
        if (forecast->wind_shear_hgt_ft_agl () != "") {
            _text_forecasts.append ("\n    Сдвиг ветера на " + forecast->wind_shear_hgt_ft_agl () + "м. ");
        };
        if (forecast->wind_shear_dir_degrees () != "") {
            _text_forecasts.append (forecast->wind_shear_dir_degrees () + "° ");
        };
        if (forecast->wind_shear_speed_kt () != "") {
            _text_forecasts.append (forecast->wind_shear_speed_kt () + " м/с ");
        };
        // видимость
        if (forecast->visibility_statute_mi () != "") {
            _text_forecasts.append ("\n    Видимость: " + forecast->visibility_statute_mi () + " м. ");
        };

        if (!forecast->tuple_list_sky_condition ().empty ()) {

            for (auto elem : forecast->tuple_list_sky_condition ()) {
                _text_forecasts.append ("\n    ").append (QString (std::get<0> (elem))).append ("\t");
                _text_forecasts.append (QString (std::get<1> (elem))).append (" ");
                _text_forecasts.append (QString (std::get<2> (elem))).append (" ");
            }
        };

        if (forecast->altim_in_hg () != "") {
            _text_forecasts.append ("\n    Нижняя граница облачности:" + forecast->altim_in_hg () + " м. ");
        };
        if (forecast->vert_vis_ft () != "") {
            _text_forecasts.append ("\n    Вертикальная видимость:" + forecast->vert_vis_ft () + " м. ");
        };
        if (forecast->wx_string () != "") {
            _text_forecasts.append ("\n    " + forecast->wx_string () + " ");
        };
        if (forecast->not_decoded () != "") {
            // НЕ ВЫВОДИТЬ :_text_forecasts.append ("\n Данные не расшифрованы:" + forecast->not_decoded () + " ");
        };

        if (!forecast->turbulence_list_condition ().empty ()) {
            for (auto elem : forecast->turbulence_list_condition ()) {
                _text_forecasts.append ("\n    ").append (QString (std::get<0> (elem))).append (" ");
                _text_forecasts.append (QString (std::get<1> (elem))).append (" ");
                _text_forecasts.append (QString (std::get<2> (elem))).append (" ");
            }
        };
        if (!forecast->icing_list_condition ().empty ()) {
            for (auto elem : forecast->icing_list_condition ()) {
                _text_forecasts.append ("\n    ").append (QString (std::get<0> (elem))).append (" ");
                _text_forecasts.append (QString (std::get<1> (elem))).append (" ");
                _text_forecasts.append (QString (std::get<2> (elem))).append (" ");
            }
        };
    }
    return _text_taf + _text_forecasts;
    ;
}
void Widget::Show_weather ()
{
    switch (position_selection) {
        case 1:
            emit this->bt_UUWW->clicked ();
            weather->move (10, 0);
            position_selection++;
            break;
        case 2:
            emit this->bt_UUDD->clicked ();
            weather->move (300, 0);
            position_selection++;
            break;
        case 3:
            emit this->bt_UUEE->clicked ();
            weather->move (600, 0);
            position_selection = 1;

            break;
    }
}
