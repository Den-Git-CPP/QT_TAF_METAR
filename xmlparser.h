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
  explicit XMLParser(QObject *parent = nullptr);

  void read_TAF(MainTAF *main_TAF);
  void read_forecast(MainTAF *main_TAF);

public slots:
  void Read(MainTAF *main_TAF);

private:
  QXmlStreamReader reader;
  Forecast_TAF *forecast_TAF_node = nullptr;
};
