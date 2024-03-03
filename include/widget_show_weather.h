#pragma once
#include "include/forecast.h"

#include <QIcon>
#include <QLabel>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class Widget_Show_Weather : public QWidget {
    Q_OBJECT
  public:
    explicit Widget_Show_Weather (QWidget* parent = nullptr);
    ~Widget_Show_Weather ();

    QLabel* label_name_airport{ nullptr };
    QLabel* label_text_raw_METAR{ nullptr };
    QLabel* label_text_METAR{ nullptr };
    QLabel* label_text_raw_TAF{ nullptr };
    QLabel* label_text_TAF{ nullptr };
  public slots:
    void start_close_timer ();

  private:
    QIcon* icon = nullptr;
    QTimer* timer_close_weather;
};
