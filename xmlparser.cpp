
#include "xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent) {}

void XMLParser::Read (MainTAF* main_TAF)
{
    QFile file (":/resource/file.xml");
    if (!file.open (QFile::ReadOnly | QFile::Text)) {
        qDebug () << "Cannot read file" << file.errorString ();
        exit (0);
    }
    reader.setDevice (&file);
    reader.readNext ();
    while (!reader.atEnd () && !reader.hasError ()) {
        QXmlStreamReader::TokenType token = reader.readNext ();
        if (token == QXmlStreamReader::StartDocument) {
            continue;
        }
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name ().toString () == "response") {
                continue;
            }
            else if (reader.name ().toString () == "request_index") {
                Q_ASSERT (reader.name () == QString ("request_index"));
                main_TAF->forecast_Title->set_request_index (reader.readElementText ());
            }
            else if (reader.name ().toString () == "data_source") {
                Q_ASSERT (reader.name () == QString ("data_source") && reader.attributes ().hasAttribute ("name"));
                main_TAF->forecast_Title->set_name (reader.attributes ().value ("name").toString ());
                reader.skipCurrentElement ();
            }
            else if (reader.name ().toString () == "request") {
                Q_ASSERT (reader.name () == QString ("request") && reader.attributes ().hasAttribute ("type"));
                main_TAF->forecast_Title->set_type (reader.attributes ().value ("type").toString ());
                reader.skipCurrentElement ();
            }
            else if (reader.name ().toString () == "errors") {
                Q_ASSERT (reader.isStartElement () && reader.name () == QString ("errors"));
                QStringList errors_list;
                while (reader.readNextStartElement ()) {
                    if (reader.name () == QString ("error")) {
                        errors_list.append (reader.readElementText ());
                    }
                }
                main_TAF->forecast_Title->set_erorrs (errors_list);
            }
            else if (reader.name ().toString () == "warnings") {
                Q_ASSERT (reader.isStartElement () && reader.name () == QString ("warnings"));
                QStringList warnings_list;
                while (reader.readNextStartElement ()) {
                    if (reader.name () == QString ("warning")) {
                        warnings_list.append (reader.readElementText ());
                    }
                }
                main_TAF->forecast_Title->set_warnings (warnings_list);
            }
            else if (reader.name ().toString () == "time_taken_ms") {
                Q_ASSERT (reader.name () == QString ("time_taken_ms"));
                main_TAF->forecast_Title->set_time_taken_ms (reader.readElementText ());
            }
            else if (reader.name ().toString () == "data") {
                Q_ASSERT (reader.name () == QString ("data") && reader.attributes ().hasAttribute ("num_results"));
                main_TAF->forecast_Title->set_num_results (reader.attributes ().value ("num_results").toString ());
            }
            else if (reader.name ().toString () == "TAF") {
                read_TAF (main_TAF);
            }
        }
    } // while end file

    if (reader.hasError ()) {
        qDebug () << reader.errorString ();
        return;
    }
    main_TAF->forecast_Title->print ();
    main_TAF->forecast_TAF->print ();
    qDebug () << "READ_END";
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
}

void XMLParser::read_TAF (MainTAF* main_TAF)
{
    while (reader.readNextStartElement ()) {
        if (reader.name ().toString () == "raw_text") {
            Q_ASSERT (reader.name () == QString ("raw_text"));
            main_TAF->forecast_TAF->set_raw_text (reader.readElementText ());
        }
        else if (reader.name ().toString () == "station_id") {
            Q_ASSERT (reader.name () == QString ("station_id"));
            main_TAF->forecast_TAF->set_station_id (reader.readElementText ());
        }
        else if (reader.name ().toString () == "issue_time") {
            Q_ASSERT (reader.name () == QString ("issue_time"));
            main_TAF->forecast_TAF->set_issue_time (reader.readElementText ());
        }
        else if (reader.name ().toString () == "bulletin_time") {
            Q_ASSERT (reader.name () == QString ("bulletin_time"));
            main_TAF->forecast_TAF->set_bulletin_time (reader.readElementText ());
        }
        else if (reader.name ().toString () == "valid_time_from") {
            Q_ASSERT (reader.name () == QString ("valid_time_from"));
            main_TAF->forecast_TAF->set_valid_time_from (reader.readElementText ());
        }
        else if (reader.name ().toString () == "valid_time_to") {
            Q_ASSERT (reader.name () == QString ("valid_time_to"));
            main_TAF->forecast_TAF->set_valid_time_to (reader.readElementText ());
        }
        else if (reader.name ().toString () == "remarks") {
            Q_ASSERT (reader.name () == QString ("remarks"));
            main_TAF->forecast_TAF->set_remarks (reader.readElementText ());
        }
        else if (reader.name ().toString () == "latitude") {
            Q_ASSERT (reader.name () == QString ("latitude"));
            main_TAF->forecast_TAF->set_latitude (reader.readElementText ());
        }
        else if (reader.name ().toString () == "longitude") {
            Q_ASSERT (reader.name () == QString ("longitude"));
            main_TAF->forecast_TAF->set_longitude (reader.readElementText ());
        }
        else if (reader.name ().toString () == "elevation_m") {
            Q_ASSERT (reader.name () == QString ("elevation_m"));
            main_TAF->forecast_TAF->set_elevation_m (reader.readElementText ());
        }
        else if (reader.name ().toString () == "forecast") {
            read_forecast (main_TAF);
        }
    } // end while

    if (QXmlStreamReader::EndElement && reader.name ().toString () == "TAF") {
        qDebug () << "Create TAF\n";
        read_TAF (main_TAF);
    }
}

void XMLParser::read_forecast (MainTAF* main_TAF)
{
    while (reader.readNextStartElement ()) {
        if (reader.name ().toString () == "fcst_time_from") {
            Q_ASSERT (reader.name () == QString ("fcst_time_from"));
            main_TAF->forecast_TAF->forecast->set_fcst_time_to (reader.readElementText ());
        }
        else if (reader.name ().toString () == "fcst_time_to") {
            Q_ASSERT (reader.name () == QString ("fcst_time_to"));
            main_TAF->forecast_TAF->forecast->set_fcst_time_to (reader.readElementText ());
        }
        else if (reader.name ().toString () == "change_indicator") {
            Q_ASSERT (reader.name () == QString ("change_indicator"));
            main_TAF->forecast_TAF->forecast->set_change_indicator (reader.readElementText ());
        }
        else if (reader.name ().toString () == "time_becoming") {
            Q_ASSERT (reader.name () == QString ("time_becoming"));
            main_TAF->forecast_TAF->forecast->set_time_becoming (reader.readElementText ());
        }
        else if (reader.name ().toString () == "probability") {
            Q_ASSERT (reader.name () == QString ("probability"));
            main_TAF->forecast_TAF->forecast->set_probability (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wind_dir_degrees") {
            Q_ASSERT (reader.name () == QString ("wind_dir_degrees"));
            main_TAF->forecast_TAF->forecast->set_wind_dir_degrees (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wind_speed_kt") {
            Q_ASSERT (reader.name () == QString ("wind_speed_kt"));
            main_TAF->forecast_TAF->forecast->set_wind_speed_kt (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wind_gust_kt") {
            Q_ASSERT (reader.name () == QString ("wind_gust_kt"));
            main_TAF->forecast_TAF->forecast->set_wind_gust_kt (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wind_shear_hgt_ft_agl") {
            Q_ASSERT (reader.name () == QString ("wind_shear_hgt_ft_agl"));
            main_TAF->forecast_TAF->forecast->set_wind_shear_hgt_ft_agl (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wind_shear_dir_degrees") {
            Q_ASSERT (reader.name () == QString ("wind_shear_dir_degrees"));
            main_TAF->forecast_TAF->forecast->set_wind_shear_dir_degrees (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wind_shear_speed_kt") {
            Q_ASSERT (reader.name () == QString ("wind_shear_dir_degrees"));
            main_TAF->forecast_TAF->forecast->set_wind_shear_dir_degrees (reader.readElementText ());
        }
        else if (reader.name ().toString () == "visibility_statute_mi") {
            Q_ASSERT (reader.name () == QString ("visibility_statute_mi"));
            main_TAF->forecast_TAF->forecast->set_wind_shear_speed_kt (reader.readElementText ());
        }
        else if (reader.name ().toString () == "altim_in_hg") {
            Q_ASSERT (reader.name () == QString ("altim_in_hg"));
            main_TAF->forecast_TAF->forecast->set_altim_in_hg (reader.readElementText ());
        }
        else if (reader.name ().toString () == "vert_vis_ft") {
            Q_ASSERT (reader.name () == QString ("vert_vis_ft"));
            main_TAF->forecast_TAF->forecast->set_vert_vis_ft (reader.readElementText ());
        }
        else if (reader.name ().toString () == "wx_string") {
            Q_ASSERT (reader.name () == QString ("wx_string"));
            main_TAF->forecast_TAF->forecast->set_wx_string (reader.readElementText ());
        }
        else if (reader.name ().toString () == "not_decoded") {
            Q_ASSERT (reader.name () == QString ("not_decoded"));
            main_TAF->forecast_TAF->forecast->set_not_decoded (reader.readElementText ());
        }
        else if (reader.name ().toString () == "sky_condition") {
            //    Q_ASSERT (reader.name () == QString ("sky_condition")
            //              && reader.attributes ().hasAttribute ("sky_cover")
            //              && reader.attributes ().hasAttribute ("cloud_base_ft_agl")
            //              && reader.attributes ().hasAttribute ("cloud_type"));

            QList<std::tuple<QString, QString, QString>> tuple_List_sky_condition;

            std::tuple sky_condition{ reader.attributes ().value ("sky_cover").toString (),
                reader.attributes ().value ("cloud_base_ft_agl").toString (), reader.attributes ().value ("cloud_type").toString () };
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
        }
        else if (reader.name ().toString () == "turbulence_condition") {
            qDebug () << reader.attributes ().value ("turbulence_intensity").toString ()
                      << reader.attributes ().value ("turbulence_min_alt_ft_agl").toString ()
                      << reader.attributes ().value ("turbulence_max_alt_ft_agl").toString ();
        }
        else if (reader.name ().toString () == "icing_condition") {
            qDebug () << reader.attributes ().value ("icing_intensity").toString () << reader.attributes ().value ("icing_min_alt_ft_agl").toString ()
                      << reader.attributes ().value ("icing_max_alt_ft_agl").toString ();
        }
        else {
            reader.skipCurrentElement ();
        }
        reader.readNext ();
    }
}

/*

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
