#pragma once

#include <QDebug>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>

class Downloader : public QObject {
  Q_OBJECT
public:
  explicit Downloader(QObject *parent = nullptr);
  QString get_name_airport();
  QString get_dir_file_with_xml_for_parser();

  void set_name_airport(QString const &name);
  void set_name_airport_typeforecast(QString const &name,QString const &typeforecast);

signals:
  void onReady();

public slots:
  void getData();
  void onResult(QNetworkReply *reply);

private:
  QNetworkAccessManager *manager;
  QString _name_airport{""};
    QString _typeforecast{""};
  QString _dir_file_with_xml_for_parser{""};
};
