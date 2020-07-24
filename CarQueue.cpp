// Implementation file for the DynIntStack class.

#include <iostream>
#include <string>
#include "CarQueue.h"
using namespace std;


//****************************************************************
// Constructor													 *
//																 *
// The constructor creates an empty queue.						 *
//****************************************************************

CarQueue::CarQueue()
{
	front = nullptr;
	rear = nullptr;
	carsInQueue = 0;
}

//****************************************************************
// Destructor													 *
//																 *
// The destruct clears all elements in the queue.				 *
//****************************************************************

CarQueue::~CarQueue()
{
	clear();
}

//****************************************************************
// enqueue Function												 *
//																 *
// This function inserts a node value at the rear of the queue.  *
//****************************************************************

void CarQueue::enqueue(string name, int num)
{
	// If name is empty or is greater than or equal to 20 characters in length, print an error message and exit the program.
	if (name == "" || name.length() >= 20)
	{
		cout << "\nInvalid car name.\n";
		exit(EXIT_FAILURE);
	}

	// If num is less than '0', print an error message and exit the program.
	if (num < 0)
	{
		cout << "\nInvalid number of children.\n";
		exit(EXIT_FAILURE);
	}

	QueueNode* newNode = nullptr;  // Points to a new node.

	// Create a new node and store values passed into it's member variables.
	newNode = new QueueNode;
	newNode->carName = name;
	newNode->numChildren = num;
	newNode->next = nullptr;
	newNode->previous = nullptr;

	// If the queue is empty set the front and rear pointers to newNode.
	if (isEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	// Otherwise, set the current rear next pointer to newNode, and make newNode the new rear pointer.
	else
	{
		rear->next = newNode;
		rear->previous = rear;
		rear = newNode;
	}

	// Increment numCars.
	carsInQueue++;
}

//****************************************************************
// dequeue Function												 *
//																 *
// This function stores the member variables of the front node,  *
// then deletes the front node from the queue.					 *
//****************************************************************

void CarQueue::dequeue(string& name, int& num)
{
	QueueNode* temp = nullptr;  // Temporary pointer to store, then delete the front node.

	// If the queue is empty, print a message to the user that the queue is empty.
	if (isEmpty())
	{
		cout << "\nThe queue is empty.\n";
	}
	// Otherwise, save the values in the front node to the passed variables and delete the fron node.
	else
	{
		// Save the front node variables.
		name = front->carName;
		num = front->numChildren;

		// Remove the front node from the queue.
		temp = front;

		// Make the next node the new front.
		front = front->next;

		// Delete the old front node.
		delete temp;

		// Decrement the counter to reflect the new size of the queue.
		carsInQueue--;
	}
}

//****************************************************************
// moveLargestCar Function                                       *
//                                                               *
// This function uses the largestNum function to find the car    *
// with the largest number of children, then breaks that car     *
// from the queue and moves it to the front.                     *
//****************************************************************

int CarQueue::moveLargestCar()
{
	if (isEmpty())
	{
		return 0;
	}
	else
	{
		QueueNode* nodePtr = front;           // To traverse the queue.
		QueueNode* nextNode = nodePtr->next;  // To hold a pointer to the next node.
		int largestCar = largestNum(front);   // To hold the largest numChildren variable found.

		// If no cars have children in them, inform the user.
		if (largestCar == 0)
		{
			cout << "\nThere are no cars with children in line.\n";
		}
		// Otherwise, traverse the queue and move the largest car to the front.
		else
		{
			// While the pointer is not null, traverse the queue.
			while (nodePtr)
			{
				// If the fron is the largest node, do nothing.
				if (nodePtr->numChildren == largestCar)
				{
					break;
				}
				// Else, if the next node's numChildren variable equals largestCar, break next from the queue, and put it to the front.
				else if (nextNode->numChildren == largestCar)
				{
					nodePtr->next = nextNode->next;
					nextNode->next = front;
					front = nextNode;
					break;
				}

				// Increase each pointer to the next node.
				nodePtr = nextNode;
				nextNode = nextNode->next;
			}
		}
		return largestCar;
	}
}

//****************************************************************
// moveNameMatched Function										 *
//																 *
// This function calls nameMath to find a match. If a match is   *
// found, the node with the match is broken from the queue and   *
// placed in the front.											 *
//****************************************************************

int CarQueue::moveNameMatched(string& name)
{
	QueueNode* nodePtr = front;           // To traverse the queue.
	QueueNode* nextNode = nodePtr->next;  // To hold a pointer to the next node.
	int tempPosition = 0;
	int matchPosition = nameMatch(front, name, tempPosition);
	int counter = 0;

	// If nameMatch return -1 position let the user know the name was not found.
	if (matchPosition == -1)
	{
		cout << "\nThe car '" << name << "' was not found in line.\n";
		return -1;
	}
	// Else, if the nameMatch did not find the name in the front position, find the name and move it to the front.
	else if (matchPosition > 0)
	{
		// While the counter is not the matchPosition, traverse the queue.
		while (counter <= matchPosition)
		{
			// If the counter is equal to the matchPosition - 1, break the next pointer from the queue and place it in the front.
			if (counter == matchPosition - 1)
			{
				nodePtr->next = nextNode->next;
				nextNode->next = front;
				front = nextNode;
				break;
			}
			// Otherwise, increment the counter and increase each pointer to the next node.
			else
			{
				counter++;
				nodePtr = nextNode;
				nextNode = nextNode->next;
			}
		}

		return matchPosition;
	}
}

//****************************************************************
// printQueue Function											 *
//																 *
// This function loops through the queue and prints each node.	 *
//****************************************************************

void CarQueue::printQueue()
{
	QueueNode* nodePtr = front;  // To traverse the queue.
	int counter = 1;			 // To store a node's position in the queue.

	// If the queue is empty tell the user.
	if (isEmpty())
	{
		cout << "\nThere are no cars in the queue.\n";
	}
	// Otherwise, print the queue.
	else
	{
		// Title of display.
		cout << "\nCar Queue\n\n";

		// While the pointer is not null, display the information in the node.
		while (nodePtr)
		{
			cout << "Car Name: " << nodePtr->carName << "\n";
			cout << "Number of children: " << nodePtr->numChildren << "\n";
			cout << "Position in line: " << counter << "\n\n";

			// Pointer to the next node and increment the counter.
			nodePtr = nodePtr->next;
			counter++;
		}
	}
}

//****************************************************************
// isEmpty Function												 *
//																 *
// This funtion test the size of the queue to return true if	 *
// the queue has more than '0' nodes, and false otherwise.		 *
//****************************************************************

bool CarQueue::isEmpty() const
{
	bool status;  // Returns the status of the queue being empty or not.

	// If there are items within the queue returns the status as false.
	if (carsInQueue > 0)
	{
		return false;
	}
	// Otherwise, return a true status to indicate an empty queue.
	else
	{
		return true;
	}
}

//****************************************************************
// clear Function												 *
//																 *
// This function loops through the entire queue and clears		 *
// every node within it.										 *
//****************************************************************

void CarQueue::clear()
{
	string dumName;  // Dummy name value to pass into dequeue function.
	int dumNum;		 // Dummy number value to pass into dequeue function.

	// While the queue is not empty, dequeue the front node.
	while (!isEmpty())
	{
		dequeue(dumName, dumNum);
	}
}



//****************************************************************
//                PRIVATE MEMEBER FUNCTIONS						 *
//****************************************************************

//****************************************************************
// countCars Function											 *
//																 *
// This function traverses the queue and creates a running		 *
// total of cars in the queue using recursion.					 *
//****************************************************************

int CarQueue::countCars(QueueNode* nodePtr) const
{
	// If the nodePtr is not pointing to a null value, return the function to itself with the next node
	// as the argument + 1.
	if (nodePtr)
	{
		return 1 + countCars(nodePtr->next);
	}
	// Otherwise return 0.
	else
	{
		return 0;
	}
}

//****************************************************************
// largestNum Function											 *
//																 *
// This function uses recursion to traverse while storing a      *
// 'left' and 'right' value at each iteration to compare on the  *
// reverse traverse, then it returns the highest value.          *
//****************************************************************

int CarQueue::largestNum(QueueNode* nodePtr)
{
	int currentNum = nodePtr->numChildren;  // To hold the numChildren value of the current (left) node for each recursive iteration.
	int nextNum;							// To hold the numChildren value of the next (right) node using recursive iterations.

	// If the pointer is pointing to the last node, return current nodes numChildren value.
	if (nodePtr->next == nullptr)
	{
		return currentNum;
	}
	// Otherwise, call largestCar recursively and store it's value into nextNum.
	else
	{
		nextNum = largestNum(nodePtr->next);
	}

	// If the current node numChildren variable is less than the node to the left's numChildren variable return currentNum as largest.
	if (currentNum > nextNum)
	{
		return currentNum;
	}
	// Otherwise return the 'left' numChildren variable as the largest.
	else
	{
		return nextNum;
	}
}

//****************************************************************
// nameMatch Function											 *
//																 *
// This function uses recursion to traverse the queue and check  *
// for a name match, then returns it's position in the queue.	 *
//****************************************************************

int CarQueue::nameMatch(QueueNode* nodePtr, string& name, int position)
{
	// If the front node's name match the name passed, return the current position.
	if (nodePtr->carName == name && nodePtr == front)
	{
		return position;
	}
	// Else, if the pointer is at the end of the queue, and the name is not a match return a -1 value.
	else if (nodePtr->next == nullptr && nodePtr->carName != name)
	{
		return -1;
	}
	// Else, if the pointer's name is a match, return the current position.
	else if (nodePtr->carName == name)
	{
		return position;
	}
	// Otherwise, use recursion to traverse.
	else
	{
		return nameMatch(nodePtr->next, name, position + 1);
	}
}
