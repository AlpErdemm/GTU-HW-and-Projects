#ifndef CFABSTRACT_H
#define CFABSTRACT_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "cell.h"

using namespace std;

namespace CFAbstract
{
	class ConnectFourAbstract{
	public:
		void undoFunction();
		void playGame();		// Single object main function
		int gameSettings();			// Single object game's loop caller
		void gameLoop();
		int Loop();				// The actual loop
		void play();			// Computer move maker
		int play(string locate);// User move maker
		inline void setObjType(char typ){
			objectType = typ;
		}
		inline char getObjType(){
			return objectType;
		}

		inline int getHeight() const{	// Inline getter for board height
			return height;
		}
		void incCOUNT();
		void decCOUNT();
		void setHeight(int newHeight);	// Setter for the board height

		int getWidth() const;			// Width getter
		void setWidth(int newWidth);	// Width setter

		int getType() const;			// Getter for game type C or P
		void setType(int gameType);		// Setter

		int getTurn() const;			// Who's turn? Getter
		void setTurn(int newTurn);		// Setter

					// Load a board
	protected:
		void fillBoard();				// Board init
		void drawBoard();				// Board print
		Cell ** gameBoard;
		int globCOUNT;
		string getMove();				// Helper functin for void play() 
		int winControl(char term, int &last_i, int &last_j);		// Is there a winner?

		int cont_left(char term, int coord_i, int coord_j);			// Helper functions from HW2
		int cont_bottom_left(char term, int coord_i, int coord_j);
		int cont_bottom(char term, int coord_i, int coord_j);
		int cont_bottom_right(char term, int coord_i, int coord_j);
		int cont_right(char term, int coord_i, int coord_j);

		void game_over(int term, int last_i, int last_j);		// End-game procedures
		int filledBoard();					// Board is filled, game is draw
		void decider();						// Computer AI
		int legality(int coord_i, int coord_j);			// Move legality checker
		void fileSave();				// Save a board
		void fileLoad();
		char objectType;
		int height;				//Board height
		int width;				//Board width
		int gameType;			// P or C
		int turn;				// Who's turn?
		int winStyle;			// How did the winner win the game, left? right? right-diagonal? vertical?


	};
}
#endif
