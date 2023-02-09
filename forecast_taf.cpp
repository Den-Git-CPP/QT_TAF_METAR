#include "forecast_taf.h"

Forecast_TAF::Forecast_TAF (QObject* parent) { forecast = new Forecast (); }

void Forecast_TAF::print ()
{
    qDebug () << _raw_text << "\n"
              << _station_id << "\n"
              << _issue_time << "\n"
              << _bulletin_time << "\n"
              << _valid_time_from << "\n"
              << _valid_time_to << "\n"
              << _remarks << "\n"
              << _latitude << "\n"
              << _longitude << "\n"
              << _elevation_m << "\n";
    qDebug () << "Forecast_TAF END";
}
