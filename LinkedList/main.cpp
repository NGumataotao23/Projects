#include <iostream>
#include <cstring>
using namespace std;

struct node {
    string event;
    node* next;
};

void addevent(node** head);
void addeventatfront(node** head, string newevent);
void addeventatback(node** head, string newEvent);
void addEventAfterAnother(node* previous, string newEvent);
void removeEvent(node** n);
void displaycalender(node* n);
int displaymenu();

int main() {
    node* head = nullptr;

    cout << "Welcome to the L.L Calendar!" << endl;
    cout << "----------------------------" << endl;
    int choice;
    choice = displaymenu();
    while (choice != 4) {
        switch (choice) {
            case 1:
                addevent(&head);
                break;
            case 2:
                removeEvent(&head);
                break;
            case 3:
                displaycalender(head);
                break;
            default:
                if (choice != 4) cout << "Invalid" << endl;
        }
        choice = displaymenu();
    }

    node* current = head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}

int displaymenu() {
    int choice;
    string menu = "1- Add an Event, 2- Remove an Event, 3- Display Calendar, 4- Exit: ";
    cout << menu;
    cin >> choice;
    return choice;
}

void addevent(node** head) {
    string newevent;
    cout << "Enter the Time and Event you would like to add:" << endl;
    cin.ignore();
    getline(cin, newevent);

    int choice;
    string menu = "1- Add event at the start of Calendar, 2- Add event at the end of Calendar, 3- Add event after another event, 4- Back: ";
    cout << menu;
    cin >> choice;

    if (choice != 4) {
        switch (choice) {
            case 1:
                addeventatfront(head, newevent);
                break;
            case 2:
                addeventatback(head, newevent);
                break;
            case 3:
                addEventAfterAnother(*head, newevent);
                break;
            default:
                if (choice != 4) cout << "Invalid" << endl;
        }
    }
}

void addeventatfront(node** head, string newevent) {
    node* newNode = new node();
    newNode->event = newevent;
    newNode->next = *head;
    *head = newNode;
}

void addeventatback(node** head, string newEvent) {
    node* newNode = new node();
    newNode->event = newEvent;
    newNode->next = nullptr;

    if (*head == nullptr) {
        *head = newNode;
        return;
    }

    node* last = *head;
    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = newNode;
}

void addEventAfterAnother(node* previous, string newEvent) {
    if (previous == nullptr) {
        cout << "Previous cannot be NULL";
        return;
    }

    node* newNode = new node();
    newNode->event = newEvent;

    newNode->next = previous->next;
    previous->next = newNode;
}

void displaycalender(node* n) {
    while (n != nullptr) {
        cout << n->event << endl;
        n = n->next;
    }
}
void removeEvent(node** head) {
    string removed;
    cout << "Select an event to remove:" << endl;
    displaycalender(*head);
    cin.ignore();
    getline(cin, removed);
    node* current = *head;
    node* previous = nullptr;
    while (current != nullptr && current->event != removed) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous != nullptr) {
            previous->next = current->next;
        } else {
            *head = current->next;
        }
        delete current;
        cout << "Event removed: " << removed << endl;
    } else {
        cout << "Event not found: " << removed << endl;
    }
}


