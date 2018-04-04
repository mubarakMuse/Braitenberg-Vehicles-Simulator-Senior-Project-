/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// @TODO add clamped

void MotionHandlerRobot::TurnLeft() {
  set_velocity(
    get_velocity().left  - get_angle_delta(),
    get_velocity().right + get_angle_delta());
}

void MotionHandlerRobot::TurnRight() {
  set_velocity(
    get_velocity().left  + get_angle_delta(),
    get_velocity().right - get_angle_delta());
}

void MotionHandlerRobot::IncreaseSpeed() {  // added for priorty
  if ((get_velocity().left + get_speed_delta()) <= ROBOT_MAX_SPEED
    && (get_velocity().right + get_speed_delta()) <= ROBOT_MAX_SPEED) {
     set_velocity(
    get_velocity().left  + get_speed_delta(),
    get_velocity().right + get_speed_delta());
  }
}
void MotionHandlerRobot::DecreaseSpeed() {  // added for priorty
    if (0.00 <=( get_velocity().left - get_speed_delta())
    && 0.00 <= (get_velocity().right - get_speed_delta())) {
      set_velocity(
    get_velocity().left  - get_speed_delta(),
    get_velocity().right - get_speed_delta());
    }
  }
void MotionHandlerRobot::Stop() {  // added for priorty 1 iteration 1
  set_velocity(0.00, 0.00);
}

void MotionHandlerRobot::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
    entity_->RelativeChangeHeading(+180);
  }
}

double MotionHandlerRobot::clamp_vel(double vel) {
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
