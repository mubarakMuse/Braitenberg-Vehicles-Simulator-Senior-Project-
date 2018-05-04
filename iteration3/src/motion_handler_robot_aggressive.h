/**
 * @file motion_handler_robot_aggressive.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_AGGRESSIVE_H_
#define SRC_MOTION_HANDLER_ROBOT_AGGRESSIVE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler.h"
#include "src/sensor_touch.h"
#include "src/communication.h"
#include "src/robot_type.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief Class managing a Robot's and Light's speed and heading angle based
 * on aggressive sensor readings.
 */
class MotionHandlerRobotAggressive : public MotionHandler {
 public:
  explicit MotionHandlerRobotAggressive(ArenaMobileEntity * ent)
      : MotionHandler(ent) {}

  MotionHandlerRobotAggressive(const MotionHandlerRobotAggressive& other)
  = default;
  MotionHandlerRobotAggressive& operator=(const MotionHandlerRobotAggressive& o)
  = default;

  /**
  * @brief Update the speed and the pose angle according to
  * the aggressive sensor readings.
  */
  void UpdateVelocity() override;

  /**
   * @brief Increase the overall speed of the entity by speed_delta.
   */
  void IncreaseSpeed() override;

  /**
   * @brief Decrease the overall speed of the entity by speed_delta.
   */
  void DecreaseSpeed() override;

  /**
   * @brief Turn the entity to the right by angle_delta (in degrees?)
   */
  void TurnRight() override;

  /**
   * @brief Turn the entity to the left by angle_delta (in degrees?)
   */
  void TurnLeft() override;

  /**
   * @brief stop the entity to be at zero velocity.
   */
  void Stop() override;



 private:
  double clamp_vel(double vel);
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_AGGRESSIVE_H_
