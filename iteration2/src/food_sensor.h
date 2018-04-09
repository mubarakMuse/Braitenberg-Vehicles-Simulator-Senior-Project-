/**
 * @file food_sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FOOD_SENSOR_H_
#define SRC_FOOD_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/common.h"
#include "src/sensor.h"
#include "src/food.h"
#include "src/arena_mobile_entity.h"
#include "src/arena_entity.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);



class FoodSensor: public Sensor {
 public:
  /**
 * @brief ArenaEntity constructor initialized with default values from params.h
 */
  explicit FoodSensor(ArenaMobileEntity * ent)
      : Sensor(ent) {}

  int CalculateReading(Food *ent);

  void Reset() override ;

  void update(std::vector<class ArenaEntity *> stimili) override;

};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H_
