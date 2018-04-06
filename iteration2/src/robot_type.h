/**
 * @file robot_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_TYPE_H_
#define SRC_ROBOT_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum RobotType {
  kLove, kExplore, kAgressive,kCoward,kUndefinedRT
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_TYPE_H_
