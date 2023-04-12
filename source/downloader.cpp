#include "./include/downloader.h"

Downloader::Downloader (QObject* parent) : QObject (parent)
{
    manager = new QNetworkAccessManager ();
    connect (manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData ()
{
    QUrl url ("http://www.aviationweather.gov/adds/dataserver_current/"
              "httpparam?dataSource=tafs&requestType=retrieve&format=xml&"
              "stationString="
              + _name_airport + "&hoursBeforeNow=1");
    QNetworkRequest request;
    request.setUrl (url);
    manager->get (request);
}

void Downloader::onResult (QNetworkReply* reply)
{
    if (reply->error ()) {
        qDebug () << "ERROR";
        qDebug () << reply->errorString ();
    }
    else {
        QFile* file = new QFile (_dir_file_with_xml_for_parser);
        if (file->open (QFile::WriteOnly)) {
            file->write (reply->readAll ());
            file->close ();
            //   qDebug () << "Downloading is completed";
            emit onReady ();
        }
    }
}

void Downloader::set_name_airport (const QString& name)
{
    _name_airport                 = name;
    _dir_file_with_xml_for_parser = "./file" + name + ".xml";
}

QString Downloader::get_name_airport () { return _name_airport; }

QString Downloader::get_dir_file_with_xml_for_parser () { return this->_dir_file_with_xml_for_parser; }
