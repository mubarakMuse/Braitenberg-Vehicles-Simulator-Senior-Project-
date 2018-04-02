
#include "src/light_sensor.h"

NAMESPACE_BEGIN(csci3081);


  LightSensor::LightSensor() {}

  void LightSensor::CalculateReading(__unused ArenaEntity *ent) {
  	set_reading(0);
  }

  void LightSensor::Reset() {
  	set_reading(0);
  }




NAMESPACE_END(csci3081);


