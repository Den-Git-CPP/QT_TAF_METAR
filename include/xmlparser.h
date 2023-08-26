#pragma once
#include "./include/forecast_title.h"
#include "./include/metar.h"
#include "./include/taf.h"
#include <memory>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QXmlStreamReader>

class XMLParser : public QObject {
    Q_OBJECT
  public:
    explicit XMLParser (QObject* parent = nullptr);
    ~XMLParser ();
    void set_vec_buf_xml (const std::vector<std::tuple<QString, QByteArray>>& in_vec_tuple_data_for_parsing);
    void create_shr_ptr_forecast ();
    template <class T> std::shared_ptr<T> Read_XML ();

  private:
    std::vector<std::tuple<QString, QByteArray>> vec_tuple_data_for_parsing;
    QByteArray _buff{};
    std::shared_ptr<TAF> xml_taf ;
    std::shared_ptr<METAR> xml_metar;
};
