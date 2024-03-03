#include "include/forecast.h"

#include <iostream>
#include <tuple>
#include <functional>

Forecast::Forecast () {}

Forecast::~Forecast () {}

std::string Forecast::getForecast () const
{
    std::string AllDataForecast{};
    if (flag_TAF) {
        AllDataForecast.append ("ПРОГНОЗ: ");
    }
    if (flag_TEMPO) {
        AllDataForecast.append ("\n-ВРЕМЕНАМИ: ");
    };
    if (flag_BECMG) {
        AllDataForecast.append ("\n-ПОСТЕПЕННО ");
    };

    if (Time_Date_Group) {
        AllDataForecast.append (*Time_Date_Group).append ("\n");
    };

    if (Wind_Group) {
        AllDataForecast.append (*Wind_Group).append ("\n");
    };

    if (Var_Wind_Group) {
        AllDataForecast.append (*Var_Wind_Group).append ("\n");
    };
    if (Visib_Group) {
        AllDataForecast.append (*Visib_Group).append ("\n");
    };

    if (Visib_Min_Group) {
        AllDataForecast.append (*Visib_Min_Group).append ("\n");
    };
    if (Visib_RNW_Group) {
        AllDataForecast.append (*Visib_RNW_Group).append ("\n");
    };
    for (const auto& elem : v_Cloud_Group) {
        AllDataForecast.append (*elem).append ("\n");
    }

    for (const auto& elem : v_Weather_Group) {
        AllDataForecast.append (*elem).append ("\n");
    }

    if (Weather_Group) {
        AllDataForecast.append (*Weather_Group).append ("\n");
    };
    if (Temperature_Group) {
        AllDataForecast.append (*Temperature_Group).append ("\n");
    };
    if (Pressure_Group) {
        AllDataForecast.append (*Pressure_Group).append ("\n");
    };
    if (Probably) {
        AllDataForecast.append (*Probably).append ("\n");
    };
    if (flag_NOSIG) {
        AllDataForecast.append ("Без существенных изменений.\n");
    };

    return AllDataForecast;
}
