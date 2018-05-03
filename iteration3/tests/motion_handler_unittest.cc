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

#ifdef MOTIONHANDLER_TESTS

/******************************************************
* MotionHnadler TestCase
*******************************************************/
class MotionHandlerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    explore_robot = new csci3081::Robot(csci3081::kExplore);
    explore_robot->set_radius(10);
    // explore_robot.set_pose(100,100,0);

    coward_robot = new csci3081::Robot(csci3081::kCoward);
    coward_robot->set_radius(10);
    // coward_robot.set_pose(100,100,0);
  }
  csci3081::Robot * explore_robot;
  csci3081::Robot * coward_robot;
  std::vector<class ArenaEntity *> light_entities_;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// TEST_F(MotionHandlerTest,onecloselight) {
//   explore_robot.set_pose(100,100,0);
//   explore_robot.UpdateSensorPoses();
//   Light * light1 = new csci3081::Light();
//   light1->set_pose(100,100,0);
//   light_entities_.clear();
//   light_entities_.push_back(ligh1);
//   get_right_light_sensor()->set_reading(0);
//   get_right_light_sensor()->update(light_entities_);
//   get_left_light_sensor()->set_reading(0);
//   get_left_light_sensor()->update(light_entities_);
//   csci3081::WheelVelocity v = explore_robot->get_motion_handler().get_velocity();
//   explore_robot.TimestepUpdate(1);
//   csci3081::WheelVelocity v = explore_robot->get_motion_handler().get_velocity();
//   EXPECT_EQ(std::make_tuple(v.left, v.right), std::make_tuple(0, 0)) << "Fail: Robot did not stop on collision with an Obstacle";
//   explore_robot.TimestepUpdate(1);

//   EXPECT_EQ(get_right_light_sensor()->get_pose(),Pose(108,106,0));
//   EXPECT_EQ(get_left_light_sensor()->get_pose(),Pose(108,-106,0));
//  }

#endif /*MOTIONHANDLER_TESTS*/
