#pragma once
#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QString>
#include <QTextStream>
class Function {
  public:
    Function ();
    ~Function (){};

  protected:
    QString replace_id_staion (QString& _raw_str);
    QString replace_raw_text (QString& _raw_text);
    QString replace_time (QString& _time);
    QString replace_change_indicator (QString& _change_indicator);
    QString replace_wx_string (QString& _wx_string);

    QString convert_kt_to_ms (QString& _kt_to_ms);
    QString convert_ft_to_m (QString& _ft_to_m);
    QString convert_mi_to_m (QString& mi_to_m);
    QMap<QString, QString> AMOFSG_Dictionary;
    void Load_AMOFSG_Dictionary ();
    QString replace_sky_cover (QString& sky_cover_);
    QString replace_cloud_type (QString& cloud_type_);
    void replace_tuple_list_sky_condition (QList<std::tuple<QString, QString, QString>>& tuple_list_sky_condition);

    QList<std::tuple<QString, QString, QString>> replace_turbulence_list_condition (QList<std::tuple<QString, QString, QString>>& turbulence_list_condition_);

    QList<std::tuple<QString, QString, QString>> replace_icing_list_condition (QList<std::tuple<QString, QString, QString>>& icing_list_condition_);
};
