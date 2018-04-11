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
#include <vector>

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
 	* @brief food sesnor that inherits from the parent sesnor class
 	*/
  explicit FoodSensor(ArenaMobileEntity * ent)
      : Sensor(ent) {}

  /**
 	* @brief calaculates the reading using the expontial function
 	*/
  int CalculateReading(Food *ent);

  /**
 	* @brief resets the sensors reading
 	*/
  void Reset() override;

  /**
 	* @brief accumalates the reading by calling the CalculateReading
 	* for each food in the arena
 	*/
  void update(std::vector<class ArenaEntity *> stimili) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H_
