#pragma once
#include "maintaf.h"

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QXmlSimpleReader>
#include <QXmlStreamReader>

class XMLParser : public QObject {
    Q_OBJECT
  public:
    explicit XMLParser (QObject* parent = nullptr);
    explicit XMLParser (MainTAF* in_main_taf);
    ~XMLParser ();

    void read_TAF ();
    void read_forecast (Forecast_TAF* inTAF);
    MainTAF* get_inf_from_parser ();

  public slots:
    void Read_XML ();

  private:
    QXmlStreamReader reader;
    MainTAF* _main_taf = nullptr;
};
