/**
 * @file sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <string>
#include <vector>

#include "src/common.h"
#include "src/pose.h"
#include "src/arena_entity.h"

#include "src/rgb_color.h"
#include "src/arena_mobile_entity.h"
#include "src/light.h"



/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);


class Sensor {
 public:
  explicit Sensor(ArenaMobileEntity * ent) :sensorpose_(),
  color_(),
  entity_{ent} {}

  virtual ~Sensor() = default;
  Sensor(const Sensor&) = default;
  Sensor& operator=(const Sensor& other) = default;

  virtual void update(__unused std::vector<class ArenaEntity *> stimili) {}


  virtual void Reset() {}

  void set_reading(int num) {
    reading_ = num;
  }
  int get_reading() {
    return reading_;
  }

  void set_pose(Pose p) {
    sensorpose_ = p;
  }

  Pose get_pose() {
    return sensorpose_;
  }

  void sensor_robot_location(double angle) {
    double theta = entity_->get_pose().theta + angle;
    double x = entity_->get_radius() * cos(theta)+ entity_->get_pose().x;
    double y = entity_->get_radius() * sin(theta)+ entity_->get_pose().y;
    set_position(x, y);
  }

  const RgbColor &get_color() const { return color_; }

  void set_color(const RgbColor &color) { color_ = color; }

  /**
   * @brief Setter method for position within entity pose variable.
   */
  void set_position(const double inx, const double iny) {
    sensorpose_.x = inx;
    sensorpose_.y = iny;
  }

  void set_heading(const double t) {sensorpose_.theta = t;}

  /**
   * @brief Setter for heading within pose, but change is relative to current
   * value.
   *
   * @param[in] delta by which to modify current heading. Can be positive
   * or negative.
   */
  void RelativeChangeHeading(const double delta) {
    sensorpose_.theta += delta;
  }
  void change_sensor_sensitivity(double ss){
    sensor_sensitivity = ss;
  }

 private:
  int reading_{0};
  Pose sensorpose_;
  RgbColor color_;

 protected:
  ArenaMobileEntity * entity_;
  double sensor_sensitivity{1.02};
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
