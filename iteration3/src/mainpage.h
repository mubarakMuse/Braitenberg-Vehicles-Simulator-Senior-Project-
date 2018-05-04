/**
 * @file mainpage.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 
This is a program that simulates the Braitenberg Vehicles Braitenberg Vehicles are the thought experiments of Valentino Braitenberg, who imagined complex behavior from simple design. His vehicles exhibit aggression, fear, exploration, and love through simple sensor-motor connections. In my program, the robots play the role of the vehicles and inhibit those four different behaviors. Robots exhibits those behaviors towards 2 arena entities, food and lights.

 * \section Technical_Guide

Food

Foods objects in my arena are immobile arena entities which inherits from arena entitles. When the simulation begins, foods, with a fixed radius, are randomly placed around the arena and are colored red.

Light

Lights objects in my arena are mobile arena entities, which also inherits from the arena entities. At the start of the simulation, lights began moving a velocity of 5 for both wheels and are colored white. lights&#39; motion is handled by motion handler robot class. It updates it velocity. It also changes the heading again by 180 degrees.

Sensor (Light Sensor/ Food Sensor)

Sensors in my program are not arena entity but a stand alone class. Both the light and food sensor inherit from this class. The main function of the sensor class is to serve as an interface for those two sensors. The sensors essentially calculate reading based on the distance it is to either food or light, respectively. The update function of both types of sensors takes in a vector of arena entities as argument, which ever it sensing, and then from there calculates the total reading be accumulating the separate individual readings.

Robot

Robots are also mobile arena entities in my arena. When a robot object is created it begins off by having the generic motion handler robot class handle it motion. Every robot has a type which is assigned to through its constructer. The constructer takes in one of the four behaviors as an argument and based of that assigns that robot the appropriate behavior (we will dive deeper into how that works in the Strategy pattern implementation section below). At the start of the simulation, a robot is placed randomly in the arena, is stationary and is colored blue. Every robot has four sensors, one right food and one light sensor at an offset angle of -65 degrees of the robot&#39;s position, and one left light sensor and one food sensor at an offset angle of 65 degree of the robot&#39;s position.

Key tasks that are done within the robot class (TimeStepUpdate method):

- Initializing the four sensors (food and light sensors)
- Assigning the appropriate motion handler based on the robot type/behavior
- Keeping track of the the hunger of the robot and handling the transition to the aggressive behavior towards food.
- Update the sensor position based of the position of its position.
- Strategy Pattern
  - in the way that robots exhibit different behaviors towards entities with the arena. I created different motion handler classes that inherit from the parent class. In particular, I have 4 different motion handler child classes that represents the four different behaviors robots exhibit (fear, love, explore, and aggression). Each of the classes then implement the update velocity function and thereby allowing it to implemented it with respect to the behaviors that class is representing.

Arena

Arena is the main class within the program, Its the model for my program in the MVC model. The arena class is where all the entitles interact with each other.

Some of the key tasks that the are handled are:

- Adding Robots and Entities
- Observer Design Pattern implementation:
  - My implementation of the observer design strategy takes advantage of the arena and it knowledge of all the entities that are in our simulation. I realized that the arena would be the best candidate to be the subject in my implementation of the observer strategy. I modified my arena to be my subject by creating several new pointer vectors that would keep track of the robot sensors and light and food entities. Therefore, when it comes time to notify and update the observers it would have all the info about those entities and can pass them along to its observers. My choice for the observers of the arena was a bit tricky at first. It was a choice between making the robots observer or the sensors of each robot directly the observers of the arena. I end up implementing the strategy with the sensors as the observers of the arena because first it would mean less methods being called since if the robot it self was the observer it would then need update it sensor whenever it was updated itself. When the arena is creating robots it also registers the pointers to the sensor of that robot. Then the notify function is called at each times stamp update and that updates all the sensor with a vector all the entities its tracking.

- Collision Handling:
  - Collisions are only handled either if the entities are of the same types or if an arena entity collides with a wall or a robot collides with a food object. Generally, collisions are in the arena by calling on the individual collision handling methods of those entities. For the most part, that method just add 180 degrees to the heading, which creates a bouncing off effect.



Graphics Arena Viewer:

The graphics arena viewer serves as the viewer for my program in the MVC model. This class&#39;s 2 main function is to display my program on to the arena and to provide the GUI functionality for the user to configure my simulation.

- GUI:
  - The GUI panel consists of the three buttons and and 5 slider
  - Play and Pause button: This button is linked to a function that alternates the setting of the truth value of a class variable called paused. The variable is a condition to whether the time is advanced.
  - New game Button: this button pauses the simulation and then looks for any changes in the GUI provided to the user and calls the config\_arena function. This function is a pass through function pass along the settings of the GUI to the controller which then passes along to the arena and then arena then use those new setting to reset and reconfigure the arena to match the GUI.
  - Food on and off button: linked to a bool variable that it set accordingly, to be passed along to the arena as one of the arguments of the Pass thru function, config\_arena.
  - The remaining five sliders all have variables that the slider sets and is also then passed a long to the arena as arguments to the pass thru function, Config\_Arena. Those five sliders set the amount of robots, the ratio of coward to explore robots, the number of foods, the number of lights and the sensitivity of the light sensor in sensing the lights around it.

- Displaying Arena Entities:
  - The class utilized the NanoVG library to draw the entitles that are in the arena the class is linked to via a pointer.

* \section User_Guide

The start of the game:

When the game begins, the arena has 10 robots, 5 which exhibit explore behavior and 5 which exhibit coward behavior towards the light. There also 4 food items which are colored red and 4 light items that are colored white. The lights are the only things that should be moving initially then slowly the robot began to move as a reaction to the lights.

Configuring the simulation:

As a user, via the GUI panel in the upper right corner of the window, are allowed to:

- Pause and play the game - play button
- Start a new game- new game button
- Turn of food (no food in the simulation at all) – FoodOn button
- Choose the amount of robots in the simulation (1-10) - 1st Slider
- Choose the amount of light in the simulation (1-5) -  2nd slider
- Choose the amount of food in the simulation (1-5) -  3rd slider
- Choose the ratio of explore robots to coward robots (1%-100%) – 4th slider
- Choose the sensitivity of the light sensor (0-1) – 5th slider



All change to GUI go into effect after a new game has been started.
 *
 */
#endif  // SRC_MAINPAGE_H_
