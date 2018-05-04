/*
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <gtest/gtest.h>
#include "src/robot.h"
#include "src/params.h"
#include "src/robot_type.h"
#include "src/light.h"
#include "src/light_sensor.h"
#include "src/sensor.h"
#include "src/arena_entity.h"
#include "src/wheel_velocity.h"

#ifdef MOTIONHANDLER_TESTS

/******************************************************
* MotionHnadler TestCase
*******************************************************/
class MotionHandlerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    explore_robot = new csci3081::Robot(csci3081::kExplore);
    explore_robot->set_radius(16);
  

    coward_robot = new csci3081::Robot(csci3081::kCoward);
    coward_robot->set_radius(16);
   
  }
  csci3081::Robot * explore_robot;
  csci3081::Robot * coward_robot;
  std::vector<class csci3081::ArenaEntity *> light_entities_;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

 TEST_F(MotionHandlerTest,OnelightApproching) {
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 300, 300, 0};
  csci3081::Pose Lposeafter = { 200, 200, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  explore_robot->set_pose(Rpose);
  explore_robot->UpdateSensorPoses();
  coward_robot->set_pose(Rpose);
  coward_robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  explore_robot->get_left_light_sensor()->update(light_entities_);
  explore_robot->get_right_light_sensor()->update(light_entities_);
  coward_robot->get_left_light_sensor()->update(light_entities_);
  coward_robot->get_right_light_sensor()->update(light_entities_);
  explore_robot->TimestepUpdate(1);
  coward_robot->TimestepUpdate(1);

  csci3081::WheelVelocity ve_before = explore_robot->get_motion_handler()->get_velocity();
  csci3081::WheelVelocity vc_before = coward_robot->get_motion_handler()->get_velocity();
  
  light1->set_pose(Lposeafter);
  explore_robot->get_left_light_sensor()->update(light_entities_);
  explore_robot->get_right_light_sensor()->update(light_entities_);
  coward_robot->get_left_light_sensor()->update(light_entities_);
  coward_robot->get_right_light_sensor()->update(light_entities_);
  explore_robot->TimestepUpdate(1);
  coward_robot->TimestepUpdate(1);

  csci3081::WheelVelocity ve_after = explore_robot->get_motion_handler()->get_velocity();
  csci3081::WheelVelocity vc_after = coward_robot->get_motion_handler()->get_velocity();

  EXPECT_GT(ve_before.left,ve_after.left);
  EXPECT_GT(ve_before.right,ve_after.right);
  EXPECT_LT(vc_before.left,vc_after.left);
  EXPECT_LT(vc_before.right,vc_after.right);
  
}

 TEST_F(MotionHandlerTest,OneLightMovingAway) {
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 100, 100, 0};
  csci3081::Pose Lposeafter = { 200, 200, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  explore_robot->set_pose(Rpose);
  explore_robot->UpdateSensorPoses();
  coward_robot->set_pose(Rpose);
  coward_robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  explore_robot->get_left_light_sensor()->update(light_entities_);
  explore_robot->get_right_light_sensor()->update(light_entities_);
  coward_robot->get_left_light_sensor()->update(light_entities_);
  coward_robot->get_right_light_sensor()->update(light_entities_);
  explore_robot->TimestepUpdate(1);
  coward_robot->TimestepUpdate(1);

  csci3081::WheelVelocity ve_before = explore_robot->get_motion_handler()->get_velocity();
  csci3081::WheelVelocity vc_before = coward_robot->get_motion_handler()->get_velocity();
  
  light1->set_pose(Lposeafter);
  explore_robot->get_left_light_sensor()->update(light_entities_);
  explore_robot->get_right_light_sensor()->update(light_entities_);
  coward_robot->get_left_light_sensor()->update(light_entities_);
  coward_robot->get_right_light_sensor()->update(light_entities_);
  explore_robot->TimestepUpdate(1);
  coward_robot->TimestepUpdate(1);

  csci3081::WheelVelocity ve_after = explore_robot->get_motion_handler()->get_velocity();
  csci3081::WheelVelocity vc_after = coward_robot->get_motion_handler()->get_velocity();

  EXPECT_LT(ve_before.left,ve_after.left);
  EXPECT_LT(ve_before.right,ve_after.right);
  EXPECT_GT(vc_before.left,vc_after.left);
  EXPECT_GT(vc_before.right,vc_after.right);
  
}

#endif /*MOTIONHANDLER_TESTS*/
