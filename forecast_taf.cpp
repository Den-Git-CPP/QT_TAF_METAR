#include "forecast_taf.h"

Forecast_TAF::Forecast_TAF () {}

Forecast_TAF::~Forecast_TAF () {}

void Forecast_TAF::add_forecast (Forecast in_forecast)
{
    //
    forecasts.push_back (in_forecast);
}
