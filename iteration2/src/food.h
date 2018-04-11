/**
 * @file food.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FOOD_H_
#define SRC_FOOD_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/params.h"
#include "src/arena_immobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a immobile Food within the Arena.
 *
 *
 * Food have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Food : public ArenaImmobileEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A Food_params passed down from main.cc for the
   * initialization of the Food.
   */
  Food();

  /**
   * @brief Reset the Food using the initialization parameters received
   * by the constructor.
   */
  void Reset() override;

  /**
   * @brief Get the name of the Food for visualization purposes, and to
   * aid in debugging.
   *
   * @return Name of the Food.
   */
  std::string get_name() const override { return "Food"; }

  /**
   * @brief Getter for captured_, which is the state of the Food
   *
   * @return true if captured.
   */
  bool IsCaptured() const { return captured_; }

  /**
   * @brief Setter for captured_, which is the state of the Food. It also changes the color of the Food once its captured.
   */
void set_captured(bool state) {
  captured_ = state;
  if (IsCaptured()) {
    set_color(FOOD_COLOR_POST_COLLISION);
  }
}
 // void set_robot_type(__unused RobotType rt) override {}
 //  RobotType get_robot_type() override{
 //    return kUndefinedRT;
 //  }
 //  //virtual void set_TotalSensorReading(double tsr);
 //   double get_TotalSensorReading() override {
 //    return 0;
 //   }

 private:
  bool captured_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_H_