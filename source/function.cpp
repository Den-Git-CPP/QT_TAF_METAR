#include "./include/function.h"

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
    return _kt_to_ms = QString::number (static_cast<int> (round (0.5 * _kt_to_ms.toDouble ())));
}
QString Function::convert_ft_to_m (QString& _ft_to_m)
{ //
    return _ft_to_m = QString::number (static_cast<int> (0.3 * _ft_to_m.toDouble ()));
}
QString Function::convert_mi_to_m (QString& _mi_to_m)
{ //
    return _mi_to_m = QString::number (static_cast<int> (1000 * round (1.609344 * _mi_to_m.toDouble ())));
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

QString Function::replace_cloud_type (QString& cloud_type_)
{
    cloud_type_.replace ("CB", " (кучеводождевая)");
    cloud_type_.replace ("TCU", " (мощно-кучеводождевая)");
    cloud_type_.replace ("CU", " (кучеводождевая)");
    return cloud_type_;
}

void Function::replace_tuple_sky_condition (std::tuple<QString, QString, QString>& tuple_list_sky_condition_)
{
    replace_sky_cover (std::get<0> (tuple_list_sky_condition_));
    convert_ft_to_m (std::get<1> (tuple_list_sky_condition_));
    replace_cloud_type (std::get<2> (tuple_list_sky_condition_));
}

void Function::replace_turbulence_condition (std::tuple<QString, QString, QString>& turbulence_list_condition_)
{ // turbulence_intensity [0-9]
  // turbulence_min_alt_ft_agl
  // turbulence_max_alt_ft_agl
    convert_ft_to_m (std::get<1> (turbulence_list_condition_));
    convert_ft_to_m (std::get<2> (turbulence_list_condition_));
}

void Function::replace_icing_condition (std::tuple<QString, QString, QString>& icing_list_condition_)
{ // icing_intensity [0-9]
    // icing_min_alt_ft_agl
    // icing_max_alt_ft_agl
    convert_ft_to_m (std::get<1> (icing_list_condition_));
    convert_ft_to_m (std::get<2> (icing_list_condition_));
}
