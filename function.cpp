#include "function.h"

#include <QList>

Function::Function () {}

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
    _raw_text.replace ("FM", "\n       FM\t ");
    return _raw_text;
}
QString Function::replace_time (QString& _time)
{
    // 2023-02-25T05:00:00Z
    QString format  = "yyyy-MM-ddThh:mm:ssZ";
    QDateTime valid = QDateTime::fromString (_time, format);
    _time           = valid.time ().toString ("hh:mm") + "z  " + valid.date ().toString ("dd.MM.yyyy");
    return _time;
}
QString Function::replace_change_indicator (QString& _change_indicator)
{
    _change_indicator.replace ("TEMPO", "ВРЕМЕНАМИ: ");
    _change_indicator.replace ("BECMG", "УСТОЙЧИВО: ");
    _change_indicator.replace ("FM", "ИЗМЕНЕНИЯ: ");
    return _change_indicator;
}
QString Function::replace_wx_string (QString& _wx_string)
{
    QList<QString> lst_weather_phenomenon{};
    lst_weather_phenomenon = _wx_string.split (' ');
    _wx_string.clear ();

    if ((!AMOFSG_Dictionary.empty ()) && (!lst_weather_phenomenon.empty ())) {

        for (auto elem : lst_weather_phenomenon) {
            try {
                elem = AMOFSG_Dictionary.value (elem);
            }
            catch (const std::exception&) {
                elem = "  КОД ЯВЛЕНИЯ ПОГОДЫ " + elem + " НЕ РАСШИФРОВАН";
            }
            _wx_string.append (elem + " ");
        }
    }

    return _wx_string;
}
QString Function::convert_kt_to_ms (QString& _kt_to_ms)
{
    //
    return _kt_to_ms = QString::number (static_cast<int> (0.514444 * _kt_to_ms.toDouble ()));
}
QString Function::convert_ft_to_m (QString& _ft_to_m)
{ //
    return _ft_to_m = QString::number (static_cast<int> (0.3048 * _ft_to_m.toDouble ()));
}
QString Function::convert_mi_to_m (QString& _mi_to_m)
{ //
    return _mi_to_m = QString::number (static_cast<int> (1609.1 * _mi_to_m.toDouble ()));
}

void Function::Load_AMOFSG_Dictionary ()
{
    QFile file (":/resource/AMOFSG_Dictionary.txt");
    if (!file.open (QFile::ReadOnly | QFile::Text)) {
        qDebug () << "Can't open file Dictionary AMOFSG_Dictionary.txt ";
        exit (EXIT_FAILURE);
    }

    while (!file.atEnd ()) {
        QString line  = file.readLine ();
        QString line1 = line.section ('/', 0, 0);
        QString line2 = line.section ('/', 1, 1);
        line2.chop (1); // убрали /n
        AMOFSG_Dictionary [line1] = line2;
    }
}
