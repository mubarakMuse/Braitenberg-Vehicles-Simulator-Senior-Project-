/**
 * @file entity_factory.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <ctime>
#include <iostream>

#include "src/common.h"
#include "src/entity_factory.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

EntityFactory::EntityFactory() {
  srand(time(nullptr));
}

ArenaEntity* EntityFactory::CreateEntity(EntityType etype, RobotType rt) {
  switch (etype) {
    case (kRobot):
      return CreateRobot(rt);
      break;
    case (kLight):
      return CreateLight();
      break;
    case (kBase):
      return CreateBase();
      break;
    default:
      std::cout << "FATAL: Bad entity type on creation\n";
      assert(false);
  }
  return nullptr;
}

Robot* EntityFactory::CreateRobot( RobotType rt) {
  auto* robot = new Robot(rt);
  robot->set_type(kRobot);
  robot->set_color(ROBOT_COLOR);
  robot->set_pose(ROBOT_INIT_POS);
  robot->set_radius(ROBOT_RADIUS);
  ++entity_count_;
  ++robot_count_;
  robot->set_id(robot_count_);
  return robot;
}

Light* EntityFactory::CreateLight() {
  auto* light = new Light;
  light->set_type(kLight);
  light->set_color(Light_COLOR);
  light->set_pose(SetPoseRandomly());
  light->set_radius(SetRadiusRandomly());
  ++entity_count_;
  ++light_count_;
  light->set_id(light_count_);
  return light;
}

Base* EntityFactory::CreateBase() {
  auto* base = new Base;
  base->set_type(kBase);
  base->set_color(BASE_COLOR);
  base->set_pose(SetPoseRandomly());
  base->set_radius(BASE_RADIUS);
  ++entity_count_;
  ++base_count_;
  base->set_id(base_count_);
  return base;
}

Pose EntityFactory::SetPoseRandomly() {
  // Dividing arena into 19x14 grid. Each grid square is 50x50
  return {static_cast<double>((30 + (random() % 19) * 50)),
        static_cast<double>((30 + (random() % 14) * 50))};
}

double EntityFactory::SetRadiusRandomly() {
  // randomly set the radius of the Lights
  return (random()%41)+10;
}

NAMESPACE_END(csci3081);
