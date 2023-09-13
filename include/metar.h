#pragma once
#include "./include/forecast_title.h"
#include "./include/function.h"

#include <memory>
class METAR : private Function {
  public:
    explicit METAR ();
    virtual ~METAR ();

    const QString& raw_text () const;
    void setRaw_text (const QString& newRaw_text);

    const QString& station_id () const;
    void setStation_id (const QString& newStation_id);

    const QString& observation_time () const;
    void setObservation_time (const QString& newObservation_time);

    const QString& latitude () const;
    const QString& longitude () const;
    const QString& temp_c () const;
    const QString& dwepoint_c () const;
    const QString& visibility_statute_mi () const;
    const QString& altim_in_hg () const;
    const QString& sea_level_pressure_mb () const;
    const QString& wx_string () const;
    const QString& flight_category () const;
    const QString& three_hr_pressure_tendency_mb () const;
    const QString& maxT_c () const;
    const QString& minT_c () const;
    const QString& maxT24hr_c () const;
    const QString& minT24hr_c () const;
    const QString& precip_in () const;
    const QString& pcp3hr_in () const;
    const QString& pcp6hr_in () const;
    const QString& pcp24hr_in () const;
    const QString& snow_in () const;
    const QString& vert_vis_ft () const;
    const QString& metar_type () const;
    const QString& elevation_m () const;
    const QString& getWind_dir_degrees () const;
    const QString& getWind_speed_kt () const;

    void setLongitude (const QString& newLongitude);
    void setLatitude (const QString& newLatitude);
    void setTemp_c (const QString& newTemp_c);
    void setDwepoint_c (const QString& newDwepoint_c);
    void setVisibility_statute_mi (const QString& newVisibility_statute_mi);
    void setAltim_in_hg (const QString& newAltim_in_hg);
    void setSea_level_pressure_mb (const QString& newSea_level_pressure_mb);
    void setWx_string (const QString& newWx_string);
    void setFlight_category (const QString& newFlight_category);
    void setThree_hr_pressure_tendency_mb (const QString& newThree_hr_pressure_tendency_mb);
    void setMaxT_c (const QString& newMaxT_c);
    void setMinT_c (const QString& newMinT_c);
    void setMaxT24hr_c (const QString& newMaxT24hr_c);
    void setMinT24hr_c (const QString& newMinT24hr_c);
    void setPrecip_in (const QString& newPrecip_in);
    void setPcp3hr_in (const QString& newPcp3hr_in);
    void setPcp6hr_in (const QString& newPcp6hr_in);
    void setPcp24hr_in (const QString& newPcp24hr_in);
    void setSnow_in (const QString& newSnow_in);
    void setVert_vis_ft (const QString& newVert_vis_ft);
    void setMetar_type (const QString& newMetar_type);
    void setElevation_m (const QString& newElevation_m);
    void setWind_dir_degrees (const QString& newWind_dir_degrees);
    void setWind_speed_kt (const QString& newWind_speed_kt);

  private:
    QString raw_text_{};   //
    QString station_id_{}; //
    QString observation_time_{};
    QString latitude_{};                      //
    QString longitude_{};                     //
    QString temp_c_{};                        //
    QString dwepoint_c_{};                    //
    QString wind_dir_degrees{};               //
    QString wind_speed_kt{};                  //
    QString visibility_statute_mi_{};         //
    QString altim_in_hg_{};                   //
    QString sea_level_pressure_mb_{};         //
    QString wx_string_{};                     //
    QString flight_category_{};               //
    QString three_hr_pressure_tendency_mb_{}; //
    QString maxT_c_{};                        //
    QString minT_c_{};                        //
    QString maxT24hr_c_{};                    //
    QString minT24hr_c_{};                    //
    QString precip_in_{};                     //
    QString pcp3hr_in_{};                     //
    QString pcp6hr_in_{};                     //
    QString pcp24hr_in_{};                    //
    QString snow_in_{};                       //
    QString vert_vis_ft_{};                   //
    QString metar_type_{};                    //
    QString elevation_m_{};                   //

    std::shared_ptr<Forecast_Title> ForecastTitle = nullptr;
    // std::shared_ptr<Wind> wind = nullptr;
    // std::shared_ptr<Station_Sensors> station_sensors = nullptr;
    // std::shared_ptr<sky_cover> = nullptr;
};
