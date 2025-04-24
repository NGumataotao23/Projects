#include "pch.h"
#pragma once
#include <vector>
#include <string>


using namespace std;

//I feel like the namespaces were unncessary but I didn't want any unforeseen problems so this was just for safety
namespace coin {
	class coin
	{
	protected:
		const double input;

	public:
		coin(const vector<string>& quarter) : input(quarter.size() > 1 ? atof(quarter[1].c_str()) : 0) {}
		void output(ostream&) const;
		virtual coin& operator<<(ostream&);

	};
}

namespace songs{

	struct song {
		virtual void output(ostream&) const = 0;
		virtual ~song(){}
		virtual song& operator<<(ostream&);
	};

	//every song is marked with a length indictaing the length of the song in seconds

	class prince: public song {
	
		const int length = 520;
	
	public:
		void output(ostream&) const;

	};
	class summer : public song {
		const int length = 315;
	public:
		void output(ostream&) const;
	};
	class tyler : public song {
		const int length = 267;
	public:
		void output(ostream&) const;
	};
	class motor : public song {
		const int length = 168;
	public:
		void output(ostream&) const;
	};
	class lepard : public song {
		const int length = 267;
	public:
		void output(ostream&) const;
	};
	class Heads : public song {
		const int length = 241;
	public:
		void output(ostream&) const;
	};
	class Huey : public song {
		const int length = 245;
	public:
		void output(ostream&) const;
	};
	class guns : public song {
		const int length = 536;
	public:
		void output(ostream&) const;
	};

}