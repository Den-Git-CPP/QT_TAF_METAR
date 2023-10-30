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
  void set_name_airport(const QString &name_airport_);
  void set_text_raw_TAF(const QString &raw_TAF);
  void set_text_TAF(const QString &text_TAF);
  void set_text_raw_METAR(const QString &raw_METAR);
  void set_text_METAR(const QString &text_METAR);

public slots:
  void start_close_timer();

private:
  QLabel *label_name_airport = nullptr;
  QLabel *label_text_raw_TAF = nullptr;
  QLabel *label_text_TAF = nullptr;
  QLabel *label_text_raw_METAR = nullptr;
  QLabel *label_text_METAR = nullptr;

  QIcon *icon = nullptr;
  QTimer *timer_close_weather = nullptr;
};
