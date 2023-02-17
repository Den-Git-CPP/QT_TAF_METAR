#pragma once
#include <QIcon>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class lb_weather : public QWidget {
    Q_OBJECT
  public:
    explicit lb_weather (QWidget* parent = nullptr);
    void set_name_airport (QString name_airport_);
    QLabel* label          = nullptr;
    QLabel* label_forecast = nullptr;

  private:
    QString name_airport{ "" };
    QString Forecast_on_airport{ "" };

    QIcon* icon                 = nullptr;
    QTimer* timer_close_weather = nullptr;
};
