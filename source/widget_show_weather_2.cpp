#include "include/widget_show_weather_2.h"
#include "ui_widget_show_weather_2.h"

Widget_Show_Weather_2::Widget_Show_Weather_2 (QWidget* parent) : QWidget (parent), ui (new Ui::Widget_Show_Weather_2)
{
    ui->setupUi (this);

    timer_close_weather = new QTimer (this);
    timer_close_weather->setInterval (120000); // Qtimer 1000 ->1сек
    timer_close_weather->setSingleShot (true);

    connect (timer_close_weather, &QTimer::timeout, [=, this] {
        //      qDebug () << "Close time:" << QTime::currentTime ().toString ();
        close ();
    });
}

Widget_Show_Weather_2::~Widget_Show_Weather_2 ()
{
    delete ui;
}

void Widget_Show_Weather_2::set_Label_Name_Airport (std::string&& in_str_Label_Name_Airport)
{ // Название аэропорта
    std::string str_Label_Name_Airport{ std::move (in_str_Label_Name_Airport) };
    ui->label_name_airport->setText (QString::fromStdString (str_Label_Name_Airport));
}

void Widget_Show_Weather_2::set_Label_Text_Raw_METAR (std::string&& in_str_Label_Text_Raw_METAR)
{
    std::string str_Label_Text_Raw_METAR{ std::move (in_str_Label_Text_Raw_METAR) };
    ui->label_text_raw_METAR->setText (QString::fromStdString (std::move (str_Label_Text_Raw_METAR)));
}

void Widget_Show_Weather_2::set_Label_Text_METAR (std::string&& in_str_Label_Text_METAR)
{
    std::string str_Label_Text_METAR{ std::move (in_str_Label_Text_METAR) };
    ui->label_text_METAR->setText (QString::fromStdString (std::move (str_Label_Text_METAR)));
}

void Widget_Show_Weather_2::set_Label_Text_Raw_TAF (std::string&& in_str_set_Label_Text_Raw_TAF)
{
    std::string str_set_Label_Text_Raw_TAF{ std::move (in_str_set_Label_Text_Raw_TAF) };
    ui->label_text_raw_TAF->setText (QString::fromStdString (std::move (str_set_Label_Text_Raw_TAF)));
}

void Widget_Show_Weather_2::set_Label_Text_TAF (std::string&& in_str_Label_Text_TAF)
{
    std::string str_Label_Text_TAF{ std::move (in_str_Label_Text_TAF) };
    ui->label_text_TAF->setText (QString::fromStdString (std::move (str_Label_Text_TAF)));
}

void Widget_Show_Weather_2::showEvent (QShowEvent* event)
{
    QWidget::showEvent (event);
    // Старт таймера закрытия
    //  qDebug () << "Start time:" << QTime::currentTime ().toString ();
    timer_close_weather->start ();
}
