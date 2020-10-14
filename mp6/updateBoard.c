
/* Intro Paragraph
 
	In countlive neighbhors we checked for neighbhors on top,bottom, right,left and all diagonals. We then added or subtracted 1 from locate 		in order to check if the neighbhors are alive or not. Then we incremented the number of alive in order to return at the end the count for 		alive neighbhors around the particular row and column.

	in Updateboard we checked for the conditions given and updated the new states in the board for the next iteration. We did this by using 	two for loops and checking the conditions in each one. In order to change the old states to the new states we used an array to store the 		state values temporarily and then changed the states in board at the end using our state array.

	In alivestable we check for the alive cells staying in the same in the next step, we do this by checking the same conditions we checked in 		Update board and we return 0 as soon as something changes else we return 1 if the conditions say it doesnt change.


*/

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */


#include <stdio.h>

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{
	int alive= 0;
	int locate = row * boardColSize + col;
	if( col != 0 && ((locate - 1) >= 0))								// does n exist to the left
	{
		if(board[locate - 1] == 1)
			alive++;
	} 

	if( col != (boardColSize - 1))									// does n exist to the right
	{
		if(board[locate + 1] == 1 )
			alive++;
	}
	
	if( (row + 1) != 0 && ((locate-boardColSize) >= 0))				// does n exist to the top
	{	
		if(board[locate - boardColSize] == 1)
			alive++;
	}

	if( (row) != (boardRowSize - 1) )											// does n exist to the bottom
	{
		if(board[locate + boardColSize] == 1)
			alive++;
	}

	if( ((row + 1) != 0) && (col!= 0) && (locate - (boardColSize+1) >= 0))			// does n exist to the top left
	{
		if(board[locate - (boardColSize + 1)] == 1)
			alive++;
	}

	if( ((row+1 ) != 0) && (col != (boardColSize - 1)) && (locate - (boardColSize - 1) >= 0))	// does n exist to the top right
	{
		if(board[locate - (boardColSize - 1)] == 1)
			alive++;
	}

	if( ((row ) != (boardRowSize-1)) && (col != 0) )					// does n exist to the bottom left
	{
		if(board[locate + ( boardColSize - 1)] == 1)
			alive++;
	}
									
	if( ((row ) != (boardRowSize-1)) && (col != (boardColSize-1)) )		// does n exist to the bottom right
	{	
		if(board[locate + (boardColSize + 1)] == 1)
			alive++;
	}

	return alive;
}	

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize)
{
	int i,j,m,n,live_count,current_state;
	int state[boardRowSize*boardColSize];

	for(i = 0; i < boardRowSize; i++)
	{
		for(j = 0; j < boardColSize; j++)
		{
			current_state = board[i*boardColSize + j];
			live_count = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);

			if ( (current_state == 1) && ((live_count == 2) || (live_count == 3)) ) 		// if cell is alive and has two or three living neighbors, cell stays alive
			{
				state[i*boardColSize+j] = 1;
				
			} 
	
			else if ((current_state == 1) && ((live_count > 3) || (live_count < 2)))		 // if cell is alive and doesnt have 2 or 3 neighbors, it dies
			{
				state[i*boardColSize+j] = 0;
				

			}
			
			else if ((current_state == 0) && (live_count == 3)) 							// if cell is dead and has exactly 3 living neighbors, cell becomes alive.
			{
				state[i*boardColSize+j] = 1;	
			}
			else
			{
				state[i*boardColSize+j] = current_state;				
			}
		}
	}

	for( m = 0; m < boardRowSize; m++)
	{
		for( n = 0; n < boardColSize; n++)
		{
			board[m*boardColSize + n] = state[m*boardColSize+n];							// update the old states to new states using array
		}
	}

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize)
{
	int i,j,current,live_count;
	

	for(i = 0; i < boardRowSize; i++)
	{
		for(j = 0; j < boardColSize; j++)											// two for loops for grid
		{	
			current = board[i*boardColSize + j];									//get current board
			live_count = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);// get count of live neighbhors
			
	
			if ((current == 1) && ((live_count > 3) || (live_count < 2)))			// check conditions like updateboard above

			{
				return 0;															// alive cells change return 0
			
			}
			
			else if ((current == 0) && (live_count == 3)) 							
			{
				return 0;															// alive cells change return 0
	
			}


			else if ((current == 1) && ((live_count == 2) || (live_count == 3))) 		
			{
				continue;
			} 
		}
	}
	
	return 1;																		// alive cells do not change return 1
	
}

				
				
			

