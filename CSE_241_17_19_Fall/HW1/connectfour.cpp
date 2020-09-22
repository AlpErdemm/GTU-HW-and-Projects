#include <iostream>
#include "connectfour.h"

using namespace std;

int connectfour(char board[][20])
{
    
	int board_size = 0, game_type = 0, result = 0, coord_i = 0, coord_j = 0, winner_1 = 0, 
		winner_2 = 0, type_of_win = 0, last_i = 0, last_j = 0, raw_j = 0;
	


	cout << "Hello, to start the game; please enter a board size. The board size should be an even integer(4 - 20)";
	cin >> board_size;

	if(board_size < 4 || board_size > 20 || board_size % 2 == 1){		/* This condition checks for board size errors */
		cout << "You entered a size out of bounds.";
		return 0;
	}
	cout << "Please type 1 for versus computer; 2 for two player game.";
	cin >> game_type;
	if(game_type != 1 && game_type != 2){								/* This condition checks for game type errors */
		cout << "You entered a wrong game type";
		return 0;
	}
	
	fill_board(board, board_size);										/* This function fills the dimensional array with dots */
 	draw_board(board, board_size);										/* This function prints the dimensional array on the screen with cout */

	if(game_type == 1)													/* If game type is 1, then the game will be versus computer */ 								
	{
		while(1){									
			decider(board, board_size, 'X', coord_i, coord_j);	/* This function contains everything the computer needs. It returns the decided coordinates.(coord_i and coord_j) */
			computer(board, board_size, coord_i, coord_j);					/* This function takes the coordinates that decide_mech_block4 created and makes its move */
			cout << endl << "Computer made its move." << endl << endl;
			winner_2 = win_control(board, board_size, 'X', last_i, last_j, type_of_win);	/* win_control function checks the board for a winner, I used it for every player */
			draw_board(board, board_size);
			if(winner_2 == 1){							
				game_over(board, board_size, 'X', last_i, last_j, type_of_win);				/* If there is a winner then I call game_over function, it does the end-game procedures */
				draw_board(board, board_size);
				cout << "Computer VICTORY, the game will be closed. To play again, restart the game." << endl;
				return 0;
			}
			if(board_is_filled(board, board_size)){							/* I need to check the board after every move with board_is_filled function. It does what it says in its name */
				cout << "There is no winner, this match is DRAW.";
				break;
			}
			else{
				coord_i = player_2(board, board_size, coord_j);				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
				if(coord_j < 0 || coord_j > board_size - 1)
				{
					cout << "Wrong location, the game is going to close" << endl;		/* Checks if the user typed something wrong */
					return 0;
				}
				winner_1 = win_control(board, board_size, 'O', last_i, last_j, type_of_win); /* Called win_control for player 2 */
				draw_board(board, board_size);
				if(winner_1 == 1){
					game_over(board, board_size, 'O', last_i, last_j, type_of_win);			/* End-game procedures */
					draw_board(board, board_size);
					cout << "Player One VICTORY, the game will be closed. To play again, restart the game." << endl;
					return 0;
				}
				else{
					if(board_is_filled(board, board_size)){						/* Checked if the board is filled with X and O's */
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}
				}			
			}
		}
	}
	else						/* Else is for two player game. */
	{
		while(1)
		{				
			coord_i = player_1(board, board_size, coord_j);  	/* Player 1's turn. */
			if(coord_j < 0 || coord_j > board_size - 1)
			{
				cout << "Wrong location, the game is going to close" << endl;			/* Checks if the user typed something wrong */
				return 0;
			}
			draw_board(board, board_size);
			winner_1 = win_control(board, board_size, 'X', last_i, last_j, type_of_win);		/* Win control for player 1 */
			if(winner_1 == 1){
				game_over(board, board_size, 'X', last_i, last_j, type_of_win);			/* End-game procedures */
				draw_board(board, board_size);
				cout << "Player One VICTORY, the game will be closed. To play again, restart the game." << endl;
				break;
			}
			else{
				if(board_is_filled(board, board_size)){
					cout << "There is no winner, this match is DRAW.";
					break;
				}
				else{
					coord_i = player_2(board, board_size, coord_j);
					if(coord_j < 0 || coord_j > board_size - 1)
					{
						cout << "Wrong location, the game is going to close" << endl;			/* Checks if the user typed something wrong */
						return 0;
					}
					draw_board(board, board_size);
					winner_2 = win_control(board, board_size, 'O', last_i, last_j, type_of_win);			/* Win control for player 2 */
					if(winner_2 == 1){
						game_over(board, board_size, 'O', last_i, last_j, type_of_win);
						draw_board(board, board_size);
						cout << "Player Two Victory, the game will be closed. To play again, restart the game." << endl;		/* End-game procedures */
						break;
					}
					if(board_is_filled(board, board_size)){
						cout << "There is no winner, this match is DRAW.";
						break;
					}
				}
			}
		}
	}

	return 0;
}

void draw_board(char board[][20], int size)		/* Simply prints the board on the screen */
{
	int i = 0, j = 0;

	for(i = 0; i < size+1; i++)
	{
		for(j = 0; j < size; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void fill_board(char board[][20], int size)		/* Writes a,b,c... to the first line and filles the other lines with dots */
{
	int i = 0, j = 0;
	char temp = 'a';

	for(i = 0; i < size+1; i++)
	{
		for(j = 0; j < size; j++)
		{
			if(i == 0)
			{
				board[i][j] = temp;
				temp++;
			}
			else
			{

				board[i][j] = '.';
			}	
		}
	}	
}

int player_1(char board[][20], int size, int & coord_j)
{
	int i =0, counter = 0, real_loc = 0, coord_i = 1;
	char locate;

	cout << "Player One's turn\n\n" << "Please select a location.(a, b, c, etc.)";
	cin >> locate;																		/* Requesting a character from the user */
	
	real_loc = locate - 'a';					/* The location trasformed to use in array, like a = 0, b = 1 */
	coord_j = real_loc;

	if(coord_j < 0 || coord_j > 19){			/* Checks for Caps and turnes them into lower case. User friendly. */
		coord_j += 'a' - 'A';
		real_loc += 'a' - 'A';
	}

	for(i = size; i > 0; i--)
	{
		if(board[i][real_loc] == '.' && counter == 0)			/* Scans the selected column bottom to top and puts an X to the first dot. */
		{		
			board[i][real_loc] = 'X';
			counter++;
			break;		
		}
		coord_i++;
	}
	coord_i = size - coord_i;
	return coord_i;
}

int player_2(char board[][20], int size, int & coord_j)
{
	int i =0, counter = 0, real_loc = 0, coord_i = 1;
	char locate;
	cout << "Player Two's turn\n\n" << "Please select a location.(a, b, c, etc.)";			
	cin >> locate;																		/* Requesting a character from the user */
	
			
	real_loc = locate - 'a';				/* The location trasformed to use in array, like a = 0, b = 1 */
	coord_j = real_loc;

	if(coord_j < 0 || coord_j > 19){		/* Checks for Caps and turnes them into lower case. User friendly. */
		coord_j += 'a' - 'A';
		real_loc += 'a' - 'A';
	}

	for(i = size; i > 0; i--)
	{
		if(board[i][real_loc] == '.' && counter == 0)			/* Scans the selected column bottom to top and puts an O to the first dot. */
		{		
			board[i][real_loc] = 'O';
			counter++;
			break;		
		}
		coord_i++;
	}
	coord_i = size - coord_i;
	return coord_i;
}

int win_control(char board[][20], int size, char term, int &last_i, int &last_j, int &type_of_win)		/* This function uses some sub-functions to find winner, holds the winning type (left, bottom_right etc.)
																											It returns 1 if the subs finds a winner */
{
	int i = 0, j = 0, result = 0;

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			result = cont_left(board, size, term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				type_of_win = 1;
				return 1;
			}
			result = 0;
			result = cont_bottom_left(board, size, term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				type_of_win = 2;
				return 1;
			}
			result = 0;
			result = cont_bottom(board, size, term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				type_of_win = 3;
				return 1;
			}
			result = 0;
			result = cont_bottom_right(board, size, term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				type_of_win = 4;
				return 1;
			}
			result = 0;
			result = cont_right(board, size, term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				type_of_win = 5;
				return 1;
			}
		}
	}
	return 0;
}
int cont_left(char board[][20], int size, char term, int coord_i, int coord_j)	/* Looks left for three X(or 0) if the current point is X(or O) */
{
	int result = 0;
	if(board[coord_i][coord_j] == term){	
		if(board[coord_i][coord_j - 1] == term){
			result += 1;
			if(board[coord_i][coord_j - 2] == term){
				result += 1;
				if(board[coord_i][coord_j - 3] == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int cont_bottom_left(char board[][20], int size, char term, int coord_i, int coord_j)	/* Looks bottom-left for three X(or 0) if the current point is X(or O) */
{
	int result = 0;
	if(board[coord_i][coord_j] == term){	
		if(board[coord_i + 1][coord_j - 1] == term){
			result += 1;
			if(board[coord_i + 2][coord_j - 2] == term){
				result += 1;
				if(board[coord_i + 3][coord_j - 3] == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int cont_bottom(char board[][20], int size, char term, int coord_i, int coord_j)	/* Looks bottom for three X(or 0) if the current point is X(or O) */
{
	int result = 0;
	if(board[coord_i][coord_j] == term){	
		if(board[coord_i + 1][coord_j] == term){
			result += 1;
			if(board[coord_i + 2][coord_j] == term){
				result += 1;
				if(board[coord_i + 3][coord_j] == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int cont_bottom_right(char board[][20], int size, char term, int coord_i, int coord_j)	/* Looks bottom-right for three X(or 0) if the current point is X(or O) */
{
	int result = 0;
	if(board[coord_i][coord_j] == term){	
		if(board[coord_i + 1][coord_j + 1] == term){
			result += 1;
			if(board[coord_i + 2][coord_j + 2] == term){
				result += 1;
				if(board[coord_i + 3][coord_j + 3] == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int cont_right(char board[][20], int size, char term, int coord_i, int coord_j)	/* Looks right for three X(or 0) if the current point is X(or O) */
{
	int result = 0;
	if(board[coord_i][coord_j] == term){	
		if(board[coord_i][coord_j + 1] == term){
			result += 1;
			if(board[coord_i][coord_j + 2] == term){
				result += 1;
				if(board[coord_i][coord_j + 3] == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int board_is_filled(char board[][20], int size)
{
	int i = 0, j = 0;
	
	for(i = 1; i < size + 1; i++)		/* Fills the board with dots */
	{
		for(j = 0; j < size; j++)
		{
			if(board[i][j] == '.')
				return 0;
		}
	}
	return 1;
}
void computer(char board[][20], int size, int coord_i, int coord_j)		/* Takes a coordinate and puts X */
{
	board[coord_i][coord_j] = 'X';
}

void decider(char board[][20], int size, char term, int &coord_i, int &coord_j)
{
	int i = 0, j = 0, temp_i = 0, temp_j = 0, result = 0;
	char term2 = 'O';
	

// Block your opponents finishing move -------------------------------

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j - 1] == term2){
				result += 1;
				if(board[i + 2][j - 2] == term2){
					result += 1;
					if(board[i + 3][j - 3] == term2){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}
			if(result >= 2 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i][j - 1] == term2){
				result += 1;
				if(board[i][j - 2] == term2){
					result += 1;
					if(board[i][j - 3] == term2){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}			
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j + 1] == term2){
				result += 1;
				if(board[i + 2][j + 2] == term2){
					result += 1;
					if(board[i + 3][j + 3] == term2){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j] == term2){
				result += 1;
				if(board[i + 2][j] == term2){
					result += 1;
					if(board[i + 3][j] == term2){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}

			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i][j + 1] == term2){
				result += 1;
				if(board[i][j + 2] == term2){
					result += 1;
					if(board[i][j + 3] == term2){
						result += 1;
						temp_i = i;
						temp_j = j;

					}
				}

			}
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}

		}
	}



// End of the block ------------------------------------------------
// Put fourth 'O' to finish the game  -----------------------------

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i][j - 1] == term){
				result += 1;
				if(board[i][j - 2] == term){
					result += 1;
					if(board[i][j - 3] == term){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}			
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j - 1] == term){
				result += 1;
				if(board[i + 2][j - 2] == term){
					result += 1;
					if(board[i + 3][j - 3] == term){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j] == term){
				result += 1;
				if(board[i + 2][j] == term){
					result += 1;
					if(board[i + 3][j] == term){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}

			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j + 1] == term){
				result += 1;
				if(board[i + 2][j + 2] == term){
					result += 1;
					if(board[i + 3][j + 3] == term){
						result += 1;
						temp_i = i;
						temp_j = j;
					}
				}

			}
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i][j + 1] == term){
				result += 1;
				if(board[i][j + 2] == term){
					result += 1;
					if(board[i][j + 3] == term){
						result += 1;
						temp_i = i;
						temp_j = j;

					}
				}

			}
			if(result == 3 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}

		}
	}

//  End of the block  -----------------------------------------------------------



// Making the AI more comfortable  -------------------------------

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j - 1] == term2){
				result += 1;
				if(board[i + 2][j - 2] == term2){
					result += 1;
					temp_i = i;
					temp_j = j;
				}

			}
			if(result == 2 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i][j - 1] == term2){
				result += 1;
				if(board[i][j - 2] == term2){
					result += 1;
					temp_i = i;
					temp_j = j;
				}

			}			
			if(result == 2 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}

	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i + 1][j + 1] == term2){
				result += 1;
				if(board[i + 2][j + 2] == term2){
					result += 1;
					temp_i = i;
					temp_j = j;
				}

			}
			if(result == 2 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}
			result = 0;
		}
	}



	for(i = 1; i <= size; ++i){
		for(j = 0; j < size; ++j){
			if(board[i][j + 1] == term2){
				result += 1;
				if(board[i][j + 2] == term2){
					result += 1;
					temp_i = i;
					temp_j = j;

		
				}

			}
			if(result == 2 && legality(board, size, temp_i, temp_j)){
				coord_i = temp_i;
				coord_j = temp_j;
				return;
			}

		}
	}



// End of the block ------------------------------------------------
	//---------------------------------------------------------------------------

	for(i = size; i > 0; --i){
		for(j = size - 1; j >= 0; --j){
			if(legality(board, size, i, j)){
				coord_i = i;
				coord_j = j;
				return;
			}

		}
	}






}

int legality(char board[][20], int size, int coord_i, int coord_j)		/* Legality controller for coordinates */
{
	if(coord_i <= size && coord_j < size && board[coord_i][coord_j] == '.' && board[coord_i + 1][coord_j] != '.')
		return 1;
	return 0;
}

void game_over(char board[][20], int size, int term, int last_i, int last_j, int type_of_win)	/* Takes the type of win  from win_control function and draws a lines from the coordinates through the 
																									direction(type) it has taken */
{
	int lower = 0, i = 0, j = 0, result = 0;;

	lower = 'a' - 'A';

	switch (type_of_win) {
		case 1:																		/* Left */
			board[last_i][last_j] = term + lower;
			board[last_i][last_j - 1] = term + lower;
			board[last_i][last_j - 2] = term + lower;
			board[last_i][last_j - 3] = term + lower;
			break;
		case 2:																		/* Bottom - Left */
			board[last_i][last_j] = term + lower;
			board[last_i + 1][last_j - 1] = term + lower;
			board[last_i + 2][last_j - 2] = term + lower;
			board[last_i + 3][last_j - 3] = term + lower;
			break;			
		case 3:																		/* Bottom */
			board[last_i][last_j] = term + lower;
			board[last_i + 1][last_j] = term + lower;
			board[last_i + 2][last_j] = term + lower;
			board[last_i + 3][last_j] = term + lower;
			break;
		case 4:																		/* Bottom - Right */
			board[last_i][last_j] = term + lower;
			board[last_i + 1][last_j + 1] = term + lower;
			board[last_i + 2][last_j + 2] = term + lower;
			board[last_i + 3][last_j + 3] = term + lower;
			break;		
		case 5:																		/* Right */
			board[last_i][last_j] = term + lower;
			board[last_i][last_j + 1] = term + lower;
			board[last_i][last_j + 2] = term + lower;
			board[last_i][last_j + 3] = term + lower;
			break;
	}
																					/* And turnes the X(or 0, depended on the term variable)'s to lower case just to make them outstanding */


}

