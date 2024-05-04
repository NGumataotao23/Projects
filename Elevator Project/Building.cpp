#include "Building.h"
#include "Floor.h"
#include "Elevator.h"
#include <iostream>
using namespace std;
#include <cstdlib>
#include <cmath>
Floor Building::floors[] =
{
Floor(0, "Ground Floor", "G"),
Floor(100, "Second Floor", "2"),
Floor(200, "Third Floor", "3"),
Floor(305, "Fourth Floor", "4"),
Floor(400, "Fifth Floor", "5"),

};
const int Building::FLOORS = sizeof(floors) / sizeof(Floor);
Elevator Building::elevators[] =
{
Elevator(12, 5, 0),
Elevator(12, 5, 1),
Elevator(12, 5, 2),

};
const int Building::ELEVATORS = sizeof(elevators) / sizeof(Elevator);
// used by Building::placeNewRiders
void Building::getDifferentInts(int& a, int& b)
{
	do
	{
		a = rand() % FLOORS; // range is 0 to (FLOORS-1)
		b = rand() % FLOORS; // range is 0 to (FLOORS-1)
	} while (a == b); // try again if they are the same
}
// used by Building::placeNewRiders
int Building::getPoisson(double avg)
{
	int arrivals = 0;
	double probOfnArrivals = exp(-avg); // requires cmath
	for (double randomValue = (rand() % 1000) / 1000.0; // requires cstdlib
		(randomValue -= probOfnArrivals) > 0.0;
		probOfnArrivals *= avg / ++arrivals);
	return arrivals;
}
// given an arrival rate, randomly select #of riders to add...
// ...and add them to randomly selected floors with random destinations
void Building::placeNewRiders(double arrivalsPerSecond)
{
	int n = getPoisson(arrivalsPerSecond);
	for (int i = 0; i < n; i++)
	{
		int from, to;
		getDifferentInts(from, to);
		Rider rider(from, to);
		floors[from].addRider(rider);
	}
}
// STEP 1 of 9, "Open their door if there is a rider to disembark"
bool Building::openDoorToDisembarkRider(int e)
{
	if (!elevators[e].isOpen()) // if the door is closed...
		for (int f = 0; f < FLOORS; f++) // check each floor to see if its elevation matches
			if (floors[f] == elevators[e] &&
				elevators[e].panel.isLit(floors[f].label)) // ...and the elevator's panel has that floor lit
			{
			elevators[e].openDoorTo(f); // then open the door to that floor
			return true; // ...and report that an action was taken
			}
	return false; // if I get this far, no action was taken in this function
}
// the "action function" to perform one action per elevator per time step
void Building::action(double arrivalsPerSecond)
{
	placeNewRiders(arrivalsPerSecond);
	// one action per elevator
	for (int e = 0; e < ELEVATORS; e++)
	{
		if (openDoorToDisembarkRider(e)) continue;
		if (disembarkRider(e)) continue;
		if (boardRider(e)) continue;
		if (waitingForMoreRiders(e)) continue;
		if (doneWaitingMove(e)) continue;
		if (moveableMove(e)) continue;
		if (setIdleElevatorInMotion(e)) continue;
		if (sendIdleElevatorToCallingFloor(e)) continue;
		elevators[e].goIdle();
	}

}
bool Building::disembarkRider(int e)
{
	// if open and rider to disembark, do that
	if (elevators[e].isOpen() && elevators[e].hasRiderForFloor())
	{
		elevators[e].removeRider();
		return true;
	}
	return false;
}
bool Building::boardRider(int e) // Assignment 9
{
	// if door is open and not full and rider to load, load
	if (elevators[e].isOpen() && !elevators[e].isFull())
	{
		Floor& floor = floors[elevators[e].getFloorIndex()];
		if (elevators[e].goingUp() && floor.hasUpRider())
		{
			Rider rider = floor.removeUpRider();
			elevators[e].board(rider);
			return true;
		}
		else if (elevators[e].goingDown() && floor.hasDownRider())
		{
			Rider rider = floor.removeDownRider();
			elevators[e].board(rider);
			return true;
		}
	}
	return false;
}

bool Building::waitingForMoreRiders(int e) {
	
	if ( elevators[e].isOpen() && !elevators[e].isIdle() &&  !elevators[e].timedOut() ) {
		
		elevators[e].tickTimer();
		
		return true;
	}
	else {
		return false; 
	}

}

bool Building::doneWaitingMove(int e) {
	
	if ( elevators[e].isOpen() && !elevators[e].isIdle() && elevators[e].timedOut()) {
		
		elevators[e].closeDoor();
		elevators[e].move();
		return true;


	}
	else {
		return false;
	}
	
}
bool Building::moveableMove(int e) {

	if (elevators[e].isOpen() || elevators[e].isIdle()) {
		return false;
	}
	else if(elevators[e].move()) {
		
		return true;
	}
	else if (!elevators[e].move()) {
		
		return false;
	}
}
bool Building::setIdleElevatorInMotion(int e){
	
	if (elevators[e].goingUp() && elevators[e].goingDown()) {
		return false;
	}
	else {
		for (int i = 0; i < Building::FLOORS; i++) {
			if (floors[i].elevation != floors[e].elevation) {
				continue;
			}
			if (floors[i].panel.getFirstLit() == Floor::UP) {
				elevators[e].openDoorTo(floors[i].elevation);
				elevators[e].setDirectionUp();
				return true;
			}
			else if (floors[i].panel.getFirstLit() == Floor::DOWN) {
				elevators[e].openDoorTo(floors[i].elevation);
				elevators[e].setDirectionDown();
				return true;
			}
		}
		return false;
	}
}
bool Building::sendIdleElevatorToCallingFloor(int e) {

	if (elevators[e].goingUp() || elevators[e].goingDown()) {
		return false;
	}
	else {
		for (int i = 0; i < FLOORS; i++) {
			if (!floors[i].panel.isLit(Floor::UP) && !floors[i].panel.isLit(Floor::DOWN)) {
				return false;
			}
			if (floors[i].elevation > elevators[e]) {
				elevators[e].setDirectionUp();
				elevators[e].move();
				return true;
			}
			else if (floors[i].elevation < elevators[e]) {
				elevators[e].setDirectionDown();
				elevators[e].move();
				return true;
			}
		}
		return false;
	}
}