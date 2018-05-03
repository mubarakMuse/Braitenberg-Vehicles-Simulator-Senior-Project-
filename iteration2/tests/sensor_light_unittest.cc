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
#include "src/pose.h"




#ifdef LIGHTSENSOR_TESTS

/******************************************************
* lightsensor TestCase
*******************************************************/
class LightSensorTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    robot = new csci3081::Robot(csci3081::kUndefinedRT);
    robot.set_radius(10);
    // csci3081::Pose pose1 = { 500, 500 , 0};
    // robot->set_pose(pose1);
    robot.set_pose(100,100,0);
  }
  csci3081::Robot robot = new csci3081::Robot(csci3081::kUndefinedRT);
  std::vector<class ArenaEntity *> light_entities_;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(LightSensorTest,UpdatePositionHeading0) {
  // boundary: robot heading at 0
  // csci3081::Pose pose1 = { 500, 500 , 0};
  // robot->set_pose(Pose(100,100,0));
  // robot->get_right_light_sensor()->sensor_robot_location(65*M_PI/180);
  // robot->get_left_light_sensor()->sensor_robot_location(-65*M_PI/180);
  // csci3081::Pose poseR = { 500, 500 , 0};
  // csci3081::Pose poseL = { 500, 500 , 0};
  //EXPECT_EQ(robot->get_pose(),poseR);
  //EXPECT_EQ(robot->get_pose(),poseL);
 }

// TEST_F(LightSensorTest,UpdatePositionHeading30) {
//   // boundary: robot heading at 30
//   robot.set_pose(100,100,30);
//   robot.UpdateSensorPoses();

//   EXPECT_EQ(get_right_light_sensor()->get_pose(),Pose(108,106,0));
//   EXPECT_EQ(get_left_light_sensor()->get_pose(),Pose(108,-106,0));
//  }

// TEST_F(LightSensorTest,UpdatePositionHeadingNeg30) {
//   // boundary: robot heading at -30
//   robot.set_pose(100,100,-30);
//   robot.UpdateSensorPoses();

//   EXPECT_EQ(get_right_light_sensor()->get_pose(),Pose(108,106,0));
//   EXPECT_EQ(get_left_light_sensor()->get_pose(),Pose(108,-106,0));
//  }

// TEST_F(LightSensorTest,UpdatePositionHeading0) {
//   // boundary: robot heading at 0
//   robot.set_pose(100,100,0);
//   robot.UpdateSensorPoses();

//   EXPECT_EQ(get_right_light_sensor()->get_pose(),Pose(108,106,0));
//   EXPECT_EQ(get_left_light_sensor()->get_pose(),Pose(108,-106,0));
//  }

// TEST_F(LightSensorTest,UpdatePositionHeading0) {
//   // boundary: robot heading at 0
//   robot.set_pose(100,100,0);
//   robot.UpdateSensorPoses();

//   EXPECT_EQ(get_right_light_sensor()->get_pose(),Pose(108,106,0));
//   EXPECT_EQ(get_left_light_sensor()->get_pose(),Pose(108,-106,0));
//  }
// TEST_F(LightSensorTest,Update) {
//   // boundary: robot heading at 0
//   robot.set_pose(100,100,0);
//   robot.UpdateSensorPoses();
//   Light * light1 = new Light();
//   light1->set_pose(100,100,0);
//   light_entities_.clear();
//   light_entities_.push_back(ligh1);
//   get_right_light_sensor()->set_reading(0);
//   get_right_light_sensor()->update(light_entities_);
//   EXPECT_EQ(get_right_light_sensor()->get_reading(),1000);
 
//  }
#endif /*LIGHTSENSOR_TEST*/
