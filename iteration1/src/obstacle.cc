/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Obstacle::Obstacle():
	motion_handler_(this),
    motion_behavior_(this){
  motion_handler_.set_velocity(5, 5); // obstacles being to move that fast at first
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_POSITION);
  set_radius(OBSTACLE_RADIUS);
  set_type(kObstacle);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Obstacle::TimestepUpdate(unsigned int dt) {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();
  if (random()%10 == 0){ // randomly changing the heading so the obtsacle can move around
  	RelativeChangeHeading(+10);
  }
  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());
  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Obstacle::Reset() {
  set_pose(SetPoseRandomly());
  motion_handler_.set_max_speed(OBSTACLE_MAX_SPEED);
  motion_handler_.set_max_angle(OBSTACLE_MAX_ANGLE);
  sensor_touch_->Reset();
} /* Reset() */

void Obstacle::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  WheelVelocity currentVelocity = motion_handler_.get_velocity(); // to maintain the speed it was moving at 
  motion_handler_.Stop(); // stop the obstacle when it collides with something 
  motion_handler_.set_velocity(currentVelocity);
}

void Obstacle::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
void Obstacle::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Obstacle::TurnRight() {
  motion_handler_.TurnRight();
}
void Obstacle::TurnLeft() {
  motion_handler_.TurnLeft();
}

NAMESPACE_END(csci3081);
