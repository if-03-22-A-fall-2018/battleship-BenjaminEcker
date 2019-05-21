/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "battleship.h"

static CellContent my[FIELDSIZE][FIELDSIZE];
static CellContent op[FIELDSIZE][FIELDSIZE];
CellContent myguesses[FIELDSIZE][FIELDSIZE];

/**
*** Loads the two files battleship.my and battleship.op which hold the fields
*** of the players. The files hold a stream of 10 times 10 values of type
*** CellContent.
*/
void load_game()
{
  FILE *my_fd = fopen("battleship.my", "r");
	FILE *op_fd = fopen("battleship.op", "r");

  for(int i=0;i<FIELDSIZE;i++)
  {
    for(int x=0;x<FIELDSIZE;x++)
    {
      fread(&my[i][x],sizeof(CellContent),1,my_fd);
    }
  }
  for(int i=0;i<FIELDSIZE;i++)
  {
    for(int x=0;x<FIELDSIZE;x++)
    {
      fread(&op[i][x],sizeof(CellContent),1,op_fd);
    }
  }

  for(int i=0;i<FIELDSIZE;i++)
  {
    for(int x=0;x<FIELDSIZE;x++)
    {
      myguesses[i][x]=Unknown;
    }
  }

  fclose(my_fd);
	fclose(op_fd);
}

/**
*** @param row The row where we get the shot.
*** @param col The col where we get the shot.
*** @return The value of cell indicated by row and column of the own field (filled
*** with the values of battleship.my). If row/col point outside the field the
*** value OutOfRange is returned.
*/
CellContent get_shot(int row, int col)
{
  if((row<FIELDSIZE && row>=0)&&(col<FIELDSIZE && col>=0))
  {
    return my[row][col];
  }
  return OutOfRange;
}

/**
*** Sets the row and column of the my guesses table to the value held in the
*** opponents field. If this is a boat all surrounding cells are marked as water.
*** @param row The row where we place the shot
*** @param col The columnt where we place the shot.
*** @return True if target field is valid, i.e., inside the field, False otherwise.
*/
bool shoot(int row, int col)
{
  if((row<FIELDSIZE && row>=0)&&(col<FIELDSIZE && col>=0))
  {
    if(op[row][col]==Boat)
    {
      myguesses[row][col]=Boat;
      for(int i=row-1;i<=row-11;i++)
      {
        for(int x=col-1;x<=col-1;x++)
        {
          if((row<FIELDSIZE && row>=0)&&(col<FIELDSIZE && col>=0))
          {
            myguesses[i][x]=Water;
          }
        }
      }
      return true;
    }
    else if(op[row][col]==Water)
    {
      myguesses[row][col]=Water;
      return true;
    }
  }
  return false;
}

/**
*** @param row The row where we want to get our own guess.
*** @param col The column where we want to get our own guess.
*** @return The value of the table with my guesses at row and column. If row/col
*** is outside the field OutOfRange is returned.
*/
CellContent get_my_guess(int row, int col)
{
  if((row<FIELDSIZE && row>=0)&&(col<FIELDSIZE && col>=0))
  {
    return myguesses[row][col];
  }
  return OutOfRange;
}
