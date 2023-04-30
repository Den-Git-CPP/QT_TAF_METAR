#pragma once
#include<memory>
#include "./include/forecast_title.h"
class METAR  {
public:
	explicit METAR();
	virtual ~METAR();
	
private:
	QString raw_text_{};
	QString station_id_{};
	QString observation_time_{};
	QString latitude_{};
	QString longitude_{};
	QString temp_c_{};
	QString dwepoint_c_{};
	QString visibility_statute_mi_{};
	QString altim_in_hg_{};
	QString sea_level_pressure_mb_{};
	QString wx_string_{};
	QString flight_category_{};
	QString three_hr_pressure_tendency_mb_{};
	QString maxT_c_{};
	QString minT_c_{};
	QString maxT24hr_c_{};
	QString minT24hr_c_{};
	QString precip_in_{};
	QString pcp3hr_in_{};
	QString pcp6hr_in_{};
	QString pcp24hr_in_{};
	QString snow_in_{};
	QString vert_vis_ft_{};
	QString metar_type_{};
	QString elevation_m_{};

std::shared_ptr<Forecast_Title> ForecastTitle = nullptr;
//std::shared_ptr<Wind> wind = nullptr; 
//std::shared_ptr<Station_Sensors> station_sensors = nullptr;
//std::shared_ptr<sky_cover> = nullptr; 

};