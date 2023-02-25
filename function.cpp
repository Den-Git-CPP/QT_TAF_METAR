#include "function.h"

QString Function::replace_id_staion (QString& _id_str)
{
    if (_id_str == "UUWW") {
        _id_str = "ВНУКОВО";
    };
    if (_id_str == "UUEE") {
        _id_str = "ШЕРЕМЕТЬЕВО";
    };
    if (_id_str == "UUDD") {
        _id_str = "ДОМОДЕДОВО";
    };
    return _id_str;
}
QString Function::replace_raw_text (QString& _raw_text)
{
    _raw_text.replace ("TEMPO", "\n       TEMPO ");
    _raw_text.replace ("BECMG", "\n       BECMG ");
    _raw_text.replace ("FM", "\n       FM ");
    return _raw_text;
}
QString Function::replace_time (QString& _bulletin_time)
{
    // 2023-02-25T05:00:00Z
    QString format  = "yyyy-MM-ddThh:mm:ssZ";
    QDateTime valid = QDateTime::fromString (_bulletin_time, format);
    _bulletin_time  = valid.time ().toString ("hh:mm") + " " + valid.date ().toString ("dd.MM.yyyy");
    return _bulletin_time;
}
QString Function::replace_change_indicator (QString& _change_indicator)
{
    _change_indicator.replace ("TEMPO", "ВРЕМЕНАМИ: ");
    _change_indicator.replace ("BECMG", "УСТОЙЧИВО: ");
    _change_indicator.replace ("FM", "ИЗМЕНЕНИЯ: ");
    return _change_indicator;
}

QString Function::convert_kt_to_ms (QString& _kt_to_ms) { return QString::number (_kt_to_ms.toDouble () * 0.514444); }

QString Function::convert_ft_to_m (QString& _ft_to_m) { return QString::number (_ft_to_m.toDouble () * 0.3048); }

QString Function::convert_mi_to_m (QString& _mi_to_m) { return QString::number (_mi_to_m.toDouble () * 1609.1); }
