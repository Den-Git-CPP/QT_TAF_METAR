#pragma once
#include "forecast_taf.h"
#include "forecast_title.h"

#include <QObject>
#include <QVector>

class MainTAF {

  public:
    explicit MainTAF ();
    ~MainTAF ();
    Forecast_Title* Title = nullptr;

    QVector<Forecast_TAF> vec_taf{};
    void add_taf (Forecast_TAF inTAF);
};
