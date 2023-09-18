#pragma once
#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QString>
#include <QTextStream>
class Function {
  public:
    Function ();
    ~Function ();
    ;

  protected:
    QString replace_id_staion (const QString& _raw_str);
    QString replace_raw_text (const QString& _raw_text);
    QString replace_time (const QString& _time);
    QString replace_change_indicator (const QString& _change_indicator);
    QString replace_wx_string (const QString& _wx_string);
    QString convert_kt_to_ms (const QString& _kt_to_ms);
    QString convert_ft_to_m (const QString& _ft_to_m);
    QString convert_mi_to_m (const QString& mi_to_m);
    QString convert_inchHg_to_hPa (const QString& inchHg);
    QString convert_inchHg_to_mmHg (const QString& inchHg);

    QString replace_sky_cover (QString& sky_cover_);
    QString replace_cloud_type (QString& cloud_type_);
    QMap<QString, QString> AMOFSG_Dictionary;
    void Load_AMOFSG_Dictionary ();
};
