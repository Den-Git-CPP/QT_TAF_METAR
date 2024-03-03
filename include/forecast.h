#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Forecast {

  public:
    Forecast ();
    ~Forecast ();
    std::string getForecast () const;
    bool flag_Airport{ false };
    bool flag_TAF{ false };
    bool flag_SPECI{ false };
    bool flag_COR{ false };
    bool flag_NIL{ false };
    bool flag_AUTO{ false };
    bool flag_TEMPO{ false };
    bool flag_BECMG{ false };
    bool flag_NOSIG{ false };
    std::unique_ptr<std::string> Airport{ nullptr };
    std::unique_ptr<std::string> Type_Forecast{ nullptr };
    std::unique_ptr<std::string> Time_Group{ nullptr };
    std::unique_ptr<std::string> Time_Date_Group{ nullptr };
    std::unique_ptr<std::string> Wind_Group{ nullptr };
    std::unique_ptr<std::string> Var_Wind_Group{ nullptr };
    std::unique_ptr<std::string> Visib_Group{ nullptr };
    std::unique_ptr<std::string> Visib_Min_Group{ nullptr };
    std::unique_ptr<std::string> Visib_RNW_Group{ nullptr };
    std::unique_ptr<std::string> Weather_Group{ nullptr };
    std::unique_ptr<std::string> Temperature_Group{ nullptr };
    std::unique_ptr<std::string> Pressure_Group{ nullptr };
    std::unique_ptr<std::string> Probably{ nullptr };
    std::vector<std::unique_ptr<std::string>> v_Cloud_Group{};
    std::vector<std::unique_ptr<std::string>> v_Weather_Group{};
};
