#pragma once
#include "./include/forecast.h"
#include "./include/function.h"
#include <QDebug>
#include <QObject>
#include <QVector>

class TAF : private Function {

public:
  explicit TAF();
  ~TAF();
  QString raw_text() const;
  QString station_id() const;
  QString issue_time() const;
  QString valid_time_from() const;
  QString valid_time_to() const;
  QString remarks() const;

  void set_raw_text(const QString &raw_text);
  void set_station_id(const QString &station_id);
  void set_issue_time(const QString &issue_time);
  void set_valid_time_from(const QString &valid_time_from);
  void set_valid_time_to(const QString &valid_time_to);
  void set_remarks(const QString &remarks);

  std::vector<std::unique_ptr<Forecast>> v_forecasts{};

private:
  QString _raw_text{};
  QString _station_id{};
  QString _issue_time{};
  //  QString _bulletin_time{};
  QString _valid_time_from{};
  QString _valid_time_to{};
  QString _remarks{};
  //  QString _latitude{};
  //  QString _longitude{};
  QString _elevation_m{};
};
