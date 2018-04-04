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
#include <string>

#include "src/common.h"
#include "src/pose.h"
#include "src/arena_entity.h"

#include "src/rgb_color.h"
#include "src/arena_mobile_entity.h"
#include "src/light.h"
<<<<<<< HEAD
=======

>>>>>>> bd3f800e588ee4d70fbd2ba3eb1d05bc48205a74
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);


class Sensor {
 public:

<<<<<<< HEAD
=======

>>>>>>> bd3f800e588ee4d70fbd2ba3eb1d05bc48205a74
  explicit Sensor(ArenaMobileEntity * ent) : entity_{ent} {}

  virtual ~Sensor() = default;

<<<<<<< HEAD
  virtual int CalculateReading( __unused Light *ent);
=======
  virtual void update(__unused std::vector<class Light *> stimili){}
>>>>>>> bd3f800e588ee4d70fbd2ba3eb1d05bc48205a74

  virtual void Reset() {};





  void set_reading(int num){
    reading_ = num;
  }
  int get_reading(){
    return reading_;
  }
<<<<<<< HEAD
  
  // void set_Pose(Pose &p){
  //   SensorPose_ = p;
  // }

  // Pose get_pose(){
  //   return SensorPose_;
  // }
=======

>>>>>>> bd3f800e588ee4d70fbd2ba3eb1d05bc48205a74


  const RgbColor &get_color() const { return color_; }

  void set_color(const RgbColor &color) { color_ = color; }

  const Pose &get_pose() const { return SensorPose_; }
  void set_pose(const Pose &pose) { SensorPose_ = pose; }

  /**
   * @brief Setter method for position within entity pose variable.
   */
  void set_position(const double inx, const double iny) {
    SensorPose_.x = inx;
    SensorPose_.y = iny;
  }

  void set_heading(const double t) {SensorPose_.theta = t;}

  /**
   * @brief Setter for heading within pose, but change is relative to current
   * value.
   *
   * @param[in] delta by which to modify current heading. Can be positive
   * or negative.
   */
  void RelativeChangeHeading(const double delta) {
    SensorPose_.theta += delta;
  }

 private:
  int reading_{0};
  Pose SensorPose_;
  RgbColor color_;
 
 protected:
  ArenaMobileEntity * entity_;
<<<<<<< HEAD
=======

>>>>>>> bd3f800e588ee4d70fbd2ba3eb1d05bc48205a74
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
