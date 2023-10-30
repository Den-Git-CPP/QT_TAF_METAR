#pragma once

#include <QColor>
#include <QDebug>
#include <QIcon>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>

#include <QMenu>           //2
#include <QMessageBox>     //3
#include <QSystemTrayIcon> //1

#include "./include/downloader.h"
#include "./include/lb_weather.h"
#include "./include/metar.h"
#include "./include/taf.h"
#include "./include/xmlparser.h"

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();
public slots:
  void changeEvent(QEvent *event);
  void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
  void setTrayIconActions();
  void showTrayIcon();

private:
  // окно запроса погоды
  QLabel *label = nullptr;
  QVBoxLayout *vbox = nullptr;
  QFont *ft = nullptr;
  QPalette *pa = nullptr;
  QIcon *icon1 = nullptr;
  QPushButton *bt_UUWW = nullptr;
  QPushButton *bt_UUDD = nullptr;
  QPushButton *bt_UUEE = nullptr;

  // меню к основному окну запроса погоды
  QMenu *trayIconMenu;
  QAction *minimizeAction;
  QAction *restoreAction;
  QAction *quitAction;
  QSystemTrayIcon *trayIcon;

  // окно погоды
  lb_weather *weather = nullptr;
  QTimer *timer_show_weather = nullptr;

  Downloader *downloader = nullptr;
  XMLParser *xmlparser = nullptr;

  QString forming_text_metar();
  QString forming_text_taf();

  int position_selection{1};
  void Show_weather();
};
