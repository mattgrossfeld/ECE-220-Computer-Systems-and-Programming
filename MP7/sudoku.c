/*
To check if the sudoku puzzle has a valid number in a cell, we check each row, column, and 3x3 grid. If a cell is unfilled, it will be filled with a number from 1-9. If there is a duplicate number found, then it backtracks and replaces the value with the next value to be checked. If there are no duplicates and every cell is filled, then the sudoku puzzle is solved. To check if every cell is filled, a counter is used and is incremented everytime there is a filled cell. Once all cells are filled, the counter equals 81 and the puzzle is done.
*/

#include "sudoku.h"

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}

//-------------------------------------------------------------------------------------------------
// Start coding your MP here.
// ------------------------------------------------------------------------------------------------

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  	assert(i>=0 && i<9);

  	// BEG TODO
	int y;
	for (y = 0; y < 9; y++)
	{
		if(sudoku[i][y] == val) //If value found in row, return 1
			return 1;
	}
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

	assert(j>=0 && j<9);

    // BEG TODO
	int x;
	for(x = 0; x < 9; x++)
	{
	if(sudoku[x][j] == val) // If value found in column, return 1
		return 1;
	}
  
	return 0;
	// END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
assert(i>=0 && i<9);
  
	// BEG TODO
	int x = i/3; //Get 3x3 row coordinate 
	int y = j/3; //Get 3x3 column coordinate
	int m,n;
	x*= 3;
	y*=3;	

	for (m = x ; m < (x+3); m++)
	{
		for (n = y; n < (y+3); n++)
		{
			if(sudoku[m][n] == val) //If the value in the 3x3 is found, return 1
				return 1;
		}
	}

	return 0;
	// END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  if(is_val_in_row(val, i, sudoku)) return 0;
  if(is_val_in_col(val, j, sudoku)) return 0;
  if(is_val_in_3x3_zone(val, i, j, sudoku)) return 0;
  return 1;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

	// BEG TODO.

	int i,j,filled_cells = 0;
	
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{

			if ((sudoku[i][j] > 0) && (sudoku[i][j] <= 9))
			{
			filled_cells++; // Increment every time there is a cell that is filled.

				if (filled_cells == 81) // When all cells full, return 1
				return 1;
			}

			else
			{
				for (int num = 1; num <= 9; num++)
				{
					if (is_val_valid(num, i, j, sudoku)) //Check if number is valid
					{
						sudoku[i][j] = num; // If valid, fill cell with num
						if (solve_sudoku(sudoku))
						{
							return 1;
						}
						
						sudoku[i][j] = 0; // if num doesn't work, empty cell
					}
				}
			return 0;
			}
		}
	}			
	
	
	return 0;

	// END TODO.
}



