#include "include/downloader.h"

Downloader::Downloader (QObject* parent) : QObject (parent)
{ // Инициализируем менеджер ...
    manager = new QNetworkAccessManager (this);
    buff    = new QByteArray ();
    // ... и подключаем сигнал о завершении получения данных к обработчику
    // полученного ответа
    connect (manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData (const QString& name)
{
    QUrl url ("https://aviationweather.gov/api/data/taf?ids=" + name + "&format=raw&metar=true");
    manager->get (QNetworkRequest (url)); // Выполняем запрос  // Выполняем запрос
}

void Downloader::onResult (QNetworkReply* reply)
{ // Если в процесе получения данных произошла ошибка
    if (reply->error ()) {
        // Сообщаем об этом и показываем информацию об ошибках
        ErrorString = reply->errorString ();
        emit ErrorDownload ();
    }
    else {
        buff->append (reply->readAll ());
        // сигнал забрать буффер
        emit onReady ();
    }
    reply->deleteLater ();
}
