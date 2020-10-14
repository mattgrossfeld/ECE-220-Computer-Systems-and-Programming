#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/* First we open a file and dynamically allocate memory for the maze and free the memory correctly 
		and then we solved the maze using a DPS recursive algorithm which has a base case and a recursive case.
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
	int h, w;
	int i, j;

	FILE *File;
	File = fopen(fileName, "r");					// opening file for read
	
	fscanf(File, "%d %d", &w, &h);					// scan for dimensions
	maze_t *madeMaze;
	madeMaze = (maze_t*)malloc(sizeof(maze_t));			// allocating space
	madeMaze->width = w;
	madeMaze->height = h;

	madeMaze->cells = malloc(madeMaze->width * sizeof(char*));		
	
	for (i = 0; i < madeMaze->width; i++)
	{
		madeMaze->cells[i] = malloc(sizeof(char) * madeMaze->height);	// allocating space for array
	}
	
	i = fgetc(File);
	for (i = 0; i < madeMaze->height; i++)
	{
		for (j = 0; j < madeMaze->width; j++)
		{
			madeMaze->cells[i][j] = fgetc(File);
			
			if (madeMaze->cells[i][j] == 'S')
			{
				madeMaze->startRow = i;
				madeMaze->startColumn = j;
			}
			
			if (madeMaze->cells[i][j] == 'E')
			{
				madeMaze->endRow = i;
				madeMaze->endColumn = j;
			}
		}
		
		j = fgetc(File);
	}

	fclose(File);							// closing file
	return madeMaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	int x;
	for (x = 0; x < maze->width; x++)					
	{
		free(maze->cells[x]);							// free the cells
	}
	free(maze->cells);								
	free(maze);											// free maze

}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{															// just printing the maze
    // Your code here.
	int i, j;

	for (i = 0; i < maze->height; i++)
	{
		for (j = 0; j < maze->width; j++)
		{
			printf("%c", maze->cells[i][j]);
		}
		printf("\n");
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search and a manhattan distance heuristic
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
	if ( (col < 0) || (col >= maze->width) || (row < 0) || (row >= maze->height))
		return 0;
	
	if ( (maze->cells[row][col] != EMPTY) && (maze->cells[row][col] != START) )
	{
		if (maze->cells[row][col] == END)
			return 1;
		else
			return 0;
	}

	if (maze->cells[row][col] != START)
		maze->cells[row][col] = PATH;
	if ( (col == maze->startColumn - 1) && (row == maze->startRow) )
		maze->cells[row][col] = VISITED;

	int leftDist = abs(row - maze->endRow) + abs(col - 1 - maze->endColumn);
	int rightDist = abs(row - maze->endRow) + abs(col + 1 - maze->endColumn);
	int upDist = abs(row - 1 - maze->endRow) + abs(col - maze->endColumn);
	int downDist = abs(row + 1 - maze->endRow) + abs(col - maze->endColumn);

	int sum = upDist + downDist + rightDist + leftDist;
	int shortestDist = 1000;

	while (sum != -4)
	{
		shortestDist = 1000;
		if ( (leftDist < shortestDist) && (leftDist != -1) )
			shortestDist = leftDist;
		if ( (rightDist < shortestDist) && (rightDist != -1) )
			shortestDist = rightDist;
		if ( (upDist < shortestDist) && (upDist != -1) )
			shortestDist = upDist;
		if ( (downDist < shortestDist) && (downDist != -1) )
			shortestDist = downDist;

		if (shortestDist == leftDist)						// left
		{
			if(solveMazeManhattanDFS(maze, col-1, row) == 1)
				return 1;
			leftDist = -1;
		}

		
		if(shortestDist == rightDist)						// right
		{
			if(solveMazeManhattanDFS(maze, col+1, row) == 1)
				return 1;
			rightDist = -1;
		}

		
		if(shortestDist == upDist)							// up
		{
			if(solveMazeManhattanDFS(maze, col, row-1) == 1)
				return 1;
			upDist = -1;
		}
		

		if(shortestDist == downDist)						// down
		{
			if(solveMazeManhattanDFS(maze, col, row+1) == 1)
				return 1;
			downDist = -1;
		}

		sum = upDist + downDist + rightDist + leftDist;
	}

	if(maze->cells[row][col] != START)						// unmark  the solution 
		maze->cells[row][col] = VISITED;
	
	return 0;
}
