#pragma once
#include "forecast.h"

#include <QDebug>
#include <QObject>
#include <QVector>

class Forecast_TAF {

  public:
    explicit Forecast_TAF ();
    ~Forecast_TAF ();

    QString raw_text () const;
    QString station_id () const;
    QString issue_time () const;
    QString bulletin_time () const;
    QString valid_time_from () const;
    QString valid_time_to () const;
    QString remarks () const;
    QString latitude () const;
    QString longitude () const;
    QString elevation_m () const;

    void set_raw_text (const QString& raw_text) { this->_raw_text = raw_text; };
    void set_station_id (const QString& station_id) { this->_station_id = station_id; };
    void set_issue_time (const QString& issue_time) { this->_issue_time = issue_time; };
    void set_bulletin_time (const QString& bulletin_time) { this->_bulletin_time = bulletin_time; };
    void set_valid_time_from (const QString& valid_time_from) { this->_valid_time_from = valid_time_from; };

    void set_valid_time_to (const QString& valid_time_to) { this->_valid_time_to = valid_time_to; };
    void set_remarks (const QString& remarks) { this->_remarks = remarks; };
    void set_latitude (const QString& latitude) { this->_latitude = latitude; };
    void set_longitude (const QString& longitude) { this->_longitude = longitude; };
    void set_elevation_m (const QString& elevation_m) { this->_elevation_m = elevation_m; };

    QVector<Forecast> forecasts;
    void add_forecast (Forecast in_forecast);

  private:
    QString _raw_text;
    QString _station_id{};
    QString _issue_time{};
    QString _bulletin_time{};
    QString _valid_time_from{};
    QString _valid_time_to{};
    QString _remarks{};
    QString _latitude{};
    QString _longitude{};
    QString _elevation_m{};
};
