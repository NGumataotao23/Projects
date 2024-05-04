#include "Elevator.h"
#include "Panel.h"
#include "Building.h"
#include <iostream>
#include <vector>
using namespace std;
#include <cstdlib>
Elevator::Elevator(unsigned int capacity, int Speed, int start) : CAPACITY(capacity), speed(Speed),timer(3),atFloorIndex(-1),direction(IDLE)
{
	location = Building::floors[start].elevation;
		
	
	for (int i = 0; i < 5; i++) {

		panel.addButton(Building::floors[i].label);
	}

}
ostream& operator<<(ostream& out, const Elevator& e)
{
	cout << "Elevator at "; cout.width(5); cout << e.location; 
	cout.width(11);
	switch(e.direction){ 
		case Elevator::UP: cout << "going UP"; 
			break; 
		case Elevator::DOWN: cout << "going DOWN"; 
			break; 
		case Elevator::IDLE: cout << "IDLE"; 
			break; 
	} 
	cout.width(3); 
	cout << e.getNumberOfRiders() << " riders"; 
	cout.width(16); 
	if(e.atFloorIndex != -1) cout << " door is OPEN|" << e.timer;
	else{ 
		
		cout.width(15); cout << " "; 		
	} 
	
	cout << " " << e.panel; 
	return out;
}
void Elevator::openDoorTo(int f) {

	
	panel.clear(Building::floors->label);

	atFloorIndex = f;

	resetTimer();
}
void Elevator::board(const Rider& r) {

	riders.push_back(r);
	
	string going = Building::floors[r.to].label;

	panel.press(going);

	if (r.goingUp) {
		direction = UP;
	}
	else if (r.goingDown) {
		direction = DOWN;
	}
	else {
		cout << "Direction Error";
	}
	resetTimer();
}
bool Elevator::hasRiderForFloor() const {

	if (atFloorIndex != -1) {
		for (int i = 0; i < riders.size(); i++) {

			if (riders[i].to == atFloorIndex) {

				return true;
			}
		}
		return false;
	}
	else if(atFloorIndex == -1)  {
		return false;
	}
}
void Elevator::removeRider() {

	for (auto i = riders.begin(); i != riders.end();) {
		if (i->to == atFloorIndex) {
			
			i = riders.erase(i);
			panel.clear(Building::floors[atFloorIndex].label);
			resetTimer();
			return;
		}
		else {
			++i;
		}
	}
}
bool Elevator::closeDoor() {
	if (isOpen()) {
		if ( goingUp() && (&Floor::hasUpRider == 0) ) {

			panel.clear(Building::floors[atFloorIndex].UP);

		}
		else if ( goingDown() && (&Floor::hasDownRider == 0)) {

			panel.clear(Building::floors[atFloorIndex].DOWN);
			
			
		}
		atFloorIndex = -1;
		return true;

	}
	else {
		return false;
	}
}
bool Elevator::move() {
	
	int loc = location;

	if (goingUp()) {
		
		for (int i = 0; i < Building::FLOORS; i++ ) {
			if (Building::floors[i].elevation <= loc) {
				continue;
			}
			if (Building::floors[i].elevation == loc + 1) {
				continue;
			}
			if (Building::floors[i].panel.isLit(Floor::UP)) {
				location = Building::floors[i].elevation;
				openDoorTo(i);
				return true;
			}
		}
		if (loc < Building::floors[Building::FLOORS - 1].elevation) {
			location = Building::floors[Building::FLOORS - 1].elevation;
			return false;
		}
		else{

		}
		
		return false;
		
		
	}
	else if (goingDown()) {

		for (int i = 0 ; i < Building::FLOORS; i++) {
			if (Building::floors[i].elevation >= loc) {
				continue;
			}
			if (Building::floors[i].elevation == loc -1) {
				continue;
			}
			if (Building::floors[i].panel.isLit(Floor::DOWN)) {
				location = Building::floors[i].elevation;
				openDoorTo(i);
				return true;
			}
		}
		if (loc > Building::floors[0].elevation) {
			location = Building::floors[0].elevation;
			return true;
		}
		return false;

	}
	else if (isIdle()) {
		return false;
	}
	return false;
}
void Elevator::goIdle() {
	
	direction = IDLE;

}
void Elevator::setDirectionUp() {

	direction = UP;
}
void Elevator::setDirectionDown() {
	
	direction = DOWN;
}