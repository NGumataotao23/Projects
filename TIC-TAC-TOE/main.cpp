// The program written allows the user to tally the favorite beverages of the selected amount of people
// Writer: Nathan Gumataotao
// Date: 2/21/2023
// Completed
#include <iostream>

using namespace std;
//initilizes the rows and the columns to 3
const int rows = 3;
const int columns = 3;

//all functions for the rest of the game
void display(char [][columns]);
void turn(char [][columns], char);
bool gameOver(char [][columns]);
bool playerWin(char [][columns], char);
bool almostWin(char [][columns], char);
void Winner(char [][columns]);
int main()
{
    //set our array up
    char gameBoard[rows][columns] ={{'*','*','*'},{'*','*','*'},{'*','*','*'}};
    //this will display the gameboard, decide the turn and detect if the game is over using the functions
    do{
        display(gameBoard);
        turn(gameBoard, 'X');
        display(gameBoard);
        if(!gameOver(gameBoard))
            turn(gameBoard, '0');

    } while(!gameOver(gameBoard));
        display(gameBoard);
        Winner(gameBoard);
        return 0;
}
//this function displays the gameboard
void display(char board[][columns]){
    cout << "      Columns "<< endl;
    cout << "       1 2 3"<<endl;
    //shows the rows in
    for(int row = 0; row < rows; row++){
        cout << "Row " << (row+1) <<": ";
        for(int col = 0; col <columns; col++){
            cout <<board[row][col] <<" ";
        }
         cout <<endl;
    }
}
//this function decides whose turn it is
void turn(char board[][columns], char symbol){
    bool available =false;

    int row;
    int col;

    cout <<"Player " << symbol <<"'s turn." <<endl;
    cout <<"Enter a row and column to place an " <<symbol<<"."<<endl;
    //asks player what row and column
    while(!available){
        cout << "Row:";
        cin >> row;
    //checks to see if its a valid row
        while (row <1 || row > rows){
            cout << "Invalid Row" <<endl;
            cout <<"Row: ";
            cin >> row;
        }
        cout <<"Column: ";
        cin >>col;
    //checks to see if its a valid column
        while (col < 1 || col > columns){
            cout << "Invalid Column" <<endl;
            cout <<"Column: ";
            cin >> col;
    }
    //looks to see if the symbol placement is available
    if(board[row -1][col -1 ] =='*')
        available =true;
    else{
        cout <<"That location is not available. Select another location." <<endl;
        }
    }
    //this puts the persons symbols on the gameboard
    board[row - 1 ][col - 1] = symbol;
}
//checks if the game is over or not
bool gameOver(char board[][columns]){
    //this is a status indicator to relay info to the other functions
    bool status;
    //checks other functions to see if the X or 0 symbol has created a line
    if (playerWin(board, 'X') || playerWin(board, '0'))
        status= true;
    else if (almostWin(board, 'X') || almostWin(board, '0'))
        status = false;
    else
        status =true;

    return status;
}
//checks to see if any player has won
bool playerWin(char board[][columns], char symbol){
    //status indicator
    bool status =false;
    //all of the if statements check to see if a symbol is in its place
    if(board[0][0] ==symbol && board[0][1] == symbol && board[0][2] == symbol){
        status = true;
    }
    if(board[1][0] ==symbol && board[1][1] == symbol && board[1][2] == symbol){
        status = true;
    }
    if(board[2][0] ==symbol && board[2][1] == symbol && board[2][2] == symbol){
        status = true;
    }
    if(board[0][0] ==symbol && board[1][0] == symbol && board[2][0] == symbol){
        status = true;
    }
    if(board[0][1] ==symbol && board[1][1] == symbol && board[1][2] == symbol){
        status = true;
    }
    if(board[0][2] ==symbol && board[1][2] == symbol && board[2][2] == symbol){
        status = true;
    }
    if(board[0][0] ==symbol && board[1][1] == symbol && board[2][2] == symbol){
        status = true;
    }
    //returns whether or not the game is over
    return status;

}
//checks to see if a player can still win
bool almostWin(char board[][columns], char symbol){
    bool status = false;
    //checks all spaces for symbols to see
    if(   (board[0][0] ==symbol || board[0][0] == '*')
       && (board[0][1] ==symbol || board[0][1] == '*')
       && (board[0][2] ==symbol || board[0][2] == '*'))
       status = true;

    if(   (board[1][0] ==symbol || board[1][0] == '*')
       && (board[1][1] ==symbol || board[1][1] == '*')
       && (board[1][2] ==symbol || board[1][2] == '*'))
       status = true;

    if(   (board[2][0] ==symbol || board[2][0] == '*')
       && (board[2][1] ==symbol || board[2][1] == '*')
       && (board[2][2] ==symbol || board[2][2] == '*'))
       status = true;

    if(   (board[0][0] ==symbol || board[0][0] == '*')
       && (board[1][0] ==symbol || board[1][0] == '*')
       && (board[2][0] ==symbol || board[2][0] == '*'))
       status = true;

    if(   (board[0][1] ==symbol || board[0][1] == '*')
       && (board[1][1] ==symbol || board[1][1] == '*')
       && (board[2][1] ==symbol || board[2][1] == '*'))
       status = true;

    if(   (board[0][2] ==symbol || board[0][2] == '*')
       && (board[1][2] ==symbol || board[1][2] == '*')
       && (board[2][2] ==symbol || board[2][2] == '*'))
       status = true;

    if(   (board[0][0] ==symbol || board[0][0] == '*')
       && (board[1][1] ==symbol || board[1][1] == '*')
       && (board[2][2] ==symbol || board[2][2] == '*'))
       status = true;

       return status;
}
//declares the winner
void Winner(char board[][columns]){
    //checks to see if any of the players have met the win condition in the other function
    //if everything lines up one player will come out on top or there will be a draw
    if(playerWin(board, 'X'))
        cout <<"Player 1 Wins!" <<endl;
    else if (playerWin(board, '0'))
        cout <<"Player 2 Wins!" <<endl;
    else
        cout <<"Game Over its a Draw"<<endl;
}
