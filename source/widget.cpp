#include "./include/widget.h"

Widget::Widget (QWidget* parent) : QWidget (parent)
{ //
    this->resize (180, 70);
    this->setWindowTitle ("Запрос погоды");
    this->setWindowFlags (Qt::Window | Qt::WindowCloseButtonHint);

    icon1 = new QIcon ("./resource/meteo.ico");
    this->setWindowIcon (*icon1);                  // Значок для окна

    label = new QLabel (this);
    ft    = new QFont ("Arial", 12, QFont::Bold); // Устанавливаем размер шрифта
    pa    = new QPalette ();
    pa->setColor (QPalette::WindowText,
      Qt::darkBlue);                              // Устанавливаем цвет шрифта

    label->setFont (*ft);
    label->setPalette (*pa);
    label->setAlignment (Qt::AlignCenter);
    label->setText ("Проводим запрос погоды\n по аэропортам.");

    downloader = new Downloader (this); // Инициализируем Downloader
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

    // передача вектора с буфером в парсер
    connect (downloader, &Downloader::onReady, xmlparser, [=] () {
        xmlparser->set_vec_buf_xml (downloader->get_vec_buf_xml ());
        xmlparser->fill_u_ptr_Forecast_METAR_TAF ();
        //  формируется строка прогноза
        weather->set_name_airport (xmlparser->taf->station_id ());
        weather->set_text_forecast (forming_text_forecast ());
        //  показываем Label
        weather->show ();
    });

    vbox = new QVBoxLayout (this);
    vbox->addWidget (label);
    vbox->addWidget (bt_UUWW);
    vbox->addWidget (bt_UUDD);
    vbox->addWidget (bt_UUEE);
    this->setLayout (vbox);
    // меню трея
    this->setTrayIconActions ();
    this->showTrayIcon ();

    timer_show_weather = new QTimer (this);
    timer_show_weather->setInterval (600000); // интервал 10 мин Qtimer 1000 ->1сек
    connect (timer_show_weather, &QTimer::timeout, this, &Widget::Show_weather);
    timer_show_weather->start ();
}

Widget::~Widget () {}

void Widget::changeEvent (QEvent* event)
{
    if (isMinimized ()) {
        this->hide ();
    }
}

void Widget::trayIconActivated (QSystemTrayIcon::ActivationReason reason)
{

    switch (reason) {
        case QSystemTrayIcon::Trigger: //
            setVisible (!isVisible ());
        default:
            break;
    }
}

void Widget::setTrayIconActions ()
{
    // контекстное меню для нашего значка
    minimizeAction = new QAction ("Свернуть", this);
    restoreAction  = new QAction ("Восстановить", this);
    quitAction     = new QAction ("Выход", this);

    // Connecting actions to slots...
    connect (minimizeAction, SIGNAL (triggered ()), this, SLOT (hide ()));
    connect (restoreAction, SIGNAL (triggered ()), this, SLOT (showNormal ()));
    connect (quitAction, SIGNAL (triggered ()), this, SLOT (close ()));

    // Setting system tray's icon menu...
    trayIconMenu = new QMenu (this);
    trayIconMenu->addAction (minimizeAction);
    trayIconMenu->addAction (restoreAction);
    trayIconMenu->addAction (quitAction);
}

void Widget::showTrayIcon ()
{
    // Создаём экземпляр класса и задаём его свойства...
    trayIcon = new QSystemTrayIcon (this);
    QIcon trayImage (":/resource/meteo.ico");
    trayIcon->setIcon (trayImage);
    trayIcon->setContextMenu (trayIconMenu);

    // Подключаем обработчик клика по иконке...
    connect (trayIcon, SIGNAL (activated (QSystemTrayIcon::ActivationReason)), //
      this, SLOT (trayIconActivated (QSystemTrayIcon::ActivationReason)));

    // Выводим значок...
    trayIcon->show ();
}
QString Widget::forming_text_forecast ()
{
    QString text_metar{};

    if (!xmlparser->metar->getObservation_time ().isEmpty ()) {
        text_metar.append ("ФАКТИЧЕСКАЯ за " + xmlparser->metar->getObservation_time ());
    };
    if (!xmlparser->metar->getRaw_text ().isEmpty ()) {
        text_metar.append ("\n" + xmlparser->metar->getRaw_text ());
    };
    if (!xmlparser->metar->getWind_dir_degrees ().isEmpty ()) {
        text_metar.append ("\nВетер: " + xmlparser->metar->getWind_dir_degrees () + "°");
    };
    if (!xmlparser->metar->getWind_speed_kt ().isEmpty ()) {
        text_metar.append (" " + xmlparser->metar->getWind_speed_kt () + "м/с");
    };
    if (!xmlparser->metar->getVisibility_statute_mi ().isEmpty ()) {
        text_metar.append ("\nВидимость: ").append (xmlparser->metar->getVisibility_statute_mi ()).append ("м");
    };
    if (!xmlparser->metar->getVert_vis_ft ().isEmpty ()) {
        text_metar.append ("\nВертикальная видимость:" + xmlparser->metar->getVert_vis_ft ());
    };
    if (!xmlparser->metar->getTuple_list_sky_condition ().isEmpty ()) {
        for (auto elem : xmlparser->metar->getTuple_list_sky_condition ()) {
            text_metar.append ("\n" + QString (std::get<0> (elem))).append (" ");
            text_metar.append (QString (std::get<1> (elem))).append (" ");
            text_metar.append (QString (std::get<2> (elem))).append (" ");
        }
    };
    if (!xmlparser->metar->getTemp_c ().isEmpty ()) {
        text_metar.append ("\nТемпература: " + xmlparser->metar->getTemp_c () + "°C");
    };
    if (!xmlparser->metar->getDwepoint_c ().isEmpty ()) {
        text_metar.append ("\nТочка россы: " + xmlparser->metar->getDwepoint_c () + "°C");
    };
    if (!xmlparser->metar->getAltim_in_hg_hPa ().isEmpty ()) {
        text_metar.append ("\nQNH: " + xmlparser->metar->getAltim_in_hg_hPa ());
        text_metar.append (" (" + xmlparser->metar->getAltim_in_hg_mmHg () + " мм.рт.ст.)");
    };
    if (!xmlparser->metar->getSnow_in ().isEmpty ()) {
        text_metar.append ("\nГлубина снега на земле:" + xmlparser->metar->getSnow_in ());
    };
    // TAF
    QString text_taf{};
    if (xmlparser->taf->valid_time_from () != "") {
        text_taf.append ("\nПРОГНОЗ НА ПЕРИОД С " + xmlparser->taf->valid_time_from () + " ");
    }
    if (xmlparser->taf->valid_time_to () != "") {
        text_taf.append (" ПО " + xmlparser->taf->valid_time_to ()).append (" \n");
    }
    if (xmlparser->taf->raw_text () != "") {
        text_taf.append (xmlparser->taf->raw_text ());
    }
    for (const auto& forecast : xmlparser->taf->v_forecasts) {

        if (forecast->fcst_time_from () != "") {
            text_taf.append ("\n\n-В период с " + forecast->fcst_time_from () + " ");
        }
        if (forecast->fcst_time_to () != "") {
            text_taf.append ("по " + forecast->fcst_time_to ());
        }
        if (forecast->change_indicator () != "") {
            text_taf.append ("\n    " + forecast->change_indicator () + " ");
        }
        if (forecast->time_becoming () != "") {
            text_taf.append ("начиная с " + forecast->time_becoming () + " ");
        }
        if (forecast->probability () != "") {
            text_taf.append ("\nс вероятностью" + forecast->probability ());
        }
        if (forecast->wind_dir_degrees () != "") {
            text_taf.append ("\n    Ветер: " + forecast->wind_dir_degrees () + "° ");
        }
        if (forecast->wind_speed_kt () != "") {
            text_taf.append (forecast->wind_speed_kt () + " м/с ");
        }
        if (forecast->wind_gust_kt () != "") {
            text_taf.append (" (порывы " + forecast->wind_gust_kt () + " м/с)");
        };
        if (forecast->wind_shear_hgt_ft_agl () != "") {
            text_taf.append ("\n    Сдвиг ветера на " + forecast->wind_shear_hgt_ft_agl () + "м. ");
        };
        if (forecast->wind_shear_dir_degrees () != "") {
            text_taf.append (forecast->wind_shear_dir_degrees () + "° ");
        };
        if (forecast->wind_shear_speed_kt () != "") {
            text_taf.append (forecast->wind_shear_speed_kt () + " м/с ");
        };
        if (forecast->visibility_statute_mi () != "") {
            text_taf.append ("\n    Видимость: " + forecast->visibility_statute_mi () + " м. ");
        };
        if (!forecast->tuple_list_sky_condition ().empty ()) {
            for (auto elem : forecast->tuple_list_sky_condition ()) {
                text_taf.append ("\n    ").append (QString (std::get<0> (elem))).append ("\t");
                text_taf.append (QString (std::get<1> (elem))).append (" ");
                text_taf.append (QString (std::get<2> (elem))).append (" ");
            }
        };

        if (forecast->altim_in_hg () != "") {
            text_taf.append ("\n    Нижняя граница облачности:" + forecast->altim_in_hg () + " м. ");
        };
        if (forecast->vert_vis_ft () != "") {
            text_taf.append ("\n    Вертикальная видимость:" + forecast->vert_vis_ft () + " м. ");
        };
        if (forecast->wx_string () != "") {
            text_taf.append ("\n    " + forecast->wx_string () + " ");
        };

        if (!forecast->turbulence_list_condition ().empty ()) {
            for (auto elem : forecast->turbulence_list_condition ()) {
                text_taf.append ("\n    ").append (QString (std::get<0> (elem))).append (" ");
                text_taf.append (QString (std::get<1> (elem))).append (" ");
                text_taf.append (QString (std::get<2> (elem))).append (" ");
            }
        };
        if (!forecast->icing_list_condition ().empty ()) {
            for (auto elem : forecast->icing_list_condition ()) {
                text_taf.append ("\n    ").append (QString (std::get<0> (elem))).append (" ");
                text_taf.append (QString (std::get<1> (elem))).append (" ");
                text_taf.append (QString (std::get<2> (elem))).append (" ");
            }
        };
    }
    return text_metar + "\n" + text_taf;
}
void Widget::Show_weather ()
{
    qDebug () << "Show weather" << QTime::currentTime ().toString ();
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
