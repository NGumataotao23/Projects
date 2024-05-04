#include "Floor.h"
#include "Rider.h"
#include "Panel.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <climits>

const char* const Floor::UP = "Up";
const char* const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN; // defined in climits
int Floor::BOTTOM = INT_MAX; // also in climits
Floor::Floor(const int elevation, const char* const name, const char* const label) : elevation(elevation), name(name), label(label)
{
	panel.addButton(UP);
	panel.addButton(DOWN);

	if (TOP < elevation) TOP = elevation;
	if (elevation < BOTTOM) BOTTOM = elevation;

}
ostream& operator<<(ostream& out, const Floor& floor)
{
	
	out << floor.label << " " << floor.name << " at " << floor.elevation << " " << " UP/DOWN " << floor.getNumberOfUpRiders() << "/" << floor.getNumberOfDownRiders() << " Button:" << floor.panel;
	
	return out;
}
void Floor::addRider(const Rider& r) {
	
	if (r.from > r.to) {
		panel.press(DOWN);
		downRiders.push(r);
	}
	else if (r.to > r.from) {
		panel.press(UP);
		upRiders.push(r);
	}

}
Rider Floor::removeUpRider() {


	if (upRiders.empty()) {
		throw "Up-Rider Queue is empty";
	}

	Rider copyURider = upRiders.front();

	upRiders.pop();

	return copyURider;

}
Rider Floor::removeDownRider() {


	if (downRiders.empty()) {
		throw "Down-Rider Queue is empty";
	}
	
	Rider copyDRider = downRiders.front();

	downRiders.pop();

	return copyDRider;

}