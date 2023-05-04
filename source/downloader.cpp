#include "./include/downloader.h"

Downloader::Downloader (QObject* parent) : QObject (parent)
{
    manager = new QNetworkAccessManager ();
    connect (manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData ()
{
    QUrl url ("http://www.aviationweather.gov/adds/dataserver_current/"
              "httpparam?dataSource=tafs&requestType=retrieve&format=xml&stationString="
              + _name_airport + "&hoursBeforeNow=1");

    QNetworkRequest request;             // Отправляемый запрос
    request.setUrl (url);                // Устанавлвиваем URL в запрос
    auto reply = manager->get (request); // Выполняем запрос
    reply->setProperty (_typeforecast, "Taf");

    url = "http://www.aviationweather.gov/adds/dataserver_current/"
          "httpparam?dataSource=metars&requestType=retrieve&format=xml&stationString="
        + _name_airport + "&hoursBeforeNow=1";

    request.setUrl (url);
    auto reply2 = manager->get (request);
    reply2->setProperty (_typeforecast, "Metar");
}

void Downloader::onResult (QNetworkReply* reply)
{
    if (reply->error ()) {
        qDebug () << "ERROR";
        qDebug () << reply->errorString ();
    }
    else {
        // _dir_file_with_xml_for_parser = "./" + _name_airport + "_" + reply->property (_typeforecast).toString () + ".xml";

        // QFile* file     = new QFile (_dir_file_with_xml_for_parser);
        buff = reply->readAll ();
        //        if (file->open (QFile::WriteOnly)) {
        //            file->write (reply->readAll ());
        //            file->close ();
        //            // qDebug () << "Downloading is completed" << _dir_file_with_xml_for_parser;
        //            emit onReady ();
        //        }
        emit onReady ();
    }
}

void Downloader::set_name_airport (QString const& name) { _name_airport = name; }

QString Downloader::get_name_airport () { return _name_airport; }

// QString Downloader::get_dir_file_with_xml_for_parser () { return this->_dir_file_with_xml_for_parser; }

QByteArray Downloader::get_buff () { return this->buff; }
