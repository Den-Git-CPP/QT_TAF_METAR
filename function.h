#pragma once
#include <QDateTime>
#include <QFile>
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
};
