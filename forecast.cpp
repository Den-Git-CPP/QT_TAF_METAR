#include "forecast.h"

Forecast::Forecast() {}

void Forecast::print() {
  qDebug()

      << _fcst_time_from << _fcst_time_to << _change_indicator << _time_becoming
      << _probability << _wind_dir_degrees << _wind_speed_kt << _wind_gust_kt
      << _wind_shear_hgt_ft_agl << _wind_shear_dir_degrees
      << _wind_shear_speed_kt << _visibility_statute_mi << _altim_in_hg
      << _vert_vis_ft << _wx_string << _not_decoded;

  //=============
  for (auto elem : _tuple_list_sky_condition) {
    qDebug() << "sky_cover:" << std::get<0>(elem)
             << "cloud_base_ft_agl:" << std::get<1>(elem)
             << "cloud_type:" << std::get<2>(elem);
  }
  for (auto elem : _turbulence_list_condition) {
    qDebug() << "turbulence_intensity:" << std::get<0>(elem)
             << "turbulence_min_alt_ft_agl:" << std::get<1>(elem)
             << "turbulence_max_alt_ft_agl:" << std::get<2>(elem);
  }
  for (auto elem : _icing_list_condition) {
    qDebug() << "icing_intensity:" << std::get<0>(elem)
             << "icing_min_alt_ft_agl:" << std::get<1>(elem)
             << "icing_max_alt_ft_agl:" << std::get<2>(elem);
  }
}

void Forecast::set_condition(const QString name_list_condion,
                             const std::tuple<QString, QString, QString> node) {

  if (name_list_condion == "sky_condition") {
    this->_tuple_list_sky_condition.append(node);
  } else if (name_list_condion == "turbulence_condition") {
    this->_turbulence_list_condition.append(node);
  } else if (name_list_condion == "icing_condition") {
    this->_icing_list_condition.append(node);
  } else
    qDebug() << "Condition not known";
}
