#include "./include/forecast_title.h"

Forecast_Title::Forecast_Title () {}
Forecast_Title::~Forecast_Title () {}

QString Forecast_Title::request_index () const { return _request_index; }
QString Forecast_Title::name () const { return _name; }
QString Forecast_Title::type () const { return _type; }
QString Forecast_Title::time_taken_ms () const { return _time_taken_ms; }
QString Forecast_Title::num_results () const { return _num_results; }

void Forecast_Title::set_request_index (const QString& request_index) { _request_index = request_index; }
void Forecast_Title::set_name (const QString& name) { _name = name; }
void Forecast_Title::set_type (const QString& type) { _type = type; }
void Forecast_Title::set_time_taken_ms (const QString& time_taken_ms) { _time_taken_ms = time_taken_ms; }
void Forecast_Title::set_num_results (const QString& num_results) { _num_results = num_results; }
void Forecast_Title::set_erorrs (const QStringList& errors_list) { _erorrs = errors_list; }
void Forecast_Title::set_warnings (const QStringList& warnings_list) { _warnings = warnings_list; }
