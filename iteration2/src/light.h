/**
 * @file light.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionBehaviorDifferential;



/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an mobile Light within the Arena.
 *
 *
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Light" + std::to_string(get_id());
  }
  /**
   * @brief Reset the onstacle to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the Light's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision(EntityType object_type,
    ArenaEntity * object = NULL) override;

  /**
   * @brief Command that comes from the controller, then is passed to handler.
   */
  void IncreaseSpeed();

  /**
  * @brief Command that comes from the controller, then is passed to handler.
  */
  void DecreaseSpeed();

  /**
  * @brief Command that comes from the controller, then is passed to handler.
  */
  void TurnRight();

  /**
  * @brief Command that comes from the controller, then is passed to handler.
  */
  void TurnLeft();

  MotionHandlerRobot get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }

  // void set_robot_type(__unused RobotType rt) override {}
  // RobotType get_robot_type() override{
  //   return kUndefinedRT;
  // }
  // //virtual void set_TotalSensorReading(double tsr);
  //  double get_TotalSensorReading() override {
  //   return 0;
  //  }

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerRobot motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
