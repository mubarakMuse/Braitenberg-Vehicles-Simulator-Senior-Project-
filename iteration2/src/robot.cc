/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#define _USE_MATH_DEFINES
 
#include <cmath>

#include "src/robot.h"
#include "src/params.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(RobotType rt) :
    motion_handler_(),
    motion_behavior_(this),
    lives_(9),
    left_light_sensor_(),
    right_light_sensor_(){
  // motion_handler_->set_velocity(1, 1);
  set_type(kRobot);
  set_robot_type(rt);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);

  switch(get_robot_type()){
    case(kAggressive):
    motion_handler_ = new MotionHandlerRobotAggressive(this);
    break;
    case(kLove):
    motion_handler_ = new MotionHandlerRobotLove(this);
    break;
    case(kCoward):
    motion_handler_ = new MotionHandlerRobotCoward(this);
    break;
    case(kExplore):
    motion_handler_ = new MotionHandlerRobotExplore(this);
    break;
    default: break;
  }

  left_light_sensor_ = new LightSensor(this);
  right_light_sensor_ = new LightSensor(this);

  left_light_sensor_->sensor_robot_location(40*M_PI/180);
  right_light_sensor_->sensor_robot_location(-40*M_PI/180);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  //std::cout << left_light_sensor_->get_reading();
  motion_handler_->set_lightsensor_reading(left_light_sensor_->get_reading(),right_light_sensor_->get_reading());
  // Update heading as indicated by touch sensor
  motion_handler_->UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_->get_velocity());

  left_light_sensor_->sensor_robot_location(40*M_PI/180);
  right_light_sensor_->sensor_robot_location(-40*M_PI/180);

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(SetPoseRandomly());
  motion_handler_->set_max_speed(ROBOT_MAX_SPEED);
  motion_handler_->set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
  set_color(ROBOT_COLOR);
  set_lives(9);
} /* Reset() */

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  WheelVelocity currentVelocity  = motion_handler_->get_velocity();
  motion_handler_->Stop();  // stop the car right away. added for priorty.
  motion_handler_->set_velocity(currentVelocity);
}

void Robot::IncreaseSpeed() {
  motion_handler_->IncreaseSpeed();
}
void Robot::DecreaseSpeed() {
  motion_handler_->DecreaseSpeed();
}
void Robot::TurnRight() {
  motion_handler_->TurnRight();
}
void Robot::TurnLeft() {
  motion_handler_->TurnLeft();
}

NAMESPACE_END(csci3081);
