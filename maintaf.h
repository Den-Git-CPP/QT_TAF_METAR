#pragma once
#include "forecast_taf.h"
#include "forecast_title.h"

#include <QObject>
#include <QVector>

class MainTAF : public QObject {
  Q_OBJECT
public:
  explicit MainTAF(QObject *parent = nullptr);
  ~MainTAF();
  Forecast_Title *forecast_Title = nullptr;
  Forecast_TAF *forecast_TAF = nullptr;
  QVector<Forecast_TAF *> Vec_All_TAFF{};

signals:
};
