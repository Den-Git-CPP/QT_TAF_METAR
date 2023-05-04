#pragma once
#include "./include/metar.h"
#include "./include/taf.h"
#include <memory>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QXmlSimpleReader>
#include <QXmlStreamReader>

class XMLParser : public QObject {
    Q_OBJECT
  public:
    explicit XMLParser (QObject* parent = nullptr);
    ~XMLParser ();
    void set_dir_file_with_xml (QString const& dir);
    void set_buf_xml (QByteArray const& buff);

  public slots:
    std::shared_ptr<TAF> Read_XML ();

  private:
    QByteArray _buff{};
    //   QXmlStreamReader reader;
    QString _dir_file_with_xml{ "" };
};
