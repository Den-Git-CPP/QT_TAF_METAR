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
  explicit lb_weather(QWidget *parent = nullptr);
  ~lb_weather();
  void set_name_airport(QString name_airport_);
  void set_text_forecast(QString text_forecast_);

public slots:
  void start_close_timer();

private:
  QLabel *label_name_airport = nullptr;
  QLabel *label_forecast = nullptr;

  QIcon *icon = nullptr;
  QTimer *timer_close_weather = nullptr;
};
