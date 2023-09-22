#pragma once
#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QString>
#include <QVector>

enum From_To {
    kt_to_ms,      // км в м/с
    ft_to_m,       // футы в м
    mi_to_m,       // мили в м
    inchHg_to_hPa, // Дюймы ртутного столба в Гектопаскаль
    inchHg_to_mmHg // Дюймы ртутного столба в Миллиметры ртутного столба
};

class Function {
  public:
    Function ();
    ~Function ();

  protected:
    QString replace_text (const QString& _text);
    QString replace_val_from_to (const From_To& sign_val, const QString& _text);
    QString replace_raw_text (const QString& _raw_text);
    QString replace_time (const QString& _time);
    QMap<QString, QString> All_Dictionary;
    void Load_AMOFSG_Dictionary ();
};
