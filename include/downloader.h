#pragma once
#include <memory>
#include <QEventLoop>
#include <QMultiMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>
class Downloader : public QObject {
    Q_OBJECT
  public:
    explicit Downloader (QObject* parent = nullptr);
    void set_name_airport (const QString& newAirport_IKAO_name);
    std::vector<std::tuple<QString, QByteArray>> get_vec_buf_xml ();
  signals:
    void onReady ();

  public slots:
    void getData (QUrl in_url);
    void getDataForecast ();

  private:
    QMultiMap<QString, QString> map_weather_forecast_sign; // QMultiMap (признак прогноза аэропорт)
    QString weather_forecast_sign_{};
    QString airport_IKAO_name_{};
    std::vector<std::tuple<QString, QByteArray>> v_storage_gorecast{};
};
