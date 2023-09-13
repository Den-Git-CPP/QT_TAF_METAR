#pragma once
#include "./include/forecast_title.h"
#include "./include/metar.h"
#include "./include/taf.h"
#include <memory>
#include <QDebug>
#include <QObject>
#include <QXmlStreamReader>
#include <tuple>
#include <type_traits>

class XMLParser : public QObject {
    Q_OBJECT
  public:
    explicit XMLParser (QObject* parent = nullptr);
    ~XMLParser ();
    void set_vec_buf_xml (const std::vector<std::tuple<QString, QString>>& in_vec_tuple_data_for_parsing);
    void fill_u_ptr_Forecast ();
    std::unique_ptr<TAF> taf     = nullptr;
    std::unique_ptr<METAR> metar = nullptr;

  private:
    QXmlStreamReader xmlReader;
    std::vector<std::tuple<QString, QString>> vec_tuple_data_for_parsing;
};
