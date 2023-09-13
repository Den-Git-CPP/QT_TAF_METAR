#include "./include/metar.h"
METAR::METAR () {}
METAR::~METAR () {}

const QString& METAR::raw_text () const { return raw_text_; }
const QString& METAR::station_id () const { return station_id_; }
const QString& METAR::observation_time () const { return observation_time_; }
const QString& METAR::latitude () const { return latitude_; }
const QString& METAR::longitude () const { return longitude_; }
const QString& METAR::temp_c () const { return temp_c_; }
const QString& METAR::dwepoint_c () const { return dwepoint_c_; }
const QString& METAR::getWind_dir_degrees () const { return wind_dir_degrees; }
const QString& METAR::getWind_speed_kt () const { return wind_speed_kt; }
const QString& METAR::visibility_statute_mi () const { return visibility_statute_mi_; }
const QString& METAR::altim_in_hg () const { return altim_in_hg_; }
const QString& METAR::sea_level_pressure_mb () const { return sea_level_pressure_mb_; }
const QString& METAR::wx_string () const { return wx_string_; }
const QString& METAR::flight_category () const { return flight_category_; }
const QString& METAR::three_hr_pressure_tendency_mb () const { return three_hr_pressure_tendency_mb_; }
const QString& METAR::maxT_c () const { return maxT_c_; }
const QString& METAR::minT_c () const { return minT_c_; }
const QString& METAR::maxT24hr_c () const { return maxT24hr_c_; }
const QString& METAR::minT24hr_c () const { return minT24hr_c_; }
const QString& METAR::precip_in () const { return precip_in_; }
const QString& METAR::pcp3hr_in () const { return pcp3hr_in_; }
const QString& METAR::pcp6hr_in () const { return pcp6hr_in_; }
const QString& METAR::pcp24hr_in () const { return pcp24hr_in_; }
const QString& METAR::snow_in () const { return snow_in_; }
const QString& METAR::vert_vis_ft () const { return vert_vis_ft_; }
const QString& METAR::metar_type () const { return metar_type_; }
const QString& METAR::elevation_m () const { return elevation_m_; }
void METAR::setRaw_text (const QString& newRaw_text) { raw_text_ = Function::replace_raw_text (newRaw_text); }
void METAR::setStation_id (const QString& newStation_id) { station_id_ = Function::replace_id_staion (newStation_id); }
void METAR::setObservation_time (const QString& newObservation_time) { observation_time_ = Function::replace_time (newObservation_time); }
void METAR::setLatitude (const QString& newLatitude) { latitude_ = newLatitude; }
void METAR::setLongitude (const QString& newLongitude) { longitude_ = newLongitude; }
void METAR::setTemp_c (const QString& newTemp_c) { temp_c_ = newTemp_c; }
void METAR::setDwepoint_c (const QString& newDwepoint_c) { dwepoint_c_ = newDwepoint_c; }
void METAR::setWind_dir_degrees (const QString& newWind_dir_degrees) { wind_dir_degrees = newWind_dir_degrees; }
void METAR::setWind_speed_kt (const QString& newWind_speed_kt) { wind_speed_kt = newWind_speed_kt; }
void METAR::setVisibility_statute_mi (const QString& newVisibility_statute_mi) { visibility_statute_mi_ = newVisibility_statute_mi; }
void METAR::setAltim_in_hg (const QString& newAltim_in_hg) { altim_in_hg_ = newAltim_in_hg; }
void METAR::setSea_level_pressure_mb (const QString& newSea_level_pressure_mb) { sea_level_pressure_mb_ = newSea_level_pressure_mb; }
void METAR::setWx_string (const QString& newWx_string) { wx_string_ = Function::replace_wx_string (newWx_string); }
void METAR::setFlight_category (const QString& newFlight_category) { flight_category_ = newFlight_category; }
void METAR::setThree_hr_pressure_tendency_mb (const QString& newThree_hr_pressure_tendency_mb)
{
    three_hr_pressure_tendency_mb_ = newThree_hr_pressure_tendency_mb;
}
void METAR::setMaxT_c (const QString& newMaxT_c) { maxT_c_ = newMaxT_c; }
void METAR::setMinT_c (const QString& newMinT_c) { minT_c_ = newMinT_c; }
void METAR::setMaxT24hr_c (const QString& newMaxT24hr_c) { maxT24hr_c_ = newMaxT24hr_c; }
void METAR::setMinT24hr_c (const QString& newMinT24hr_c) { minT24hr_c_ = newMinT24hr_c; }
void METAR::setPrecip_in (const QString& newPrecip_in) { precip_in_ = newPrecip_in; }
void METAR::setPcp3hr_in (const QString& newPcp3hr_in) { pcp3hr_in_ = newPcp3hr_in; }
void METAR::setPcp6hr_in (const QString& newPcp6hr_in) { pcp6hr_in_ = newPcp6hr_in; }
void METAR::setPcp24hr_in (const QString& newPcp24hr_in) { pcp24hr_in_ = newPcp24hr_in; }
void METAR::setSnow_in (const QString& newSnow_in) { snow_in_ = newSnow_in; }
void METAR::setVert_vis_ft (const QString& newVert_vis_ft) { vert_vis_ft_ = Function::convert_ft_to_m (newVert_vis_ft); }
void METAR::setMetar_type (const QString& newMetar_type) { metar_type_ = newMetar_type; }
void METAR::setElevation_m (const QString& newElevation_m) { elevation_m_ = newElevation_m; }
