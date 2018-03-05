### Feedback for Iteration 1

Run on March 02, 03:55:32 AM.


#### Necessary Files and Structure

+ Pass: Check that directory "iteration1" exists.

+ Pass: Check that directory "iteration1/src" exists.

+ Pass: Check that directory "iteration1/docs" exists.

+ Fail: Check that file "iteration1/docs/Doxyfile" exists.

     "iteration1/docs/Doxyfile" not found.


### .gitignore set up properly

+ Pass: Check that file/directory "iteration1/build" does not exist.

+ Pass: Check that file/directory "iteration/docs/html" does not exist.

+ Pass: Check that file/directory "iteration1/docs/latex" does not exist.

+ Pass: Change into directory "iteration1".


#### Doxygen

+ Fail: Generating documentation by running doxygen

+ Fail: Check that file "src/mainpage.h" exists.

     "src/mainpage.h" not found.

+ Fail: Check that file "html/classRobot.html" exists.

     "html/classRobot.html" not found.

+ Fail: Check that file "html/classObstacle.html" exists.

     "html/classObstacle.html" not found.


#### Google Style Compliance

+ Fail: Cpplint checking for for Google C++ compliance

Done processing src/wheel_velocity.h
Done processing src/arena_entity.h
Done processing src/params.h
Done processing src/sensor_touch.h
Done processing src/entity_factory.h
Done processing src/motion_handler.h
Done processing src/robot.h
Done processing src/rgb_color.h
Done processing src/common.h
Done processing src/controller.h
Done processing src/pose.h
Done processing src/obstacle.h
Done processing src/motion_behavior.h
Done processing src/arena_immobile_entity.h
Done processing src/graphics_arena_viewer.h
Done processing src/communication.h
Done processing src/arena.h
Done processing src/arena_params.h
Done processing src/base.h
Done processing src/motion_handler_robot.h
Done processing src/entity_type.h
Done processing src/arena_mobile_entity.h
Done processing src/motion_behavior_differential.h
Total errors found: 14src/motion_handler.h:42:  Missing space after ,  [whitespace/comma] [3]
src/robot.h:106:  At least two spaces is best between code and comments  [whitespace/comments] [2]
src/robot.h:106:  Missing space before {  [whitespace/braces] [5]
src/arena.h:171:  Line ends in whitespace.  Consider deleting these extra spaces.  [whitespace/end_of_line] [4]
src/arena.h:172:  Weird number of spaces at line-start.  Are you using a 2-space indent?  [whitespace/indent] [3]
src/arena.h:196:  Line ends in whitespace.  Consider deleting these extra spaces.  [whitespace/end_of_line] [4]
src/arena.h:196:  Redundant blank line at the end of a code block should be deleted.  [whitespace/blank_line] [3]
src/arena_params.h:34:  Line ends in whitespace.  Consider deleting these extra spaces.  [whitespace/end_of_line] [4]
src/arena_params.h:34:  At least two spaces is best between code and comments  [whitespace/comments] [2]
src/base.h:75:  private: should be indented +1 space inside class Base  [whitespace/indent] [3]
src/motion_handler_robot.h:78:  Line ends in whitespace.  Consider deleting these extra spaces.  [whitespace/end_of_line] [4]
src/arena_mobile_entity.h:72:  #endif line should be "#endif  // SRC_ARENA_MOBILE_ENTITY_H_"  [build/header_guard] [5]
src/motion_behavior_differential.h:87:  #endif line should be "#endif  // SRC_MOTION_BEHAVIOR_DIFFERENTIAL_H_"  [build/header_guard] [5]
src/motion_behavior_differential.h:34:  Missing space after ,  [whitespace/comma] [3]


#### Compilation on a CSE Labs machine

+ Pass: Change into directory "src".

+ Fail: make 'all' in directory '.': expect result=../build/bin/arenaviewer, timeout=500, extra_args='CS3081DIR=/classes/csel-s18c3081'
    make finished compiling target=all, directory=. with errors:

```shell
arena.cc: In constructor ‘csci3081::Arena::Arena(const csci3081::arena_params*)’:
arena.cc:24:1: error: ‘csci3081::Arena::num_Bases_coloidedWith’ should be initialized in the member initialization list [-Werror=effc++]
 Arena::Arena(const struct arena_params *const params)
 ^
cc1plus: all warnings being treated as errors
make: *** [../build/obj/src/arena.o] Error 1

```


#### Unit Tests

+ Pass: Change into directory "../../".

+ Pass: make 'all' in directory '.': expect result=build/bin/unittest, timeout=500, extra_args='PROJROOTDIR=../../project-musex025/iteration1/'

    make successful.
    Check build/bin/unittest exists...OK: result build/bin/unittest found

+ Pass: Run unit test 'build/bin/unittest', extra_args='', allowed_fails=0

