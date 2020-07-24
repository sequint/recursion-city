// Specification file for the DynIntStack class.

#ifndef CARQUEUE_H
#define CARQUEUE_H
#include <string>
using namespace std;

class CarQueue
{
private:
	struct QueueNode
	{
		string carName;       // Name of the party in line.
		int numChildren;      // Number of children in a car.
		QueueNode* next;      // Pointer to the next node.
		QueueNode* previous;  // Pointer to the previous node.
	};

	QueueNode* front;  // Points to the front of the queue.
	QueueNode* rear;   // Points to the rear of the queue.
	int carsInQueue;   // Number of items in the queue.

	// Private Member Functions
	int countCars(QueueNode*) const;
	int largestNum(QueueNode*);
	int nameMatch(QueueNode*, string&, int);

public:
	// Constructor
	CarQueue();

	// Destructor
	~CarQueue();

	// Queue Operations
	void enqueue(string, int);
	void dequeue(string&, int&);
	int moveLargestCar();
	int moveNameMatched(string&);
	void printQueue();
	bool isEmpty() const;
	void clear();

	int numCars() const		  // Returns number of cars in the queue using countCars.
	{
		return countCars(front);
	}
	string getFrontName() const       // Returns name of the front car in the queue.
	{
		return front->carName;
	}
};
#endif
