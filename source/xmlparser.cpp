
#include "./include/xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent) {}

XMLParser::~XMLParser () {}

void XMLParser::set_vec_buf_xml (const std::vector<std::tuple<QString, QByteArray> >& in_vec_tuple_data_for_parsing)
{
    vec_tuple_data_for_parsing = std::move (in_vec_tuple_data_for_parsing);
    qDebug () << "set_vec_buf_xml";
}

void XMLParser::create_shr_ptr_forecast ()
{
    for (auto const& i : vec_tuple_data_for_parsing) {
        _buff = std::get<1> (i);

        if (std::get<0> (i) == "Taf") {
            xml_taf = Read_XML<TAF> ();
        }
        else if (std::get<0> (i) == "Metar") {
            xml_metar = Read_XML<METAR> ();
        }
    }
}

template <class T> std::shared_ptr<T> XMLParser::Read_XML ()
{
    //    auto forecast_title = std::shared_ptr<Forecast_Title> ();

    if (std::is_same<T, TAF>::value) {
        qDebug () << "TAF\n";
        auto oz = std::shared_ptr<T> ();
    }
    else if (std::is_same<T, METAR>::value) {
        qDebug () << "METAR\n";
        auto oz = std::shared_ptr<T> ();
    }

    //  QXmlStreamReader reader (_buff);

    //    reader.readNext ();
    //    while (!reader.atEnd () && !reader.hasError ()) {

    //        QXmlStreamReader::TokenType token = reader.readNext ();
    //     //   qDebug () << token << "\n";
    //        if (token == QXmlStreamReader::StartDocument) {
    //            continue;
    //        }
    //        if (token == QXmlStreamReader::StartElement) {
    //            if (reader.name ().toString () == "response") {
    //                continue;
    //            }
    //            else if (reader.name ().toString () == "request_index") {
    //                forecast_title->set_request_index (reader.readElementText ());
    //            }
    //            else if (reader.name ().toString () == "data_source") {
    //                forecast_title->set_name (reader.attributes ().value ("name").toString ());
    //                /* создаем std::shared_ptr по типу data_source*/

    //                if (reader.attributes ().value ("name").toString () == "tafs") {
    //                  //  auto main_forecast = std::shared_ptr<TAF> ();
    //                }
    //                else if (reader.attributes ().value ("name").toString () == "metars") {
    //                  //  auto main_forecast = std::shared_ptr<METAR> ();
    //                }
    //                reader.skipCurrentElement ();
    //            }
    //            else if (reader.name ().toString () == "request") {
    //                forecast_title->set_type (reader.attributes ().value ("type").toString ());
    //                reader.skipCurrentElement ();
    //            }
    //            else if (reader.name ().toString () == "errors") {
    //                QStringList errors_list;
    //                while (reader.readNextStartElement ()) {
    //                    if (reader.name () == QString ("error")) {
    //                        errors_list.append (reader.readElementText ());
    //                    }
    //                }
    //                forecast_title->set_erorrs (errors_list);
    //            }
    //            else if (reader.name ().toString () == "warnings") {
    //                QStringList warnings_list;
    //                while (reader.readNextStartElement ()) {
    //                    if (reader.name () == QString ("warning")) {
    //                        warnings_list.append (reader.readElementText ());
    //                    }
    //                }
    //                forecast_title->set_warnings (warnings_list);
    //            }
    //            else if (reader.name ().toString () == "time_taken_ms") {
    //                forecast_title->set_time_taken_ms (reader.readElementText ());
    //            }
    //            else if (reader.name ().toString () == "data") {
    //                forecast_title->set_num_results (reader.attributes ().value ("num_results").toString ());

    //            } /*end forecast_title*/
    //            else if (reader.name ().toString () == "TAF") {
    //                auto forecast_taf = std::shared_ptr<Forecast_TAF> ();
    //                while (reader.readNextStartElement ()) {
    //                    if (reader.name ().toString () == "raw_text") {
    //                        forecast_taf->set_raw_text (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "station_id") {
    //                        forecast_taf->set_station_id (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "issue_time") {
    //                        forecast_taf->set_issue_time (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "bulletin_time") {
    //                        forecast_taf->set_bulletin_time (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "valid_time_from") {
    //                        forecast_taf->set_valid_time_from (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "valid_time_to") {
    //                        forecast_taf->set_valid_time_to (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "remarks") {
    //                        forecast_taf->set_remarks (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "latitude") {
    //                        forecast_taf->set_latitude (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "longitude") {
    //                        forecast_taf->set_longitude (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "elevation_m") {
    //                        forecast_taf->set_elevation_m (reader.readElementText ());
    //                    }
    //                    else if (reader.name ().toString () == "forecast") {
    //                        //   read_forecast
    //                        auto forecast = std::shared_ptr<Forecast> ();
    //                        while (reader.readNextStartElement ()) {
    //                            if (reader.name ().toString () == "fcst_time_from") {
    //                                forecast->set_fcst_time_from (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "fcst_time_to") {
    //                                forecast->set_fcst_time_to (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "change_indicator") {
    //                                forecast->set_change_indicator (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "time_becoming") {
    //                                forecast->set_time_becoming (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "probability") {
    //                                forecast->set_probability (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wind_dir_degrees") {
    //                                forecast->set_wind_dir_degrees (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wind_speed_kt") {
    //                                forecast->set_wind_speed_kt (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wind_gust_kt") {
    //                                forecast->set_wind_gust_kt (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wind_shear_hgt_ft_agl") {
    //                                forecast->set_wind_shear_hgt_ft_agl (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wind_shear_dir_degrees") {
    //                                forecast->set_wind_shear_dir_degrees (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wind_shear_speed_kt") {
    //                                forecast->set_wind_shear_dir_degrees (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "visibility_statute_mi") {
    //                                forecast->set_visibility_statute_mi (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "altim_in_hg") {
    //                                forecast->set_altim_in_hg (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "vert_vis_ft") {
    //                                forecast->set_vert_vis_ft (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "wx_string") {
    //                                forecast->set_wx_string (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "not_decoded") {
    //                                forecast->set_not_decoded (reader.readElementText ());
    //                            }
    //                            else if (reader.name ().toString () == "sky_condition") {
    //                                //      Q_ASSERT(reader.name() == QString("sky_condition") &&
    //                                //               reader.attributes().hasAttribute("sky_cover") &&
    //                                //               reader.attributes().hasAttribute("cloud_base_ft_agl"));

    //                                forecast->set_condition ("sky_condition", std::make_tuple (reader.attributes ().value ("sky_cover").toString (),
    //                                                                            reader.attributes ().value ("cloud_base_ft_agl").toString (),
    //                                                                            reader.attributes ().value ("cloud_type").toString ()));
    //                            }
    //                            else if (reader.name ().toString () == "turbulence_condition") {
    //                                Q_ASSERT (reader.name () == QString ("turbulence_condition") && reader.attributes ().hasAttribute ("turbulence_intensity")
    //                                          && reader.attributes ().hasAttribute ("turbulence_min_alt_ft_agl")
    //                                          && reader.attributes ().hasAttribute ("turbulence_max_alt_ft_agl"));

    //                                forecast->set_condition ("turbulence_condition", std::make_tuple (reader.attributes ().value ("turbulence_intensity").toString (),
    //                                                                                   reader.attributes ().value ("turbulence_min_alt_ft_agl").toString (),
    //                                                                                   reader.attributes ().value ("turbulence_max_alt_ft_agl").toString ()));
    //                            }
    //                            else if (reader.name ().toString () == "icing_condition") {
    //                                Q_ASSERT (reader.name () == QString ("icing_condition") && reader.attributes ().hasAttribute ("icing_intensity")
    //                                          && reader.attributes ().hasAttribute ("icing_min_alt_ft_agl")
    //                                          && reader.attributes ().hasAttribute ("icing_max_alt_ft_agl"));

    //                                forecast->set_condition ("icing_condition", std::make_tuple (reader.attributes ().value ("icing_intensity").toString (),
    //                                                                              reader.attributes ().value ("icing_min_alt_ft_agl").toString (),
    //                                                                              reader.attributes ().value ("icing_max_alt_ft_agl").toString ()));
    //                            }
    //                            else {
    //                                reader.skipCurrentElement ();
    //                            }
    //                            reader.readNext ();
    //                        }
    //                        if (QXmlStreamReader::EndElement && reader.name ().toString () == "forecast") {

    //                            forecast_taf->v_forecasts.emplace_back (std::move (forecast));
    //                        } // end read forecast
    //                    }

    //                } // end while Forecast_TAF
    //                if (QXmlStreamReader::EndElement && reader.name ().toString () == "TAF") {

    //                    // main_forecast->v_forecasttaf.emplace_back (std::move (forecast_taf));
    //                }
    //            } // while end TAF
    //        }

    //    } // while end file

    //    if (reader.hasError ()) {
    //        qDebug () << reader.errorString ();
    //        exit (0);
    //    }

    return std::shared_ptr<T> ();
}
