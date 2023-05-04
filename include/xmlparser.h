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
    void set_buf_xml (QByteArray const& buff);
    void get_buf_xml (QByteArray const& buff);
    template <class T> std::shared_ptr<T> Read_XML ();

  public slots:

    QVariant get_result_parser ();

  private:
    QByteArray _buff{};
    QString _dir_file_with_xml{ "" };
};
