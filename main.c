#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

bool checkRunning(bool running)
{
    if(running == true)
    {
      return true;
    }else{return false;};
}

/*
return a pointer to the board of tic tac toe. We will modify chars stored at each index
location with our player's & computers move choices.
*/
char * returnBaseBoard()
{
  static char baseBoard[9] = {'1','2','3','4','5','6','7','8','9'};
  return baseBoard;
}
//setup the game icons
int init()
{
  printf("Do you want to be X or O?\n");
  char player;
  scanf(" %c", &player);
  if(player == 'X' || player == 'x')
  {
    return 1;
  }
  else if(player == 'O' || player == 'o')
  {
    return 0;
  }else{return 2;};
}
//print the default static messages each game
void announcments()
{
  printf("Tic-Tac-Toe\n");
  printf("Code by Mark McDonald\n");    
  printf("You will be asked if you want to be X or O.\n");
  printf("A new game will then start.\n");
  printf("A heads/tails will decide who goes first.\n");
  printf("You make your selections using numbers: \n");
  printf("1 | 2 | 3\n");
  printf("--+---+---\n");
  printf("4 | 5 | 6\n");
  printf("--+---+---\n");
  printf("7 | 8 | 9\n");
}
//function to print the board each time we update it on the game loop
void printBoard(char * baseBoard)
{
  printf(" %c | %c | %c", baseBoard[0], baseBoard[1], baseBoard[2]);
  printf("\n --+---+--\n");
  printf(" %c | %c | %c", baseBoard[3], baseBoard[4], baseBoard[5]);
  printf("\n --+---+--\n");
  printf(" %c | %c | %c\n", baseBoard[6], baseBoard[7], baseBoard[8]);
  printf("\n");
}

typedef enum
{
  WIN_TYPE_WIN,
  WIN_TYPE_CONTINUE,
  WIN_TYPE_NOBODY,
} win_t;

win_t check_winner(char symbol)
{
  //puts("TODO: Check winner")
  char * game_brd = returnBaseBoard();
  if( /* Horizontatl Win */
    (symbol == game_brd[0] && game_brd[0] == game_brd[1] && game_brd[1] == game_brd[2]) ||
    (symbol == game_brd[3] && game_brd[3] == game_brd[4] && game_brd[4] == game_brd[5]) ||
    (symbol == game_brd[6] && game_brd[6] == game_brd[7] && game_brd[7] == game_brd[8]) ||
    //testing custom win condition
    (symbol == game_brd[6] && symbol == game_brd[7] && symbol == game_brd[8]) ||
    /* Vertical Win */
    (symbol == game_brd[0] && game_brd[0] == game_brd[3] && game_brd[3] == game_brd[6]) ||
    (symbol == game_brd[1] && game_brd[1] == game_brd[4] && game_brd[4] == game_brd[7]) ||
    (symbol == game_brd[2] && game_brd[2] == game_brd[5] && game_brd[5] == game_brd[8]) ||
    /* Diagonal Win */
    (symbol == game_brd[0] && game_brd[0] == game_brd[4] && game_brd[4] == game_brd[8]) ||
    (symbol == game_brd[2] && game_brd[2] == game_brd[4] && game_brd[4] == game_brd[6])
    )
    {
      return WIN_TYPE_WIN; //We have a winner!
    }
    else{return WIN_TYPE_NOBODY;}
      
  }
//controls all logic for the computer to choose grids
int computerLogic(int turn , char playerIcon)
{
  char * baseBoard = returnBaseBoard(); //creating a local scope pointer to the original board array
  int computerChoices[9];
  bool valid = false;
  int computerIndex;
  while(valid == false)
  {
    computerIndex = rand() % 9;
    int matches = 0;
    for(int i = 0; i < 9; i++)
    {
      if(computerChoices[i] == computerIndex)
      {
        matches++;
      }
    }
    if(baseBoard[computerIndex] == playerIcon)
    {
      matches++;
    }
    if(matches == 0)
    {
      valid = true;
    }
  }
  if(valid)
  {
    computerChoices[turn] = computerIndex;
    return computerIndex;
  }
  return 20; // the number itself makes no difference long as it's outside the range of the array.
  //we use it to signify that the computer's choice is invalid
}
// gets the player's choice for grid
int playerLogic()
{
  int playerIndex;
  int answer;
  scanf(" %d" , &answer);
  if(answer == 1)
    return 0;
  else{return playerIndex = answer - 1;};
}

int main(void) 
{
  char playerIcon;
  char cpuIcon;
  announcments();
  bool notpicked = true;
  while(notpicked)
  {
    int player = init();
    if(player == 0)
    {
      playerIcon = 'O';
      cpuIcon = 'X';
      printf("Player is O\n");
      printf("Computer is X\n");
      notpicked = false;
    }
    else if(player == 1)
    {
      playerIcon = 'X';
      cpuIcon = 'O';
      notpicked = false;
    }
    else if(player == 2)
    {
      playerIcon = '2';
      printf("You have selected an invalid answer.\n");
    }
  }
  bool running = true;
  bool state = true;
  int playerScore = 0;
  int computerScore = 0;
  int turns = 9;
  int cpuTurn = 0;
  while(checkRunning(running)) //main gameplay loop
  {
    while(state == true)
    {
      time_t now = time(NULL);
      srand(now);
      int first = rand() % 3;
      char * baseBoard = returnBaseBoard(); //creating a local scope pointer to the original board array
      if(first >= 2)
      {
        printf("Player goes first!\n");
        int answer;
        printBoard(baseBoard);
        scanf(" %d" , &answer);
        if(answer == 1)
          baseBoard[0] = playerIcon;
        else{baseBoard[answer - 1] = playerIcon;};
        printBoard(baseBoard);
        turns--;
        state = false;
      }else{printf("Computer goes first!\n");};
    
  //int cpuIndex returned to show if computer choice is valid or not & what grid if it's valid
      int cpuIndex = computerLogic(cpuTurn, playerIcon);
      if(cpuIndex != 20) 
        baseBoard[cpuIndex] = cpuIcon;
        printf("Computer print.\n");
        printBoard(baseBoard);
        cpuTurn++;
        turns--;
        state = false;
    }
    char * baseBoard = returnBaseBoard(); //creating a local scope pointer to the original board array
    bool win = false;
    while(turns > 0 && win == false)
    {
      printf("player print.\n");
      printBoard(baseBoard);
      int playerIndex = playerLogic();
      int cpuIndex = computerLogic(cpuTurn, playerIcon);
      if(baseBoard[playerIndex] == playerIcon || baseBoard[playerIndex] == cpuIcon)
      {
        printf("invalid grid, turned skipped...\n");
      }
      else if(baseBoard[cpuIndex] == playerIcon || cpuIndex == 20)
      {
        printf("invalid grid, cpu turn skipped...\n");
      }
      else {baseBoard[playerIndex] = playerIcon;} //only write the player's move if it's valid
      if(check_winner(playerIcon) == WIN_TYPE_WIN)
      {
        printf("PLAYER WINS!!!!\n");
        playerScore++;
        win = true;
        break;
      }
      turns--;
      printf("player print.\n");
      printBoard(baseBoard);
      //quick check to make sure the computer still has turns remaining
      if(cpuTurn < 9) 
      {
        baseBoard[cpuIndex] = cpuIcon;
        if(check_winner(cpuIcon) == WIN_TYPE_WIN)
        {
          printf("COMPUTER WINS!!!!\n");
          computerScore++;
          win = true;
          break;
        }
        cpuTurn++;
        turns--;
        printf("computer print.\n");
        printBoard(baseBoard);
      }
    }
    printf("FINAL BOARD PRINT.\n");
    printBoard(baseBoard);
    printf("GAME ENDED....\n");
    char input;
    printf("Play Again? y/n \n"); //get user input to check for replay
    scanf(" %c", &input);
    if(input == 'y' || input == 'Y')
    {
      char newBoard[9] = {'1','2','3','4','5','6','7','8','9'}; // clear the current board by writing each index to the original numbers
      for(int i = 0; i < 10; i++)
      {
        baseBoard[i] = newBoard[i];
      }
      continue;
    }
    else if(input == 'n' || input == 'N')
    {
      running = false;
    }
  }
    return 0;
}
