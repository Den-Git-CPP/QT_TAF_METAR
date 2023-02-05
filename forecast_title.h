#pragma once
#include <QDebug>
#include <QObject>

class Forecast_Title : public QObject {
    Q_OBJECT
  public:
    explicit Forecast_Title (QObject* parent = nullptr);
    QString request_index () const { return _request_index; };
    QString name () const { return _name; };
    QString type () const { return _type; };
    QString time_taken_ms () const { return _time_taken_ms; };
    QString num_results () const { return _num_results; };

    void set_request_index (const QString& request_index) { this->_request_index = request_index; };
    void set_name (const QString& name) { this->_name = name; };
    void set_type (const QString& type) { this->_type = type; };
    void set_time_taken_ms (const QString& time_taken_ms) { this->_time_taken_ms = time_taken_ms; };
    void set_num_results (const QString& num_results) { this->_num_results = num_results; };
    void set_erorrs (const QStringList& errors_list) { this->_erorrs = errors_list; };
    void set_warnings (const QStringList& warnings_list) { this->_warnings = warnings_list; };

    void print ();

  signals:
  private:
    QString _request_index;
    QString _name;
    QString _type;
    QStringList _erorrs;
    QStringList _warnings;
    QString _time_taken_ms;
    QString _num_results;
};
