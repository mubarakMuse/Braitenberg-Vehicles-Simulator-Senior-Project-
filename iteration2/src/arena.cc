/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>

#include "src/arena.h"
#include "src/arena_params.h"
#include "src/robot_type.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params *const params)
    : x_dim_(params->x_dim),
      y_dim_(params->y_dim),
      factory_(new EntityFactory),
      entities_(),
      mobile_entities_(),
      light_entities_(),
      lightsensor_observers_(),
      foodsensor_observers_(),
      game_status_(PLAYING) {
  AddRobot(kCoward);
  AddRobot(kCoward);
  AddRobot(kCoward);
  AddRobot(kCoward);
  AddRobot(kCoward);
  AddRobot(kExplore);
  AddRobot(kExplore);
  AddRobot(kExplore);
  AddRobot(kExplore);
  AddRobot(kExplore);


  AddEntity(kFood, 4);  // 4 foods
  AddEntity(kLight,4);   // changed the params to 4
}

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Arena::AddRobot(RobotType rt) {
  robot_ = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot,rt));
  entities_.push_back(robot_);
  mobile_entities_.push_back(robot_);
  LightSensor* right = robot_->get_right_light_sensor();
  LightSensor* left = robot_->get_left_light_sensor();
  FoodSensor* left_foodsensor = robot_->get_left_food_sensor();
  FoodSensor* right_foodsensor = robot_->get_right_food_sensor();
  RegisterLightSensorObserver(right); // sensors are observers of my arena
  RegisterLightSensorObserver(left);
  RegisterFoodSensorObserver(left_foodsensor);
  RegisterFoodSensorObserver(right_foodsensor);
}

void Arena::AddEntity(EntityType type, int quantity) {
  for (int i = 0; i < quantity; i++) {
    if (type == kLight) {
      // making Lights mobile adding them to the mobeil entity vector
      Light_ = dynamic_cast<Light *>(factory_->CreateEntity(kLight));
      entities_.push_back(Light_);
      mobile_entities_.push_back(Light_);
      light_entities_.push_back(Light_);
    }
    else if (type == kFood) {
      food_ = dynamic_cast<Food *>(factory_->CreateEntity(kFood));
      entities_.push_back(factory_->CreateEntity(type));
      food_entities_.push_back(food_);
    } else {
      entities_.push_back(factory_->CreateEntity(type));
      // something else
    }
  }
}
void Arena::RegisterLightSensorObserver(LightSensor* ob){
  lightsensor_observers_.push_back(ob);
}
void Arena::RegisterFoodSensorObserver(FoodSensor* ob){
  foodsensor_observers_.push_back(ob);
}

void Arena::Notify(){ // called at each timesupdate
   for (auto observer: lightsensor_observers_) {
    observer->update(light_entities_);
  }
   for (auto observer: foodsensor_observers_) {
    observer->update(food_entities_);
  }

}


void Arena::Reset() {
  for (auto ent : entities_) {
    ent->Reset();
    set_game_status(PLAYING);  // reset the game status
  } /* for(ent..) */
} /* reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0)) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    if (game_status_ == PLAYING) {  // only if the game hasnt been losed or won
      UpdateEntitiesTimestep();
    }
    // UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */
void Arena::UpdateEntitiesTimestep() {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  Notify(); // set sesnor readings

  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  }
  /* Determine if any mobile entity is colliding with wall.
   * Adjust the position accordingly so it doesn't overlap.
   */
  for (auto &ent1 : mobile_entities_) {
    EntityType wall = GetCollisionWall(ent1);
    if (kUndefined != wall) {
      AdjustWallOverlap(ent1, wall);
      ent1->HandleCollision(wall, NULL);
    }
    /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */    
    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        if (ent2->get_type() == ent1->get_type()){ // lights and robots only
          AdjustEntityOverlap(ent1, ent2);
          ent1->HandleCollision(ent2->get_type(), ent2);
        }
        if (ent2->get_type() == kFood && ent1->get_type() == kRobot){ // to see if robot eat the food
          ent1->HandleCollision(ent2->get_type(), ent2);
        }
      }
    }
  }
}  // UpdateEntitiesTimestep()

// Determine if the entity is colliding with a wall.
// Always returns an entity type. If not collision, returns kUndefined.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move the entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default:
    {}
  }
}

/* Calculates the distance between the center points to determine overlap */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
}

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
/* @TODO: Add functionality to Pose to determine the distance distance_between two instances (e.g. overload operator -)
*/
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
    double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between;
    double angle = atan2(delta_y, delta_x);
    mobile_e->set_position(
      mobile_e->get_pose().x+cos(angle)*distance_to_move,
      mobile_e->get_pose().y+sin(angle)*distance_to_move);
}

// Accept communication from the controller. Dispatching as appropriate.
void Arena::AcceptCommand(Communication com) { // disabled arrows to direct robot
  switch (com) {
    case(kIncreaseSpeed):
    break;
    case(kDecreaseSpeed):
    break;
    case(kTurnLeft):
    break;
    case(kTurnRight):
    break;
    case(kPlay):
    break;
    case(kPause):
    case(kReset):
    Reset();
    break;
    case(kNone):
    default: break;
  }
} /* AcceptCommand */

NAMESPACE_END(csci3081);
