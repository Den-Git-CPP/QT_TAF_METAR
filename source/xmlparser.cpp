
#include "./include/xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent) {}

XMLParser::~XMLParser () {}

void XMLParser::set_vec_buf_xml (const std::vector<std::tuple<QString, QString> >& in_vec_tuple_data_for_parsing)
{
    vec_tuple_data_for_parsing = std::move (in_vec_tuple_data_for_parsing);
}

void XMLParser::fill_u_ptr_Forecast_METAR_TAF ()
{
    taf   = std::make_unique<TAF> ();
    metar = std::make_unique<METAR> ();
    for (auto& [sign_buff, buff] : vec_tuple_data_for_parsing) {
        QXmlStreamReader xmlReader (buff);
        while (!xmlReader.atEnd () && !xmlReader.hasError ()) {

            QXmlStreamReader::TokenType token = xmlReader.readNext ();
            QString xml_name                  = xmlReader.name ().toString ();

            if (token == QXmlStreamReader::StartDocument) {
                continue;
            }
            if (token == QXmlStreamReader::StartElement) {
                if (xml_name == "response"                 //
                    || xml_name == "request_index"         //
                    || xml_name == "data_source"           //
                    || xml_name == "request"               //
                    || xml_name == "errors"                //
                    || xml_name == "warnings"              //
                    || xml_name == "time_taken_ms"         //
                    || xml_name == "data"                  //
                    || xml_name == "quality_control_flags" //
                    || xml_name == "no_signal"             //
                    || xml_name == "flight_category"       //
                    || xml_name == "metar_type"            //
                    || xml_name == "elevation_m"           //
                    || xml_name == "METAR"                 //
                    || xml_name == "TAF"                   //
                ) {
                    continue;
                }

                else if (xml_name == "forecast") {
                    forecast = std::make_unique<Forecast> ();
                    continue;
                }
                else if (xml_name == "raw_text") {
                    if (sign_buff == "tafs") {
                        taf->ForecastTAF->set_raw_text (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setRaw_text (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "station_id") {
                    if (sign_buff == "tafs") {
                        taf->ForecastTAF->set_station_id (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setStation_id (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "issue_time") {
                }
                else if (xml_name == "observation_time_") {
                    metar->setObservation_time (xmlReader.readElementText ());
                }
                else if (xml_name == "issue_time") {
                    taf->ForecastTAF->set_issue_time (xmlReader.readElementText ());
                }
                else if (xml_name == "bulletin_time") {
                    taf->ForecastTAF->set_bulletin_time (xmlReader.readElementText ());
                }
                else if (xml_name == "valid_time_from") {
                    taf->ForecastTAF->set_valid_time_from (xmlReader.readElementText ());
                }
                else if (xml_name == "fcst_time_from") {
                    forecast->set_fcst_time_from (xmlReader.readElementText ());
                }
                else if (xml_name == "fcst_time_to") {
                    forecast->set_fcst_time_to (xmlReader.readElementText ());
                }
                else if (xml_name == "wind_gust_kt") {
                    forecast->set_wind_gust_kt (xmlReader.readElementText ());
                }
                else if (xml_name == "wind_shear_hgt_ft_agl") {
                    forecast->set_wind_shear_hgt_ft_agl (xmlReader.readElementText ());
                }
                else if (xml_name == "wind_shear_dir_degrees") {
                    forecast->set_wind_shear_dir_degrees (xmlReader.readElementText ());
                }
                else if (xml_name == "wind_shear_speed_kt") {
                    forecast->set_wind_shear_dir_degrees (xmlReader.readElementText ());
                }
                else if (xml_name == "change_indicator") {
                    forecast->set_change_indicator (xmlReader.readElementText ());
                }
                else if (xml_name == "time_becoming") {
                    forecast->set_time_becoming (xmlReader.readElementText ());
                }
                else if (xml_name == "probability") {
                    forecast->set_probability (xmlReader.readElementText ());
                }
                else if (xml_name == "vert_vis_ft") {
                    forecast->set_vert_vis_ft (xmlReader.readElementText ());
                }
                else if (xml_name == "valid_time_to") {
                    taf->ForecastTAF->set_valid_time_to (xmlReader.readElementText ());
                }
                else if (xml_name == "latitude") {
                    if (sign_buff == "tafs") {
                        taf->ForecastTAF->set_latitude (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setLatitude (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "longitude") {
                    if (sign_buff == "tafs") {
                        taf->ForecastTAF->set_longitude (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setLongitude (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "temp_c") {
                    metar->setTemp_c (xmlReader.readElementText ());
                }
                else if (xml_name == "dewpoint_c") {
                    metar->setDwepoint_c (xmlReader.readElementText ());
                }
                else if (xml_name == "wind_dir_degrees") {
                    if (sign_buff == "tafs") {
                        forecast->set_wind_dir_degrees (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setWind_dir_degrees (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "wind_speed_kt") {
                    if (sign_buff == "tafs") {
                        forecast->set_wind_speed_kt (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setWind_speed_kt (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "visibility_statute_mi") {
                    if (sign_buff == "tafs") {
                        forecast->set_visibility_statute_mi (xmlReader.readElementText ());
                    };
                    if (sign_buff == "metars") {
                        metar->setVisibility_statute_mi (xmlReader.readElementText ());
                    };
                }
                else if (xml_name == "altim_in_hg") {
                    metar->setAltim_in_hg (xmlReader.readElementText ());
                }
                else if (xml_name == "sea_level_pressure_mb") {
                    metar->setSea_level_pressure_mb (xmlReader.readElementText ());
                }
                else if (xml_name == "wx_string") {
                    if (sign_buff == "tafs") {
                        forecast->set_wx_string (xmlReader.readElementText ());
                    }
                    if (sign_buff == "metars") {
                        metar->setWx_string (xmlReader.readElementText ());
                    }
                }
                else if (xml_name == "not_decoded") {
                    forecast->set_not_decoded (xmlReader.readElementText ());
                }
                else if (xml_name == "three_hr_pressure_tendency_mb") {
                    metar->setThree_hr_pressure_tendency_mb (xmlReader.readElementText ());
                }
                else if (xml_name == "maxT_c") {
                    metar->setMaxT_c (xmlReader.readElementText ());
                }
                else if (xml_name == "minT_c") {
                    metar->setMinT_c (xmlReader.readElementText ());
                }
                else if (xml_name == "maxT24hr_c") {
                    metar->setMaxT24hr_c (xmlReader.readElementText ());
                }
                else if (xml_name == "minT24hr_c") {
                    metar->setMinT24hr_c (xmlReader.readElementText ());
                }
                else if (xml_name == "precip_in") {
                    metar->setPrecip_in (xmlReader.readElementText ());
                }
                else if (xml_name == "pcp3hr_in") {
                    metar->setPcp3hr_in (xmlReader.readElementText ());
                }
                else if (xml_name == "pcp6hr_in") {
                    metar->setPcp6hr_in (xmlReader.readElementText ());
                }
                else if (xml_name == "pcp24hr_in") {
                    metar->setPcp24hr_in (xmlReader.readElementText ());
                }
                else if (xml_name == "snow_in") {
                    metar->setSnow_in (xmlReader.readElementText ());
                }
                else if (xml_name == "vert_vis_ft") {
                    metar->setVert_vis_ft (xmlReader.readElementText ());
                }
                else if (xml_name == "sky_condition") {
                    if (sign_buff == "tafs") {
                        forecast->set_condition ("sky_condition", std::make_tuple (xmlReader.attributes ().value ("sky_cover").toString (),
                                                                    xmlReader.attributes ().value ("cloud_base_ft_agl").toString (), //
                                                                    xmlReader.attributes ().value ("cloud_type").toString ()));
                    };
                    if (sign_buff == "metars") {
                        metar->set_condition ("sky_condition", std::make_tuple (xmlReader.attributes ().value ("sky_cover").toString (),
                                                                 xmlReader.attributes ().value ("cloud_base_ft_agl").toString (), //
                                                                 xmlReader.attributes ().value ("cloud_type").toString ()));
                    };
                }
                else if (xml_name == "turbulence_condition") {
                    forecast->set_condition ("turbulence_condition", std::make_tuple (xmlReader.attributes ().value ("turbulence_intensity").toString (),
                                                                       xmlReader.attributes ().value ("turbulence_min_alt_ft_agl").toString (),
                                                                       xmlReader.attributes ().value ("turbulence_max_alt_ft_agl").toString ()));
                }
                else if (xml_name == "icing_condition") {
                    forecast->set_condition ("icing_condition", std::make_tuple (xmlReader.attributes ().value ("icing_intensity").toString (),
                                                                  xmlReader.attributes ().value ("icing_min_alt_ft_agl").toString (),
                                                                  xmlReader.attributes ().value ("icing_max_alt_ft_agl").toString ()));
                }
                else
                    xmlReader.skipCurrentElement ();
            }

            if (token == QXmlStreamReader::EndElement && xml_name == "TAF") {
                break;
            }
            if (token == QXmlStreamReader::EndElement && xml_name == "forecast") {
                taf->ForecastTAF->v_forecasts.emplace_back (std::move (forecast));
            }
            if (token == QXmlStreamReader::EndElement && xml_name == "METAR") {
                break;
            }

        } // while end file

        if (xmlReader.hasError ()) {
            qDebug () << xmlReader.errorString ();
            return;
        }

    } // end for
}
