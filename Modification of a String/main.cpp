// The program written allows the user input a string and modify it in several ways
// Writer: Nathan Gumataotao
// Date: 3/21/2023
// Completed
#include <iostream>
#include <cstring>


using namespace std;

const int Size =80;

//functions
void Search(char Search[]);
void Insert(char inserT[]);
void Append(char appenD[]);
void Delete(char deletE[]);
void Replace(char replacE[]);
int ssearch(char sourceString[], char targetString[]);
int main()
{
    //need char functions in order to account for word inputs
    char input[Size];
    char option;

    cout << "Please Input a string" << endl;
    cin.getline(input, Size);

    cout << "Current String: " << input << endl;

    cout << "Choose an Option: " <<endl;
    string menu = "s-Search,I-Insert,a-append,d-delete,r-replace,e-exit";
    cout << menu << endl;
    cin >> option;
    cin.ignore();
    //allows the user to input any option from the string
    while(option != 'e'){
        switch(option){
            case 's':Search(input);
            break;
            case 'i':Insert(input);
            break;
            case 'a':Append(input);
            break;
            case 'd':Delete(input);
            break;
            case 'r':Replace(input);
            break;
            default: cout << "Invalid" <<endl;
        }
        cout << menu << endl;
        cin >> option;
        cin.ignore();
    }
    return 0;

}
//this function allows the user to search for one substring and it tells them where it is
void Search(char Search[]){

   char searCH[Size];
   int found;

   cout << "Enter a substring to search" <<endl;
   cin.getline(searCH, Size);
   found=ssearch(Search, searCH);
   if(found== -1)
    cout << "the substring is not found"<<endl;
   else
    cout << "The substring is found at the position "<< found <<endl;
    cout << endl;

    cout <<"The new string is "<< Search <<endl;

}
//This allows the user to input another substring at any point in the string
void Insert(char inserT[]){

    char inseRT[Size];
    char emptY[Size] = " ";
    int position;
    char temp[Size];

    cout << "Enter a string to insert" <<endl;
    cin.getline(inseRT, Size);
    cout << "At which position should it be interested?"<<endl;
    cin >> position;
    cin.ignore();

    strcpy(temp, &inserT[position]);
    inserT[position] = '\0';
    strcat(inserT, emptY);
    strcat(inserT, inseRT);
    strcat(inserT, temp);
    cout << "The new String is "<<inserT<<endl;
}
//This allows the user to input another substring on the end of the string
void Append(char appenD[]){

    char appeND[Size];
    char Empty[Size];

    cout << "enter the string to be appended"<<endl;
    cin.getline(appeND, Size);

    strcat(appenD, Empty);
    strcat(appenD, appeND);

    cout << "The new string is " << appenD <<endl;
}
//allows the user to delete any substring in the string
void Delete(char deletE[]){

    char deleTE[Size];
    int position;
    char empty[Size]= " ";
    char temp[Size];
    cout << "Enter a string to be deleted "<<endl;
    cin.getline(deleTE, Size);
    position= ssearch(deletE, deleTE);

    if(position== -1)
        cout <<"the substring is not in the string"<<endl;
    else{
        strcpy(temp, &deletE[position+strlen(deleTE)]);
        deletE[position]= '\0';
        strcat(deletE, temp);
        cout <<"The updated string is" << deletE<<endl;
    }
}
//allows the user to replace any substring with another of the users choice
void Replace(char replacE[]){

    char replaCE[Size];
    char newsubstring[Size];
    char temp[Size];
    int found;
    char empty[Size] = " ";

    cout <<"Enter a substring to be replaced" <<endl;
    cin.getline(replaCE, Size);
    cout << "Enter the new substring " <<endl;
    cin.getline(newsubstring, Size);
    found=ssearch(replacE, replaCE);
    if(found == -1)
        cout <<"The string you want to replace does not exist"<<endl;
    else{
        strcpy(temp, &replacE[found+strlen(replaCE)]);
        replacE[found]= '\0';
        strcat(replacE, empty);
        strcat(replacE, newsubstring);
        strcat(replacE, temp);
        cout<< "The updated string is "<<replacE<<endl;
    }
}
//this allows the program to keep track of how long the string is and modify it in itself
int ssearch(char sourceString[], char targetString[]){

    int sourceLength, targetLength, index, returnValue;
    sourceLength=strlen(sourceString);
    targetLength=strlen(targetString);
    index =-1;

    for(int i=0; i <(sourceLength - (targetLength -1)); i++){

        returnValue =strncmp (&sourceString[i], targetString, targetLength);
        if (returnValue == 0){
            index=i;
            break;
        }
    }
    return index;
}
