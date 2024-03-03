#include "include/widget.h"
#include "source/ui_widget.h"

Widget::Widget (QWidget* parent) : QWidget (parent), ui (new Ui::Widget)
{
    ui->setupUi (this);
    // настройки окна widget
    this->setWindowTitle ("Погода");
    // Значок для окна
    QIcon* icon1 = new QIcon (":/resource/meteo.ico");
    this->setWindowIcon (*icon1);
    // Инициализируем Downloader
    downloader       = new Downloader (this);
    storage_forecast = std::make_unique<Storage_Forecast> ();
    wshow_weather2   = new Widget_Show_Weather_2 ();

    // по нажатию кнопки запускаем получение данных по http
    connect (ui->pushButton_UUWW, &QPushButton::clicked, downloader, [=, this] () {
        downloader->getData ("UUWW");
        // getBufferFromDowloanderToSForecast ();
    });
    // по окончанию получения данных считываем данные из буфера
    connect (ui->pushButton_UUDD, &QPushButton::clicked, downloader, [=, this] () {
        downloader->getData ("UUDD");
    });
    connect (ui->pushButton_UUEE, &QPushButton::clicked, downloader, [=, this] () {
        downloader->getData ("UUEE");
    });
    connect (downloader, &Downloader::onReady, this, &Widget::getBufferFromDowloanderToSForecast);
    connect (downloader, &Downloader::ErrorDownload, downloader, [=, this] () {
        Show_Error (downloader->ErrorString);
    });

    //  запуск запроса по умолчанию
    timer_show_weather = new QTimer (this);
    timer_show_weather->setInterval (600000); // интервал 10 мин Qtimer 1000 ->1сек
    connect (timer_show_weather, &QTimer::timeout, [=, this] () {
        Show_weather ();
    });
    //"Start timer_show_weather" << QTime::currentTime ().toString ();
    timer_show_weather->start ();
}

Widget::~Widget ()
{
    delete ui;
}

void Widget::getBufferFromDowloanderToSForecast ()
{ // забираем буфер и инициализируем класс Storage_Forecast
    if (downloader->buff->data ()) {
        storage_forecast->split_str (std::move (downloader->buff->data ()));
    }
    // название аэропорта
    wshow_weather2->set_Label_Name_Airport (std::move (std::move (storage_forecast->Name_Airport)));
    //// название METAR
    wshow_weather2->set_Label_Text_Raw_METAR (std::move (std::move (storage_forecast->RawMETAR)));
    wshow_weather2->set_Label_Text_METAR (std::move (std::move (storage_forecast->METAR)));
    //// название TAF
    wshow_weather2->set_Label_Text_Raw_TAF (std::move (std::move (storage_forecast->RawTAF)));
    wshow_weather2->set_Label_Text_TAF (std::move (std::move (storage_forecast->TAF)));

    downloader->buff->clear ();
    // показ погоды
    wshow_weather2->move (10, 0);
    wshow_weather2->show ();
}

void Widget::Show_weather ()
{
    // qDebug () << "\nposition_selection" << position_selection << "\n";
    switch (position_selection) {
        case 1:
            emit ui->pushButton_UUWW->clicked ();
            wshow_weather2->move (10, 0);
            break;
        case 2:
            emit ui->pushButton_UUDD->clicked ();
            wshow_weather2->move (300, 0);
            break;
        case 3:
            emit ui->pushButton_UUEE->clicked ();
            wshow_weather2->move (600, 0);
            break;
        default:
            break;
    }

    if (position_selection < 3) {
        position_selection++;
    }
    else {
        position_selection = 1;
    }
}

void Widget::Show_Error (const QString& ErrorMsg)
{
    QMessageBox m (QMessageBox::Information, "Ошибка доступа", ErrorMsg, QMessageBox::NoButton, this);
    m.exec ();
}
