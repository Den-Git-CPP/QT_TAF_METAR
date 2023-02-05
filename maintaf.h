#pragma once
#include "forecast_taf.h"
#include "forecast_title.h"

#include <QObject>

class MainTAF : public QObject {
    Q_OBJECT
  public:
    explicit MainTAF (QObject* parent = nullptr);
    Forecast_Title* forecast_Title = nullptr;
    Forecast_TAF* forecast_TAF     = nullptr;

  signals:
};
