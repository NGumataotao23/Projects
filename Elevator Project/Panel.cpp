#include "Panel.h"
#include "Building.h"
using namespace std;

int Panel::Button::count = 0;


void Panel::addButton(string addedButton) {

	Panel::Button::count++;


	Panel::Button newButton;
	newButton.label = addedButton;
	newButton.lit = false;
	newButton.sequence = Panel::Button::count;
	buttons.push_back(newButton);


}
void Panel::press(string pressed) {

	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].label == pressed && !buttons[i].lit) {
			buttons[i].lit = true;

		}
	}

}
void Panel::clear(string cleared) {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].label == cleared) {
			buttons[i].lit = false;
			
		}
		
	}
	
}
string Panel::getFirstLit() const {
	string firstLit = "";
	for (auto& Button : buttons) {
		if (Button.lit) {
			if (firstLit.empty() && buttons[1].sequence > buttons[0].sequence) {
				firstLit = Button.label;
				return firstLit;
			}
		}
	}
	return "";

}
bool Panel::isLit(string lit) const {

	for (unsigned int i = 0; i < buttons.size(); i++) {
		if ((buttons[i].label == lit) && (buttons[i].lit == true)) {

			return true;
		}

	}
	return false;
}
bool Panel::areAnyLit() const {
	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].lit == true) {

			return true;
		}
	}
	return false;

}
ostream& operator<<(ostream& out, const Panel& panel) {

	for (const auto& button : panel.buttons) {
		if (button.lit)
			out << "[" << button.label << "]";
	}
	return out;

}
