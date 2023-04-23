#pragma once
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

  public slots:
    std::shared_ptr<TAF> Read_XML ();

  private:
    QXmlStreamReader reader;
    QString _dir_file_with_xml{ "" };
};
