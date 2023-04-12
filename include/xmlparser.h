#pragma once
#include "./include/maintaf.h"

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QXmlSimpleReader>
#include <QXmlStreamReader>

class XMLParser : public QObject {
    Q_OBJECT
  public:
    explicit XMLParser (QObject* parent = nullptr);
    explicit XMLParser (MainTAF* main_taf_);
    ~XMLParser ();
    void set_dir_file_with_xml (QString const& dir);
    void read_TAF ();
    void read_forecast (Forecast_TAF* inTAF);

  public slots:
    void Read_XML ();

  private:
    QXmlStreamReader reader;
    MainTAF* _main_taf = nullptr;
    QString _dir_file_with_xml{ "" };
};
