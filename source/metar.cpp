#include "./include/metar.h"

METAR::METAR () {}
METAR::~METAR () {}

const QString& METAR::getRaw_text () const { return raw_text_; }
const QString& METAR::getStation_id () const { return station_id_; }
const QString& METAR::getObservation_time () const { return observation_time_; }
const QString& METAR::getTemp_c () const { return temp_c_; }
const QString& METAR::getDwepoint_c () const { return dwepoint_c_; }
const QString& METAR::getWind_dir_degrees () const { return wind_dir_degrees; }
const QString& METAR::getWind_speed_kt () const { return wind_speed_kt; }
const QString& METAR::getWind_gust_kt () const { return wind_gust_kt; }
const QString& METAR::getVisibility_statute_mi () const { return visibility_statute_mi_; }
const QString& METAR::getAltim_in_hg_hPa () const { return altim_in_hg_hPa; }
const QString& METAR::getAltim_in_hg_mmHg () const { return altim_in_hg_mmHg; }

const QString& METAR::getWx_string () const { return wx_string_; }
const QString& METAR::getSnow_in () const { return snow_in_; }
const QString& METAR::getVert_vis_ft () const { return vert_vis_ft_; }
const QList<std::tuple<QString, QString, QString> >& METAR::getTuple_list_sky_condition () const { return tuple_list_sky_condition; }

void METAR::setRaw_text (const QString& newRaw_text) { raw_text_ = std::move (Function::replace_raw_text (newRaw_text)); }
void METAR::setStation_id (const QString& newStation_id)
{    station_id_ = std::move (Function::replace_text (newStation_id));
}
void METAR::setObservation_time (const QString& newObservation_time) { observation_time_ = std::move (Function::replace_time (newObservation_time)); }
void METAR::setTemp_c (const QString& newTemp_c) { temp_c_ = newTemp_c; }
void METAR::setDwepoint_c (const QString& newDwepoint_c) { dwepoint_c_ = newDwepoint_c; }
void METAR::setWind_dir_degrees (const QString& newWind_dir_degrees) { wind_dir_degrees = newWind_dir_degrees; }
void METAR::setWind_speed_kt (const QString& newWind_speed_kt)
{
    wind_speed_kt = std::move (Function::replace_val_from_to (From_To::kt_to_ms, newWind_speed_kt));
}
void METAR::setWind_gust_kt (const QString& newWind_gust_kt)
{
    wind_gust_kt = std::move (Function::replace_val_from_to (From_To::kt_to_ms, newWind_gust_kt));
}
void METAR::setSky_condition (const QString name_list_condion, std::tuple<QString, QString, QString> node)
{
    tuple_list_sky_condition.append (std::move (std::make_tuple (std::move (Function::replace_text (std::get<0> (node))), //
      std::move (Function::replace_val_from_to (From_To::ft_to_m, std::get<1> (node))),                                   //
      std::move (Function::replace_text (std::get<2> (node)))                                                             //
      )));
}
void METAR::setVisibility_statute_mi (const QString& newVisibility_statute_mi)
{
    visibility_statute_mi_ = Function::replace_val_from_to (From_To::mi_to_m, newVisibility_statute_mi);
}
void METAR::setAltim_in_hg (const QString& newAltim_in_hg)
{
    altim_in_hg_hPa = std::move (Function::replace_val_from_to (From_To::inchHg_to_hPa, newAltim_in_hg)); // Дюймы ртутного столба в Гектопаскаль
    altim_in_hg_mmHg = std::move (Function::replace_val_from_to (From_To::inchHg_to_mmHg, newAltim_in_hg)); // Дюймы ртутного столба в Миллиметры ртутного столба
}
void METAR::setWx_string (const QString& newWx_string) { wx_string_ = std::move (Function::replace_text (newWx_string)); }
void METAR::setSnow_in (const QString& newSnow_in) { snow_in_ = newSnow_in; }
void METAR::setVert_vis_ft (const QString& newVert_vis_ft)
{
    vert_vis_ft_ = std::move (Function::replace_val_from_to (From_To::ft_to_m, newVert_vis_ft));
}
