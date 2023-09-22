#include "./include/function.h"

Function::Function () { Function::Load_AMOFSG_Dictionary (); }
Function::~Function () {}
QString Function::replace_val_from_to (const From_To& sign_val, const QString& _text)
{
    QString val{};
    switch (sign_val) {
        case From_To::kt_to_ms: // км в м/с
            val = QString::number (static_cast<int> (round (0.5 * _text.toDouble ())));
            break;
        case From_To::ft_to_m: //
            val = QString::number (static_cast<int> (0.3 * _text.toDouble ()));
            break;
        case From_To::mi_to_m: //
            val = QString::number (static_cast<int> (1000 * round (1.609344 * _text.toDouble ())));
            break;
        case From_To::inchHg_to_hPa: //
            val = QString::number (static_cast<int> (round (33.8638 * _text.toDouble ())));
            break;
        case From_To::inchHg_to_mmHg: //
            val = QString::number (static_cast<int> (round (25.4 * _text.toDouble ())));
            break;
        default: val = "Not Converting";
    }
    return val;
}
QString Function::replace_raw_text (const QString& _raw_text)
{
    QString raw_text{ _raw_text };
    raw_text.replace ("TEMPO", "\n       TEMPO ");
    raw_text.replace ("BECMG", "\n       BECMG ");
    raw_text.replace ("FM", "\n       FM\t ");
    return raw_text;
}
QString Function::replace_time (const QString& _time)
{ // 2023-02-25T05:00:00Z
    QString format  = "yyyy-MM-ddThh:mm:ssZ";
    QDateTime valid = QDateTime::fromString (_time, format);
    return valid.time ().toString ("hh:mm") + "z  " + valid.date ().toString ("dd.MM.yyyy");
}
QString Function::replace_text (const QString& _wx_string)
{
    QString wx_string{};
    QList<QString> lst_weather_phenomenon{};
    lst_weather_phenomenon = _wx_string.split (' ');
    if ((!All_Dictionary.empty ()) && (!lst_weather_phenomenon.empty ())) {

        for (auto elem : lst_weather_phenomenon) {
            try {
                elem = All_Dictionary.value (elem);
            }
            catch (const std::exception&) {
                elem = "  КОД ЯВЛЕНИЯ ПОГОДЫ " + elem + " НЕ РАСШИФРОВАН";
            }
            wx_string.append (elem + " ");
        }
    }
    return wx_string;
}
void Function::Load_AMOFSG_Dictionary ()
{
    QVector<QString> v_file_path{
        ":/resource/AMOFSG_Dictionary.txt",      // словарь с явлениями погоды
        ":/resource/AirportName_Dictionary.txt", // словарь с названиями аэропортов
        ":/resource/Dictionary.txt"              // словарь с остальными термиинами
    };

    for (const auto& elem : v_file_path) {
        QFile file = elem;
        if (!file.open (QFile::ReadOnly | QFile::Text)) {
            qDebug () << "Can't open file Dictionary: " + elem;
            exit (EXIT_FAILURE);
        }
        while (!file.atEnd ()) {
            QString line  = file.readLine ();
            QString line1 = line.section ('/', 0, 0);
            QString line2 = line.section ('/', 1, 1);
            line2.chop (1); // убрали /n
            All_Dictionary [line1] = line2;
        }
    }
}
