// This program acts as my Final Project for Data Strutures the main structure it uses is Linked Lists
// This program also includes a usage of multithreads, the SDL2 Library, and the mutex class
//Written by: Nathan Gumataotao
//Start Date: 11/21/23~~End Date: 11/26/23

#include <iostream>
#include <string>
#include <mutex>
#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>
#include <thread>
#undef main
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_mixer.lib")

using namespace std;

std::mutex queueMutex;
std::mutex currentlyPlayingMutex;

struct node {
    string event;
    node* next;
};

struct Playlist {
    node* head;
    node* currentlyPlaying;
};

void addSong(Playlist& playlist);
void addSongtoFront(Playlist& playlist, string fullPath);
void addSongtoBack(Playlist& playlist, string fullPath);
void addSongAfterAnother(node* previous, string fullPath);
void removeSong(Playlist& playlist);
void displayQueue(const Playlist& playlist);
void playSoundThread(Playlist& playlist);

int menu();

int main() {
    Playlist playlist;
    playlist.head = nullptr;
    playlist.currentlyPlaying = nullptr;

    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_Init(MIX_INIT_MP3);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 1024);
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return 1;
    }

    cout << "LLpod Nano MP3 player" << endl;
    cout << "---------------------" << endl;

    int choice;
    choice = menu();
    while (choice != 4) {
        switch (choice) {
        case 1:
            addSong(playlist);
            break;
        case 2:
            removeSong(playlist);
            break;
        case 3:
            displayQueue(playlist);
            break;
        default:
            if (choice != 4) cout << "Invalid" << endl;
        }

        choice = menu();
    }


    Mix_CloseAudio();

    node* current = playlist.head;
    while (current != nullptr) {
        node* temp = current;
        current = current->next;
        delete temp;
    }


    SDL_Quit();

    return 0;
}

int menu() {
    int choice;
    string menu = "1- Add a Song to Queue, 2- Remove a Song from queue, 3- Display Queue, 4- Exit: ";
    cout << menu << endl;
    cin >> choice;
    return choice;
}

void addSong(Playlist& playlist) {
    string newsong;
    string folderPath = ".\music";
    cout << "Enter the MP3 file you would like to add: " << endl;
    cin.ignore();
    getline(cin, newsong);
    string fullPath = folderPath + "\\" + newsong;

    ifstream fileCheck(fullPath);
    if (!fileCheck) {
        cerr << "File not found: " << fullPath << endl;
        return;
    }

    int choice;
    string menu = "1- Add at the Start of the Queue, 2- Add at the end of the Queue, 3- Add Song after first in queue 4- Back: ";
    cout << menu;
    cin >> choice;

    if (choice != 4) {
        switch (choice) {
        case 1:
            addSongtoFront(playlist, fullPath);
            break;
        case 2:
            addSongtoBack(playlist, fullPath);
            break;
        case 3:
            addSongAfterAnother(playlist.head, fullPath);
            break;
        default:
            if (choice != 4) cout << "Invalid" << endl;
        }
    }
    std::thread(playSoundThread, ref(playlist)).detach();
}

void addSongtoFront(Playlist& playlist, string fullPath) {
    node* newNode = new node();
    newNode->event = fullPath;
    newNode->next = playlist.head;
    playlist.head = newNode;
}

void addSongtoBack(Playlist& playlist, string fullPath) {
    node* newNode = new node();
    newNode->event = fullPath;
    newNode->next = nullptr;

    if (playlist.head == nullptr) {
        playlist.head = newNode;
        return;
    }

    node* last = playlist.head;
    while (last->next != nullptr) {
        last = last->next;
    }

    last->next = newNode;
}

void addSongAfterAnother(node* previous, string fullPath) {
    if (previous == nullptr) {
        cout << "Previous cannot be NULL";
        return;
    }

    node* newNode = new node();
    newNode->event = fullPath;

    newNode->next = previous->next;
    previous->next = newNode;
}

void displayQueue(const Playlist& playlist) {
    node* n = playlist.head;
    while (n != nullptr) {
        cout << n->event << endl;
        n = n->next;
    }
}

void removeSong(Playlist& playlist) {
    string removed;
    cout << "Select a Song to Remove:" << endl;
    displayQueue(playlist);
    cin.ignore();
    getline(cin, removed);
    node* current = playlist.head;
    node* previous = nullptr;
    while (current != nullptr && current->event != removed) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (previous != nullptr) {
            previous->next = current->next;
        }
        else {
            playlist.head = current->next;
        }
        delete current;
        cout << "Song removed: " << removed << endl;
    }
    else {
        cout << "Song not found: " << removed << endl;
    }
}

void playSoundThread(Playlist& playlist) {
    std::lock_guard<std::mutex> lock(currentlyPlayingMutex);

    if (playlist.currentlyPlaying != nullptr) {
        cout << "Already playing a song." << endl;
        return;
    }

    if (playlist.head == nullptr) {
        cout << "Queue is empty." << endl;
        return;
    }

    node* songNode = playlist.head;
    playlist.head = songNode->next;


    const char* mp3File = songNode->event.c_str();


    Mix_Music* music = Mix_LoadMUS(mp3File);
    if (music == nullptr) {
        cerr << "Failed to load MP3 file! SDL_mixer Error: " << Mix_GetError() << endl;
        return;
    }


    playlist.currentlyPlaying = songNode;

    if (Mix_PlayMusic(music, 0) == -1) {
        cerr << "Failed to play MP3 file! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    SDL_Delay(100);


    while (Mix_PlayingMusic()) {
        SDL_Delay(100);
    }

    if (current != nullptr) {
        if (previous != nullptr) {
            previous->next = current->next;
        }
        else {
            playlist.head = current->next;
        }
        delete current;
        cout << "Song removed: " << removed << endl;
    }
    else {
        cerr << "Error: Song not found in the queue: " << removed << endl;
    }



    playlist.currentlyPlaying = nullptr;

    Mix_FreeMusic(music);
}
