#include "lb_weather.h"

lb_weather::lb_weather(QWidget *parent) 
: QWidget(parent){
  this->resize(180, 70);
  this->setWindowTitle("Погода в аэропорту");
  this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

  icon = new QIcon(":/resource/avia.png");
  this->setWindowIcon(*icon); // Значок для окна

  QLabel *label = new QLabel();
  label->setText("Погода в аэропорту." + name_airport);

  QVBoxLayout *vbox = new QVBoxLayout();
  vbox->addWidget(label);
  this->setLayout(vbox);

  qDebug() << "Show weather" << QTime::currentTime().toString(); /*  */
  timer_close_weather = new QTimer(this);
  timer_close_weather->setInterval(2000); // интервал 2 сек
  timer_close_weather->setSingleShot(true);

  connect(timer_close_weather, &QTimer::timeout, [=] {
    this->close();
    qDebug() << "Close weather" << QTime::currentTime().toString();
  });
  timer_close_weather->start();
}
