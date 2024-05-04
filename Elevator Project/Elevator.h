#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <vector>
using namespace std;
#include "Rider.h"
#include "Floor.h"
#include "Panel.h"
class Elevator
{
	static const int IDLE = 0;
	static const int UP = 1;
	static const int DOWN = -1;
	static const int COURTESY_WAIT_TIME = 3;
	// elevator metrics
	int location; // inches above ground level
	int direction; // equal to IDLE, UP, DOWN
	int atFloorIndex; // if -1 the door is closed, if not the door is open
	int timer;
	vector<Rider> riders;

public:

	Elevator(unsigned int, int, int);
	operator int() const { return location; }
	Panel panel;
	const int speed; 
	const unsigned int CAPACITY;
	

	void resetTimer() { timer = COURTESY_WAIT_TIME; }
	void tickTimer() { timer--; }
	bool timedOut() const { return timer == 0; }

	bool isOpen() const { return atFloorIndex >= 0; }
	void openDoorTo(int);
	void board(const Rider&);

	bool hasRiderForFloor() const;
	void removeRider();

	bool isIdle() const { return direction == IDLE; }
	bool move();
	bool closeDoor();
	bool isFull() const { return CAPACITY == riders.size(); }
	bool goingUp() const { return direction == UP; }
	bool goingDown() const { return direction == DOWN; }
	int getFloorIndex() const { return atFloorIndex; }
	int getNumberOfRiders() const { return riders.size(); }
	void goIdle();
	void setDirectionUp();
	void setDirectionDown();
	
	friend ostream& operator<<(ostream&, const Elevator&);
};
#endif