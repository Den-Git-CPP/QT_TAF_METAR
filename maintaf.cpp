#include "maintaf.h"

MainTAF::MainTAF(QObject *parent) : QObject(parent) {
  //
  forecast_Title = new Forecast_Title(this);
  forecast_TAF = new Forecast_TAF(this);
}

MainTAF::~MainTAF() {
  //
  delete forecast_Title;
}
