// Steven Quintana
// Ch. 20 Assignment - Recursion and Queue Assigment
// July 23, 2020

// Main function file for Recursion and Queue Project.

#include <iostream>
#include <string>
#include "CarQueue.h"
#include "functions.h"
using namespace std;

int main()
{
	CarQueue car;  // Car object.

	int choice;	   // Variable that holds the menu choice.

 // While the choice is not EXIT_PROGRAM, continue printing the menu.
	do
	{
		// Print the menu, get the user's choice.
		menu(choice);

		// Perform the user's choice.
		switch (choice)
		{
		case APPEND_CAR:
			enqueueCar(car);
			break;
		case PLACE_ORDER:
			dequeueCar(car);
			break;
		case COUNT_CARS:
			displayNumCars(car);
			break;
		case MOVE_KIDS_TO_FRONT:
			moveKidsToFront(car);
			break;
		case MOVE_FRIEND_TO_FRONT:
			moveFriendToFront(car);
			break;
		case DISPLAY_QUEUE:
			displayQueue(car);
			break;
		case EXIT_PROGRAM:
			goodbyeMessage();
			break;
		default:
			menuChoiceError(choice);
			break;
		}

	} while (choice != EXIT_PROGRAM);

	return 0;
}