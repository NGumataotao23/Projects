#include "pch.h"
#include "JukeBox.h"
#include <iostream>
#include <vector>
#include "FinalDlg.h"
#include "afxdialogex.h"
#include "vfw.h"
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

void coin::coin::output(ostream& out) const{

	if (input == 25) {

		out << "Thank You" << endl;
	}
	else {

		out << "Invalid" << endl;
	
	}
}

void songs::prince::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(2);
	
	//Simple caculation to turn a number into minutes and seconds 
	//I had to do this in every output function unfortunately because I couldn't figure out a way
	//to implement it across all functions because all there lengths are different
	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;



	out << "Album- Purple Rain\r\n";
	out << "Artist- Prince\r\n";
	out << "Released- 1984\r\n";
	out << "Length: " << min << ":" << sec << "\r\n";
}
void songs::summer::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(1);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Bad Girls\r\n";
	out << "Artist- Donna Summer\r\n";
	out << "Released- 1979\r\n";
	out << "Length: " << min << ":" << sec << "\r\n";
}
void songs::tyler::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(1);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Faster than the Speed of Light\r\n";
	out << "Artist- Bonnie Tyler\r\n";
	out << "Released- 1983\r\n";
	out << "Length: " << min << ":" << sec << "\r\n";
}
void songs::motor::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(1);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Ace of Spades\r\n";
	out << "Artist- Motorhead\r\n";
	out << "Released-1980\r\n";
	out << "Length: " << min << ":" << sec << "\r\n";
}
void songs::lepard::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(1);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Hysteria\r\n";
	out << "Artist- Def Leppard\r\n";
	out << "Released- 1987\r\n";
	out << "Length: " << min << ":" << sec << "\r\n";
}
void songs::Heads::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(2);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Speaking in Tongues\r\n";
	out << "Artist- Talking Heads\r\n";
	out << "Released- 1983\r\n";
	out << "Length: " << min << ":0" << sec << "\r\n";
}
void songs::Huey::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(2);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Fore!\r\n";
	out << "Artist- Huey Lewis and the News\r\n";
	out << "Released- 1986\r\n";
	out << "Length: " << min << ":0" << sec << "\r\n";
}
void songs::guns::output(ostream& out) const {

	out.setf(ios::fixed); out.precision(2);

	int time;
	int min;
	int sec;

	time = length % 3600;
	min = time / 60;
	time = length % 60;
	sec = time;

	out << "Album- Use your Illusion 1\r\n";
	out << "Artist- Guns N Roses\r\n";
	out << "Released- 1991\r\n";
	out << "Length: " << min << ":" << sec << "\r\n";
}


//output operators for the coin function and all the song functions
coin::coin& coin::coin::operator<<(ostream& out) {

	output(out);
	return *this;
}
songs::song& songs::song::operator<<(ostream& out) {

	output(out);
	return *this;
}