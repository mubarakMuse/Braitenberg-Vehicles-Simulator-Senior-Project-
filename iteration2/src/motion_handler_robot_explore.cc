/**
 * @file motion_handler_robot_explore.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot_explore.h"
#include "src/motion_behavior_differential.h"
#include "src/robot.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// @TODO add clamped

void MotionHandlerRobotExplore::TurnLeft() {
  set_velocity(
    get_velocity().left  - get_angle_delta(),
    get_velocity().right + get_angle_delta());
}

void MotionHandlerRobotExplore::TurnRight() {
  set_velocity(
    get_velocity().left  + get_angle_delta(),
    get_velocity().right - get_angle_delta());
}

void MotionHandlerRobotExplore::IncreaseSpeed() {  // added for priorty
  if ((get_velocity().left + get_speed_delta()) <= ROBOT_MAX_SPEED
    && (get_velocity().right + get_speed_delta()) <= ROBOT_MAX_SPEED) {
     set_velocity(
    get_velocity().left  + get_speed_delta(),
    get_velocity().right + get_speed_delta());
  }
}
void MotionHandlerRobotExplore::DecreaseSpeed() {  // added for priorty
    if (0.00 <=( get_velocity().left - get_speed_delta())
    && 0.00 <= (get_velocity().right - get_speed_delta())) {
      set_velocity(
    get_velocity().left  - get_speed_delta(),
    get_velocity().right - get_speed_delta());
    }
  }
void MotionHandlerRobotExplore::Stop() {  // added for priorty 1 iteration 1
  set_velocity(0.00, 0.00);
}

void MotionHandlerRobotExplore::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
     entity_->RelativeChangeHeading(+180);
  }

  set_velocity(
    clamp_vel((1000-get_right_sensor_reading())/120),
    clamp_vel((1000-get_left_sensor_reading())/120));
}

double MotionHandlerRobotExplore::clamp_vel(double vel) {
  // @TODO: don't go backwards
  double clamped = 0.0;
  if (vel > 0) {
    clamped = (vel > get_max_speed()) ?
              get_max_speed():
              vel;
  } else {
    clamped = (vel < -get_max_speed()) ?
              -get_max_speed():
              vel;
  }
  return clamped;
} /* clamp_vel() */



NAMESPACE_END(csci3081);
