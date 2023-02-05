#include <QDebug>
#include <QString>
#include <tuple>

#pragma once
class Forecast {
  public:
    Forecast ();
    ~Forecast (){};
    void print ();
    QString fcst_time_from () const { return _fcst_time_from; }
    QString fcst_time_to () const { return _fcst_time_to; }
    QString change_indicator () const { return _change_indicator; }
    QString time_becoming () const { return _time_becoming; }
    QString probability () const { return _probability; }

    QString wind_dir_degrees () const { return _wind_dir_degrees; }
    QString wind_speed_kt () const { return _wind_speed_kt; }
    QString wind_gust_kt () const { return _wind_gust_kt; }

    QString wind_shear_hgt_ft_agl () const { return _wind_shear_hgt_ft_agl; }
    QString wind_shear_dir_degrees () const { return _wind_shear_dir_degrees; }
    QString wind_shear_speed_kt () const { return _wind_shear_speed_kt; }

    QString visibility_statute_mi () const { return _visibility_statute_mi; }
    QString altim_in_hg () const { return _altim_in_hg; }
    QString vert_vis_ft () const { return _vert_vis_ft; }
    QString wx_string () const { return _wx_string; }
    QString not_decoded () const { return _not_decoded; }

    void set_fcst_time_from (const QString& fcst_time_from) { this->_fcst_time_from = fcst_time_from; }
    void set_fcst_time_to (const QString& fcst_time_to) { this->_fcst_time_to = fcst_time_to; }
    void set_change_indicator (const QString& change_indicator) { this->_change_indicator = change_indicator; }
    void set_time_becoming (const QString& time_becoming) { this->_time_becoming = time_becoming; }
    void set_probability (const QString& probability) { this->_probability = probability; }
    void set_wind_dir_degrees (const QString& wind_dir_degrees) { this->_wind_dir_degrees = wind_dir_degrees; }
    void set_wind_speed_kt (const QString& wind_speed_kt) { this->_wind_speed_kt = wind_speed_kt; }
    void set_wind_gust_kt (const QString& wind_gust_kt) { this->_wind_gust_kt = wind_gust_kt; }
    void set_wind_shear_hgt_ft_agl (const QString& wind_shear_hgt_ft_agl) { this->_wind_shear_hgt_ft_agl = wind_shear_hgt_ft_agl; }
    void set_wind_shear_dir_degrees (const QString& wind_shear_dir_degrees) { this->_wind_shear_dir_degrees = wind_shear_dir_degrees; }
    void set_wind_shear_speed_kt (const QString& wind_shear_speed_kt) { this->_wind_shear_speed_kt = wind_shear_speed_kt; }
    void set_visibility_statute_mi (const QString& visibility_statute_mi) { this->_visibility_statute_mi = visibility_statute_mi; }
    void set_altim_in_hg (const QString& altim_in_hg) { this->_altim_in_hg = altim_in_hg; }
    void set_vert_vis_ft (const QString& vert_vis_ft) { this->_vert_vis_ft = vert_vis_ft; }
    void set_wx_string (const QString& wx_string) { this->_wx_string = wx_string; }
    void set_not_decoded (const QString& not_decoded) { this->_not_decoded = not_decoded; }
    void set_tuple_list_sky_condition (const QList<std::tuple<QString, QString, QString>>);

  private:
    QString _fcst_time_from{};
    QString _fcst_time_to{};
    QString _change_indicator{};
    QString _time_becoming{};
    QString _probability{};
    QString _wind_dir_degrees{};
    QString _wind_speed_kt{};
    QString _wind_gust_kt{};
    QString _wind_shear_hgt_ft_agl{};
    QString _wind_shear_dir_degrees{};
    QString _wind_shear_speed_kt{};
    QString _visibility_statute_mi{};
    QString _altim_in_hg{};
    QString _vert_vis_ft{};
    QString _wx_string{};
    QString _not_decoded{};

    /*
    QString _turbulence_intensity{};
    QString _turbulence_min_alt_ft_agl{};
    QString _turbulence_max_alt_ft_agl{};

    QString _icing_intensity{};
    QString _icing_min_alt_ft_agl{};
    QString _icing_max_alt_ft_agl{};

    QString _valid_time{};
    QString _sfc_temp_c{};
    QString _max_temp_c{};
    QString _min_temp_c{};

    */
    // sky_condition
    QList<std::tuple<QString, QString, QString>> _tuple_list_sky_condition;
};
