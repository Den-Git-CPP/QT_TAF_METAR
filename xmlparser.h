#pragma once
#include "maintaf.h"

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QXmlSimpleReader>
#include <QXmlStreamReader>

class XMLParser : public QObject {
  Q_OBJECT
public:
  explicit XMLParser(QObject *parent = nullptr);

  void read_request_index(MainTAF *main_TAF);
  void read_data_sourse(MainTAF *main_TAF);
  void read_data_request_type(MainTAF *main_TAF);
  void read_data_errors(MainTAF *main_TAF);
  void read_data_warnings(MainTAF *main_TAF);
  void read_time_taken_ms(MainTAF *main_TAF);
  void read_data(MainTAF *main_TAF);
  void read_data_num_results(MainTAF *main_TAF);
  void read_TAF(MainTAF *main_TAF);
  void read_raw_text(MainTAF *main_TAF);
  void read_station_id(MainTAF *main_TAF);
  void read_issue_time(MainTAF *main_TAF);
  void read_bulletin_time(MainTAF *main_TAF);
  void read_valid_time_from(MainTAF *main_TAF);
  void read_valid_time_to(MainTAF *main_TAF);
  void read_remarks(MainTAF *main_TAF);
  void read_latitude(MainTAF *main_TAF);
  void read_longitude(MainTAF *main_TAF);
  void read_elevation_m(MainTAF *main_TAF);
  void read_forecast(MainTAF *main_TAF);
  void read_fcst_time_from(MainTAF *main_TAF);
  void read_fcst_time_to(MainTAF *main_TAF);
  void read_change_indicator(MainTAF *main_TAF);
  void read_time_becoming(MainTAF *main_TAF);
  void read_probability(MainTAF *main_TAF);

  void read_wind_dir_degrees(MainTAF *main_TAF);
  void read_wind_speed_kt(MainTAF *main_TAF);
  void read_wind_gust_kt(MainTAF *main_TAF);
  void read_wind_shear_hgt_ft_agl(MainTAF *main_TAF);
  void read_wind_shear_dir_degrees(MainTAF *main_TAF);
  void read_wind_shear_speed_kt(MainTAF *main_TAF);
  void read_visibility_statute_mi(MainTAF *main_TAF);
  void read_altim_in_hg(MainTAF *main_TAF);
  void read_vert_vis_ft(MainTAF *main_TAF);
  void read_wx_string(MainTAF *main_TAF);
  void read_not_decoded(MainTAF *main_TAF);
  void read_sky_condition(MainTAF *main_TAF);

  void read_errors();
  void read_my_warninngs();
  void read_TAF();
  void read_forecast();

public slots:
  void Read(MainTAF *main_TAF);

private:
  QXmlStreamReader reader;
};
