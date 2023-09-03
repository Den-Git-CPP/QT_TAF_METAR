#include "./include/metar.h"
METAR::METAR () {}
METAR::~METAR () {}

QString METAR::raw_text () const { return raw_text_; }

void METAR::set_raw_text (const QString& raw_text)
{ //

    raw_text_ = Function::replace_raw_text (raw_text_);
}

const QString& METAR::station_id () const { return station_id_; }

void METAR::setStation_id (const QString& newStation_id) { station_id_ = newStation_id; }

const QString& METAR::observation_time () const { return observation_time_; }

void METAR::setObservation_time (const QString& newObservation_time) { observation_time_ = newObservation_time; }

const QString& METAR::latitude () const { return latitude_; }

void METAR::setLatitude (const QString& newLatitude) { latitude_ = newLatitude; }

const QString& METAR::longitude () const { return longitude_; }

void METAR::setLongitude (const QString& newLongitude) { longitude_ = newLongitude; }

const QString& METAR::visibility_statute_mi () const { return visibility_statute_mi_; }

void METAR::setVisibility_statute_mi (const QString& newVisibility_statute_mi) { visibility_statute_mi_ = newVisibility_statute_mi; }

const QString& METAR::altim_in_hg () const { return altim_in_hg_; }

void METAR::setAltim_in_hg (const QString& newAltim_in_hg) { altim_in_hg_ = newAltim_in_hg; }

const QString& METAR::flight_category () const { return flight_category_; }

void METAR::setFlight_category (const QString& newFlight_category) { flight_category_ = newFlight_category; };
