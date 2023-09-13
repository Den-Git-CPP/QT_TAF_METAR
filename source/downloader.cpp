#include "./include/downloader.h"
Downloader::Downloader (QObject* parent) : QObject (parent) {}

void Downloader::getDataForecast ()
{
    QMultiMapIterator<QString, QString> i (map_weather_forecast_sign);
    while (i.hasNext ()) {
        i.next ();
        weather_forecast_sign_ = i.key ();
        airport_IKAO_name_     = i.value ();
        QUrl url               = "http://www.aviationweather.gov/adds/dataserver_current/"
                                 "httpparam?dataSource="
                 + weather_forecast_sign_
                 + "&requestType=retrieve&format=xml&stationString="
                   ""
                 + airport_IKAO_name_ + "&hoursBeforeNow=1";
        getData (url);
    }

    // Загрузка завершена
    emit onReady ();
}

void Downloader::set_name_airport (const QString& newAirport_IKAO_name)
{
    map_weather_forecast_sign.insert ("tafs", newAirport_IKAO_name);
    map_weather_forecast_sign.insert ("metars", newAirport_IKAO_name);
}

std::vector<std::tuple<QString, QString>> Downloader::get_vec_buf_xml () { return this->v_storage_gorecast; }

void Downloader::getData (QUrl in_url)
{
    // Построить запрос
    QNetworkRequest request;
    request.setUrl (in_url);

    QNetworkAccessManager* manager = new QNetworkAccessManager (this);
    // послать запрос
    QNetworkReply* pReplay = manager->get (request);

    // Запускаем локальный цикл обработки событий, ожидаем окончания ответа и
    QEventLoop eventLoop;
    QObject::connect (manager, &QNetworkAccessManager::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec ();
    // Получить информацию об ответе
    if (pReplay->error ()) {
        // Показываем информацию об ошибках
        qDebug () << "ERROR";
        qDebug () << pReplay->errorString ();
    }
    else {
        QString buff = QString (pReplay->readAll ());
        v_storage_gorecast.emplace_back (std::move (std::make_tuple (weather_forecast_sign_, std::move (buff))));
    }
    pReplay->deleteLater ();
}
