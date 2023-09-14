#include "./include/taf.h"

TAF::TAF ()
{
    // ForecastTitle = std::make_unique<Forecast_Title> ();
    ForecastTAF = std::make_unique<Forecast_TAF> ();
}
TAF::~TAF () {}
