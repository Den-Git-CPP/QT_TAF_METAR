#pragma once
#include "./include/forecast_taf.h"
#include "./include/forecast_title.h"

#include <memory>
#include <vector>
class TAF {
  public:
    explicit TAF ();
    virtual ~TAF ();

    std::shared_ptr<Forecast_Title> ForecastTitle = nullptr;
    std::vector<std::shared_ptr<Forecast_TAF>> v_forecasttaf{};
};
