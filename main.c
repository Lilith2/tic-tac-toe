#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


bool checkRunning(bool state) // not used yet
{
    if(state == true)
    {
      return true;
    }else{return false;};
}

int checkTurns(int turns)
{
  if(turns <= 9)
  {
    return turns;
  }else{return 0;};
}

char * returnBaseBoard()
{
  static char baseBoard[9] = {'1','2','3','4','5','6','7','8','9'};
  return baseBoard;
}

char * returnInteractiveBoard()
{
  static char interactiveBoard[9];
  return interactiveBoard;
}

int init() //setup game
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

void announcments()
{
  printf("Tic-Tac-Toe\n");
  printf("Code by Mark McDonald\n");    printf("You will be asked if you want to be X or O.\n");
  printf("A new game will then start.\n");
  printf("A heads/tails will decide who goes first.\n");
  printf("You make your selections using numbers: \n");
  printf("1 | 2 | 3\n");
  printf("---+---+---\n");
  printf("4 | 5 | 6\n");
  printf("---+---+---\n");
  printf("7 | 8 | 9\n");
}

void printBoard(char * baseBoard)
{
  printf(" %c | %c | %c", baseBoard[0], baseBoard[1], baseBoard[2]);
  printf("\n ---+---+---\n");
  printf(" %c | %c | %c", baseBoard[3], baseBoard[4], baseBoard[5]);
  printf("\n ---+---+---\n");
  printf(" %c | %c | %c\n", baseBoard[6], baseBoard[7], baseBoard[8]);
  printf("\n");
}

typedef enum
{
  WIN_TYPE_WIN,
  WIN_TYPE_CONTINUE,
  WIN_TYPE_NOBODY,
} win_t;

int computerLogic(int turn)
{
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
    if(matches == 0)
    {
      valid = true;
    }
  }
  computerChoices[turn] = computerIndex;
  return computerIndex;
}

void playerLogic(char * baseBoard[9], char * playerIcon)
{
  int playerIndex;
  int answer;
  char icon = *playerIcon;
    printBoard(*baseBoard);
    scanf(" %d" , &answer);
    if(answer == 1)
      baseBoard[0] = &icon;
    else{baseBoard[answer - 1] = &icon;};
    printBoard(*baseBoard);
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
  bool state = true;
  int turns = 9;
  int cpuTurn = 0;
  while(state == true)
  {
    time_t now = time(NULL);
    srand(now);
    int first = rand() % 3;
    char * baseBoard = returnBaseBoard();
    if(first >= 2)
    {
      printf("Player goes first!\n");
      int answer;
      printBoard(baseBoard);
      scanf(" %d" , &answer);
      if(answer == 1)
        baseBoard[0] = playerIcon;
      else{baseBoard[answer] = playerIcon;};
      printBoard(baseBoard);
      turns--;
    }else{printf("Computer goes first!\n");};
//array to store computer choices so it doesn't choose same place 2 times
    baseBoard[computerLogic(cpuTurn)] = cpuIcon;
    cpuTurn++;
    turns--;
    printBoard(baseBoard);
    char * playerIconP = &playerIcon;
    playerLogic(&baseBoard, playerIconP);
    printBoard(baseBoard);
    //add more logic later
    state = false;
  }

  return 0;
}
