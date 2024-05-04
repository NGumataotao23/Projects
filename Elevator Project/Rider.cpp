#include "Rider.h"
#include "Building.h"

Rider::Rider(int From, int To) : from(From), to(To),goingDown(Building::floors[to] < Building::floors[from]), goingUp(Building::floors[to] > Building::floors[from]){

	
}
Rider& Rider::operator=(const Rider& copy) {

	
	if (this != &copy) {
		const_cast<int&>(from) = copy.from;
		const_cast<int&>(to) = copy.to;
		const_cast<bool&>(goingUp) = copy.goingUp;
		const_cast<bool&>(goingDown) = copy.goingDown;
	}
	return *this;
}
