#pragma once

#include <QColor>
#include <QDebug>
#include <QIcon>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "downloader.h"
#include "lb_weather.h"
#include "xmlparser.h"

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 private:
  QLabel *label = nullptr;
  QVBoxLayout *vbox = nullptr;

  QFont *ft = nullptr;
  QPalette *pa = nullptr;
  QIcon *icon = nullptr;
  QPushButton *bt_UUWW = nullptr;
  QPushButton *bt_UUDD = nullptr;
  QPushButton *bt_UUEE = nullptr;

  lb_weather *weather = nullptr;
  QTimer *timer_show_weather = nullptr;
  Downloader *downloader = nullptr;
  XMLParser *xmlparser = nullptr;
  void Show_weather();
};
