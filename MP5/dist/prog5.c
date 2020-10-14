/* The prog5.c file contains the functions for the game. set_seed takes an input value and uses the seed for generating random numbers. Only integers are allowed for it.
start_game generates four random numbers and puts them in their respective variables. It then sets the guess number to keep try of how many guesses have been made.
make_guess checks if four integers between 0 and 7 were put in and will then determine how many
perfect matches and mismatches there are.
*/

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
	int seed; //seed variable
	char post[2]; //used to check if non-integer was put in

	if ((sscanf(seed_str, "%d%1s", &seed, post)) == 1)
	{
		srand(seed); //if integer was put in, seed used to generate random numbers.
		return 1; //if integer was put in, will return 1.
	}

	else
	{
		printf("set_seed: invalid seed\n"); //if entered seed was invalid
		return 0; //print messaage and return 0.
	}

//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
   
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
	solution1 = rand()%8; //solution1 = random # from 0-7
	solution2 = rand()%8; //solution2 = random # from 0-7
	solution3 = rand()%8; //solution3 = random # from 0-7
	solution4 = rand()%8; //solution4 = random # from 0-7

	*one = solution1; //stores solution1 at address of pointer 1
	*two = solution2; //stores solution2 at address of pointer 2
	*three = solution3; //stores solution3 at address of pointer 3
	*four = solution4; //stores solution4 at address of pointer 4

	guess_number = 1; //sets # of guesses for game

	return;
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
	int guessOne, guessTwo, guessThree, guessFour;
	int pairOne = 0, pairTwo = 0, pairThree = 0, pairFour = 0;
	int oneFound = 0, twoFound = 0, threeFound = 0, fourFound = 0;
	int perfMatch = 0;	
	int misMatch = 0;
	char post[2];

	if ((sscanf(guess_str, "%d%d%d%d%1s", &guessOne, &guessTwo, &guessThree, &guessFour, post) == 4) && ( (guessOne >= 0 && guessOne <= 7) && (guessTwo >= 0 && guessTwo <= 7) && (guessThree >= 0 && guessThree <= 7) && (guessFour >= 0 && guessFour <= 7) ))
	{
	//If all inputs are valid (integers between 0 and 7) then puts guessed values at 
	//addresses of pointer variables
		*one = guessOne;
		*two = guessTwo;
		*three = guessThree;
		*four = guessFour;

//check if perfect matches first
	if (guessOne == solution1)
	{
		perfMatch++;
		pairOne++;
		oneFound++;
	}

	if (guessTwo == solution2)
	{
		perfMatch++;
		pairTwo++;
		twoFound++;
	}

	if (guessThree == solution3)
	{
		perfMatch++;
		pairThree++;
		threeFound++;
	}

	if (guessFour == solution4)
	{
		perfMatch++;
		pairFour++;
		fourFound++;
	}		

//Check for misplaced matches

	//check first guess
	if (guessOne == solution2 && (pairTwo != 1) && (oneFound != 1))
	{
		misMatch++;
		pairTwo++;
	}

	else if (guessOne == solution3 && (pairThree != 1) && (oneFound != 1))
	{
		misMatch++;
		pairThree++;
	}

	else if (guessOne == solution4 && (pairFour != 1) && (oneFound != 1))
	{
		misMatch++;
		pairFour++;
	}

	//check second guess
	if (guessTwo == solution1 && (pairOne != 1) && (twoFound != 1))
	{
		misMatch++;
		pairOne++;
	}

	else if (guessTwo == solution3 && (pairThree != 1) && (twoFound != 1))
	{
		misMatch++;
		pairThree++;
	}

	else if (guessTwo == solution4 && (pairFour != 1) && (twoFound != 1))
	{
		misMatch++;
		pairFour++;
	}

	//check third guess
	if (guessThree == solution1 && (pairOne != 1) && (threeFound != 1))
	{
		misMatch++;
		pairOne++;
	}

	else if (guessThree == solution2 && (pairTwo != 1) && (threeFound != 1))
	{
		misMatch++;
		pairTwo++;
	}

	else if (guessThree == solution4 && (pairFour != 1) && (threeFound != 1))
	{
		misMatch++;
		pairFour++;
	}

	//check fourth guess
	if (guessFour == solution1 && (pairOne != 1) && (fourFound != 1))
	{
		misMatch++;
		pairOne++;
	}

	else if (guessFour == solution2 && (pairTwo != 1) && (fourFound != 1))
	{
		misMatch++;
		pairTwo++;
	}

	else if (guessFour == solution3 && (pairThree != 1) && (fourFound != 1))
	{
		misMatch++;
		pairThree++;
	}


		printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfMatch, misMatch);
		guess_number++;

		return 1;
	}

	else
	{
		printf("make_guess: invalid guess\n");
		return 0;
	}

//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    return 1;
}


