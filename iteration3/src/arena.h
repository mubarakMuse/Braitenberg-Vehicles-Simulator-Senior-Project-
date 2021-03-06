/**
 * @file arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>

#include "src/common.h"
#include "src/food.h"
#include "src/entity_factory.h"
#include "src/robot.h"
#include "src/robot_type.h"
#include "src/communication.h"
#include "src/light_sensor.h"
#include "src/light.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many entities
 * running around.
 *
 * While GraphicsArenaViewer handles the graphics, Arena handles all the
 * data and all the entities (it is the model of MVC). It manages the
 * interaction among the entities in the Arena.
 *
 */

class Arena {
 public:
  /**
   * @brief Arena's constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of Arena and the entities therein.
   *
   * Initialize all private variables and entities.
   */
  explicit Arena(const struct arena_params *const params);

  /**
   * @brief Arena's destructor. `delete` all entities created.
   */
  ~Arena();

  /**
   * @brief Advance the simulation by the specified # of steps.
   *
   * @param[in] dt The # of steps to increment by. This is
   * practically unused because the arena state is advanced
   * incrementally at a fixed rate.
   *
   * If `dt == 0`, `return` immediately. Otherwise calls
   * Arena::UpdateEntitiesTimestep() once.
   */
  void AdvanceTime(double dt);

   /**
   * @brief function to add a robot to the arena
   *
   * @param rt the behavior of the robot's motion toward sensors
   *
   **/
  void AddRobot(RobotType rt, int quantity);

  /**
   * @brief function to add an entity to the arena
   *
   * @param type of the entity (food or light)
   *
   **/
  void AddEntity(EntityType type, int quantity);

  /**
   * @brief registers the light sensors of the robot as observes of arena
   *
   * @param[in] ob The lightsensor of the robot
   *
   */
  void RegisterLightSensorObserver(LightSensor* ob);

  /**
   * @brief registers the food sensors of the robot as observes of arena
   *
   * @param[in] ob The foodsensor of the robot
   *
   */
  void RegisterFoodSensorObserver(FoodSensor* ob);

  /**
   * @brief notify the observes of the new postions of the foods and lights
   */
  void Notify();

  /**
   * @brief translates communication from the controller to action in the arena
   */
  void AcceptCommand(Communication com);

  /**
   * @brief Reset all entities in Arena.
   */
  void Reset();

  /**
   * @brief Get the Robot  in Arena.
   *
   * @return A pointer to the Robot.
   */
  class Robot *robot() const { return robot_; }

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  Arena &operator=(const Arena &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  Arena(const Arena &other) = delete;

  /**
   * @brief Determine if two entities have collided in the Arena. Collision is
   * defined as the distance between two entities being less than the sum of
   * their radii.
   *
   * @param mobile_e This entity is definitely moving.
   * @param other_e This entity might be mobile or immobile.
   * @param[out] True if entities overlapping.
   *
   **/
  bool IsColliding(
    ArenaMobileEntity * const mobile_e, ArenaEntity * const other_e);

  /**
  * @brief Move the mobile entity to the edge of the other without overlap.
  * Without this, entities tend to get stuck inside one another.
  **/
  void AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
    ArenaEntity *const other_e);

  /**
   * @brief Determine if a particular entity has gone out of the boundaries of
   * the simulation (i.e. has collided with any one of the walls).
   *
   * @param ent The entity to check.
   * @param [out] An entity type signifying wall (e.g. kRightWall). kUndefined
   * if no collision.
   *
   * The checked entity's position will be updated to a "back-off position" so
   * that it won't get stuck into a wall. The calculation of the "back-off
   * position" is technically not accurate, but good enough for our purpose.
   */
  EntityType GetCollisionWall(ArenaMobileEntity * const ent);

  /**
  * @brief Move the entity to the edge of the wall without overlap.
  * Without this, entities tend to get stuck in walls.
  **/
  void AdjustWallOverlap(ArenaMobileEntity * const ent, EntityType wall);


  /**
   * @brief Update all entities for a single timestep.
   *
   * First calls each entity's TimestepUpdate method to update their speed,
   * heading angle, and position. Then check for collisions between entities
   * or between an entity and a wall.
   */
  void UpdateEntitiesTimestep();

   /**
   * @brief Update the game status to win or loss.
   *
   * Check if the robots lives is zero or less after each collison
   * or check if robot touched all bases
   *
   */
  void UpdateGameStatus();

  void ConfigArena(int robotnum, double coward_percent,
    int lightnum, int foodnum, double sensitivity, bool food_on_);


  std::vector<class ArenaEntity *> get_entities() const { return entities_; }

  double get_x_dim() { return x_dim_; }
  double get_y_dim() { return y_dim_; }

  int get_game_status() const { return game_status_; }
  void set_game_status(int status) { game_status_ = status; }

 private:
// Dimensions of graphics window inside which entities must operate
  double x_dim_;
  double y_dim_;

  // Used to create all entities within the arena
  EntityFactory *factory_;

  // Robot is special. It's also stored in the entity vectors.
  Robot *robot_{nullptr};

// Light object in order to store it in the mobiile entites correclty.
  Light *Light_{nullptr};

  Food *food_{nullptr};

  // All entities mobile and immobile.
  std::vector<class ArenaEntity *> entities_;

  // A subset of the entities -- only those that can move .
  std::vector<class ArenaMobileEntity *> mobile_entities_;
  // A subset of the entities -- lights only
  std::vector<class ArenaEntity *> light_entities_;

  // A subset of the entities -- lights only
  std::vector<class ArenaEntity *> food_entities_;

  // All of the lightsensors in the arena
  std::vector<class LightSensor* > lightsensor_observers_;

  // All of the foodsensors in the arena
  std::vector<class FoodSensor* > foodsensor_observers_;

  // win/lose/playing state
  int game_status_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
