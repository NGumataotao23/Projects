#pragma once
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>


using namespace std;

class Panel
{
    struct Button
    {
        string label;
        bool lit;
        int sequence;
        static int count;
    };

    vector<Button> buttons;

public:

    void addButton(string);
    void press(string);
    void clear(string);
    string getFirstLit() const;
    bool isLit(string) const;
    bool areAnyLit() const;
    friend ostream& operator<<(ostream&, const Panel&);
};
