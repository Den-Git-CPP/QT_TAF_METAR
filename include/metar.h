#pragma once
#include "./include/function.h"
#include <memory>
#include <QList>
class METAR : private Function {
  public:
    explicit METAR ();
    virtual ~METAR ();

    const QString& getRaw_text () const;
    const QString& getStation_id () const;
    const QString& getObservation_time () const;
    const QString& getTemp_c () const;
    const QString& getDwepoint_c () const;
    const QString& getWind_dir_degrees () const;
    const QString& getWind_speed_kt () const;
    const QString& getWind_gust_kt () const;
    const QString& getAltim_in_hg_mmHg () const;
    const QString& getAltim_in_hg_hPa () const;
    const QString& getVisibility_statute_mi () const;
    const QString& getWx_string () const;
    const QString& getMaxT_c () const;
    const QString& getMinT_c () const;
    const QString& getSnow_in () const;
    const QString& getVert_vis_ft () const;

    void setRaw_text (const QString& newRaw_text);
    void setStation_id (const QString& newStation_id);
    void setObservation_time (const QString& newObservation_time);
    void setTemp_c (const QString& newTemp_c);
    void setDwepoint_c (const QString& newDwepoint_c);
    void setWind_dir_degrees (const QString& newWind_dir_degrees);
    void setWind_speed_kt (const QString& newWind_speed_kt);
    void setWind_gust_kt (const QString& newWind_gust_kt);
    void setVisibility_statute_mi (const QString& newVisibility_statute_mi);
    void setAltim_in_hg (const QString& newAltim_in_hg);
    void setWx_string (const QString& newWx_string);
    void setMaxT_c (const QString& newMaxT_c);
    void setMinT_c (const QString& newMinT_c);
    void setSnow_in (const QString& newSnow_in);
    void setVert_vis_ft (const QString& newVert_vis_ft);
    void setSky_condition (const QString name_list_condion, std::tuple<QString, QString, QString> node);

    const QList<std::tuple<QString, QString, QString>>& getTuple_list_sky_condition () const;

  private:
    QString raw_text_{};   //
    QString station_id_{}; //
    QString observation_time_{};
    //  QString latitude_{};                      //
    //  QString longitude_{};                     //
    QString temp_c_{};          //
    QString dwepoint_c_{};      //
    QString wind_dir_degrees{}; //
    QString wind_speed_kt{};    //
    QString wind_gust_kt{};
    QString visibility_statute_mi_{}; //
    QString altim_in_hg_hPa{};        //
    QString altim_in_hg_mmHg{};       //
    //QString sea_level_pressure_mb_{};         //
    QString wx_string_{}; //
    //QString flight_category_{};               //
    //QString three_hr_pressure_tendency_mb_{}; //
    //QString maxT_c_{};                        //
    //QString minT_c_{};                        //
    //QString maxT24hr_c_{};                    //
    //QString minT24hr_c_{};                    //
    //QString precip_in_{};                     //
    //QString pcp3hr_in_{};                     //
    //QString pcp6hr_in_{};                     //
    //QString pcp24hr_in_{};                    //
    QString snow_in_{};     //
    QString vert_vis_ft_{}; //
    //QString metar_type_{};                    //
    //QString elevation_m_{};                   //
    QList<std::tuple<QString, QString, QString>> tuple_list_sky_condition;
};
