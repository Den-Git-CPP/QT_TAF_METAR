#include "./include/forecast.h"

Forecast::Forecast () {}

Forecast::~Forecast () {}

QString Forecast::fcst_time_from () const { return _fcst_time_from; }
QString Forecast::fcst_time_to () const { return _fcst_time_to; }
QString Forecast::change_indicator () const { return _change_indicator; }
QString Forecast::time_becoming () const { return _time_becoming; }
QString Forecast::probability () const { return _probability; }
QString Forecast::wind_dir_degrees () const { return _wind_dir_degrees; }
QString Forecast::wind_speed_kt () const { return _wind_speed_kt; }
QString Forecast::wind_gust_kt () const { return _wind_gust_kt; }
QString Forecast::wind_shear_hgt_ft_agl () const { return _wind_shear_hgt_ft_agl; }
QString Forecast::wind_shear_dir_degrees () const { return _wind_shear_dir_degrees; }
QString Forecast::wind_shear_speed_kt () const { return _wind_shear_speed_kt; }
QString Forecast::visibility_statute_mi () const { return _visibility_statute_mi; }
QString Forecast::altim_in_hg () const { return _altim_in_hg; }
QString Forecast::vert_vis_ft () const { return _vert_vis_ft; }
QString Forecast::wx_string () const { return _wx_string; }
QString Forecast::not_decoded () const { return _not_decoded; }

QList<std::tuple<QString, QString, QString> > Forecast::tuple_list_sky_condition () const { return this->_tuple_list_sky_condition; }
QList<std::tuple<QString, QString, QString> > Forecast::turbulence_list_condition () const { return this->_turbulence_list_condition; }
QList<std::tuple<QString, QString, QString> > Forecast::icing_list_condition () const { return this->_icing_list_condition; }

void Forecast::set_fcst_time_from (const QString& fcst_time_from) { this->_fcst_time_from = Function::replace_time (fcst_time_from); }
void Forecast::set_fcst_time_to (const QString& fcst_time_to) { this->_fcst_time_to = Function::replace_time (fcst_time_to); }
void Forecast::set_change_indicator (const QString& change_indicator)
{ //
    this->_change_indicator = Function::replace_change_indicator (change_indicator);
}
void Forecast::set_time_becoming (const QString& time_becoming)
{ //
    this->_time_becoming = Function::replace_time (time_becoming);
}
void Forecast::set_probability (const QString& probability) { this->_probability = probability; }
void Forecast::set_wind_dir_degrees (const QString& wind_dir_degrees) { this->_wind_dir_degrees = wind_dir_degrees; }
void Forecast::set_wind_speed_kt (const QString& wind_speed_kt)
{ //
    this->_wind_speed_kt = Function::convert_kt_to_ms (wind_speed_kt);
}
void Forecast::set_wind_gust_kt (const QString& wind_gust_kt) { this->_wind_gust_kt = Function::convert_kt_to_ms (wind_gust_kt); }
void Forecast::set_wind_shear_hgt_ft_agl (const QString& wind_shear_hgt_ft_agl)
{ //
    this->_wind_shear_hgt_ft_agl = Function::convert_ft_to_m (wind_shear_hgt_ft_agl);
}
void Forecast::set_wind_shear_dir_degrees (const QString& wind_shear_dir_degrees) { this->_wind_shear_dir_degrees = wind_shear_dir_degrees; }
void Forecast::set_wind_shear_speed_kt (const QString& wind_shear_speed_kt)
{ //
    this->_wind_shear_speed_kt = Function::convert_kt_to_ms (wind_shear_speed_kt);
}
void Forecast::set_visibility_statute_mi (const QString& visibility_statute_mi)
{ //
    this->_visibility_statute_mi = Function::convert_mi_to_m (visibility_statute_mi);
}
void Forecast::set_altim_in_hg (const QString& altim_in_hg) { this->_altim_in_hg = altim_in_hg; }
void Forecast::set_vert_vis_ft (const QString& vert_vis_ft) { this->_vert_vis_ft = Function::convert_ft_to_m (vert_vis_ft); }
void Forecast::set_wx_string (const QString& wx_string) { this->_wx_string = Function::replace_wx_string (wx_string); }
void Forecast::set_not_decoded (const QString& not_decoded) { this->_not_decoded = not_decoded; }
void Forecast::set_condition (const QString name_list_condion, std::tuple<QString, QString, QString> node)
{
    if (name_list_condion == "sky_condition") {

        Function::replace_tuple_sky_condition (node);
        this->_tuple_list_sky_condition.append (node);
    }
    else if (name_list_condion == "turbulence_condition") {
        Function::replace_turbulence_condition (node);
        this->_turbulence_list_condition.append (node);
    }
    else if (name_list_condion == "icing_condition") {
        Function::replace_icing_condition (node);
        this->_icing_list_condition.append (node);
    }
    else {
        qDebug () << "Condition not known";
    }
}
