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
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) 
{
  
  assert(i>=0 && i<9);
  int j;

 
    // BEG TODO
  for(j = 0; j < 9; j++)
  {
    if(sudoku[i][j] == val)
    {
      return true;
      
    }
    
  }
  
   return 0;
    
  // END TODO
    
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  int i;
  // BEG TODO
   for(i = 0; i < 9; i++)
  {
    if(sudoku[i][j] == val)
    {
    
      return true;
    }
    

  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  int m, n;
  // BEG TODO
  if(i >= 0 && i < 3)
  {
    if(j >= 0 && j < 3)
    {
    for(m = 0; m < 3; m++)
      { 
        for(n = 0; n < 3; n++)
        {
          if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j >= 3 && j < 6)
    {
      for(m = 0; m < 3; m++)
      { 
        for(n = 3; n < 6; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j>=6 && j < 9)
    {
      for(m = 0; m < 3; m++)
      { 
        for(n = 6; n < 9; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    return 0;
  }
  if(i >= 3 && i < 6)
  {
    if(j >= 0 && j < 3)
    {
    for(m = 3; m < 6; m++)
      { 
        for(n = 0; n < 3; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j >= 3 && j < 6)
    {
      for(m = 3; m < 6; m++)
      { 
        for(n = 3; n < 6; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j>=6 && j < 9)
    {
      for(m = 3; m < 6; m++)
      { 
        for(n = 6; n < 9; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    return 0;
  }
  if(i >= 6 && i < 9)
  {
    if(j >= 0 && j < 3)
    {
    for(m = 6; m < 9; m++)
      { 
        for(n = 0; n < 3; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j >= 3 && j < 6)
    {
      for(m = 6; m < 9; m++)
      { 
        for(n = 3; n < 6; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    else if(j>=6 && j < 9)
    {
      for(m = 6; m < 9; m++)
      { 
        for(n = 6; n < 9; n++)
        {
           if(sudoku[m][n] == val)
          {
            return 1;
          }
        }
      }
    }
    return 0;
  }



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
int solve_sudoku(int sudoku[9][9]) 
{
 int i,j;
 int done = 0;
 
  // BEG TODO.
  for(i = 0; i < 9; i++)
    {
      for(j = 0; j < 9; j++)
        {
          done += sudoku[i][j];
            if(done == 405)
              {
                return 1;
              }
            else
              {
                if (sudoku[i][j] == 0 )
                  {
                    for (int num = 1; num <= 9; num++)
                    {
                      if(is_val_valid(num, i, j, sudoku))
                        {
                          sudoku[i][j] = num;

                          if (solve_sudoku(sudoku)) 
                            {
                              return 1;
                            }
                          sudoku[i][j] = 0;
                        }
                      
                    }
                    return 0;
                  }
              }
          }
    }        
  return 0;
// END TODO.
}


