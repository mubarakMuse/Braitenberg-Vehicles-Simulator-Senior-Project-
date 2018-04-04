/**
 * @file light_sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_SENSOR_H_
#define SRC_LIGHT_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/common.h"
#include "src/sensor.h"
#include "src/light.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);


class LightSensor: public Sensor {
 public:
  /**
 * @brief ArenaEntity constructor initialized with default values from params.h
 */
  explicit LightSensor(ArenaMobileEntity * ent)
      : Sensor(ent) {}

  int CalculateReading(Light *ent)override;

  void Reset() override ;

  void update(std::vector<class Light *> lights);

 private:
 std::vector<class ArenaEntity *> lights_;

};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_SENSOR_H_
