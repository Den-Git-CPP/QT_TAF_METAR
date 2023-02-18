#pragma once
#include <QDebug>
#include <QObject>

class Forecast_Title {
public:
  explicit Forecast_Title();
  ~Forecast_Title();
  QString request_index() const;
  QString name() const;
  QString type() const;
  QString time_taken_ms() const;
  QString num_results() const;

  void set_request_index(const QString &request_index);
  ;
  void set_name(const QString &name);
  ;
  void set_type(const QString &type);
  ;
  void set_time_taken_ms(const QString &time_taken_ms);
  ;
  void set_num_results(const QString &num_results);
  ;
  void set_erorrs(const QStringList &errors_list);
  ;
  void set_warnings(const QStringList &warnings_list);
  ;

private:
  QString _request_index{};
  QString _name;
  QString _type;
  QStringList _erorrs;
  QStringList _warnings;
  QString _time_taken_ms;
  QString _num_results;
};
