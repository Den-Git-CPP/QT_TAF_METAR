#include "function.h"
#include <QDebug>
#include <QMap>
#include <QString>
#include <tuple>
#pragma once
class Forecast : private Function {
  public:
    Forecast ();
    ~Forecast ();

    QString fcst_time_from () const;
    QString fcst_time_to () const;
    QString change_indicator () const;
    QString time_becoming () const;
    QString probability () const;
    QString wind_dir_degrees () const;
    QString wind_speed_kt () const;
    QString wind_gust_kt () const;
    QString wind_shear_hgt_ft_agl () const;
    QString wind_shear_dir_degrees () const;
    QString wind_shear_speed_kt () const;
    QString visibility_statute_mi () const;
    QString altim_in_hg () const;
    QString vert_vis_ft () const;
    QString wx_string () const;
    QString not_decoded () const;

    void set_fcst_time_from (const QString& fcst_time_from);
    void set_fcst_time_to (const QString& fcst_time_to);
    void set_change_indicator (const QString& change_indicator);
    void set_time_becoming (const QString& time_becoming);
    void set_probability (const QString& probability);
    void set_wind_dir_degrees (const QString& wind_dir_degrees);
    void set_wind_speed_kt (const QString& wind_speed_kt);
    void set_wind_gust_kt (const QString& wind_gust_kt);
    void set_wind_shear_hgt_ft_agl (const QString& wind_shear_hgt_ft_agl);
    void set_wind_shear_dir_degrees (const QString& wind_shear_dir_degrees);
    void set_wind_shear_speed_kt (const QString& wind_shear_speed_kt);
    void set_visibility_statute_mi (const QString& visibility_statute_mi);
    void set_altim_in_hg (const QString& altim_in_hg);
    void set_vert_vis_ft (const QString& vert_vis_ft);
    void set_wx_string (const QString& wx_string);
    void set_not_decoded (const QString& not_decoded);

    void set_condition (const QString name_list_condion, const std::tuple<QString, QString, QString> node);

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
    QString _valid_time{};
    QString _sfc_temp_c{};
    QString _max_temp_c{};
    QString _min_temp_c{};
    */
    // sky_turbulence_icing_condition

    QList<std::tuple<QString, QString, QString>> _tuple_list_sky_condition;
    QList<std::tuple<QString, QString, QString>> _turbulence_list_condition;
    QList<std::tuple<QString, QString, QString>> _icing_list_condition;
};
