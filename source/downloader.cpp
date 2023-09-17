#include "./include/downloader.h"
Downloader::Downloader (QObject* parent) : QObject (parent)
{
    manager = new QNetworkAccessManager (this);
    connect (manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getDataForecast ()
{
    QMultiMapIterator<QString, QString> i (map_weather_forecast_sign);

    while (i.hasNext ()) {
        i.next ();
        weather_forecast_sign_ = i.key ();
        airport_IKAO_name_     = i.value ();
        QUrl url               = "http://www.aviationweather.gov/adds/dataserver_current/"
                                 "httpparam?dataSource="
                 + weather_forecast_sign_ + "&requestType=retrieve&format=xml&stationString=" + airport_IKAO_name_ + "&hoursBeforeNow=1";
        getData (url);
    }

    // Загрузка завершена
    emit onReady ();
    v_storage_forecast.clear ();
}

void Downloader::onResult (QNetworkReply* pReplay)
{
    // Получить информацию об ответе
    if (pReplay->error ()) {
        // Показываем информацию об ошибках
        qDebug () << "ERROR";
        qDebug () << pReplay->errorString ();
    }
    else {
        pReplay->deleteLater ();
        QByteArray buff = pReplay->readAll ();
        //        QFile* file     = new QFile ("./file_" + QDateTime::currentDateTime ().toString ("yyyy_MM_dd_hhmmss") + ".xml");
        //        // Создаём файл или открываем его на перезапись ...
        //        if (file->open (QFile::WriteOnly)) {
        //            file->write (buff); // ... и записываем всю информацию со
        //            file->close ();     // закрываем файл
        //            qDebug () << "Downloading is completed";
        //            emit onReady (); // Посылаем сигнал о завершении получения файла
        //        }

        v_storage_forecast.emplace_back (std::move (std::make_tuple (std::move (weather_forecast_sign_), std::move (buff.data ()))));
    }
}
void Downloader::set_name_airport (const QString& newAirport_IKAO_name)
{
    map_weather_forecast_sign.clear ();
    map_weather_forecast_sign.insert ("tafs", newAirport_IKAO_name);
    map_weather_forecast_sign.insert ("metars", newAirport_IKAO_name);
}

std::vector<std::tuple<QString, QString>> Downloader::get_vec_buf_xml ()
{ //
    return this->v_storage_forecast;
}

void Downloader::getData (QUrl in_url)
{
    // Построить запрос
    QNetworkRequest request;
    request.setUrl (in_url);
    // послать запрос
    manager->get (request);
    // Запускаем локальный цикл обработки событий, ожидаем окончания ответа и
    QEventLoop eventLoop;
    QObject::connect (manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec ();
}
