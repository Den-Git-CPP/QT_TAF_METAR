#include "./include/forecast_taf.h"

Forecast_TAF::Forecast_TAF () {}

Forecast_TAF::~Forecast_TAF () {}

QString Forecast_TAF::raw_text () const { return _raw_text; }
QString Forecast_TAF::station_id () const { return _station_id; }
QString Forecast_TAF::issue_time () const { return _issue_time; }
QString Forecast_TAF::bulletin_time () const { return _bulletin_time; }
QString Forecast_TAF::valid_time_from () const { return _valid_time_from; }
QString Forecast_TAF::valid_time_to () const { return _valid_time_to; }
QString Forecast_TAF::remarks () const { return _remarks; }
QString Forecast_TAF::latitude () const { return _latitude; }
QString Forecast_TAF::longitude () const { return _longitude; }
QString Forecast_TAF::elevation_m () const { return _elevation_m; }
void Forecast_TAF::set_raw_text (const QString& raw_text) { _raw_text = Function::replace_raw_text (raw_text); };
void Forecast_TAF::set_station_id (const QString& station_id) { _station_id = Function::replace_id_staion (station_id); };
void Forecast_TAF::set_issue_time (const QString& issue_time) { _issue_time = Function::replace_time (issue_time); };
void Forecast_TAF::set_bulletin_time (const QString& bulletin_time) { _bulletin_time = Function::replace_time (bulletin_time); };
void Forecast_TAF::set_valid_time_from (const QString& valid_time_from) { _valid_time_from = Function::replace_time (valid_time_from); };
void Forecast_TAF::set_valid_time_to (const QString& valid_time_to) { _valid_time_to = Function::replace_time (valid_time_to); };

void Forecast_TAF::set_remarks (const QString& remarks) { _remarks = remarks; };
void Forecast_TAF::set_latitude (const QString& latitude) { _latitude = latitude; };
void Forecast_TAF::set_longitude (const QString& longitude) { _longitude = longitude; };
void Forecast_TAF::set_elevation_m (const QString& elevation_m) { _elevation_m = elevation_m; };
