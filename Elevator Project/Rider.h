#pragma once
struct Rider
{
	const int from, to;
	Rider(int, int);
	Rider& operator=(const Rider&);
public: 

	const bool goingUp;
	const bool goingDown;

};

