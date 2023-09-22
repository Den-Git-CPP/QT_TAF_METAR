#include "./include/function.h"

Function::Function ()
{
    //
    Function::Load_AMOFSG_Dictionary ();
}

Function::~Function () {}

QString Function::replace_text (const QString& _text)
{ // replace_id_staion
    QString text{ _text };
    text.replace ("UUWW", "ВНУКОВО");
    text.replace ("UUЕЕ", "ШЕРЕМЕТЬЕВО");
    text.replace ("UUDD", "ДОМОДЕДОВО");

    // replace_text
    text.replace ("TEMPO", "ВРЕМЕНАМИ: ");
    text.replace ("BECMG", "УСТОЙЧИВО: ");
    text.replace ("FM", "ИЗМЕНЕНИЯ: ");

    // replace_sky_cover
    text.replace ("NSC", "Без существенной облачность ");
    text.replace ("SKC", "Небо чистое ");
    text.replace ("CLR", "Нет облачности ниже 3700м");
    text.replace ("BKN", "Значительная облачность   ");
    text.replace ("FEW", "Незначительная облачность ");
    text.replace ("OVC", "Сплошная облачность       ");
    text.replace ("SCT", "Рассеянная облачность     ");
    text.replace ("SKT", "SKT");
    text.replace ("OVCX", "OVCX");
    text.replace ("CAVOK", "Видимость более 10 км, нет облаков ниже 1500 м, нет явлений погоды и облачности ");

    // replace_text
    text.replace ("CB", " (кучеводождевая)");
    text.replace ("TCU", " (мощно-кучеводождевая)");
    text.replace ("CU", " (кучеводождевая)");
    return text;
}

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
/*
QString Function::replace_id_staion (const QString& _id_str)
{
    QString id{ _id_str };
    id.replace ("UUWW", "ВНУКОВО");
    id.replace ("UUЕЕ", "ШЕРЕМЕТЬЕВО");
    id.replace ("UUDD", "ДОМОДЕДОВО");
    return id;
}*/
QString Function::replace_raw_text (const QString& _raw_text)
{
    QString raw_text{ _raw_text };
    raw_text.replace ("TEMPO", "\n       TEMPO ");
    raw_text.replace ("BECMG", "\n       BECMG ");
    raw_text.replace ("FM", "\n       FM\t ");
    return raw_text;
}
QString Function::replace_time (const QString& _time)
{
    // 2023-02-25T05:00:00Z

    QString format  = "yyyy-MM-ddThh:mm:ssZ";
    QDateTime valid = QDateTime::fromString (_time, format);
    return valid.time ().toString ("hh:mm") + "z  " + valid.date ().toString ("dd.MM.yyyy");
} /*
 QString Function::replace_text (const QString& _change_indicator)
 {
     QString change_indicator{ _change_indicator };
     change_indicator.replace ("TEMPO", "ВРЕМЕНАМИ: ");
     change_indicator.replace ("BECMG", "УСТОЙЧИВО: ");
     change_indicator.replace ("FM", "ИЗМЕНЕНИЯ: ");
     return change_indicator;
 }*/

QString Function::replace_wx_string (const QString& _wx_string)
{
    QString wx_string{};
    QList<QString> lst_weather_phenomenon{};
    lst_weather_phenomenon = _wx_string.split (' ');
    if ((!AMOFSG_Dictionary.empty ()) && (!lst_weather_phenomenon.empty ())) {

        for (auto elem : lst_weather_phenomenon) {
            try {
                elem = AMOFSG_Dictionary.value (elem);
            }
            catch (const std::exception&) {
                elem = "  КОД ЯВЛЕНИЯ ПОГОДЫ " + elem + " НЕ РАСШИФРОВАН";
            }
            wx_string.append (elem + " ");
        }
    }
    return wx_string;
}
/*
 QString Function::convert_kt_to_ms (const QString& _kt_to_ms)
 { //
     return QString::number (static_cast<int> (round (0.5 * _kt_to_ms.toDouble ())));
 }
 QString Function::convert_ft_to_m (const QString& _ft_to_m)
 { //

     return QString::number (static_cast<int> (0.3 * _ft_to_m.toDouble ()));
 }
 QString Function::convert_mi_to_m (const QString& _mi_to_m)
 { //
     return QString::number (static_cast<int> (1000 * round (1.609344 * _mi_to_m.toDouble ())));
 }
 QString Function::convert_inchHg_to_hPa (const QString& inchHg)
 { // Дюймы ртутного столба в Гектопаскаль
     return QString::number (static_cast<int> (round (33.8638 * inchHg.toDouble ())));
 }
 QString Function::convert_inchHg_to_mmHg (const QString& inchHg)
 { // Дюймы ртутного столба в Миллиметры ртутного столба
     return QString::number (static_cast<int> (round (25.4 * inchHg.toDouble ())));
 }
 */
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
/*
QString Function::replace_sky_cover (QString& sky_cover_)
{
    sky_cover_.replace ("NSC", "Без существенной облачность ");
    sky_cover_.replace ("SKC", "Небо чистое ");
    sky_cover_.replace ("CLR", "Нет облачности ниже 3700м");
    sky_cover_.replace ("BKN", "Значительная облачность   ");
    sky_cover_.replace ("FEW", "Незначительная облачность ");
    sky_cover_.replace ("OVC", "Сплошная облачность       ");
    sky_cover_.replace ("SCT", "Рассеянная облачность     ");
    sky_cover_.replace ("SKT", "SKT");
    sky_cover_.replace ("OVCX", "OVCX");
    sky_cover_.replace ("CAVOK", "Видимость более 10 км, нет облаков ниже 1500 м, нет явлений погоды и облачности ");
    return sky_cover_;
}

QString Function::replace_text (QString& cloud_type_)
{
    cloud_type_.replace ("CB", " (кучеводождевая)");
    cloud_type_.replace ("TCU", " (мощно-кучеводождевая)");
    cloud_type_.replace ("CU", " (кучеводождевая)");
    return cloud_type_;
}
*/
