#include "./include/storage_forecast.h"
Storage_Forecast::Storage_Forecast () {}
Storage_Forecast::~Storage_Forecast () {}
void Storage_Forecast::split_str (const std::string& in_forecast_str)
{ // Разделили RAW прогнозы TAF METAR

    all_Forecast.clear ();
    std::stringstream ss (in_forecast_str);
    std::string word;
    std::unique_ptr<Forecast> forecast = std::make_unique<Forecast> ();
    int flag_Metar_Taf{ 0 };
    size_t start_Taf{ 0 };
    while (ss >> word) { // Extract word from the stream.
        if ((word != "TEMPO") && (word != "BECMG") && (word != "TAF")) {
            if (flag_Metar_Taf == 0) {
                RawMETAR.append (word).append (" ");
            }
            else {
                RawTAF.append (word).append (" ");
            }
            convert_word_to_Forcast (forecast, word);
        }
        else {
            all_Forecast.emplace_back (std::move (forecast));
            forecast = std::make_unique<Forecast> ();
            if (word == "TAF") {
                RawTAF.append ("TAF").append (" ");
                flag_Metar_Taf = 1;
                start_Taf      = all_Forecast.size ();
            }

            if ((word == "TEMPO") || (word == "BECMG")) {
                if (flag_Metar_Taf == 0) {
                    RawMETAR.append ("\n").append (word).append (" ");
                }
                else {
                    RawTAF.append ("\n").append (word).append (" ");
                }
            }

            convert_word_to_Forcast (forecast, word);
        }
    }
    if (forecast->getForecast () != "") {
        all_Forecast.emplace_back (std::move (forecast));
    }

    Name_Airport = *all_Forecast.at (0)->Airport.get ();
    for (size_t i{ 0 }; i < start_Taf; i++) {
        METAR.append (all_Forecast.at (i)->getForecast ());
    }
    for (size_t i{ start_Taf }; i < all_Forecast.size (); i++) {
        TAF.append (all_Forecast.at (i)->getForecast ());
    }
    // конец потока
}

void Storage_Forecast::convert_word_to_Forcast (std::unique_ptr<Forecast>& u_ptr_forcast, const std::string& input_word)
{ // Группы идентификации

    std::regex Type_regex (R"(METAR|TAF|SPECI|COR|NIL|AUTO|TEMPO|BECMG|NOSIG)");
    std::regex Airport_regex (R"([A-Z]{4})");
    std::regex Time_Group_regex (R"(\d{6}Z)");
    std::regex Time_Date_Group_regex (R"(\d{4}\/\d{4})");
    // Приземный ветер dddffGfmfm(MPS|KT)dndndnVdxdxdx
    std::regex Wind_Group_regex (R"((\d{5}|\d{5}G\d{2})(MPS|KT))");
    std::regex Var_Wind_Group_regex (R"((\d{3}V\d{3}))");
    // Видимость
    std::regex Visib_Group_regex (R"(\d{4}|CAVOK)");
    std::regex Visib_Min_Group_regex (R"(\d{4}[A-Z][A-Z])");
    // Дальность видимости на ВПП
    std::regex Visib_RNW_Group_regex (R"(R\d{2}[A-Z]?\/M?\d{4}[UDN]?)");
    // Текущая погода
    std::regex Weather_Group_regex (R"((\+|\-)?[A-Z]{2,8})");
    // Облачность (или вертикальная видимость)
    std::regex Cloud_Group_regex (R"((FEW|SCT|BKN|OVC|NSC|NCD)\d{3}(CB)?)");
    // Температура воздуха и температура точки росы
    std::regex Temperature_Group_regex (R"(M?\d{2}\/M?\d{2})");
    std::regex Pressure_Group_regex (R"(Q\d{4})");
    std::regex Prob_regex (R"(PROB\d{2})");

    if (std::regex_match (input_word, Type_regex)) {
        if (input_word == "TAF") {
            u_ptr_forcast->flag_TAF = true;
        }
        if (input_word == "SPECI") {
            u_ptr_forcast->flag_SPECI = true;
        }
        if (input_word == "COR") {
            u_ptr_forcast->flag_COR = true;
        }
        if (input_word == "NIL") {
            u_ptr_forcast->flag_NIL = true;
        }
        if (input_word == "AUTO") {
            u_ptr_forcast->flag_AUTO = true;
        }
        if (input_word == "TEMPO") {
            // TEMPO
            u_ptr_forcast->flag_Airport = true;
            u_ptr_forcast->flag_TEMPO   = true;
        }
        if (input_word == "BECMG") {
            // BECMG
            u_ptr_forcast->flag_Airport = true;
            u_ptr_forcast->flag_BECMG   = true;
        }
        if (input_word == "NOSIG") {
            // NOSIG
            u_ptr_forcast->flag_Airport = true;
            u_ptr_forcast->flag_NOSIG   = true;
        }
    }
    else if (std::regex_match (input_word, Airport_regex)) {
        if (u_ptr_forcast->flag_Airport == false) {
            u_ptr_forcast->Airport      = std::make_unique<std::string> (Function::replace_text (input_word));
            u_ptr_forcast->flag_Airport = true;
        }
        else {
            u_ptr_forcast->v_Weather_Group.emplace_back (std::move (std::make_unique<std::string> (Function::replace_text (input_word))));
        }
    }
    else if (std::regex_match (input_word, Time_Group_regex)) {
        u_ptr_forcast->Time_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Time_Group, input_word) // декодируем время
        );
    }
    else if (std::regex_match (input_word, Time_Date_Group_regex)) {
        u_ptr_forcast->Time_Date_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Time_Date_Group, input_word));
    }
    else if (std::regex_match (input_word, Wind_Group_regex)) {
        u_ptr_forcast->Wind_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Wind_Group, input_word));
    }
    else if (std::regex_match (input_word, Var_Wind_Group_regex)) {
        u_ptr_forcast->Var_Wind_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Var_Wind_Group, input_word));
    }
    else if (std::regex_match (input_word, Visib_Group_regex)) {
        u_ptr_forcast->Visib_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Visib_Group, input_word));
    }
    else if (std::regex_match (input_word, Visib_Min_Group_regex)) {
        u_ptr_forcast->Visib_Min_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Visib_Min_Group, input_word));
    }
    else if (std::regex_match (input_word, Visib_RNW_Group_regex)) {
        u_ptr_forcast->Visib_RNW_Group = std::make_unique<std::string> (input_word);
    }
    else if (std::regex_match (input_word, Weather_Group_regex)) {
        u_ptr_forcast->v_Weather_Group.emplace_back (std::move (std::make_unique<std::string> (Function::replace_text (input_word))));
    }
    else if (std::regex_match (input_word, Cloud_Group_regex)) {
        u_ptr_forcast->v_Cloud_Group.emplace_back (
          std::move (std::make_unique<std::string> (Function::replace_val_from_to (From_To::v_Cloud_Group, input_word))));
    }
    else if (std::regex_match (input_word, Temperature_Group_regex)) {
        u_ptr_forcast->Temperature_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Temperature_Group, input_word));
    }
    else if (std::regex_match (input_word, Pressure_Group_regex)) {
        u_ptr_forcast->Pressure_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Pressure_Group, input_word));
    }
    else if (std::regex_match (input_word, Prob_regex)) {
        u_ptr_forcast->flag_TEMPO     = false;
        u_ptr_forcast->Pressure_Group = std::make_unique<std::string> (
          //
          Function::replace_val_from_to (From_To::Probably, input_word));
    }
    else {
        //    std::cout << "Regex is unknown: " + input_word + "\n";
    }
}
