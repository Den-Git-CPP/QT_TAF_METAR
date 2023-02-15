#include "forecast.h"

Forecast::Forecast () {}

void Forecast::set_condition (const QString name_list_condion, const std::tuple<QString, QString, QString> node)
{

    if (name_list_condion == "sky_condition") {
        this->_tuple_list_sky_condition.append (node);
    }
    else if (name_list_condion == "turbulence_condition") {
        this->_turbulence_list_condition.append (node);
    }
    else if (name_list_condion == "icing_condition") {
        this->_icing_list_condition.append (node);
    }
    else
        qDebug () << "Condition not known";
}
