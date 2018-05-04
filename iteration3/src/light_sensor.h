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
#include <vector>

#include "src/common.h"
#include "src/sensor.h"
#include "src/light.h"
#include "src/arena_mobile_entity.h"


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
  /**
 	* @brief calaculates the reading using the expontial function
 	*/
  int CalculateReading(Light *ent);

  /**
 	* @brief resets the sensors reading
 	*/
  void Reset() override;

  /**
 	* @brief accumalates the reading by calling the CalculateReading
 	* for each light in the arena
 	*/
  void update(std::vector<class ArenaEntity *> stimili) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_SENSOR_H_
