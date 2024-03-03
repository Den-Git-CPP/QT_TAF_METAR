#pragma once

#include <QWidget>
#include <QIcon>
#include "include/downloader.h"
#include "include/storage_forecast.h"
#include "include/widget_show_weather_2.h"

#include <memory>
#include <utility>
#include <iostream>
#include <QMessageBox>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

  public:
    explicit Widget (QWidget* parent = nullptr);
    ~Widget ();
  signals:
    void onReadyShow ();
  private slots:
    void getBufferFromDowloanderToSForecast ();
    void Show_weather ();
    void Show_Error (const QString& ErrorMsg);

  private:
    Ui::Widget* ui;
    // Объявляем объект класса для скачивания данных по http
    Downloader* downloader{ nullptr };
    QTimer* timer_show_weather{ nullptr };

    // Окно показа погоды
    Widget_Show_Weather_2* wshow_weather2{ nullptr };

    int position_selection{ 1 };
    // Объявляем объект класса для хранения прогноза погоды
    std::unique_ptr<Storage_Forecast> storage_forecast{ nullptr };
};
