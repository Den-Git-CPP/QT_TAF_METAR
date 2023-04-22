
#include "./include/xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent) {}

XMLParser::~XMLParser () {}

void XMLParser::set_dir_file_with_xml (const QString& dir) { this->_dir_file_with_xml = dir; }

void XMLParser::Read_XML (std::shared_ptr<TAF> taf_)
{
    auto taf = std::make_shared<TAF> ();
    QFile file (_dir_file_with_xml);
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
                taf->ForecastTitle->set_request_index (reader.readElementText ());
            }
            else if (reader.name ().toString () == "data_source") {
                taf->ForecastTitle->set_name (reader.attributes ().value ("name").toString ());
                reader.skipCurrentElement ();
            }
            else if (reader.name ().toString () == "request") {
                taf->ForecastTitle->set_type (reader.attributes ().value ("type").toString ());
                reader.skipCurrentElement ();
            }
            else if (reader.name ().toString () == "errors") {
                QStringList errors_list;
                while (reader.readNextStartElement ()) {
                    if (reader.name () == QString ("error")) {
                        errors_list.append (reader.readElementText ());
                    }
                }
                taf->ForecastTitle->set_erorrs (errors_list);
            }
            else if (reader.name ().toString () == "warnings") {
                QStringList warnings_list;
                while (reader.readNextStartElement ()) {
                    if (reader.name () == QString ("warning")) {
                        warnings_list.append (reader.readElementText ());
                    }
                }
                taf->ForecastTitle->set_warnings (warnings_list);
            }
            else if (reader.name ().toString () == "time_taken_ms") {
                taf->ForecastTitle->set_time_taken_ms (reader.readElementText ());
            }
            else if (reader.name ().toString () == "data") {
                taf->ForecastTitle->set_num_results (reader.attributes ().value ("num_results").toString ());
            }
            else if (reader.name ().toString () == "TAF") {
                auto forecast_taf = std::make_shared<Forecast_TAF> ();
                while (reader.readNextStartElement ()) {
                    if (reader.name ().toString () == "raw_text") {
                        forecast_taf->set_raw_text (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "station_id") {
                        forecast_taf->set_station_id (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "issue_time") {
                        forecast_taf->set_issue_time (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "bulletin_time") {
                        forecast_taf->set_bulletin_time (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "valid_time_from") {
                        forecast_taf->set_valid_time_from (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "valid_time_to") {
                        forecast_taf->set_valid_time_to (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "remarks") {
                        forecast_taf->set_remarks (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "latitude") {
                        forecast_taf->set_latitude (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "longitude") {
                        forecast_taf->set_longitude (reader.readElementText ());
                    }
                    else if (reader.name ().toString () == "elevation_m") {
                        forecast_taf->set_elevation_m (reader.readElementText ());
                    }
                    //                    else if (reader.name ().toString () == "forecast") {
                    //                        //   read_forecast (newTAF);
                    //                    }

                    //                    if (QXmlStreamReader::EndElement && reader.name ().toString () == "forecast") {
                    //                        forecast_taf->v_forecasts.emplace_back (std::move (forecast))
                    //                    }

                } // end while Forecast_TAF

                if (QXmlStreamReader::EndElement && reader.name ().toString () == "TAF") {
                    taf->v_forecasttaf.emplace_back (std::move (forecast_taf));
                }

            } // while end TAF
        }
    } // while end file
    if (reader.hasError ()) {
        qDebug () << reader.errorString ();
        return;
    }
    // qDebug () << "READ_END";
    taf_ = std::move (taf);
}

void XMLParser::read_forecast_taf ()
{
    //  auto forecast_taf = std::make_shared<Forecast_TAF> ();
    //    while (reader.readNextStartElement ()) {
    //        if (reader.name ().toString () == "raw_text") {
    //            forecast_taf->set_raw_text (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "station_id") {
    //            forecast_taf->set_station_id (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "issue_time") {
    //            forecast_taf->set_issue_time (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "bulletin_time") {
    //            forecast_taf->set_bulletin_time (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "valid_time_from") {
    //            forecast_taf->set_valid_time_from (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "valid_time_to") {
    //            forecast_taf->set_valid_time_to (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "remarks") {
    //            forecast_taf->set_remarks (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "latitude") {
    //            forecast_taf->set_latitude (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "longitude") {
    //            forecast_taf->set_longitude (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "elevation_m") {
    //            forecast_taf->set_elevation_m (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "forecast") {
    //            //   read_forecast (newTAF);
    //        }
    //    } // end while

    //    if (QXmlStreamReader::EndElement && reader.name ().toString () == "TAF") {
    //        taf_->v_forecasttaf.emplace_back (std::move (forecast_taf));
    //    }
}

void XMLParser::read_forecast ()
{
    //    Forecast* forecast = new Forecast;
    //    while (reader.readNextStartElement ()) {
    //        if (reader.name ().toString () == "fcst_time_from") {
    //            forecast->set_fcst_time_from (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "fcst_time_to") {
    //            forecast->set_fcst_time_to (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "change_indicator") {
    //            forecast->set_change_indicator (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "time_becoming") {
    //            forecast->set_time_becoming (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "probability") {
    //            forecast->set_probability (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wind_dir_degrees") {
    //            forecast->set_wind_dir_degrees (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wind_speed_kt") {
    //            forecast->set_wind_speed_kt (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wind_gust_kt") {
    //            forecast->set_wind_gust_kt (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wind_shear_hgt_ft_agl") {
    //            forecast->set_wind_shear_hgt_ft_agl (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wind_shear_dir_degrees") {
    //            forecast->set_wind_shear_dir_degrees (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wind_shear_speed_kt") {
    //            forecast->set_wind_shear_dir_degrees (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "visibility_statute_mi") {
    //            forecast->set_visibility_statute_mi (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "altim_in_hg") {
    //            forecast->set_altim_in_hg (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "vert_vis_ft") {
    //            forecast->set_vert_vis_ft (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "wx_string") {
    //            forecast->set_wx_string (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "not_decoded") {
    //            forecast->set_not_decoded (reader.readElementText ());
    //        }
    //        else if (reader.name ().toString () == "sky_condition") {
    //            //      Q_ASSERT(reader.name() == QString("sky_condition") &&
    //            //               reader.attributes().hasAttribute("sky_cover") &&
    //            //               reader.attributes().hasAttribute("cloud_base_ft_agl"));

    //            forecast->set_condition (
    //              "sky_condition", std::make_tuple (reader.attributes ().value ("sky_cover").toString (),
    //                                 reader.attributes ().value ("cloud_base_ft_agl").toString (), reader.attributes ().value ("cloud_type").toString ()));
    //        }
    //        else if (reader.name ().toString () == "turbulence_condition") {
    //            Q_ASSERT (reader.name () == QString ("turbulence_condition") && reader.attributes ().hasAttribute ("turbulence_intensity")
    //                      && reader.attributes ().hasAttribute ("turbulence_min_alt_ft_agl") && reader.attributes ().hasAttribute ("turbulence_max_alt_ft_agl"));

    //            forecast->set_condition ("turbulence_condition", std::make_tuple (reader.attributes ().value ("turbulence_intensity").toString (),
    //                                                               reader.attributes ().value ("turbulence_min_alt_ft_agl").toString (),
    //                                                               reader.attributes ().value ("turbulence_max_alt_ft_agl").toString ()));
    //        }
    //        else if (reader.name ().toString () == "icing_condition") {
    //            Q_ASSERT (reader.name () == QString ("icing_condition") && reader.attributes ().hasAttribute ("icing_intensity")
    //                      && reader.attributes ().hasAttribute ("icing_min_alt_ft_agl") && reader.attributes ().hasAttribute ("icing_max_alt_ft_agl"));

    //            forecast->set_condition ("icing_condition",
    //              std::make_tuple (reader.attributes ().value ("icing_intensity").toString (),
    //                reader.attributes ().value ("icing_min_alt_ft_agl").toString (), reader.attributes ().value ("icing_max_alt_ft_agl").toString ()));
    //        }
    //        else {
    //            reader.skipCurrentElement ();
    //        }
    //        reader.readNext ();
    //    }
    //    if (QXmlStreamReader::EndElement && reader.name ().toString () == "forecast") {
    //        //  inTAF->add_forecast (*forecast);
    //    }
    //    delete forecast;
}
