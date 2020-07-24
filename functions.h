// Steven Quintana
// Ch. 20 Assignment - Recursion and Queue Assigment
// July 23, 2020

// Specification file for the program functions.

#pragma once

#include <string>
#include "CarQueue.h"
using namespace std;

// Global Variables - constant menu choices
const int APPEND_CAR = 1,
		  PLACE_ORDER = 2,
		  COUNT_CARS = 3,
		  MOVE_KIDS_TO_FRONT = 4,
		  MOVE_FRIEND_TO_FRONT = 5,
		  DISPLAY_QUEUE = 6,
		  EXIT_PROGRAM = 7;

// Input Functions
void menu(int&);
void enqueueCar(CarQueue&);

// Output Functions
void dequeueCar(CarQueue&);
void displayNumCars(CarQueue&);
void moveKidsToFront(CarQueue&);
void moveFriendToFront(CarQueue&);
void displayQueue(CarQueue&);
void goodbyeMessage();
void menuChoiceError(int&);

// Input Validation Functions
void isInteger(int&);