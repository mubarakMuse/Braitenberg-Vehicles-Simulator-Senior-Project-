/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/light_sensor.h"
#include "src/food_sensor.h"
#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_robot.h"
#include "src/motion_handler_robot_love.h"
#include "src/motion_handler_robot_explore.h"
#include "src/motion_handler_robot_coward.h"
#include "src/motion_handler_robot_aggressive.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionBehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a robot within the arena.
 *
 * Robots are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * robot. At each time step, the wheel velocities are used to calculate the
 * next pose of the robot. The handler manages the pose and user requests. The
 * behavior calculates the new pose based on wheel velocities.
 *
 * Robots can be controlled through keypress, which modify wheel velocities.
 *
 * The touch sensor is activated when the robot collides with an object.
 * The heading is modified after a collision to move the robot away from the
 * other object.
 */
class Robot : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */

  Robot(RobotType rt);

  /**
   * @brief Reset the Robot to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the Robot's position and velocity after the specified
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
   * @brief Get the name of the Robot for visualization and for debugging.
   */
  std::string get_name() const override { return "Robot"; };

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

  /**
  * @brief returns the name and lives of the robot
  */
  std::string get_DisplayName() const {
     return "Robot\n"+std::to_string(hungry_);
  }

  /**
  * @brief Function called when robot loose a single life
  */
  void lose_A_Life() {  // added for priorty 1
    lives_ = lives_ - 1;
  }

  /**
  * @brief Function to increment the robots time to track hunger
  */
  void IncrementRobotTime(){
    robot_time_++;
  }

  int get_lives() const { return lives_; }

  void set_lives(int l) { lives_ = l; }

  MotionHandler* get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }

  LightSensor* get_left_light_sensor() {return left_light_sensor_; }

  LightSensor* get_right_light_sensor() {return right_light_sensor_;}

  FoodSensor* get_right_food_sensor() {return right_food_sensor_;}

  FoodSensor* get_left_food_sensor() {return left_food_sensor_;}

  void set_robot_type(RobotType rt)  {
    robot_type_ = rt;
  }
  RobotType get_robot_type() {
    return robot_type_;
  }
  void set_hunger(bool hunger){
    hungry_ = hunger;
  }
  bool get_hunger(){
    if (robot_time_ > 600){
      hungry_ = true;
    }
    else{
      hungry_ = false;
    }
    return hungry_;
  }
  int get_robot_time(){
    return robot_time_;
  }
  void RestartRobotTime(){
    robot_time_ = 0;
    hungry_ = false;
  }
  
 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandler* motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Lives are decremented when the robot collides with anything.
  // When all the lives are gone, the game is lost.
  int lives_;

  // the robot's motion behavior
  RobotType robot_type_;

  LightSensor* left_light_sensor_;

  LightSensor* right_light_sensor_;

  FoodSensor* left_food_sensor_;

  FoodSensor* right_food_sensor_;

  bool hungry_{false};

  // tracks how long since the robot ate.
  int robot_time_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
