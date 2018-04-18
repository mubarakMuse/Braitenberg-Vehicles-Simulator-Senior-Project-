/**
 * @file light_sensor.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <math.h>
#include <vector>

#include "src/light_sensor.h"
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
int LightSensor::CalculateReading(Light *ent) {
  int reading = 0;
  Pose mypose = get_pose();
  double deltaX = mypose.x - ent->get_pose().x;
  double deltaY = mypose.y - ent->get_pose().y;
  double distance = (pow(deltaX*deltaX + deltaY*deltaY, 0.5)-16);
  reading = 1200/(pow(1.02, distance));
  return reading;
}

void LightSensor::update(std::vector<class ArenaEntity *> stimili) {
  int reading = 0;
  for (auto &light : stimili) {
    reading += CalculateReading(dynamic_cast<Light *>(light));
  }
  if (reading > 1000) {
    reading = 1000;
  }
  set_reading(reading);
}
void LightSensor::Reset() {
  set_reading(0);
  }

NAMESPACE_END(csci3081);
