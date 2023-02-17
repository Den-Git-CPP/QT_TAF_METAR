#include "forecast_taf.h"

Forecast_TAF::Forecast_TAF () {}

Forecast_TAF::~Forecast_TAF () {}

QString Forecast_TAF::raw_text () const { return this->_raw_text; }

void Forecast_TAF::add_forecast (Forecast in_forecast)
{
    //
    forecasts.push_back (in_forecast);
}
