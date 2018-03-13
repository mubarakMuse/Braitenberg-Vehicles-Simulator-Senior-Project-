/**
 * @file Light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light() :
motion_handler_(this),
motion_behavior_(this) {
  motion_handler_.set_velocity(5, 5);
  // Lights being to move that fast at first
  set_color(Light_COLOR);
  set_pose(Light_POSITION);
  set_radius(Light_RADIUS);
  set_type(kLight);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Light::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();
  if (random()%13 == 0) {
  // randomly changing the heading so the obtsacle can move around
     RelativeChangeHeading(+16);
  }
  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());
  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Light::Reset() {
  set_pose(SetPoseRandomly());
  motion_handler_.set_max_speed(Light_MAX_SPEED);
  motion_handler_.set_max_angle(Light_MAX_ANGLE);
  sensor_touch_->Reset();
  set_color(Light_COLOR);
} /* Reset() */

void Light::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  WheelVelocity currentVelocity = motion_handler_.get_velocity();
  // to maintain the speed it was moving at
  motion_handler_.Stop();  // stop the Light when it collides with something
  motion_handler_.set_velocity(currentVelocity);
}

void Light::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
void Light::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Light::TurnRight() {
  motion_handler_.TurnRight();
}
void Light::TurnLeft() {
  motion_handler_.TurnLeft();
}

NAMESPACE_END(csci3081);
