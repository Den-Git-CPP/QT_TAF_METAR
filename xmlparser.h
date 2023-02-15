#pragma once
#include "maintaf.h"

#include <QDebug>
#include <QFile>
#include <QObject>
#include <QXmlSimpleReader>
#include <QXmlStreamReader>

class XMLParser {

  public:
    XMLParser ();

    ~XMLParser ();

    void read_TAF ();
    void read_forecast (Forecast_TAF* inTAF);
    // MainTAF get (MainTAF* IN_main_taf);

  public slots:
    void Read ();

  private:
    QXmlStreamReader reader;
    MainTAF* _main_taf = nullptr;
};
