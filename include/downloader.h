#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>

class Downloader : public QObject {
    Q_OBJECT
  public:
    explicit Downloader (QObject* parent = nullptr);
    QByteArray* buff;
    QString ErrorString{};
  signals:
    void onReady ();
    void ErrorDownload ();

  public slots:
    void getData (const QString& name);   // Метод инициализации запроса на получение данных
    void onResult (QNetworkReply* reply); // Слот обработки ответа о полученных данных

  private:
    QNetworkAccessManager* manager; // менеджер сетевого доступа
};
