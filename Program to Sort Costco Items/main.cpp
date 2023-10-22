// The program written allows the user to organize and record items from a list from costco
// Writer: Nathan Gumataotao
// Date: 4/24/2023
// Completed
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
//decides how many records can be recorded
const int Size = 81;
int displaymenu();
//helps us pull from the txt file and organize it properly
struct Costco{
    char Name[Size];
    int quantity;
    float wholesale;
    float retail;

};
//setting all our functions up
void addrecord();
void displayall();
int initialdataread();
void displayrecord();
void changerecord();
void getitem(Costco &);
void report();
void displayitem(const Costco&);

int main()
{

    int choice;
    initialdataread();
    choice = displaymenu();
    //choices our menu displays to choose our options from
    while(choice !=6){
        switch(choice){
            case 1 : displayall();
                break;
            case 2 : displayrecord();
                break;
            case 3 : changerecord();
                break;
            case 4 : addrecord();
                break;
            case 5 : report();
                break;

            default: if( choice !=6) cout<<"Wrong Choice" << endl;
        }
        choice = displaymenu();
    }

}
//function displays the menu to choose from and records the choice made
int displaymenu(){

    int choice;
    string menu= "1- Display all, 2- Display a record, 3- Change Record";
    menu+=", 4- Add a record, 5-prepare report, 6- Exit ";
    cout << menu;
    cin >> choice;
    return choice;
}
//reads the data from the txt file and puts it into the dat file which can be opened in other
//locations and be modified
int initialdataread(){

    Costco temp;
    ofstream out;
    ifstream in;
    in.open("data.txt");
    out.open("inventory.dat", ios::out | ios::binary);
    if(in && out){
        in >> temp.Name;
        while (!in.eof()){
            in>>temp.quantity >>temp.wholesale >>temp.retail;
            out.write((char*)&temp, sizeof(temp));
            in >> temp.Name;
        }
        in.close();
        out.close();
    }
    else{
        cout << "Error opening files" <<endl;
        exit(EXIT_FAILURE);
    }
}
//displays the data from the txt file
void displayall(){
    Costco temp;
    ifstream in("inventory.dat", ios:: binary);
    if(in){
        in.read((char*)&temp, sizeof(temp));
        while(!in.eof()){
            displayitem(temp);
            in.read((char*)&temp, sizeof(temp));
        }
        in.close();
    }
}
//displays the record of a specific product from the dat file
void displayrecord(){

    Costco temp;
    char todisplay[Size];
    cout << "Enter the name of the record you like to view" <<endl;
    cin >> todisplay;
    //checks to see
    ifstream in ("inventory.dat", ios::binary);
    if(in)
    {
        in.read((char*)&temp, sizeof(temp));
        while(!in.eof()){
            if(strcmp(temp.Name, todisplay) ==0){
                displayitem(temp);
                break;
            }
            in.read((char*)&temp, sizeof(temp));
        }
        if(in.eof()){
            cout<< "Item not in the file" <<endl;
        }
        in.close();
    }
}
//allows user to change the record of a specific product
void changerecord(){

    Costco temp;
    Costco newitem;
    long where;

    char olditem[Size];
    cout << "Enter item you would like to replace";
    cin >> olditem;
    getitem(newitem);

    fstream inOut ("inventory.dat", ios::in |ios::out| ios::binary);

    if(inOut){
        inOut.read((char*)&temp, sizeof(temp));
        while(!inOut.eof()){
            if(strcmp(temp.Name,olditem) ==0){
                cout << "Item found    " << temp.Name <<endl;
                break;
            }
            inOut.read((char*)&temp, sizeof(temp));
        }
    }
    inOut.clear();

    where = inOut.tellg();
    inOut.seekp(where-sizeof(Costco), ios::beg);
    inOut.write( (char*) &newitem, sizeof(Costco));
    inOut.close();
}
//adds a record to the dat file
void addrecord(){

    Costco temp;
    getitem(temp);

    ofstream out("inventory.dat", ios::app | ios::binary);
    if(out){
        out.write( (char*) &temp, sizeof(Costco));
    }
    else{
        cout <<"Error opening the file" <<endl;
        exit(EXIT_FAILURE);
    }
}
//displays specific products for the other functions
void displayitem(const Costco& c){

    cout <<"Item name        "<<c.Name <<endl;
    cout <<"Quantity         "<<c.quantity <<endl;
    cout <<"Wholesale cost   "<<c.wholesale <<endl;
    cout <<"Retail Cost      "<<c.retail <<endl <<endl;
}
//gets the items and allows them to be modified
void getitem(Costco & newitem){

    cout <<"Enter new item name: ";
    cin >> newitem.Name;
    cout <<"Enter new item Quantity: ";
    cin >> newitem.quantity;
    cout <<"Enter new item wholesale price: ";
    cin >> newitem.wholesale;
    cout <<"Enter new item retail price: ";
    cin >> newitem.retail;
}
//adds up the totals of all the number of products, prices, retail, and wholesales
void report(){

    Costco temp;
    float total_quantity= 0.0, total_retail=0.0,total_wholesale=0.0;
    ifstream in ("inventory.dat", ios::binary);
    if(in){
        while(in.read( (char*) &temp, sizeof(Costco))){
            total_quantity += temp.quantity;
            total_retail+=temp.retail;
            total_wholesale += temp.wholesale;
        }
        in.close();
    }
    else{
        cout <<"Error opening the file" <<endl;
        exit(EXIT_FAILURE);
    }
    cout << "REPORT" <<endl;
    cout <<"Total quantity of items on stock  "<< total_quantity <<endl;
    cout <<"Total retail amount on stock      $"<<total_retail <<endl;
    cout <<"Total wholesale amount on stock   $"<<total_wholesale <<endl <<endl;
}
