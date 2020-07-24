// Implementation file for the Inventory class.

#include <iostream>
#include <string>
#include "functions.h"
#include "CarQueue.h"
using namespace std;


//*******************************************************
//					 INPUT FUNCTIONS					*
//*******************************************************


//*************************************************************
// menu Function											  *
//															  *
// The constructor initializes all variables to null or '0'.  *
//*************************************************************

void menu(int& choice)
{
	// Display the menu and get the user's choice.
	cout << "\n\nMAIN MENU\n\n";
	cout << APPEND_CAR << ") Append (add a car to the end of the line)\n";
	cout << PLACE_ORDER << ") Place Order (add an order for the front car in line)\n";
	cout << COUNT_CARS << ") Count Line  (display the total number of cars in the queue)\n";
	cout << MOVE_KIDS_TO_FRONT << ") Move Kids to Front (Move car with most kids to the front of the queue)\n";
	cout << MOVE_FRIEND_TO_FRONT << ") Move friend to Front\n";
	cout << DISPLAY_QUEUE << ") Display Queue\n";
	cout << EXIT_PROGRAM << ") Exit the Program\n\n";
	cout << "Enter a number from the menu options: ";
	cin >> choice;

	// Check if the input is an integer.
	isInteger(choice);
}

//*******************************************************************************************
// enqueueCar Function																		*
//																							*
// This function get the user's input for a car name and the number of children in that		*
// car, checks the variable boundries, the enqueue's the checked variables.					*
//*******************************************************************************************

void enqueueCar(CarQueue& queue)
{
	string nameChoice;   // Holds the user input for name of the party in the car.
	int numChildChoice;  // Holds the user input for number of children in a car.

	// Get the car name from the user.
	cin.clear();
	cin.ignore(10, '\n');
	cout << "\nEnter a name for the car here (less than 20 characters): ";
	getline(cin, nameChoice);

	// While nameChoice is not within the boundaries, print an error message and get a new nameChoice input.
	while (nameChoice == "" || nameChoice.length() >= 20)
	{
		// If nameChoice is empty print empty error.
		if (nameChoice == "")
		{
			cout << "\nError, cannot leave the name value blank.\n";
			cout << "Please re-enter a name for the car: ";
			getline(cin, nameChoice);
		}
		// Otherwise, print length error.
		else
		{
			cout << "\nError, name must be shorter than 20 characters.\n";
			cout << "Please re-enter a name for the car: ";
			getline(cin, nameChoice);
		}
	}

	// Get the number of children in the car from the user.
	cout << "\nEnter the number of children in the car: ";
	cin >> numChildChoice;

	isInteger(numChildChoice);

	// While numChildChoice is less than 0, print an error message and get a new number.
	while (numChildChoice < 0)
	{
		cout << "\nError, number of children must be 0 or greater.\n";
		cout << "Please re-enter the number of children in the car: ";
		cin >> numChildChoice;
	}

	// Enqueue the two variables to the stack.
	queue.enqueue(nameChoice, numChildChoice);

	// Print a success message.
	cout << "\nCar '" << nameChoice << "' with '" << numChildChoice;
	if (numChildChoice == 1)
	{
		cout << "' child";
	}
	else
	{
		cout << "' children";
	}
	cout << ", has been successfully placed in the queue.\n";
}



//*******************************************************
//					 OUTPUT FUNCTIONS					*
//*******************************************************


//*******************************************************************************************
// dequeueCar Function																		*
//																							*
// This functions checks if the stack is empty, if it is it print an empty message,			*
// If the stack is not empty it dequeues the front node and prints an 'order' message.		*
//*******************************************************************************************

void dequeueCar(CarQueue& queue)
{
	string name = "";  // Variable that will hold a temporary copy of the dequeued car name.
	int num = 0;		// Vraiable that will hold a temporary copy of the number of children in the car.

	// If the stack is empty, print an error message and exit the function.
	if (queue.isEmpty())
	{
		cout << "\nError, could not dequeue because there are no cars in the queue.\n";
	}
	// Otherwise, dequeue the first car in the queue.
	else
	{
		queue.dequeue(name, num);

		// Print the confirmation message.
		cout << "\nThe '" << name << "' car can now order.\n";
	}
}

//*******************************************************************************************
// displayNumCars Function																	*
//																							*
// This function display's the number of cars in the queue.								    *
//*******************************************************************************************

void displayNumCars(CarQueue& queue)
{
	int totalInQueue = queue.numCars();  // Calls numCars and stores the total counted in the queue into total.

	// If there is one car, print a different message to make gramatical sense.
	if (totalInQueue == 1)
	{
		cout << "\nThere is " << totalInQueue << " car in line.\n";
	}
	// Otherwise, print the regular message.
	else
	{
		cout << "\nThere are " << totalInQueue << " cars in line.\n";
	}
}

//*******************************************************************************************
// moveKidsToFront Function																	*
//																							*
// This function moves the car with the largest number of children to the front of the		*
// queue by calling the largestCar function, and displays the information of the car that	*
// was moved.																				*
//*******************************************************************************************

void moveKidsToFront(CarQueue& queue)
{
	// If the stack is empty, print an error message and leave the function.
	if (queue.isEmpty())
	{
		cout << "\nError, there are no cars in line. Please enter names into the queue to search for one.\n";
	}
	// Otherwise, move the car with the largest number of children to the front.
	else
	{
		// If the queue has children in it, print the confirmation message.
		if (queue.moveLargestCar() > 0)
		{
			// Print a message that the front car with the largest children and that they have been moved to the front.
			cout << "\nCar '" << queue.getFrontName() << "' has the most children and is now in the front of the line.\n";
		}
	}
}

//*******************************************************************************************
// moveFriendToFront Function																*
//																							*
// This function get's a name from the user, then checks the queue for a matching name.		*
//*******************************************************************************************

void moveFriendToFront(CarQueue& queue)
{
	string friendName;  // To hold the name to be searched for.

	// If the stack is empty, print an error message and leave the function.
	if (queue.isEmpty())
	{
		cout << "\nError, there are no cars in line. Please enter more parties into the queue to complete a search.\n";
	}
	// Otherwise, get the name to be searched for and perform the search.
	else
	{
		cin.clear();
		cin.ignore(INT8_MAX, '\n');

		// Get a name from the user to find in the queue.
		cout << "\nPlease enter a name to be found in line: ";
		getline(cin, friendName);

		// Search for the friend name, and if the name is in the line (not -1) print the confirmation message.
		if (queue.moveNameMatched(friendName) > -1)
		{
			cout << "\nMatch in line found! Car '" << queue.getFrontName() << "' has been moved to the front of the line.\n";
		}
	}
}

//*******************************************************************************************
// displayQueue Function																	*
//																							*
// This function calls printQueue in order to display the queue.							*
//*******************************************************************************************

void displayQueue(CarQueue& queue)
{
	queue.printQueue();
}

//*******************************************************************************************
// goodbyeMessage Function																	*
//																							*
// This function prints a goodbye message used at the exit of the program. 					*
//*******************************************************************************************

void goodbyeMessage()
{
	cout << "\nHope you had a great shift. Goodbye!\n";
}

//*******************************************************************************************
// menuChoiceError Function																	*
//																							*
// This function prints an error message to inform user that their selection is not valid.	*
//*******************************************************************************************

void menuChoiceError(int& choice)
{
	cout << "\nError, '" << choice << "' is not a menu option.\n";
}



//*******************************************************
//				INPUT VALIDATION FUNCTIONS				*
//*******************************************************


//*******************************************************************************************
// isInteger Function																		*
//																							*
// This functions takes checks if the input is an integer, and prompts for another input	*
// if it is not.																			*
//*******************************************************************************************

void isInteger(int& input)
{
	// While input is not an integer, prompt the user for another choice.
	while (cin.fail())
	{
		cout << "\nError, input must be a number.\n";
		cin.clear();
		cin.ignore(INT8_MAX, '\n');
		cout << "Please enter a number: ";
		cin >> input;
	}
}
