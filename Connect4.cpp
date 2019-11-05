#include <iostream>
#include <string>

using namespace std;

//Global variables for representing the game board
const int COLS = 7;
const int ROWS = 6;
char board[COLS][ROWS]; //2D array of 7x6

//Global constants for game pieces
const char EMP = '-';
const char P1 = 'X';
const char P2 = 'O';

//initializes a connect4 board to contain
//all empty cells
void initializeBoard();

//Display contents of the board
void displayBoard();

//Add one piece to the Board
bool addPiece(int c, bool isPlayer1);

//Checks if a given player has won
bool isWinner(bool isPlayer1);

int main() {
  //Initialize game play
  bool PlayerOne = true;
  bool gameWon = false;
  int totalMoves = 0;
  const int MAX_MOVES = ROWS * COLS;

  initializeBoard();
  displayBoard();

  //Create a game play loop
  while ((totalMoves < MAX_MOVES) && (!gameWon)) {
    bool validMove = false;
    int columnToPlay = 0;
    //ask current player for a column until a valid move
    //is chosen
    while (!validMove) {
      cout << "Player ";
      if (PlayerOne) {
        cout << "1";
      } else {
        cout << "2";
      }
      cout << " - Select a column (0-"
           << (COLS-1) << ") to play: ";
      cin >> columnToPlay;
      validMove = addPiece(columnToPlay, PlayerOne);
      if (!validMove) {
        cout << "Column full. Try again." << endl;
      }
    }
    totalMoves++;
    displayBoard();
    gameWon = isWinner(PlayerOne);
    //Switch Player
    if (!gameWon){
      PlayerOne = !PlayerOne;
    }
  }
  if (gameWon) {
    cout << "Congratulations Player ";
    if (PlayerOne) {
      cout << "1";
    } else {
      cout << "2";
    }
    cout << ". You've won Connect Four!!!!" << endl;
  }
  else if (totalMoves == MAX_MOVES) {
    cout << "Game over! No moves remaining." << endl;
  }
  return 0;
}

void initializeBoard() {
  for (int c = 0; c < COLS; c++) {
    for (int r = 0; r < ROWS; r++) {
        board[c][r] = EMP;
    }
  }
}

void displayBoard() {
  cout << endl <<  "Connect 4 Board:" << endl;
  //Display board one row at a time
  for (int r = 0; r < ROWS; r++) {
    //For each row display all of the columns
    for (int c = 0; c < COLS; c++) {
      cout << board[c][r] << " ";
    }
    //After each row output newline character
    cout << endl;
  }
  for (int c = 0; c < COLS; c++) {
      cout << c << " ";
  }
  cout << endl << endl;
}

bool addPiece(int c, bool isPlayer1) {
  //check if column c is full
  if (board[c][0] != EMP) {
    return false;
  } else {
    //add piece to lowest unoccupied slot in column c
    for (int r = (ROWS-1); r >= 0; r--) {
        if (board[c][r] == EMP) {
          if (isPlayer1) {
            board[c][r] = P1;
          }
          else {
            board[c][r] = P2;
          }
          break;
        }
    }
    return true;
  }
}

bool isWinner(bool isPlayer1) {
  char currTile;
  if (isPlayer1) {
    currTile = P1;
  } else {
    currTile = P2;
  }
  //Check if current player has 4 pieces horizontally
  for(int r=0;r<ROWS;r++){
    int counter=0;
      for(int c=0;c<COLS;c++)
        {if(board[c][r]==currTile){
            counter++;
          }
          else
          {
            counter=0;
          }
          if(counter==4){
            return true;
          }
        }
      }
//checking if current player has 4 pieces vertically
for(int c=0;c<COLS;c++){
    int counter=0;
    for(int r=0;r<ROWS;r++)
      {if(board[c][r]==currTile){
        counter++;
      }
      else
      {
        counter=0;
      }
      if(counter==4){
        return true;
      }
    }
  }
//checking if there are 4 pieces in the middle diagonal starting from top left to bottom right
int counter=0;
for(int c=0;c<COLS;c++){

    if(board[c][c]==currTile){
      counter++;
    }
    else{counter=0;}
      if(counter==4){
      return true;
    }
  }
//checking if there are 4 pieces in the diagonal starting from right of the board[0][0]
for(int c=0;c<COLS;c++){
  int counter=0;
  for(int t=c+1,r=0;t<COLS;t++,r++){

    if(board[t][r]==currTile)
    {
      counter++;
     }
    else
    {counter=0;}
    if(counter==4){
      return true;
    }
  }
}
//checking if there are 4 pieces in the diagonal starting from below the board[0][0]
for(int r=0;r<ROWS;r++){
  int counter=0;
  for(int t=0,c=r+1;t<ROWS;t++,c++){

    if(board[t][c]==currTile){
      counter++;
    }
    else
    {counter=0;}
    if(counter==4){
    return true;
  }
  }
}
//checking if there are similar 4 tiles from the bottom left corner to top right corner
counter=0;
for(int c=0;c<COLS;c++){

    if(board[c][ROWS-1-c]==currTile){
      counter++;
    }
    else{counter=0;}
      if(counter==4){
      return true;
    }
  }
  //checking if there are similar 4 tiles starting from the above of board[0][5]
  for(int r=ROWS-1;r>0;r--){
    int counter=0;
    for(int t=0,c=r-1;t<ROWS;t++,c--){
//r denotes the row number.as counting started from the above of the board[0][5]
// the row number will decrease but the column will increase
//for first position it will be board[0][4].then second will be board[1][3].thus it will go on for  once
//again when the value of r changes then the first position changes to board[0][3]
      if(board[t][c]==currTile){
        counter++;
      }
      else
      {counter=0;}
      if(counter==4){
      return true;
    }
    }
  }
  //checking if there are similar 4 tiles starting from the left of the board[0][5]

  for(int c=COLS-1;c>0;c--){
    int counter=0;
    for(int t=COLS-1-c,r=ROWS-1;t<COLS;t++,r--){
      //c denotes the column number.as counting started from the left of the board[0][5]
      // the row number will decrease but the column will increase
      //for first position it will be board[0][5].then second will be board[1][4].thus it will go on once
      //again when the value of c changes then the first position changes to board[1][5]
      if(board[t][r]==currTile){
        counter++;
      }
      else
      {counter=0;}
      if(counter==4){
      return true;
    }
    }
  }


  return false;
}
