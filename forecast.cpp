#include "forecast.h"

Forecast::Forecast () {}

void Forecast::print ()
{

    for (auto elem : _tuple_list_sky_condition) {
        qDebug () << std::get<0> (elem) << "--" << std::get<1> (elem) << "--" << std::get<2> (elem);
    }
}

void Forecast::set_tuple_list_sky_condition (const QList<std::tuple<QString, QString, QString>> tuple_list_sky_condition)
{
    this->_tuple_list_sky_condition = tuple_list_sky_condition;
}
