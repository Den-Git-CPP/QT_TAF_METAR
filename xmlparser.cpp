
#include "xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent) {}

void XMLParser::Read (MainTAF* main_TAF)
{
    QFile file ("G:/ProjectQT/TitleParser/file.xml");
    if (!file.open (QFile::ReadOnly | QFile::Text)) {
        qDebug () << "*Cannot read file*" << file.errorString ();
        exit (0);
    }
    reader.setDevice (&file);
    if (reader.readNextStartElement ()) {
        if (reader.name () == QString ("response")) {
            read_response (main_TAF);
        }
    }
}
void XMLParser::read_response (MainTAF* main_TAF)
{
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("request_index")) {
            read_request_index (main_TAF);
        }
        else if (reader.name () == QString ("data_source")) {
            read_data_sourse (main_TAF);
        }
        else if (reader.name () == QString ("request")) {
            read_data_request_type (main_TAF);
        }
        else if (reader.name () == QString ("errors")) {
            read_data_errors (main_TAF);
        }
        else if (reader.name () == QString ("warnings")) {
            read_data_warnings (main_TAF);
        }
        else if (reader.name () == QString ("time_taken_ms")) {
            read_time_taken_ms (main_TAF);
        }
        else if (reader.name () == QString ("data")) {
            read_data (main_TAF);
        }
        // else             reader.skipCurrentElement ();
    }

    main_TAF->forecast_Title->print ();
}
void XMLParser::read_request_index (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("request_index"));
    main_TAF->forecast_Title->set_request_index (reader.readElementText ());
}
void XMLParser::read_data_sourse (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("data_source") && reader.attributes ().hasAttribute ("name"));
    main_TAF->forecast_Title->set_name (reader.attributes ().value ("name").toString ());
    reader.skipCurrentElement ();
}
void XMLParser::read_data_request_type (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("request") && reader.attributes ().hasAttribute ("type"));

    main_TAF->forecast_Title->set_type (reader.attributes ().value ("type").toString ());

    reader.skipCurrentElement ();
}
void XMLParser::read_data_errors (MainTAF* main_TAF)
{
    Q_ASSERT (reader.isStartElement () && reader.name () == QString ("errors"));
    QStringList errors_list;
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("error")) {
            errors_list.append (reader.readElementText ());
        }
    }
    main_TAF->forecast_Title->set_erorrs (errors_list);
}
void XMLParser::read_data_warnings (MainTAF* main_TAF)
{
    Q_ASSERT (reader.isStartElement () && reader.name () == QString ("warnings"));
    QStringList warnings_list;
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("warning")) {
            warnings_list.append (reader.readElementText ());
        }
    }
    main_TAF->forecast_Title->set_warnings (warnings_list);
}
void XMLParser::read_time_taken_ms (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("time_taken_ms"));
    main_TAF->forecast_Title->set_time_taken_ms (reader.readElementText ());
}
void XMLParser::read_data (MainTAF* main_TAF)
{
    read_data_num_results (main_TAF);
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("TAF")) {
            read_TAF (main_TAF);
        }
        else
            reader.skipCurrentElement ();
    }
}
void XMLParser::read_data_num_results (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("data") && reader.attributes ().hasAttribute ("num_results"));
    main_TAF->forecast_Title->set_num_results (reader.attributes ().value ("num_results").toString ());
    // reader.skipCurrentElement ();
}

void XMLParser::read_TAF (MainTAF* main_TAF)
{
    Q_ASSERT (reader.isStartElement () && reader.name () == QString ("TAF"));
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("raw_text")) {
            read_raw_text (main_TAF);
        }
        else if (reader.name () == QString ("station_id")) {
            read_station_id (main_TAF);
        }
        else if (reader.name () == QString ("bulletin_time")) {
            read_bulletin_time (main_TAF);
        }
        else if (reader.name () == QString ("issue_time")) {
            read_issue_time (main_TAF);
        }
        else if (reader.name () == QString ("valid_time_from")) {
            read_valid_time_from (main_TAF);
        }
        else if (reader.name () == QString ("valid_time_to")) {
            read_valid_time_to (main_TAF);
        }
        else if (reader.name () == QString ("latitude")) {
            read_latitude (main_TAF);
        }
        else if (reader.name () == QString ("longitude")) {
            read_longitude (main_TAF);
        }
        else if (reader.name () == QString ("elevation_m")) {
            read_elevation_m (main_TAF);
        }
        else if (reader.name () == QString ("forecast")) {
            read_forecast (main_TAF);
        }

        // else             reader.skipCurrentElement ();
    }
    main_TAF->forecast_TAF->print ();
}
void XMLParser::read_raw_text (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("raw_text"));
    main_TAF->forecast_TAF->set_raw_text (reader.readElementText ());
}
void XMLParser::read_station_id (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("station_id"));
    main_TAF->forecast_TAF->set_station_id (reader.readElementText ());
}
void XMLParser::read_issue_time (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("issue_time"));
    main_TAF->forecast_TAF->set_issue_time (reader.readElementText ());
}
void XMLParser::read_bulletin_time (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("bulletin_time"));
    main_TAF->forecast_TAF->set_bulletin_time (reader.readElementText ());
}
void XMLParser::read_valid_time_from (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("valid_time_from"));
    main_TAF->forecast_TAF->set_valid_time_from (reader.readElementText ());
}
void XMLParser::read_valid_time_to (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("valid_time_to"));
    main_TAF->forecast_TAF->set_valid_time_to (reader.readElementText ());
}
void XMLParser::read_remarks (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("remarks"));
    main_TAF->forecast_TAF->set_remarks (reader.readElementText ());
}
void XMLParser::read_latitude (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("latitude"));
    main_TAF->forecast_TAF->set_latitude (reader.readElementText ());
}
void XMLParser::read_longitude (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("longitude"));
    main_TAF->forecast_TAF->set_longitude (reader.readElementText ());
}
void XMLParser::read_elevation_m (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("elevation_m"));
    main_TAF->forecast_TAF->set_elevation_m (reader.readElementText ());
}
void XMLParser::read_forecast (MainTAF* main_TAF)
{
    Q_ASSERT (reader.isStartElement () && reader.name () == QString ("forecast"));
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("fcst_time_from")) {
            read_fcst_time_from (main_TAF);
        }
        else if (reader.name () == QString ("fcst_time_to")) {
            read_fcst_time_to (main_TAF);
        }
        else if (reader.name () == QString ("change_indicator")) {
            read_change_indicator (main_TAF);
        }
        else if (reader.name () == QString ("time_becoming")) {
            read_time_becoming (main_TAF);
        }
        else if (reader.name () == QString ("probability")) {
            read_probability (main_TAF);
        }
        else if (reader.name () == QString ("wind_dir_degrees")) {
            read_wind_dir_degrees (main_TAF);
        }
        else if (reader.name () == QString ("wind_speed_kt")) {
            read_wind_speed_kt (main_TAF);
        }
        else if (reader.name () == QString ("wind_gust_kt")) {
            read_wind_gust_kt (main_TAF);
        }
        else if (reader.name () == QString ("wind_shear_hgt_ft_agl")) {
            read_wind_shear_hgt_ft_agl (main_TAF);
        }
        else if (reader.name () == QString ("wind_shear_dir_degrees")) {
            read_wind_shear_dir_degrees (main_TAF);
        }
        else if (reader.name () == QString ("wind_shear_speed_kt")) {
            read_wind_shear_speed_kt (main_TAF);
        }
        else if (reader.name () == QString ("visibility_statute_mi")) {
            read_visibility_statute_mi (main_TAF);
        }
        else if (reader.name () == QString ("altim_in_hg")) {
            read_altim_in_hg (main_TAF);
        }
        else if (reader.name () == QString ("vert_vis_ft")) {
            read_vert_vis_ft (main_TAF);
        }
        else if (reader.name () == QString ("wx_string")) {
            read_wx_string (main_TAF);
        }
        else if (reader.name () == QString ("not_decoded")) {
            read_not_decoded (main_TAF);
        }
        else if (reader.name () == QString ("sky_condition")) {
            read_sky_condition (main_TAF);
        }
        else
            reader.skipCurrentElement ();
    }
}
void XMLParser::read_fcst_time_from (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("fcst_time_from"));
    main_TAF->forecast_TAF->forecast->set_fcst_time_from (reader.readElementText ());
}
void XMLParser::read_fcst_time_to (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("fcst_time_to"));
    main_TAF->forecast_TAF->forecast->set_fcst_time_to (reader.readElementText ());
}
void XMLParser::read_change_indicator (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("change_indicator"));
    main_TAF->forecast_TAF->forecast->set_change_indicator (reader.readElementText ());
}
void XMLParser::read_time_becoming (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("time_becoming"));
    main_TAF->forecast_TAF->forecast->set_time_becoming (reader.readElementText ());
}
void XMLParser::read_probability (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("probability"));
    main_TAF->forecast_TAF->forecast->set_probability (reader.readElementText ());
}
void XMLParser::read_wind_dir_degrees (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wind_dir_degrees"));
    main_TAF->forecast_TAF->forecast->set_wind_dir_degrees (reader.readElementText ());
}
void XMLParser::read_wind_speed_kt (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wind_speed_kt"));
    main_TAF->forecast_TAF->forecast->set_wind_speed_kt (reader.readElementText ());
}
void XMLParser::read_wind_gust_kt (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wind_gust_kt"));
    main_TAF->forecast_TAF->forecast->set_wind_gust_kt (reader.readElementText ());
}
void XMLParser::read_wind_shear_hgt_ft_agl (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wind_shear_hgt_ft_agl"));
    main_TAF->forecast_TAF->forecast->set_wind_shear_hgt_ft_agl (reader.readElementText ());
}
void XMLParser::read_wind_shear_dir_degrees (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wind_shear_dir_degrees"));
    main_TAF->forecast_TAF->forecast->set_wind_shear_dir_degrees (reader.readElementText ());
}
void XMLParser::read_wind_shear_speed_kt (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wind_shear_speed_kt"));
    main_TAF->forecast_TAF->forecast->set_wind_shear_speed_kt (reader.readElementText ());
}
void XMLParser::read_visibility_statute_mi (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("visibility_statute_mi"));
    main_TAF->forecast_TAF->forecast->set_visibility_statute_mi (reader.readElementText ());
}
void XMLParser::read_altim_in_hg (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("altim_in_hg"));
    main_TAF->forecast_TAF->forecast->set_altim_in_hg (reader.readElementText ());
}
void XMLParser::read_vert_vis_ft (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("vert_vis_ft"));
    main_TAF->forecast_TAF->forecast->set_vert_vis_ft (reader.readElementText ());
}
void XMLParser::read_wx_string (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("wx_string"));
    main_TAF->forecast_TAF->forecast->set_wx_string (reader.readElementText ());
}
void XMLParser::read_not_decoded (MainTAF* main_TAF)
{
    Q_ASSERT (reader.name () == QString ("not_decoded"));
    main_TAF->forecast_TAF->forecast->set_not_decoded (reader.readElementText ());
}
void XMLParser::read_sky_condition (MainTAF* main_TAF)
{ //    Q_ASSERT (reader.name () == QString ("sky_condition")
    //              && reader.attributes ().hasAttribute ("sky_cover")
    //              && reader.attributes ().hasAttribute ("cloud_base_ft_agl")
    //              && reader.attributes ().hasAttribute ("cloud_type"));

    QList<std::tuple<QString, QString, QString>> tuple_List_sky_condition;

    std::tuple sky_condition{ reader.attributes ().value ("sky_cover").toString (), reader.attributes ().value ("cloud_base_ft_agl").toString (),
        reader.attributes ().value ("cloud_type").toString () };
    while (reader.readNextStartElement ()) {
        if (reader.name () == QString ("sky_cover")) {
            std::tuple sky_condition{ reader.attributes ().value ("sky_cover").toString (),
                reader.attributes ().value ("cloud_base_ft_agl").toString (), reader.attributes ().value ("cloud_type").toString () };
            tuple_List_sky_condition.append (sky_condition);
        }
        // else
        // reader.skipCurrentElement ();
    }
    main_TAF->forecast_TAF->forecast->set_tuple_list_sky_condition (tuple_List_sky_condition);
    main_TAF->forecast_TAF->forecast->print ();
}

/*
if (reader.name () == QString ("turbulence_condition")
    && reader.attributes ().hasAttribute ("turbulence_intensity")
    && reader.attributes ().hasAttribute ("turbulence_min_alt_ft_agl")
    && reader.attributes ().hasAttribute ("turbulence_max_alt_ft_agl")) {
    QString turbulence_intensity      = reader.attributes ().value ("turbulence_intensity").toString ();
    QString turbulence_min_alt_ft_agl = reader.attributes ().value ("turbulence_min_alt_ft_agl").toString ();
    QString turbulence_max_alt_ft_agl = reader.attributes ().value ("turbulence_max_alt_ft_agl").toString ();

    reader.skipCurrentElement ();
}
if (reader.name () == QString ("icing_condition")
    && reader.attributes ().hasAttribute ("icing_intensity")
    && reader.attributes ().hasAttribute ("icing_min_alt_ft_agl")
    && reader.attributes ().hasAttribute ("icing_max_alt_ft_agl")) {
    QString icing_intensity      = reader.attributes ().value ("icing_intensity").toString ();
    QString icing_min_alt_ft_agl = reader.attributes ().value ("icing_min_alt_ft_agl").toString ();
    QString icing_max_alt_ft_agl = reader.attributes ().value ("icing_max_alt_ft_agl").toString ();

    reader.skipCurrentElement ();
}
if (reader.name () == QString ("temperature")
    && reader.attributes ().hasAttribute ("valid_time")
    && reader.attributes ().hasAttribute ("sfc_temp_c")
    && reader.attributes ().hasAttribute ("max_temp_c")
    && reader.attributes ().hasAttribute ("min_temp_c")) {

    QString valid_time = reader.attributes ().value ("valid_time").toString ();
    QString sfc_temp_c = reader.attributes ().value ("sfc_temp_c").toString ();
    QString max_temp_c = reader.attributes ().value ("max_temp_c").toString ();
    QString min_temp_c = reader.attributes ().value ("min_temp_c").toString ();

    reader.skipCurrentElement ();
}
if (reader.name () == QString ("valid_time")) {}
if (reader.name () == QString ("sfc_temp_c")) {}
if (reader.name () == QString ("max_temp_c")) {}
if (reader.name () == QString ("min_temp_c")) {}

} // while forecast
}     // FORECAST
}         // while TAF
}*/             // TAF
