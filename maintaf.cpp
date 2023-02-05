#include "maintaf.h"

MainTAF::MainTAF (QObject* parent) : QObject (parent)
{
    forecast_Title = new Forecast_Title;
    forecast_TAF   = new Forecast_TAF;
}
