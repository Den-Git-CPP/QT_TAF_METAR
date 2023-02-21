#include "maintaf.h"

MainTAF::MainTAF (QObject* parent) : QObject (parent) { Title = new Forecast_Title; }

MainTAF::~MainTAF () { delete Title; }

void MainTAF::add_taf (Forecast_TAF inTAF)
{
    //
    vec_taf.push_back (std::move (inTAF));
}
