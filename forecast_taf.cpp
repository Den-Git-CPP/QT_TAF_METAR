#include "forecast_taf.h"

Forecast_TAF::Forecast_TAF() {}

Forecast_TAF::~Forecast_TAF() {}

QString Forecast_TAF::raw_text() const { return this->_raw_text; }
QString Forecast_TAF::station_id() const { return this->_station_id; }
QString Forecast_TAF::issue_time() const { return this->_issue_time; }
QString Forecast_TAF::bulletin_time() const { return this->_bulletin_time; }
QString Forecast_TAF::valid_time_from() const { return this->_valid_time_from; }
QString Forecast_TAF::valid_time_to() const { return this->_valid_time_to; }
QString Forecast_TAF::remarks() const { return this->_remarks; }
QString Forecast_TAF::latitude() const { return this->_latitude; }
QString Forecast_TAF::longitude() const { return this->_longitude; }
QString Forecast_TAF::elevation_m() const { return this->_elevation_m; }
void Forecast_TAF::set_raw_text(const QString &raw_text) {
  this->_raw_text = raw_text;
  Function::replace_raw_text(_raw_text);
};
void Forecast_TAF::set_station_id(const QString &station_id) {
  this->_station_id = station_id;
  Function::replace_id_staion(_station_id);
};
void Forecast_TAF::set_issue_time(const QString &issue_time) {
  this->_issue_time = issue_time;
};
void Forecast_TAF::set_bulletin_time(const QString &bulletin_time) {
  this->_bulletin_time = bulletin_time;
};
void Forecast_TAF::set_valid_time_from(const QString &valid_time_from) {
  this->_valid_time_from = valid_time_from;
};
void Forecast_TAF::set_valid_time_to(const QString &valid_time_to) {
  this->_valid_time_to = valid_time_to;
};
void Forecast_TAF::set_remarks(const QString &remarks) {
  this->_remarks = remarks;
};
void Forecast_TAF::set_latitude(const QString &latitude) {
  this->_latitude = latitude;
};
void Forecast_TAF::set_longitude(const QString &longitude) {
  this->_longitude = longitude;
};
void Forecast_TAF::set_elevation_m(const QString &elevation_m) {
  this->_elevation_m = elevation_m;
};
void Forecast_TAF::add_forecast(Forecast in_forecast) {
  //
  forecasts.push_back(in_forecast);
};
