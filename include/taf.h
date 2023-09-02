#pragma once
#include "./include/forecast_taf.h"
#include "./include/forecast_title.h"

#include <memory>
#include <vector>
class TAF {
  public:
    explicit TAF ();
    ~TAF ();

    std::unique_ptr<Forecast_Title> ForecastTitle = nullptr;
    std::unique_ptr<Forecast_TAF> ForecastTAF     = nullptr;
};
