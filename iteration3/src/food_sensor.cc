/**
 * @file food_sensor.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <math.h>
#include <vector>

#include "src/food_sensor.h"
#include "src/food.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/

NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

int FoodSensor::CalculateReading(Food *ent) {
  int reading = 0;
  Pose mypose = get_pose();
  double deltaX = mypose.x - ent->get_pose().x;
  double deltaY = mypose.y - ent->get_pose().y;
  double distance = (pow(deltaX*deltaX + deltaY*deltaY, 0.5) - 16);
  reading = 1200/(pow(sensor_sensitivity, distance));
  return reading;
}

void FoodSensor::update(std::vector<class ArenaEntity *> stimili) {
  int reading = 0;
  for (auto &food : stimili) {
    reading += CalculateReading(dynamic_cast<Food *>(food));
  }
  if (reading > 1000) {
    reading = 1000;
  }
  set_reading(reading);
}
void FoodSensor::Reset() {
  set_reading(0);
  }

NAMESPACE_END(csci3081);
