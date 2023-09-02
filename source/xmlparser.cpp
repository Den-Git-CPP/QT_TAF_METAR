
#include "./include/xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent) {}

XMLParser::~XMLParser () {}

void XMLParser::set_vec_buf_xml (const std::vector<std::tuple<QString, QString> >& in_vec_tuple_data_for_parsing)
{
    vec_tuple_data_for_parsing = std::move (in_vec_tuple_data_for_parsing);
}

void XMLParser::fill_u_ptr_Forecast ()
{
    for (auto& [sign_buff, buff] : vec_tuple_data_for_parsing) {
        if (sign_buff == "tafs") {
            // Берем первый прогноз
            int startPos = buff.indexOf ("</TAF>") + 8;
            int endPos   = buff.indexOf ("</data>");
            int length   = (endPos - startPos);
            buff.remove (startPos, length);
            /*// Save to file
            QFile* file = new QFile ("G:\\file_" + QDateTime::currentDateTime ().toString ("yyyy_MM_dd_hhmmss") + ".xml");
            if (file->open (QFile::WriteOnly)) {
                file->write (buff.toUtf8 ());
                file->close ();
            }*/

            taf = std::make_unique<TAF> ();
            QXmlStreamReader reader (buff);
            reader.readNext ();
            while (!reader.atEnd () && !reader.hasError ()) {
                QXmlStreamReader::TokenType token = reader.readNext ();
                if (token == QXmlStreamReader::StartElement) {
                    continue;
                }
                else if (token == QXmlStreamReader::EndElement) {
                    continue;
                }
            }

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
                        continue;
                    }
                    else if (reader.name ().toString () == "data_source") {
                        continue;
                    }
                    else if (reader.name ().toString () == "request") {
                        continue;
                    }
                    else if (reader.name ().toString () == "errors") {
                        continue;
                    }
                    else if (reader.name ().toString () == "warnings") {
                        continue;
                    }
                    else if (reader.name ().toString () == "time_taken_ms") {
                        continue;
                    }
                    else if (reader.name ().toString () == "data") {
                        continue;
                    }
                    else if (reader.name ().toString () == "TAF") {
                        // read TAF
                        while (reader.readNextStartElement ()) {
                            if (reader.name ().toString () == "raw_text") {
                                taf->ForecastTAF->set_raw_text (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "station_id") {
                                taf->ForecastTAF->set_station_id (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "issue_time") {
                                taf->ForecastTAF->set_issue_time (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "bulletin_time") {
                                taf->ForecastTAF->set_bulletin_time (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "valid_time_from") {
                                taf->ForecastTAF->set_valid_time_from (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "valid_time_to") {
                                taf->ForecastTAF->set_valid_time_to (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "remarks") {
                                taf->ForecastTAF->set_remarks (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "latitude") {
                                taf->ForecastTAF->set_latitude (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "longitude") {
                                taf->ForecastTAF->set_longitude (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "elevation_m") {
                                taf->ForecastTAF->set_elevation_m (reader.readElementText ());
                            }
                            else if (reader.name ().toString () == "forecast") {
                                //   read_forecast
                                auto forecast = std::make_unique<Forecast> ();
                                while (reader.readNextStartElement ()) {
                                    if (reader.name ().toString () == "fcst_time_from") {
                                        forecast->set_fcst_time_from (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "fcst_time_to") {
                                        forecast->set_fcst_time_to (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "change_indicator") {
                                        forecast->set_change_indicator (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "time_becoming") {
                                        forecast->set_time_becoming (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "probability") {
                                        forecast->set_probability (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wind_dir_degrees") {
                                        forecast->set_wind_dir_degrees (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wind_speed_kt") {
                                        forecast->set_wind_speed_kt (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wind_gust_kt") {
                                        forecast->set_wind_gust_kt (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wind_shear_hgt_ft_agl") {
                                        forecast->set_wind_shear_hgt_ft_agl (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wind_shear_dir_degrees") {
                                        forecast->set_wind_shear_dir_degrees (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wind_shear_speed_kt") {
                                        forecast->set_wind_shear_dir_degrees (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "visibility_statute_mi") {
                                        forecast->set_visibility_statute_mi (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "altim_in_hg") {
                                        forecast->set_altim_in_hg (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "vert_vis_ft") {
                                        forecast->set_vert_vis_ft (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "wx_string") {
                                        forecast->set_wx_string (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "not_decoded") {
                                        forecast->set_not_decoded (reader.readElementText ());
                                    }
                                    else if (reader.name ().toString () == "sky_condition") {
                                        forecast->set_condition ("sky_condition", std::make_tuple (reader.attributes ().value ("sky_cover").toString (),
                                                                                    reader.attributes ().value ("cloud_base_ft_agl").toString (),
                                                                                    reader.attributes ().value ("cloud_type").toString ()));
                                    }
                                    else if (reader.name ().toString () == "turbulence_condition") {
                                        forecast->set_condition (
                                          "turbulence_condition", std::make_tuple (reader.attributes ().value ("turbulence_intensity").toString (),
                                                                    reader.attributes ().value ("turbulence_min_alt_ft_agl").toString (),
                                                                    reader.attributes ().value ("turbulence_max_alt_ft_agl").toString ()));
                                    }
                                    else if (reader.name ().toString () == "icing_condition") {
                                        forecast->set_condition ("icing_condition", std::make_tuple (reader.attributes ().value ("icing_intensity").toString (),
                                                                                      reader.attributes ().value ("icing_min_alt_ft_agl").toString (),
                                                                                      reader.attributes ().value ("icing_max_alt_ft_agl").toString ()));
                                    }
                                    else {
                                        reader.skipCurrentElement ();
                                    }
                                    reader.readNext ();
                                }
                                if (QXmlStreamReader::EndElement && reader.name ().toString () == "forecast") {
                                    taf->ForecastTAF->v_forecasts.emplace_back (std::move (forecast));
                                } // end read forecast
                            }
                        }
                        if (QXmlStreamReader::EndElement && reader.name ().toString () == "TAF") {
                            qDebug () << "End " << reader.name ().toString () << '\n';
                            // main_forecast->v_forecasttaf.emplace_back (std::move (forecast_taf));
                            reader.skipCurrentElement ();
                        }
                    } // end TAF
                }     // ensd start element
            }         // end while

            if (reader.hasError ()) {
                qDebug () << reader.errorString ();
                exit (0);
            }
        } // if end tafs
        if (sign_buff == "metars") {
            QFile* file = new QFile ("G:\\file_" + QDateTime::currentDateTime ().toString ("yyyy_MM_dd_hhmmss") + ".xml");
            if (file->open (QFile::WriteOnly)) {
                file->write (buff.toUtf8 ());
                file->close ();
            }

        } // if end metars
    }     // end for
}
