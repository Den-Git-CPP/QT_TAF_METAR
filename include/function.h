#pragma once
// #include <QDebug>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cmath>

enum From_To {
    Time_Group,      // Время
    Time_Date_Group, // Время действия прогноза
    Wind_Group,      // Группа ветра
    Var_Wind_Group,  // Группа ветра c изменением направления
    Visib_Group,     // Группа видимость
    Visib_Min_Group,
    Visib_RNW_Group,
    v_Cloud_Group,
    Temperature_Group,
    Pressure_Group,
    Probably
};

class Function {
  public:
    Function ();
    ~Function ();
    std::map<std::string, std::string> All_Dictionary;

  protected:
    std::string replace_text (const std::string& _text);
    std::string replace_temperature (const std::string& Temperature_Group_text);
    std::string replace_val_from_to (const From_To& sign_val, const std::string& _text);
    void Load_AMOFSG_Dictionary ();
};
