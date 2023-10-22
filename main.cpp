#include <iostream>

using namespace std;

const int row;
const int column;
const char player = 'x';
const char space[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
const bool tie =false;

bool gameDisplay(int display[]);
bool playerPosition(int player[]);
bool winOrLose(int winner[]);
int main()
{
    int row;
    int column;
    char player = 'x';
    char space[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
    bool tie =false;
    while(!winOrLose()){
        gameDisplay(space);
        playerPosition(space);
        winOrLose(space);
    if(player == 'x' && tie){
        cout <<"Player 2 wins!"<<endl;
    }
    else if(player=='0' && tie==false){
        cout<< "Player 1 Wins!"<<endl;
    }
    else{
        cout <<"It's a draw!"<<endl;
    }
    }
}
bool gameDisplay(int display[]){

    cout<<"    |    |    " <<endl;
    cout<<" " <<space[0][0]<<"  | "<<space[0][1]<<"  | "<<space[0][2]<<"  " <<endl;
    cout<<"____|____|____" <<endl;
    cout<<"    |    |    " <<endl;
    cout<<" " <<space[1][0]<<"  | "<<space[1][1]<<"  | "<<space[1][2]<<"  " <<endl;
    cout<<"____|____|____" <<endl;
    cout<<"    |    |    " <<endl;
    cout<<" " <<space[2][0]<<"  | "<<space[2][1]<<"  | "<<space[2][2]<<"  " <<endl;
    cout<<"    |    |    " <<endl;

}
bool playerPosition(int player[]){
    if(player == 'x'){
        cout << "please enter row: ";
        cin >> row;
        cout << "please enter a column: ";
        cin >> column;
    }
    while(row <1 || row>3){
        cout <<"Invalid Input for row please input a valid number: ";
        cin >>row;
    }
    while(column <1 || column>3){
        cout <<"Invalid Input for column please input a valid number: ";
        cin >>column;
    }
    if(player== 'x' && space[row][column] !='x' && space[row][column] !='0'){
        space[row][column] = 'x';
        player ='0';
    }
    else if(player =='0' && space[row][column] !='x' && space[row][column] !=0){
        space[row][column]='0';
        player= 'x';
    }
    else{
        cout <<"All spaces are filled"<<endl;
        playerPosition{}
    }
    gameDisplay();
}
bool winOrLose(int winner[]){

    for(int i=0; i<3;i++)
    {
        if(space[i][0]==space[i][1] && space[i][0]==space[i][2] ||space[0][1]==space[1][i] && space[0][i]==space[2][i])
            return true;
    }
    if(space[0][0]==space[1][1] && space[1][1]==space[2][2] ||space[0][2]==space[1][1] && space[1][1]==space[2][0])
    {
        return true;
    }
    for(int i=0;i<3,i++){
        for(int j=0; j<3,j++){
            if(space[i][j] != 'x' && space[i][j] != '0'){
                return false;
            }
        }
    }
    tie=true;
    return false;

}
