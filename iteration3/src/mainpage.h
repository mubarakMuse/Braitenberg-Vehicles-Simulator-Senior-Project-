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
 
This is a program that simulates the Braitenberg Vehicles which are the thought experiments of Valentino Braitenberg, who imagined complex behavior from simple design. His vehicles exhibit aggression, fear, exploration, and love through simple sensor-motor connections. In my program, the robots play the role of the vehicles and inhibit those four different behaviors and they exhibit the behaviors towards 2 arena entities which are food and light.
 * \section Technical_Guide

Food

Food objects in my arena are immobile arena entities which inherits from arena entities. When the simulation begins, foods, with a fixed radius, are randomly placed around the arena and are colored red.

Light

Light objects in my arena are mobile arena entities, which also inherits from the arena entities. At the start of the simulation, lights begin moving at a velocity of 5 for both wheels and are colored white. The lights&#39; motion is handled by a motion handler robot class. It updates it velocity and also changes the heading again by 180 degrees.

Sensor (Light Sensor/Food Sensor):

Sensors in my program are not an arena entity but rather, a stand-alone class and both the light and food sensors inherit from this class. The main function of the sensor class is to serve as an interface for those two sensors. The sensors essentially calculate reading based on the distance it is to either food or light, respectively. The update function of both types of sensors takes in a vector of arena entities as an argument, whichever it is sensing, and then from there calculates the total reading by accumulating the separate individual readings.

Robot

Robots are also classified as mobile arena entities in my arena. When a robot object is created it starts by having the generic motion handler robot class handle its motion. Every robot has a type which is assigned through its constructer. The constructer takes in one of the four behaviors as an argument and based off of that assigns that robot its appropriate behavior (we will dive deeper into how that works in the Strategy Pattern Implementation section below). At the start of the simulation, a robot is placed randomly in the arena, it is stationary and is colored blue. Every robot has four sensors, one right food sensor and one light sensor at an offset angle of -65 degrees of the robot&#39;s position, and one left light sensor and one food sensor at an offset angle of 65 degrees of the robot&#39;s position.

Key tasks that are done within the robot class (TimeStepUpdate method):

- Initializing the four sensors (food and light sensors)
- Assigning the appropriate motion handler based  on the robot type/behavior
- Keeping track of the hunger of the robot and handling the transition to the aggressive behavior towards food.
- Update the sensor position based off its position.
- Strategy Pattern
  - Based on the way that robots exhibit different behaviors towards entities with the arena, I created different motion handler classes that inherit from the parent class. In particular, I have 4 different motion handler child classes that represents the four different behaviors robots exhibit (fear, love, exploration, and aggression). Each of the classes then implement the update velocity function and thereby allowing it to be implemented with respect to the behaviors that each class is representing.

Arena

Arena is the main class within the program, and it is the model for my program in the MVC model. The arena class is where all the entities interact with each other.

Some of the key tasks that are handled within the arena class are:

- Adding Robots and Entities
- Observer Design Pattern Implementation:
  - My implementation of the observer design strategy takes advantage of the arena and the knowledge of all the entities that are in our simulation. I realized that the arena would be the best candidate to be the subject in my implementation of the observer strategy. I modified my arena to be my subject by creating several new pointer vectors that would keep track of the robot sensors and light and food entities. Therefore, when it comes time to notify and update the observers it would have all the info about those entities and can pass them along to its observers. My choice for the observers of the arena was a bit tricky at first. It was a choice between making the robots the observer or the sensors of each robot directly the observers of the arena. I ended up implementing the strategy with the sensors as the observers of the arena because that would mean less methods being called since the robot itself was the observer. It would then need to update the sensor whenever it was updated itself. When the arena is creating robots it also registers the pointers to the sensor of that robot. Then the notify function is called at each times the stamp updates and that updates all the sensor with a vector that all the entities its tracking.

- Collision Handling:
  - Collisions are only handled either if the entities are of the same types, if an arena entity collides with a wall or if a robot collides with a food object. Generally, collisions are in the arena by calling on the individual collision handling methods of those entities. For the most part, that method just adds 180 degrees to the heading, which creates a bouncing off effect.

Graphics Arena Viewer:

The graphics arena viewer serves as the viewer for my program in the MVC model. This class&#39;s 2 main functions are to display the program onto the arena and to provide the GUI functionality for the user to configure my simulation.

- GUI:
  - The GUI panel consists of the three buttons and 5 sliders.
  - Play and Pause button: This button is linked to a function that alternates the setting of the truth value of a class variable called paused. The variable is a condition to whether the time is advanced.
  - New Game Button: This button pauses the simulation and then looks for any changes in the GUI provided to the user and calls the config\_arena function. This function is a pass-through function that passes along the settings of the GUI to the controller, which then passes it along to the arena. Then the arena uses those new settings to reset and reconfigure the arena to match the GUI.
  - Food on and off button: This button is linked to a bool variable that is set accordingly to be passed along to the arena as one of the arguments of the pass-through function; config\_arena.
  - The remaining five sliders all have variables that the slider sets and is also then passed along to the arena as arguments to the pass-through function, Config\_Arena. Those five sliders set the amount of robots, the ratio of coward to explore robots, the number of foods, the number of lights and the sensitivity of the light sensor in sensing the lights around it.

- Displaying Arena Entities:
  - The class utilized the NanoVG library to draw the entities that are in the arena and the class is linked to via a pointer.

* \section User_Guide

The start of the game:

When the game begins the arena has 10 robots; 5 which exhibit the explore behavior and 5 which exhibit coward behavior towards the light. There also 4 food items which are colored red and 4 light items that are colored white. The lights are the only things that should be moving initially then slowly the robot begins to move as a reaction to the lights.

Configuring the simulation:

As a user, via the GUI panel in the upper right corner of the window, you are allowed to:

- Pause and play the game - play button
- Start a new game - new game button
- Turn of food (no food in the simulation at all) – Food On button
- Choose the amount of robots in the simulation (1-10) - 1st Slider
- Choose the amount of light in the simulation (1-5) -  2nd slider
- Choose the amount of food in the simulation (1-5) -  3rd slider
- Choose the ratio of explore robots to coward robots (1%-100%) – 4th slider
- Choose the sensitivity of the light sensor (0-1) – 5th slider

All change to the GUI go into effect after a new game has been started.
 *
 */
#endif  // SRC_MAINPAGE_H_
