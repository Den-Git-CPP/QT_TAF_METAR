#include "./include/taf.h"

TAF::TAF () {}

TAF::~TAF () {}

QString TAF::raw_text () const { return _raw_text; }
QString TAF::station_id () const { return _station_id; }
QString TAF::issue_time () const { return _issue_time; }
QString TAF::valid_time_from () const { return _valid_time_from; }
QString TAF::valid_time_to () const { return _valid_time_to; }
QString TAF::remarks () const { return _remarks; }

void TAF::set_raw_text (const QString& raw_text) { _raw_text = Function::replace_raw_text (raw_text); };
void TAF::set_station_id (const QString& station_id) { _station_id = Function::replace_text (station_id); };
void TAF::set_issue_time (const QString& issue_time) { _issue_time = Function::replace_time (issue_time); };
void TAF::set_valid_time_from (const QString& valid_time_from) { _valid_time_from = Function::replace_time (valid_time_from); };
void TAF::set_valid_time_to (const QString& valid_time_to) { _valid_time_to = Function::replace_time (valid_time_to); };
void TAF::set_remarks (const QString& remarks) { _remarks = remarks; };
