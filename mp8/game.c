#include "game.h"

/* Our program creates a game of 2048 with NxM dimensions. Our make_game function initializes a NxM board and fills each cell with a value of -1 to indicate that it's empty.
Then, a random number is added after every move. To move, we slide all tiles in the direction chosen (w for up, s for down, a for left, d for right) and if there are two identical values next to each other, they will merge if we slide them together. We do this by checking each target row or column, depending on which direction is chosen. Then, remake_game is used to re-initialize an empty board (creates a new game). Our cells are chosen by using a 1D array that is also a pointer. Finally, we check for moves in legal_move_check to see if there are any possible plays left. If there are no moves available, the game ends.
*/


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct

	mygame->rows = rows;
	mygame->cols = cols;
 
	mygame->score = 0;						// initializing score to 0

	int i;
	int max_size = rows*cols;				// max size of the array
	for(i = 0; i < max_size; i++)			// loop through all elements 
	{
		
		mygame->cells[i] = -1;				// set each element to -1
				
	}

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

	destroy_game(*_cur_game_ptr);				// call destroy_game

	game * remake_game = malloc(sizeof(game));		// redo make_game
    remake_game->cells = malloc(new_rows*new_cols*sizeof(cell));

	remake_game->rows = new_rows;
	remake_game->cols = new_cols;

	
	int i;
	int max_size = new_rows*new_cols;
	remake_game->score = 0;
	for(i = 0; i < max_size; i++)
	{
		
		remake_game->cells[i] = -1;
				
	}
	
	_cur_game_ptr = &remake_game;
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
	int i = row, j = col;
	int current_cell;
	if ( ((i >= 0) && (i < cur_game->rows)) && ((j >= 0) && (j < cur_game->cols)) )
	{
		current_cell = i*(cur_game->cols)+j;
		return &cur_game->cells[current_cell];		// returns a pointer to the corresponding cell on the game
	} 

	return NULL;
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
	int changed_values = 0;
	int row, col, target_row, last_combined_row;
	
	for (col = 0; col < cur_game->cols; col++) //Go by each row
	{
		last_combined_row = -1; //Reset last combined row.
		
		for (row = 0; row < cur_game->rows; row++) //Increment row being checked until max row reached
		{
			if (*get_cell(cur_game, row, col) != -1) //If cell is not empty
			{
				for (target_row = 0; target_row <= row; target_row++) //Starting from 0, check the target row.
				{
					if (*get_cell(cur_game, target_row, col) == -1) //If the value in the target row is empty
					{
						cur_game->cells[target_row*(cur_game->cols)+col] = *get_cell(cur_game, row, col); //fill it with the value in current row
						cur_game->cells[row*(cur_game->cols)+col] = -1; //make current row empty
						changed_values = 1; //Flags that there was a move made.
					}
				

					if ( (target_row > 0) && ((target_row - 1) != last_combined_row)) //If target row is > 0 and row above target row is not last combined row
					{
						if (*get_cell(cur_game, target_row-1, col) == *get_cell(cur_game, target_row, col) && *get_cell(cur_game, target_row, col) != -1)
						{
							(*cur_game).score = cur_game->score + (cur_game->cells[(target_row-1)*(cur_game->cols)+col] * 2); //Add sum to score
							(*cur_game).cells[(target_row-1)*(cur_game->cols)+col] = cur_game->cells[(target_row-1)*(cur_game->cols)+col] * 2; //Change vals
							(*cur_game).cells[target_row*(cur_game->cols)+col] = -1; //Make cell empty
							last_combined_row = target_row - 1; //Sets last combined row
							changed_values = 1; //Flags move made
						}
					}
				}
			}
		}
	}
		
	if (changed_values == 0)
		return 0;
	
	else
		return 1;
	
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
		int changed_values = 0;
	int row, col, target_row, last_combined_row;
	
	for (col = 0; col < cur_game->cols; col++)
	{
		last_combined_row = -1; //Reset last combined row.
		
		for (row = cur_game->rows - 1; row >= 0; row--) //Starting from last row, decrement until row = 0
		{
			if (*get_cell(cur_game, row, col) != -1) //If cell is not empty
			{
				for (target_row = cur_game->rows-1; target_row >= row; target_row--) //Check target row by decrementing.
				{
					if (*get_cell(cur_game, target_row, col) == -1) //If empty
					{
						cur_game->cells[target_row*(cur_game->cols)+col] = *get_cell(cur_game, row, col); //Sets value of target cell to current cell value
						cur_game->cells[row*(cur_game->cols)+col] = -1; //Clears current cell
						changed_values = 1; //Flags change
					}
				

					if ( (target_row < cur_game->rows-1) && ((target_row+1) != last_combined_row))
					{
						if (*get_cell(cur_game,target_row+1, col) == *get_cell(cur_game, target_row, col) && *get_cell(cur_game, target_row, col) != -1)
						{
							(*cur_game).score = cur_game->score + (cur_game->cells[(target_row+1)*(cur_game->cols)+col] * 2); //Adds score
							(*cur_game).cells[(target_row+1)*(cur_game->cols)+col] = cur_game->cells[(target_row+1)*(cur_game->cols)+col] * 2;
							(*cur_game).cells[target_row*(cur_game->cols)+col] = -1;
							last_combined_row = target_row+1;
							changed_values = 1; //Flags change
						}
					}
				}
			}
		}
	}
		
	if (changed_values == 0)
		return 0;
	
	else
		return 1;
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
	int changed_values = 0;
	int row, col, target_col, last_combined_col;
	
	for (row = 0; row < cur_game->rows; row++) //Checks rows first
	{
		last_combined_col = -1; //Reset last combined row.
		
		for (col = 0; col < cur_game->cols; col++) //Starting from 0, checks columns
		{
			if (*get_cell(cur_game, row, col) != -1) //If current cell is not empty
			{
				for (target_col = 0; target_col <= col; target_col++) //Start from 0, check columns and increment target row
				{
					if (*get_cell(cur_game, row, target_col) == -1) //If empty
					{
						cur_game->cells[row*(cur_game->cols)+target_col] = *get_cell(cur_game, row, col);
						cur_game->cells[row*(cur_game->cols)+col] = -1;
						changed_values = 1; //Flags change
					}
				

					if ( (target_col > 0) && ((target_col - 1) != last_combined_col))
					{
						if (*get_cell(cur_game,row, target_col-1) == *get_cell(cur_game, row, target_col) && *get_cell(cur_game, row, target_col) != -1)
						{
							(*cur_game).score = cur_game->score + (cur_game->cells[(row)*(cur_game->cols)+target_col-1] * 2); //Add score
							(*cur_game).cells[(row)*(cur_game->cols)+target_col-1] = cur_game->cells[row*(cur_game->cols)+target_col-1] * 2;
							(*cur_game).cells[row*(cur_game->cols)+target_col] = -1;
							last_combined_col = target_col - 1;
							changed_values = 1; //Flags change
						}
					}
				}
			}
		}
	}
		
	if (changed_values == 0)
		return 0;
	
	else
		return 1;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
	int changed_values = 0;
	int row, col, target_col, last_combined_col;
	
	for (row = 0; row < cur_game->rows; row++)
	{
		last_combined_col = -1; //Reset last combined row.
		
		for (col = cur_game->cols - 1; col >= 0; col--) //Starting from last column, decrement
		{
			if (*get_cell(cur_game, row, col) != -1) //if not empty
			{
				for (target_col = cur_game->cols-1; target_col >= col; target_col--) //start from top column, then go down
				{
					if (*get_cell(cur_game, row, target_col) == -1)
					{
						cur_game->cells[row*(cur_game->cols)+target_col] = *get_cell(cur_game, row, col);
						cur_game->cells[row*(cur_game->cols)+col] = -1;
						changed_values = 1; //Flags change
					}
				

					if ( (target_col < cur_game->cols-1) && ((target_col+1) != last_combined_col))
					{
						if (*get_cell(cur_game,row, target_col+1) == *get_cell(cur_game, row, target_col) && *get_cell(cur_game, row, target_col) != -1)
						{
							(*cur_game).score = cur_game->score + (cur_game->cells[(row)*(cur_game->cols)+target_col+1] * 2);
							(*cur_game).cells[(row)*(cur_game->cols)+target_col+1] = cur_game->cells[row*(cur_game->cols)+target_col+1] * 2;
							(*cur_game).cells[row*(cur_game->cols)+target_col] = -1;
							last_combined_col = target_col+1;
							changed_values = 1; //Flags change
						}
					}
				}
			}
		}
	}
		
	if (changed_values == 0)
		return 0;
	
	else
		return 1;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
	int max_size = cur_game->rows * cur_game->cols;
	int i,j,current;
	
	for(current = 0; current < max_size; current++)				// loop through all elements in cells and find empty cells
	{
		if(cur_game->cells[current] == -1)
			return 1;
	}

	// find all adjacent spaces and check if move is valid
	for(i = 0; i < cur_game->rows; i++)
	{
		for(j = 0; j < cur_game->cols; j++)
		{

			if( cur_game->rows > (i + 1))
				if(*get_cell(cur_game,i,j) == *get_cell(cur_game,i+1,j))
					return 1;
			if( cur_game->cols > (j +1))
				if(*get_cell(cur_game,i,j) == *get_cell(cur_game,i,j+1))
					return 1;
		}
	}


	return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
