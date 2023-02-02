#include "xmlparser.h"

XMLParser::XMLParser (QObject* parent) : QObject (parent)
{
}

void XMLParser::Read ()
{
    QFile file ("./file.xml");
    if (!file.open (QFile::ReadOnly | QFile::Text)) {
        qDebug () << "Cannot read file" << file.errorString ();
        exit (0);
    }
    QXmlStreamReader reader (&file);
    if (reader.readNextStartElement ()) {
        if (reader.name () == QString ("response")) {
            while (reader.readNextStartElement ()) {
                if (reader.name () == QString ("request_index")) {
                    qDebug () << reader.name () << "\t" << reader.readElementText ();
                }
                if (reader.name () == QString ("data_source") &&
                    reader.attributes ().hasAttribute ("name")) {
                    QString type_str = reader.attributes ().value ("name").toString (); // read atributes
                    qDebug () << reader.name () << "\t" << type_str;
                    reader.skipCurrentElement ();
                }
                if (reader.name () == QString ("request") &&
                    reader.attributes ().hasAttribute ("type")) {
                    QString type_str = reader.attributes ().value ("type").toString (); // read atributes
                    qDebug () << reader.name () << "\t" << type_str;
                    reader.skipCurrentElement ();
                }
                if (reader.name () == QString ("errors")) {
                    while (reader.readNextStartElement ()) {
                        if (reader.name () == QString ("error")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                    }
                }
                if (reader.name () == QString ("warnings")) {
                    while (reader.readNextStartElement ()) {
                        if (reader.name () == QString ("warning")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                    }
                }
                if (reader.name () == QString ("time_taken_ms")) {
                    qDebug () << reader.name () << "\t" << reader.readElementText ();
                }
                if (reader.name () == QString ("data") &&
                    reader.attributes ().hasAttribute ("num_results")) {
                    QString type_str =
                      reader.attributes ().value ("num_results").toString (); // read atributes
                    qDebug () << reader.name () << "\t" << type_str;
                }
                if (reader.name () == QString ("TAF")) {
                    while (reader.readNextStartElement ()) {
                        if (reader.name () == QString ("raw_text")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("station_id")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("issue_time")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("bulletin_time")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("valid_time_from")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("valid_time_to")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("latitude")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("longitude")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("elevation_m")) {
                            qDebug () << reader.name () << "\t"
                                      << reader.readElementText ();
                        }
                        if (reader.name () == QString ("forecast")) {
                            while (reader.readNextStartElement ()) {
                                if (reader.name () ==
                                    QString ("fcst_time_from")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("fcst_time_to")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("change_indicator")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () == QString ("probability")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("time_becoming")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("wind_dir_degrees")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("wind_speed_kt")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("wind_gust_kt")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                    QString ("visibility_statute_mi")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () == QString ("wx_string")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () == QString ("not_decoded")) {
                                    qDebug () << reader.name () << "\t"
                                              << reader.readElementText ();
                                }
                                if (reader.name () ==
                                      QString ("sky_condition") &&
                                    reader.attributes ().hasAttribute (
                                      "sky_cover") &&
                                    reader.attributes ().hasAttribute (
                                      "cloud_base_ft_agl")) {
                                    QString sky_cover_str =
                                      reader.attributes ().value ("sky_cover").toString ();
                                    QString cloud_base_ft_agl_str =
                                      reader.attributes ()
                                        .value ("cloud_base_ft_agl")
                                        .toString (); // read atributes

                                    qDebug () << "sky_cover_str"
                                              << "\t" << sky_cover_str << "\n"
                                              << "cloud_base_ft_agl_str"
                                              << "\t" << cloud_base_ft_agl_str;
                                    reader.skipCurrentElement ();
                                }
                            } // while forecast
                        }     // FORECAST
                    }         // while TAF
                }             // TAF
            }                 // while
        }
    }
}
