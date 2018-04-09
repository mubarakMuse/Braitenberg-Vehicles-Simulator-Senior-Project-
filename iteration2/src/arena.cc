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
      observers_(),
      game_status_(PLAYING) {
  AddRobot(kAggressive);
  AddEntity(kBase, 0);  // changed this 3 i need  to us params
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
  RegisterObserver(right);
  RegisterObserver(left);
}

void Arena::AddEntity(EntityType type, int quantity) {
  for (int i = 0; i < quantity; i++) {
    if (type == kLight) {
      // making Lights mobile adding them to the mobeil entity vector
      Light_ = dynamic_cast<Light *>(factory_->CreateEntity(kLight));
      entities_.push_back(Light_);
      mobile_entities_.push_back(Light_);
      light_entities_.push_back(Light_);

    } else {
      entities_.push_back(factory_->CreateEntity(type));
      // if its a base or something else
    }
  }
}
void Arena::RegisterObserver(LightSensor* ob){
  observers_.push_back(ob);
}

void Arena::Notify(){
   for (auto observer: observers_) {
    observer->update(light_entities_);
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
  Notify();
  for (size_t i = 0; i < 1; ++i) {
    if (game_status_ == PLAYING) {  // only if the game hasnt been losed or won
      UpdateEntitiesTimestep();
    }
    // UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

// void Arena::UpdateGameStatus() {  // checks for wins and lossses
//   if (robot_->get_lives() <= 0) {
//     set_game_status(LOST);
//     for (auto ent1 : entities_) {
//       ent1->set_color(LOSS_COLOR);
//     }
//   }
//   bool AllBasesCaptured = true;
//   for (auto ent : entities_) {
//     if (ent->get_type() == kBase) {
//       AllBasesCaptured = AllBasesCaptured &&
//       dynamic_cast<Base *>(ent)->IsCaptured();
//        // checks if all the base were captured
//     }
//   }
//   if (AllBasesCaptured) {
//     set_game_status(WON);
//     for (auto ent2 : entities_) {
//       ent2->set_color(WON_COLOR);
//     }
//   }
// }
void Arena::UpdateEntitiesTimestep() {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
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
      // if (ent1->get_type() == kRobot) {
      //   robot_->lose_A_Life();
      // UpdateGameStatus();
      // }
    }
    /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        if (ent2->get_type() == kLight && ent1->get_type() == kLight){
          AdjustEntityOverlap(ent1, ent2);
          ent1->HandleCollision(ent2->get_type(), ent2);
        }
        // if (ent2->get_type() == kLight && ent1->get_type() == kRobot){
        //   robot_->lose_A_Life();
        //   UpdateGameStatus();
        // }
        // if (ent2->get_type() == kBase && ent1->get_type() == kRobot){
        //   //ent2->set_color(BASE_COLOR_POST_COLLISION); // Added for priority 1 change color is it the base to yellow
        //   dynamic_cast<Base *> (ent2)->set_captured(true);
        //   UpdateGameStatus();
        // }

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
/* @BUG: The robot will pass through the home base on occasion. The problem
 * is likely due to the adjustment being in the wrong direction. This could
 * be because the cos/sin generate the wrong sign of the distance_to_move
 * when the collision is in a specific quadrant relative to the center of the
 * colliding entities..
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
void Arena::AcceptCommand(Communication com) {
  switch (com) {
    case(kIncreaseSpeed):
    robot_->IncreaseSpeed();
    break;
    case(kDecreaseSpeed):
    robot_->DecreaseSpeed();
    break;
    case(kTurnLeft):
    robot_->TurnLeft();
    break;
    case(kTurnRight):
    robot_->TurnRight();
    break;
    case(kPlay):
    break;
    case(kPause):
    break;
    case(kReset):
    Reset();
    break;
    case(kNone):
    default: break;
  }
} /* AcceptCommand */

NAMESPACE_END(csci3081);
