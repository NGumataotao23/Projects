// The program written allows the user input a string and modify it in several ways
// Writer: Nathan Gumataotao
// Date: 4/17/2023
// Completed
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
//decides the size of the names
const int name_size = 81;
const int num_players = 10;

//this allows us to display the same information and assign certain lines to arrays or variables
struct playerInfo{
    char lastname[name_size];
    char firstname[name_size];
    int birthMonth;
    int birthDay;
    int birthYear;
};
//functions prototypes
void getData(playerInfo[]);
void makeCopy(const playerInfo[], playerInfo[]);
void showData(const playerInfo[]);
void bubbleSort(playerInfo[]);
void swapp(playerInfo &, playerInfo &);
int searchPlayer(const playerInfo[], char[]);
void findplayer(playerInfo players[]);

int main()
{
   playerInfo players[num_players];
   int opt;
   int index;
   char ending[name_size] = "//";
   char name[name_size];
   playerInfo copyplayers[num_players];

   getData(players);

   makeCopy(players, copyplayers);

    //allows options to be chosen in order to modify the structure
   do{
        cout <<"Choose an option: "<< endl;
        cout << "(1-display original data, 2-sort data, 3-display sorted data, 4-search by last name, 5-exit program)"<<endl;
        cin >>opt;

        switch (opt){
    case 1:
        cout << "Unsorted Data:" <<endl;
        showData(players);
        break;

        case 2:bubbleSort(copyplayers);
        break;

        case 3:
        cout << "sorted Data:" <<endl;
        showData(copyplayers);
        break;
        case 4:
            findplayer(players);
            break;
        case 5: cout <<"Good bye" << endl;
        break;

        default: cout <<"Invalid option picked" <<endl;
        }
   }while (opt!=5);
   return 0;
}
//function orders the data and allows us to pull the data from the file
void getData(playerInfo players[]){

    ifstream in ("soccer.txt");


    if(in){
        for(int i = 0; i < num_players; i++){
            in >> players[i].lastname;
            in >> players[i].firstname;
            in >> players[i].birthMonth;
            in >> players[i].birthDay;
            in >> players[i].birthYear;
        }
        in.close();
    }
    else
    {
        cout <<"error opening the input file";
    }
}
//this function copies the data
void makeCopy(const playerInfo data[], playerInfo copyPlayer[]){

    for(int i=0; i < num_players; i++){
        copyPlayer[i] =data[i];
    }
}
//this function shows the data
void showData (const playerInfo data[]){

    for (int i =0; i <num_players; i++){
        cout << data[i].lastname <<" ";
        cout << data[i].firstname <<" ";
        cout << data[i].birthMonth <<" ";
        cout << data[i].birthDay <<" ";
        cout << data[i].birthYear <<endl;
    }
}
//this function uses a bubble sort method to sort the data
void bubbleSort(playerInfo data[]){

    int maxElement;
    int index;
    for (maxElement = num_players -1; maxElement > 0; maxElement--){
        for(index =0; index < maxElement; index++){
            if(strcmp(data[index].lastname, data[index+1].lastname) > 0)
                swapp(data[index], data[index+1]);
        }
    }
}
//swaps 2 of player infos
void swapp(playerInfo &a, playerInfo &b){

    playerInfo temp = a;
    a =b;
    b =temp;
}
//allows person to find players based on there lastname
void findplayer(playerInfo players[]){

    char ending[name_size] = "//";
    char searchName[name_size];

    cout <<"Enter one or more starting letters";
    cout <<"of the last name (enter '//' to quit this option)";
    cout << endl;
    cin >> searchName;
    while(strcmp(searchName, ending) != 0){
        int index =searchPlayer(players, searchName);
        if (index == -1)
            cout <<"the last name was not found" <<endl;
        else{
            cout << players[index].lastname <<" ";
            cout << players[index].firstname <<" ";
            cout << players[index].birthMonth <<" ";
            cout << players[index].birthDay <<" ";
            cout << players[index].birthYear <<endl;
        }
        cout << "enter one or more starting letters";
        cout << " of the last name(enter '//' to quit this option";
        cout << endl;
        cin >> searchName;
    }
}
//this fucntion allows someone to search players
int searchPlayer(const playerInfo data[], char name2[]){

    int index = 0;
    for(index =0; index < num_players; index++){
        if(strncmp(data[index].lastname, name2, strlen(name2)) ==0)
            return index;
    }
    return -1;
}



