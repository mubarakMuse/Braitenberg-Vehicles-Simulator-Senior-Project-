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
 *
 * This is the introduction.
 *
 * \section Progam_Description
 * The Progam is a video game in which a user controls the robot with the arrow keys.
 * The objective of the game is to touch all of the bases without running into
 * Lights or walls. The robot is given a fixed number of nine lives at the beginning of the game,
 * but it will lose a life with every collision (except for when colliding with a base).
 *
 * \section Win_loss
 * The Program determines is the robot has won or losses, it calls a function after each collision to see
 * whether all the bases have been captured or if the lives of the robot are zero or less.
 * If one of those is true and then changes the game status accordingly.
 * the game has been won all entites turn red and if the robot looses than it all turns purple.
 *_It should provide a brief overview/introduction to the software_

This is a program that simulates the brainteberg model. the different robots in my program represent different behaviors which react to two types of stimuli , food and light.

The light in my system is mobile and moves around at a constant speed of 5,

While the food in my system are immobile.

_then discuss specifics in the design and implementation that will assist any programmer who will be a new contributor to the code,_

Observer Design Pattern implementation:

My implementation of the observer design strategy takes advantage of the arena and it knowledge of all the entities that are in our simulation. I realized that the arena would be the best candidate to be the subject in my implementation of the observer strategy. I modified my arena to be my subject by creating several new pointer vectors that would keep track of the robot sensors and light and food entities. Therefore, when it comes time to notify and update the observers it would have all the info about those entities and can pass them along to its observers.

My choice for the observers of the arena was a bit tricky at first. It was a choice between making the robots observer or the sensors of each robot directly the observers of the arena. I end up implementing the strategy with the sensors as the observers of the arena because first it would mean less methods being called since if the robot it self was the observer it would then need update it sensor whenever it was updated itself. When the arena is creating robots it also registers the pointers to the sensor of that robot. Then the notify function is called at each times stamp update and that updates all the sensor with a vector all the entities its tracking.



I implemented the strategy pattern in the way that robots exhibit different behaviors towards entities with the arena. I created different motion handler classes that inherit from the parent class. In particular, I have 4 different motion handler child classes that represents the four different behaviors robots exhibit (fear, love, explore, and aggression). Each of the classes then implement the update velocity function and thereby allowing it to implemented it with respect to the behaviors that class is representing.



- _and finally provide a user guide for non-technical users to be able to download, configure, and operate the simulator. If the text were on an 8.5x11 piece of paper, it should be 3-4 pages._
 *
 */
#endif  // SRC_MAINPAGE_H_
