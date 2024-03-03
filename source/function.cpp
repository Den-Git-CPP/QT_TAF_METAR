#include "include/function.h"

Function::Function ()
{
    if (All_Dictionary.empty ()) {
        Function::Load_AMOFSG_Dictionary ();
    }
}
Function::~Function () {}
std::string Function::replace_val_from_to (const From_To& sign_val, const std::string& _text)
{
    switch (sign_val) {
        case From_To::Time_Group: {
            std::string Time_Group{ _text.substr (0, 2) + " "   // День месяца
                                    + _text.substr (2, 2) + ":" // Часы
                                    + _text.substr (4, 2)       // Минуты
                                    + "utc" };
            return Time_Group;
        }
        case From_To::Time_Date_Group: {
            std::string Time_Date_Group{
                "c " + _text.substr (2, 2) + ":00utc "     // Часы
                + _text.substr (0, 2)                      // Число месяца
                + " по " + _text.substr (7, 2) + ":00utc " //  Часы
                + _text.substr (5, 2)                      // Число месяца
            };
            return Time_Date_Group;
        }
        case From_To::Wind_Group: {
            size_t found_G = _text.find ('G');
            if (found_G != std::string::npos) {
                return ("Ветер: " + _text.substr (0, 3) + "° ")
                  .append (std::to_string (std::stoi (_text.substr (3, 2))) + " м/с")
                  .append (" (порывы: " + std::to_string (std::stoi (_text.substr (6, 2))) + " м/с)");
            }
            else {
                return ("Ветер: " + _text.substr (0, 3) + "° ") //
                  .append (std::to_string (std::stoi (_text.substr (3, 2))) + " м/с");
            };
        }
        case From_To::Var_Wind_Group: {
            return "Ветер переменный: " + std::to_string (std::stoi (_text.substr (0, 3))) // от направления ветра в градусах
                   + "°-" + std::to_string (std::stoi (_text.substr (4, 3))) + "°"; // до направления ветра в градусах
        }
        case From_To::Visib_Group: {
            if (_text == "CAVOK") {
                return "Видимость более 10 км, нет облаков ниже 1500 м, нет явлений погоды и облачности";
            };
            if (_text == "9999") {
                return "Видимость: 10км.";
            }
            else {
                return "Видимость: " + std::to_string (std::stoi (_text)) + " м.";
            }
        }
        case From_To::Visib_Min_Group: {
            std::string Visib_Min_Group{ "Минимальная видимость: " + _text.substr (0, 4) };
            if (_text.size () == 5) {
                if (_text.at (4) == 'N') {
                    Visib_Min_Group.append (" на север.");
                }
                if (_text.at (4) == 'W') {
                    Visib_Min_Group.append (" на запад.");
                }
                if (_text.at (4) == 'S') {
                    Visib_Min_Group.append (" на юг.");
                }
                if (_text.at (4) == 'E') {
                    Visib_Min_Group.append (" на восток.");
                }
            }
            else if (_text.size () == 6) {
                if (_text.find ("NW") < _text.size ()) {
                    Visib_Min_Group.append (" на северо-запад.");
                };
                if (_text.find ("NE") < _text.size ()) {
                    Visib_Min_Group.append (" на северо-восток.");
                };
                if (_text.find ("SW") < _text.size ()) {
                    Visib_Min_Group.append (" на юго-запад.");
                };
                if (_text.find ("SE") < _text.size ()) {
                    Visib_Min_Group.append (" на юго-восток.");
                }
            }
            else {
                Visib_Min_Group = "Минимальная видимость не расшифрована.";
            };
            return Visib_Min_Group;
        }
        case From_To::Visib_RNW_Group: {
            std::string Visib_RNW{ "**********" };
            return Visib_RNW;
        }
        case From_To::v_Cloud_Group: {
            std::string v_Cloud_Group = replace_text (_text.substr (0, 3))                      // тип облачности
                                        + " на "                                                //
                                        + std::to_string (std::stoi (_text.substr (3, 3)) * 30) // на высоте
                                        + " м.";
            if (_text.find ("CB") < _text.size ()) {
                // есди есть призна СВ то обчаность куечво-дождевая
                v_Cloud_Group.append ("(кучево-дождевая)");
            };
            return v_Cloud_Group;
        }
        case From_To::Temperature_Group: {
            size_t found_slash  = _text.find ('/');
            float air_temp      = std::stof (replace_temperature (_text.substr (0, found_slash)));
            float dewpoint_temp = std::stof (replace_temperature (_text.substr (found_slash + 1, _text.size ())));

            float relative_humidity = ((6.1121 * exp ((18.678 - dewpoint_temp / 234.5) * dewpoint_temp / (257.14 + dewpoint_temp)))
                                        / (6.1121 * exp ((18.678 - air_temp / 234.5) * air_temp / (257.14 + air_temp))))
                                      * 100;
            return "Температура: " + std::to_string (static_cast<int> (std::round (air_temp))) + "°C\n" // температура ворздуха
                   + "Точка россы: " + std::to_string (static_cast<int> (std::round (dewpoint_temp))) + "°C\n" // точка россы
                   + "Влажность: " + std::to_string (static_cast<int> (std::round (relative_humidity))) + "%"; // Влажность
        }
        case From_To::Pressure_Group: {
            return "QNH: " + std::to_string (std::stoi (_text.substr (1, 4))) + " гПа ("                                // Давлением гПа
                   + std::to_string (static_cast<int> (0.75 * std::stoi (_text.substr (1, 4)))).append (" мм рт ст.)"); // Давлением мм рт ст
        }
        case From_To::Probably: {
            return "-С ВЕРОЯТНОСТЬЮ " + std::to_string (std::stoi (_text.substr (4, 5))) + "%"; // Вероятностью
        }
        default:
            return "Not Converting";
    }
}
std::string Function::replace_text (const std::string& _wx_string)
{
    if (auto search_text = All_Dictionary.find (_wx_string); search_text != All_Dictionary.end ()) {
        return search_text->second;
    }
    else {
        return "Not found\n" + _wx_string;
    };

    // return All_Dictionary [_wx_string];
}
std::string Function::replace_temperature (const std::string& Temperature_Group_text)
{
    std::string Temperature_str{};
    if (Temperature_Group_text.substr (0, 1) == "M") {
        Temperature_str.append ("-").append (std::to_string (std::stoi (Temperature_Group_text.substr (1, 2)))); // температура
    }
    else {
        Temperature_str.append (std::to_string (std::stoi (Temperature_Group_text.substr (0, 2))));
    }
    return Temperature_str;
}
void Function::Load_AMOFSG_Dictionary ()
{
    std::vector<std::string> v_file_path{
        "resource/AMOFSG_Dictionary.txt",      // словарь с явлениями погоды
        "resource/AirportName_Dictionary.txt", // словарь с названиями аэропортов
        "resource/Dictionary.txt"              // словарь с остальными термиинами
    };
    for (const auto& elem : v_file_path) {
        auto currentDir      = std::filesystem::current_path ();
        auto dictionary_path = currentDir / elem;
        dictionary_path.make_preferred ();

        std::ifstream infile;
        infile.open (dictionary_path);
        if (!infile) {
            //   std::cout << "Can't open file Dictionary: " << dictionary_path << "\n";
            exit (EXIT_FAILURE);
        }
        std::string item1{}, item2{};
        while (infile) {
            std::getline (infile, item1, '/'), getline (infile, item2);
            if (item1 != "") {
                // delete /r /n unix windows]
                if ((item2.back () == '\r') || (item2.back () == '\n')) {
                    item2.pop_back ();
                }
                All_Dictionary [item1] = item2;
            }
        }
        infile.close ();
    }
}
