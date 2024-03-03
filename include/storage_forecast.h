#pragma once

#include <vector>
#include <memory>
#include <string>
#include <regex>

#include "forecast.h"
#include "function.h"

class Storage_Forecast : public Function {
  public:
    explicit Storage_Forecast ();
    ~Storage_Forecast ();
    void split_str (const std::string& in_forecast_str);
    void convert_word_to_Forcast (std::unique_ptr<Forecast>& u_ptr_forcast, const std::string& in_forecast_str);

    std::string Name_Airport{ "" };
    std::string RawTAF{ "" };
    std::string TAF{ "" };
    std::string RawMETAR{ "" };
    std::string METAR{ "" };

    std::vector<std::unique_ptr<Forecast>> all_Forecast{};
};
