#pragma once

#include <QDebug>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>

class Downloader : public QObject
{
  Q_OBJECT
public:
  explicit Downloader(QObject* parent = nullptr);

public slots:
  void getData();
  void onResult(QNetworkReply* reply);
  void set_name_airport(QString const& name);

private:
  QNetworkAccessManager* manager;
  QString _name_airport{ "" };
};
