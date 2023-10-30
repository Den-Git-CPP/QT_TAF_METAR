#include "./include/lb_weather.h"

lb_weather::lb_weather(QWidget *parent) : QWidget(parent) {

  this->resize(100, 100);
  this->setWindowTitle("Погода в аэропорту");
  this->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);

  icon = new QIcon(":/resource/meteo.ico");
  this->setWindowIcon(*icon);            // Значок для окна
  label_name_airport = new QLabel(this); // название аэропорта
  label_name_airport->setStyleSheet("QLabel {"
                                    "font-size: 18px; "
                                    "font-weight: bold;"
                                    "color: darkBlue"
                                    "}");
  /*
   * TAF
   */
  label_text_raw_TAF = new QLabel(this); // raw- текст прогноза
  label_text_raw_TAF->setStyleSheet("QLabel {"
                                    "font-size: 15px; "
                                    "font-weight: bold;"
                                    "color: royalblue"
                                    "}");

  label_text_TAF = new QLabel(this); // текст прогноза
  label_text_TAF->setStyleSheet("QLabel {"
                                "font-size: 14px; "
                                "font-weight: bold;"
                                "}");

  label_text_TAF->setTextInteractionFlags(Qt::TextSelectableByMouse);
  label_text_TAF->setFocusPolicy(Qt::StrongFocus);

  /*
   * METAR
   */

  label_text_raw_METAR = new QLabel(this); // raw- текст прогноза
  label_text_raw_METAR->setStyleSheet("QLabel {"
                                      "font-size: 15px; "
                                      "font-weight: bold;"
                                      "color: royalblue"
                                      "}");

  label_text_METAR = new QLabel(this); // текст прогноза
  label_text_METAR->setStyleSheet("QLabel {"
                                  "font-size: 14px; "
                                  "font-weight: bold;"
                                  "}");

  label_text_METAR->setTextInteractionFlags(Qt::TextSelectableByMouse);
  label_text_METAR->setFocusPolicy(Qt::StrongFocus);

  QVBoxLayout *vbox = new QVBoxLayout(this);

  vbox->setAlignment(Qt::AlignTop);
  vbox->addWidget(label_name_airport);
  vbox->addWidget(label_text_raw_METAR);
  vbox->addWidget(label_text_METAR);
  vbox->addWidget(label_text_raw_TAF);
  vbox->addWidget(label_text_TAF); //, 1, Qt::AlignTop
  this->setLayout(vbox);
  this->move(100, 100);
}

lb_weather::~lb_weather() {}

void lb_weather::set_name_airport(const QString &name_airport_) {
  label_name_airport->setText("АЭРОПОРТ: " + name_airport_);
  this->setWindowTitle("Погода в аэропорту " + name_airport_);
}

void lb_weather::set_text_raw_TAF(const QString &raw_TAF) {
  label_text_raw_TAF->setText(raw_TAF);
}

void lb_weather::set_text_TAF(const QString &text_TAF) {
  label_text_TAF->setText(text_TAF);
}

void lb_weather::set_text_raw_METAR(const QString &raw_METAR) {
  label_text_raw_METAR->setText(raw_METAR);
}

void lb_weather::set_text_METAR(const QString &text_METAR) {
  label_text_METAR->setText(text_METAR);
}

void lb_weather::start_close_timer() {
  timer_close_weather = new QTimer(this);
  timer_close_weather->setInterval(120000); // Qtimer 1000 ->1сек
  timer_close_weather->setSingleShot(true);

  connect(timer_close_weather, &QTimer::timeout, [=] {
    this->close();
    qDebug() << "Close weather" << QTime::currentTime().toString();
  });

  timer_close_weather->start();
}
