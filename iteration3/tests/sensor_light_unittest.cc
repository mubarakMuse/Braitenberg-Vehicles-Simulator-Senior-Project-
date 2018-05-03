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
    robot->set_radius(16);
    csci3081::Pose pose1 = { 100, 100, 0};
    robot->set_pose(pose1);
  }
  csci3081::Robot * robot = new csci3081::Robot(csci3081::kUndefinedRT);
  std::vector<class csci3081::ArenaEntity *> light_entities_;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/


// void sensor_robot_location(double angle) {
//     double theta = entity_->get_pose().theta + angle;
//     double x = entity_->get_radius() * cos(theta)+ entity_->get_pose().x;
//     double y = entity_->get_radius() * sin(theta)+ entity_->get_pose().y;
//     set_position(x, y);
//   }


TEST_F(LightSensorTest,UpdatePositionHeading0) {
  // boundary: robot heading at 0
  csci3081::Pose pose1 = { 100, 100, 0};
  robot->set_pose(pose1);
  robot->UpdateSensorPoses();

  csci3081::Pose poseL = { 106.762,114.501, 0};
  csci3081::Pose poseR = { 106.762, 85.4991, 0};
  
 
 
  double lx = robot->get_left_light_sensor()->get_pose().x;
  double ly = robot->get_left_light_sensor()->get_pose().y;
  double lt = robot->get_left_light_sensor()->get_pose().theta;
  double rx = robot->get_right_light_sensor()->get_pose().x;
  double ry = robot->get_right_light_sensor()->get_pose().y;
  double rt = robot->get_right_light_sensor()->get_pose().theta;
 
  EXPECT_LE(abs(lx-poseL.x),.001);
  EXPECT_LE(abs(ly-poseL.y),.001);
  EXPECT_EQ(lt,poseL.theta);
  EXPECT_LE(abs(rx-poseR.x),.001);
  EXPECT_LE(abs(ry-poseR.y),.001);
  EXPECT_EQ(rt,poseR.theta);
  

 }


 TEST_F(LightSensorTest,UpdatePositionHeading30) {
  // boundary: robot heading at 30
  csci3081::Pose pose1 = { 100, 100, 30};
  robot->set_pose(pose1);
  robot->UpdateSensorPoses();

  csci3081::Pose poseL = { 115.37, 95.5558, 0};
  csci3081::Pose poseR = { 86.7157, 91.0822, 0};
  
  
  
  double lx = robot->get_left_light_sensor()->get_pose().x;
  double ly = robot->get_left_light_sensor()->get_pose().y;
  double lt = robot->get_left_light_sensor()->get_pose().theta;
  double rx = robot->get_right_light_sensor()->get_pose().x;
  double ry = robot->get_right_light_sensor()->get_pose().y;
  double rt = robot->get_right_light_sensor()->get_pose().theta;
 
  
  EXPECT_LE(abs(lx-poseL.x),.001);
  EXPECT_LE(abs(ly-poseL.y),.001);
  EXPECT_EQ(lt,poseL.theta);
  EXPECT_LE(abs(rx-poseR.x),.001);
  EXPECT_LE(abs(ry-poseR.y),.001);
  EXPECT_EQ(rt,poseR.theta);

 }

 TEST_F(LightSensorTest,UpdatePositionHeadingNeg30) {
  // boundary: robot heading at -30
  csci3081::Pose pose1 = { 100, 100, -30};
  robot->set_pose(pose1);
  robot->UpdateSensorPoses();

  csci3081::Pose poseL = { 86.7157, 108.918, 0};
  csci3081::Pose poseR = { 115.37, 104.444, 0};
 
  
  
  double lx = robot->get_left_light_sensor()->get_pose().x;
  double ly = robot->get_left_light_sensor()->get_pose().y;
  double lt = robot->get_left_light_sensor()->get_pose().theta;
  double rx = robot->get_right_light_sensor()->get_pose().x;
  double ry = robot->get_right_light_sensor()->get_pose().y;
  double rt = robot->get_right_light_sensor()->get_pose().theta;
 

  EXPECT_LE(abs(lx-poseL.x),.001);
  EXPECT_LE(abs(ly-poseL.y),.001);
  EXPECT_EQ(lt,poseL.theta);
  EXPECT_LE(abs(rx-poseR.x),.001);
  EXPECT_LE(abs(ry-poseR.y),.001);
  EXPECT_EQ(rt,poseR.theta);
 

 }

 
 TEST_F(LightSensorTest,UpdatePositionHeading90) {
  // boundary: robot heading at 90
  csci3081::Pose pose1 = { 100, 100, 90};
  robot->set_pose(pose1);
  robot->UpdateSensorPoses();

  csci3081::Pose poseL = { 84.0064, 99.5476, 0};
  csci3081::Pose poseR = { 109.934, 112.543, 0};
 
  
  
  double lx = robot->get_left_light_sensor()->get_pose().x;
  double ly = robot->get_left_light_sensor()->get_pose().y;
  double lt = robot->get_left_light_sensor()->get_pose().theta;
  double rx = robot->get_right_light_sensor()->get_pose().x;
  double ry = robot->get_right_light_sensor()->get_pose().y;
  double rt = robot->get_right_light_sensor()->get_pose().theta;
 
  EXPECT_LE(abs(lx-poseL.x),.001);
  EXPECT_LE(abs(ly-poseL.y),.001);
  EXPECT_EQ(lt,poseL.theta);
  EXPECT_LE(abs(rx-poseR.x),.001);
  EXPECT_LE(abs(ry-poseR.y),.001);
  EXPECT_EQ(rt,poseR.theta);
 

 }

TEST_F(LightSensorTest,UpdatePositionHeadingNeg90) {
  // boundary: robot heading at -90
  csci3081::Pose pose1 = { 100, 100, -90};
  robot->set_pose(pose1);
  robot->UpdateSensorPoses();

  csci3081::Pose poseL = { 109.934, 87.4574, 0};
  csci3081::Pose poseR = { 84.0064, 100.452, 0};
 
  
  
  double lx = robot->get_left_light_sensor()->get_pose().x;
  double ly = robot->get_left_light_sensor()->get_pose().y;
  double lt = robot->get_left_light_sensor()->get_pose().theta;
  double rx = robot->get_right_light_sensor()->get_pose().x;
  double ry = robot->get_right_light_sensor()->get_pose().y;
  double rt = robot->get_right_light_sensor()->get_pose().theta;
 
  EXPECT_LE(abs(lx-poseL.x),.001);
  EXPECT_LE(abs(ly-poseL.y),.001);
  EXPECT_EQ(lt,poseL.theta);
  EXPECT_LE(abs(rx-poseR.x),.001);
  EXPECT_LE(abs(ry-poseR.y),.001);
  EXPECT_EQ(rt,poseR.theta);
 

 }
 
 TEST_F(LightSensorTest,UpdatePositionHeading270) {
  // boundary: robot heading at 270
  csci3081::Pose pose1 = {100, 100, 270};
  robot->set_pose(pose1);
  robot->UpdateSensorPoses();

  csci3081::Pose poseL = { 109.209, 113.084, 0};
  csci3081::Pose poseR = { 104.103, 84.5351, 0};
 
  
  
  double lx = robot->get_left_light_sensor()->get_pose().x;
  double ly = robot->get_left_light_sensor()->get_pose().y;
  double lt = robot->get_left_light_sensor()->get_pose().theta;
  double rx = robot->get_right_light_sensor()->get_pose().x;
  double ry = robot->get_right_light_sensor()->get_pose().y;
  double rt = robot->get_right_light_sensor()->get_pose().theta;
 

  EXPECT_LE(abs(lx-poseL.x),.001);
  EXPECT_LE(abs(ly-poseL.y),.001);
  EXPECT_EQ(lt,poseL.theta);
  EXPECT_LE(abs(rx-poseR.x),.001);
  EXPECT_LE(abs(ry-poseR.y),.001);
  EXPECT_EQ(rt,poseR.theta);
 

 }
TEST_F(LightSensorTest,UpdateOneLightBelowRobot) {
  // light below the robot should give a max reading
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 300, 300, 0};
  csci3081::Pose Lposeafter = { 100, 100, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadAfter = robot->get_right_light_sensor()->get_reading();

  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,1);
  EXPECT_LT(ReadBefore,ReadAfter);
  EXPECT_EQ(ReadAfter,1000);
 }
TEST_F(LightSensorTest,UpdateOneLightGettingCloser) {
  // update: a single light apporches closer to the robot 
  // so i test to see if the reading increases i only check one like insructer said

  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 300, 300, 0};
  csci3081::Pose Lposeafter = { 200, 200, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadAfter = robot->get_right_light_sensor()->get_reading();

  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,1);
  EXPECT_LT(ReadBefore,ReadAfter);
 
 }

 TEST_F(LightSensorTest,UpdateOneLightGoingfurther) {
  // Update: a light moving away from robot should have a decrease in reading
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 200, 200, 0};
  csci3081::Pose Lposeafter = { 300, 300, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadAfter = robot->get_right_light_sensor()->get_reading();


  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,1);
  EXPECT_GT(ReadBefore,ReadAfter);
 
 }
  TEST_F(LightSensorTest,Update2LightsGettingCloser) {
  // Update: two lights getting closer icrease the reading
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Light * light2 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 300, 300, 0};
  csci3081::Pose Lposeafter = { 200, 200, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  light_entities_.push_back(light2);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  light2->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  light2->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadAfter = robot->get_right_light_sensor()->get_reading();


  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,2);
  EXPECT_LT(ReadBefore,ReadAfter);
 
 }

 TEST_F(LightSensorTest,Update2LightsGoingfurther) {
  // Update: two lights moving further decreases the reading
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Light * light2 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 200, 200, 0};
  csci3081::Pose Lposeafter = { 300, 300, 0};
  light_entities_.clear();
  light_entities_.push_back(light1);
  light_entities_.push_back(light2);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  light2->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  light2->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadAfter = robot->get_right_light_sensor()->get_reading();


  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,2);
  EXPECT_GT(ReadBefore,ReadAfter);
 
 }

 TEST_F(LightSensorTest,UpdateEmptyVector) {
  // an emepty vector should result in a zero reading
  csci3081::Pose Rpose = { 100, 100, 0};
  csci3081::Pose Lposebefore = { 200, 200, 0};
  csci3081::Pose Lposeafter = { 300, 300, 0};
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  int ReadBefore = robot->get_right_light_sensor()->get_reading();

  light_entities_.clear();
 
  robot->get_right_light_sensor()->update(light_entities_);
  int ReadAfter = robot->get_right_light_sensor()->get_reading();


  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,0);
  EXPECT_EQ(ReadBefore,0);
  EXPECT_EQ(ReadAfter,0);
 }

 TEST_F(LightSensorTest,UpdatelargerLeftReading) {
  // Update: light thats closer to the left sensor than the right 
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};

  csci3081::Pose Lposebefore = { 100, 100, 0};
  csci3081::Pose Lposeafter = { 106.762,130.501, 0};

  light_entities_.clear();
  light_entities_.push_back(light1);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  robot->get_left_light_sensor()->update(light_entities_);
  int LeftReadBefore = robot->get_left_light_sensor()->get_reading();
  int RightReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  robot->get_left_light_sensor()->update(light_entities_);
  int LeftReadAfter = robot->get_left_light_sensor()->get_reading();
  int RightReadAfter = robot->get_right_light_sensor()->get_reading();

  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,1);
  EXPECT_EQ(LeftReadBefore,RightReadBefore);
  EXPECT_GT(LeftReadAfter,RightReadAfter);
 
 }

 TEST_F(LightSensorTest,UpdatelargerRightReading) {
  // update: a light closer to the right than the left 
  csci3081::Light * light1 = new csci3081::Light();
  csci3081::Pose Rpose = { 100, 100, 0};

  csci3081::Pose Lposebefore = { 100, 100, 0};
  csci3081::Pose Lposeafter = { 106.762,70, 0};

  light_entities_.clear();
  light_entities_.push_back(light1);
  robot->set_pose(Rpose);
  robot->UpdateSensorPoses();
  
  light1->set_pose(Lposebefore);
  robot->get_right_light_sensor()->update(light_entities_);
  robot->get_left_light_sensor()->update(light_entities_);
  int LeftReadBefore = robot->get_left_light_sensor()->get_reading();
  int RightReadBefore = robot->get_right_light_sensor()->get_reading();
  

  light1->set_pose(Lposeafter);
  robot->get_right_light_sensor()->update(light_entities_);
  robot->get_left_light_sensor()->update(light_entities_);
  int LeftReadAfter = robot->get_left_light_sensor()->get_reading();
  int RightReadAfter = robot->get_right_light_sensor()->get_reading();

  int arrsize = light_entities_.size();
  EXPECT_EQ(arrsize,1);
  EXPECT_EQ(LeftReadBefore,RightReadBefore);
  EXPECT_GT(RightReadAfter,LeftReadAfter);
 
 }


#endif /*LIGHTSENSOR_TEST*/
