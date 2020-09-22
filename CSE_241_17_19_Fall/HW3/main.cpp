#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class ConnectFour{
public:
	ConnectFour();		//ConnectFour constructor #1
	ConnectFour(const int a);	//ConnectFour constructor #2
	int playGame();		// Standart Play game
	int playGameM();	// PlayGame for multiple objects
	int playM();		// Play for multiple objects
	int play();			// Standart play

	static int getCells();		// Getter for living cell counter
	static void setCells();		// Setter for living cell counter
	static int alive;			// The actual counter

	inline int getHeight() const{	// Inline getter for board height
		return height;
	}
	void setHeight(int newHeight);	// Setter for the board height

	int getWidth() const;			// Width getter
	void setWidth(int newWidth);	// Width setter

	int getType() const;			// Getter for game type C or P
	void setType(int gameType);		// Setter

	int getTurn() const;			// Who's turn? Getter
	void setTurn(int newTurn);		// Setter

	void fillBoard();				// Board init
	void drawBoard();				// Board print

	int playerOne();				// Player one makes a move
	int playerTwo();				// Player two makes a move 
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
	void fileLoad();				// Load a board
private:
	int height;				//Board height
	int width;				//Board width
	int gameType;			// P or C
	int turn;				// Who's turn?
	int winStyle;			// How did the winner win the game, left? right? right-diagonal? vertical?

	class Cell{
	public:
		Cell();					//Getter and Setters
		char getPosition() const;
		int getRow() const;
		char getInside() const;
		void setPosition(char newPosition);
		void setRow(int newRow);
		void setInside(char newInside);

	private:
		char position;			// a,b,c?
		int row;				// 0,1,2?
		char inside;			// X, O or .
	};
	vector<vector<Cell>> gameCells;
};
int ConnectFour::alive = 0;

// GETTER AND SETTERS

char ConnectFour::Cell::getPosition() const{
	return position;
}
int ConnectFour::Cell::getRow() const{
	return row;
}
char ConnectFour::Cell::getInside() const{
	return inside;
}
void ConnectFour::Cell::setPosition(char newPosition){
	position = newPosition;
}
void ConnectFour::Cell::setRow(int newRow){
	row = newRow;
}
void ConnectFour::Cell::setInside(char newInside){
	inside = newInside;
}
ConnectFour::Cell::Cell(){
	//blank
}
ConnectFour::ConnectFour(){
	setHeight(0);
}
ConnectFour::ConnectFour(const int a){
	setHeight(a);
}

void ConnectFour::setHeight(int newHeight){
	height = newHeight;
}
int ConnectFour::getWidth() const{
	return width;
}
void ConnectFour::setWidth(int newWidth){
	width = newWidth;
}
int ConnectFour::getType() const{
	return gameType;
}
void ConnectFour::setType(int newType){
	gameType = newType;
}
int ConnectFour::getTurn() const{
	return turn;
}
void ConnectFour::setTurn(int newTurn){
	turn = newTurn;
}
///////////////////////////////////////

int main(){
	char mo;
	int obj;
	ConnectFour M0, M1, M2, M3, M4;
	cout << "Welcome to Connect Four! Choose your Game Mode! M for MultiObject, S for SingleObject!" << endl;
	cin >> mo;
	if(mo == 'S' || mo == 's'){
		M0.playGame();
	}
	else if(mo == 'M' || mo == 'm'){
		cout << "1.object >> \n";
		M0.playGameM();		
		cout << "2.object >> \n";	
		M1.playGameM();
		cout << "3.object >> \n";
		M2.playGameM();
		cout << "4.object >> \n";
		M3.playGameM();
		cout << "5.object >> \n";
		M4.playGameM();
		while(1){
			cout << "Which object?" << endl;
			cin >> obj;
			switch(obj){
				case 1:
					M0.playM();
					break;
				case 2:
					M1.playM();
					break;
				case 3:
					M2.playM();
					break;
				case 4:
					M3.playM();
					break;
				case 5:
					M4.playM();
					break;
				default:
					cout << "Something went wrong. Try again." << endl;
					break;
			}
		}
	}
	else{
		cout << "Well sorry about that..." << endl;
	}
	return 0;

}
int ConnectFour::getCells(){
	return alive;
}
void ConnectFour::setCells(){
	alive = alive + 1;
}
int ConnectFour::playGame(){
	int height = 0, width = 0, turn = 1, control = 0;
	
	char game_type;

	cout << "Hello, to start the game; please enter the height of the board.";
	cin >> height;

	while(height < 4){		/* This condition checks for board size errors */
		cerr << "You entered a size out of bounds...The board size should be an integer bigger than 4, Try again!" << endl;
		cin >> height;
	}
	setHeight(height);

	cout << "Please enter the width of the board.";
	cin >> width;

	while(width < 4){		/* This condition checks for board size errors */
		cerr << "You entered a size out of bounds...The board size should be an integer bigger than 4, Try again!" << endl;
		cin >> width;
	}
	setWidth(width);

	cout << "Please type C for versus computer; P for two player game.";
	cin >> game_type;
	while(game_type != 'P' && game_type != 'C' && game_type != 'c' && game_type != 'p'){								/* This condition checks for game type errors */
		cerr << "You entered a wrong game type, Please type C for versus computer; P for two player game!" << endl;
		cin >> game_type;
	}
	setType(game_type);
	fillBoard();
	control = play();
	while(control ==-2){		// Player requested a load.
		fileLoad();
		control = play();
	}
	return 0;
}
int ConnectFour::playGameM(){
	int height = 0, width = 0, turn = 1, control = 0;

		cout << "Please enter the height of the board.";
		cin >> height;

		while(height < 4){		/* This condition checks for board size errors */
			cerr << "You entered a size out of bounds...The board size should be an integer bigger than 4, Try again!" << endl;
			cin >> height;
		}
		setHeight(height);

		cout << "Please enter the width of the board.";
		cin >> width;

		while(width < 4){		/* This condition checks for board size errors */
			cerr << "You entered a size out of bounds...The board size should be an integer bigger than 4, Try again!" << endl;
			cin >> width;
		}
		setWidth(width);
}

int ConnectFour::playM(){
	char game_type = getType();
	if(game_type != 'C' && game_type != 'c' && game_type != 'p' && game_type != 'P'){
		cout << "Please type C for versus computer; P for two player game.";
		cin >> game_type;
		while(game_type != 'P' && game_type != 'C' && game_type != 'c' && game_type != 'p'){								/* This condition checks for game type errors */
			cerr << "You entered a wrong game type, Please type C for versus computer; P for two player game!" << endl;
			cin >> game_type;
		}	
	setType(game_type);
	fillBoard();
	}	
	int winner_1 = 0, winner_2 = 0, last_i = 0, last_j = 0, turn = 1, coord_i = 0;							
	if(gameType == 'P' || gameType == 'p')													/* If game type is 1, then the game will be versus computer */ 								
	{	

		if(turn == 1){
			drawBoard();
			coord_i = playerOne();				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
			drawBoard();
			while(coord_i == -3 || coord_i == -4)
			coord_i = playerOne();
			while(coord_i == -1){	// Player requested a load.
				fileLoad();
				coord_i = playerOne();			
			}
			setCells();
			winner_1 = 	winControl('X', last_i, last_j); /* Called win_control for player 2 */
			if(winner_1 == 1){
				game_over('X', last_i, last_j);			/* End-game procedures */
				cout << "\nPlayer One VICTORY, the game will be closed. To play again, restart the game." << endl;
				return 0;
			}
			else{
				if(filledBoard()){						/* Checked if the board is filled with X and O's */
					cout << "There is no winner, this match is DRAW.";
					return 0;
				}	
			}
		}
		turn = 2;
		if(turn == 2){
			drawBoard();
			coord_i = playerTwo();
			drawBoard();
			while(coord_i == -1){
				fileLoad();
				coord_i = playerTwo();
			}
			setCells();
			winner_2 = winControl('O', last_i, last_j);			/* Win control for player 2 */
			if(winner_2 == 1){
				game_over('O', last_i, last_j);			/* End-game procedures */
				cout << "\nPlayer Two Victory, the game will be closed. To play again, restart the game." << endl;		/* End-game procedures */
				return 0;
			}
			if(filledBoard()){
				cout << "There is no winner, this match is DRAW.";
				return 0;
			}
			
		}	
		cout << "The current living Cells --> " << getCells() << endl;			
	}
	else{

		if(turn == 1){
			drawBoard();
			coord_i = playerOne();				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
			drawBoard();
			while(coord_i == -3 || coord_i == -4)
				coord_i = playerOne();
			while(coord_i == -1){	// Player requested a load.
				fileLoad();
				coord_i = playerOne();			
			}
			drawBoard();
			setCells();
			winner_1 = winControl('X', last_i, last_j); /* Called win_control for player 2 */
			if(winner_1 == 1){
				game_over('X', last_i, last_j);			/* End-game procedures */
				cout << "\nPlayer One VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;
				return 0;
			}
			else{
				if(filledBoard()){						/* Checked if the board is filled with X and O's */
					cout << "There is no winner, this match is DRAW.";
					return 0;
				}	
			}
		}	
		turn = 2;
		if(turn == 2){
			drawBoard();
			decider();	/* This function contains everything the computer needs. It returns the decided coordinates.(coord_i and coord_j) */
			/* This function takes the coordinates that decide_mech_block4 created and makes its move */
			drawBoard();
			cout << endl << "Computer made its move." << endl << endl;
			setCells();
			winner_2 = winControl('O', last_i, last_j);	/* win_control function checks the board for a winner, I used it for every player */
			if(winner_2 == 1){							
				game_over('O', last_i, last_j);				/* If there is a winner then I call game_over function, it does the end-game procedures */
				cout << "\nComputer VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;
				return 0;
			}
			if(filledBoard()){							/* I need to check the board after every move with board_is_filled function. It does what it says in its name */
				cout << "There is no winner, this match is DRAW.";
				return 0;
			}
		}	
		cout << "The current living Cells --> " << getCells() << endl;	
	}
	return 0;
}
int ConnectFour::play(){
	int winner_1 = 0, winner_2 = 0, last_i = 0, last_j = 0, turn = 1, coord_i = 0, alive = 0;							
	if(gameType == 'P' || gameType == 'p')													/* If game type is 1, then the game will be versus computer */ 								
	{
		while(1){	

			if(turn == 1){
				drawBoard();
				coord_i = playerOne();				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
				while(coord_i == -3 || coord_i == -4)
					coord_i = playerOne();
				if(coord_i == -1) return -2;
				setCells();
				winner_1 = 	winControl('X', last_i, last_j); /* Called win_control for player 2 */
				if(winner_1 == 1){
					game_over('X', last_i, last_j);			/* End-game procedures */
					cout << "\nPlayer One VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;
					drawBoard();
					return 0;
				}
				else{
					if(filledBoard()){						/* Checked if the board is filled with X and O's */
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}	
				}
			}
			turn = 2;
			if(turn == 2){
				drawBoard();
				coord_i = playerTwo();
				if(coord_i == -1) return -2;
				setCells();
				winner_2 = winControl('O', last_i, last_j);			/* Win control for player 2 */
				if(winner_2 == 1){
					game_over('O', last_i, last_j);			/* End-game procedures */
					cout << "\nPlayer Two Victory, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;		/* End-game procedures */
					drawBoard();
					break;
				}
				if(filledBoard()){
					cout << "There is no winner, this match is DRAW.";
					break;
				}
			
			}
			turn = 1;
			cout << "The current living Cells --> " << getCells() << endl;				
		}
	}
	else{
		while(1){	

			if(turn == 1){
				drawBoard();
				coord_i = playerOne();				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
				while(coord_i == -3 || coord_i == -4)
					coord_i = playerOne();
				if(coord_i == -1) return -2;
				setCells();
				winner_1 = winControl('X', last_i, last_j); /* Called win_control for player 2 */
				if(winner_1 == 1){
					game_over('X', last_i, last_j);			/* End-game procedures */
					cout << "\nPlayer One VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;
					drawBoard();
					return 0;
				}
				else{
					if(filledBoard()){						/* Checked if the board is filled with X and O's */
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}	
				}
			}	
			turn = 2;
			if(turn == 2){
				drawBoard();
				decider();	/* This function contains everything the computer needs. It returns the decided coordinates.(coord_i and coord_j) */
				/* This function takes the coordinates that decide_mech_block4 created and makes its move */
				cout << endl << "Computer made its move." << endl << endl;
				winner_2 = winControl('O', last_i, last_j);	/* win_control function checks the board for a winner, I used it for every player */
				setCells();
				if(winner_2 == 1){							
					game_over('O', last_i, last_j);				/* If there is a winner then I call game_over function, it does the end-game procedures */
					cout << "\nComputer VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;
					drawBoard();
					return 0;
				}
				if(filledBoard()){							/* I need to check the board after every move with board_is_filled function. It does what it says in its name */
					cout << "There is no winner, this match is DRAW.";
					break;
				}
			}
			turn = 1;
			cout << "The current living Cells --> " << getCells() << endl;		
		}
	}
	return 0;
}
void ConnectFour::fillBoard(){
	int i, j;
	gameCells.resize(height);
	for(i = 0; i < height; ++i)
		gameCells[i].resize(width);

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			gameCells[i][j].setRow(i);
			gameCells[i][j].setPosition('a'+j);
			gameCells[i][j].setInside('.');
		}
	}
}
void ConnectFour::drawBoard(){
	int i, j;
	for(i = 0; i < width; i++)
		cout << (char)('A'+i) << " ";
	cout << endl;

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			cout << gameCells[i][j].getInside() << " ";;
		}
		cout << endl;
	}
}
int ConnectFour::playerOne(){
	int i = 0, j = 0, counter = 0, real_loc = 0, coord_i = 1;
	string locate;
	cout << "Player One! Make your move!\n";
	cin >> locate;	

	if(locate == "SAVE"){
		fileSave();
		return coord_i;
	}
	else if(locate == "LOAD"){
		return -1;
	}
	
	else{

		real_loc = locate[0] - 'a';					/* The location trasformed to use in array, like a = 0, b = 1 */

		if(real_loc < 0 || real_loc > 26){			/* Checks for Caps and turnes them into lower case. User friendly. */
			real_loc += 'a' - 'A';
		}
		if(gameCells[0][real_loc].getInside() != '.'){
			cerr << "That column is full. Please choose another one." << endl;
			return -3;
		}
		for(i = height-1; i >= 0; --i)
		{
			if(gameCells[i][real_loc].getInside() == '.' && counter == 0)			/* Scans the selected column bottom to top and puts an X to the first dot. */
			{		
				gameCells[i][real_loc].setInside('X');
				counter++;
				break;		
			}
			coord_i++;
		}
		coord_i = height - coord_i;
		return coord_i;
	}	
}
int ConnectFour::playerTwo(){
	int i = 0, j = 0, counter = 0, real_loc = 0, coord_i = 1;
	string locate;
	cout << "Player Two's TURN! Make your move!\n";
	cin >> locate;	

	if(locate == "SAVE"){
		fileSave();
		return coord_i;
	}
	else if(locate == "LOAD"){
		return -1;
	}
	
	else{

		real_loc = locate[0] - 'a';					/* The location trasformed to use in array, like a = 0, b = 1 */

		if(real_loc < 0 || real_loc > 26){			/* Checks for Caps and turnes them into lower case. User friendly. */
			real_loc += 'a' - 'A';
		}
		if(gameCells[0][real_loc].getInside() != '.'){
			cerr << "That column is full. Please choose another one." << endl;
			return -3;
		}
		for(i = height-1; i >= 0; --i)
		{
			if(gameCells[i][real_loc].getInside() == '.' && counter == 0)			/* Scans the selected column bottom to top and puts an X to the first dot. */
			{		
				gameCells[i][real_loc].setInside('O');
				counter++;
				break;		
			}
			coord_i++;
		}
		coord_i = height - coord_i;
		return coord_i;
	}	
}
int ConnectFour::winControl(char term, int &last_i, int &last_j){
	int i = 0, j = 0, result = 0;

	for(i = 0; i < height; ++i){
		for(j = 3; j < width; ++j){
			result = cont_left(term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				winStyle = 1;
				return 1;
			}
		}
	}
	
	result = 0;
	for(i = 0; i < height -3; ++i){
		for(j = 3; j < width; ++j){
			result = cont_bottom_left(term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				winStyle = 2;
				return 1;
			}
		}
	}
	
	result = 0;
	for(i = 0; i < height-3; ++i){
		for(j = 0; j < width; ++j){
			result = cont_bottom(term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				winStyle = 3;
				return 1;
			}
		}
	}
	
	result = 0;
	for(i = 0; i < height-3; ++i){
		for(j = 0; j < width-3; ++j){
			result = cont_bottom_right(term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				winStyle = 4;
				return 1;
			}
		}
	}

	result = 0;
	for(i = 0; i < height; ++i){
		for(j = 0; j < width-3; ++j){
			result = cont_right(term, i, j);
			if(result == 3){
				last_i = i;
				last_j = j;
				winStyle = 5;
				return 1;
			}
		}
	}
	return 0;	
}
int ConnectFour::cont_left(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameCells[coord_i][coord_j].getInside() == term){	
		if(gameCells[coord_i][coord_j-1].getInside() == term){
			result += 1;
			if(gameCells[coord_i][coord_j-2].getInside() == term){
				result += 1;
				if(gameCells[coord_i][coord_j-3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int ConnectFour::cont_bottom_left(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameCells[coord_i][coord_j].getInside() == term){	
		if(gameCells[coord_i+1][coord_j-1].getInside() == term){
			result += 1;
			if(gameCells[coord_i+2][coord_j-2].getInside() == term){
				result += 1;
				if(gameCells[coord_i+3][coord_j-3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int ConnectFour::cont_bottom(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameCells[coord_i][coord_j].getInside() == term){	
		if(gameCells[coord_i+1][coord_j].getInside() == term){
			result += 1;
			if(gameCells[coord_i+2][coord_j].getInside() == term){
				result += 1;
				if(gameCells[coord_i+3][coord_j].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}	
}
int ConnectFour::cont_bottom_right(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameCells[coord_i][coord_j].getInside() == term){	
		if(gameCells[coord_i+1][coord_j+1].getInside() == term){
			result += 1;
			if(gameCells[coord_i+2][coord_j+2].getInside() == term){
				result += 1;
				if(gameCells[coord_i+3][coord_j+3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int ConnectFour::cont_right(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameCells[coord_i][coord_j].getInside() == term){	
		if(gameCells[coord_i][coord_j+1].getInside() == term){
			result += 1;
			if(gameCells[coord_i][coord_j+2].getInside() == term){
				result += 1;
				if(gameCells[coord_i][coord_j+3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
void ConnectFour::game_over(int term, int last_i, int last_j){
	int lower = 0, i = 0, j = 0;


	lower = 'a' - 'A';	

	switch (winStyle) {
		case 1:																		/* Left */
			gameCells[last_i][last_j].setInside(term+lower);
			gameCells[last_i][last_j-1].setInside(term+lower);
			gameCells[last_i][last_j-2].setInside(term+lower);
			gameCells[last_i][last_j-3].setInside(term+lower);
			break;
		case 2:																		/* Bottom - Left */
			gameCells[last_i][last_j].setInside(term+lower);
			gameCells[last_i+1][last_j-1].setInside(term+lower);
			gameCells[last_i+2][last_j-2].setInside(term+lower);
			gameCells[last_i+2][last_j-2].setInside(term+lower);
			break;			
		case 3:																		/* Bottom */
			gameCells[last_i][last_j].setInside(term+lower);
			gameCells[last_i+1][last_j].setInside(term+lower);
			gameCells[last_i+2][last_j].setInside(term+lower);
			gameCells[last_i+3][last_j].setInside(term+lower);
			break;
		case 4:																		/* Bottom - Right */
			gameCells[last_i][last_j].setInside(term+lower);
			gameCells[last_i+1][last_j+1].setInside(term+lower);
			gameCells[last_i+2][last_j+2].setInside(term+lower);
			gameCells[last_i+3][last_j+3].setInside(term+lower);
			break;		
		case 5:																		/* Right */
			gameCells[last_i][last_j].setInside(term+lower);
			gameCells[last_i][last_j+1].setInside(term+lower);
			gameCells[last_i][last_j+2].setInside(term+lower);
			gameCells[last_i][last_j+3].setInside(term+lower);
			break;
	}
																					/* And turnes the X(or 0, depended on the term variable)'s to lower case just to make them outstanding */


}
int ConnectFour::filledBoard(){
	int i = 0, j = 0;
	
	for(i = 0; i < height + 1; i++)		/* Fills the board with dots */
	{
		for(j = 0; j < width; j++)
		{
			if(gameCells[i][j].getInside() == '.')
				return 0;
		}
	}
	return 1;
}
void ConnectFour::decider(){

int i = 0, j = 0, result = 0, result2 = 0, temp_i = 0, temp_j = 0;
char term = 'X', term2 = 'O';

	for(i = 0; i < height-3; ++i){
		for(j = 3; j < width; ++j){
			if(gameCells[i + 1][j - 1].getInside() == term2){
				result += 1;
				if(gameCells[i + 2][j - 2].getInside() == term2){
					result+= 1;
					if(gameCells[i + 3][j - 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameCells[i + 1][j - 1].getInside() == term){
				result2+= 1;
				if(gameCells[i + 2][j - 2].getInside() == term){
					result2+= 1;
					if(gameCells[i + 3][j - 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameCells[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height; ++i){
		for(j = 3; j < width; ++j){

			if(gameCells[i][j - 1].getInside() == term2){
				result += 1;
				if(gameCells[i][j - 2].getInside() == term2){
					result+= 1;
					if(gameCells[i][j - 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameCells[i][j - 1].getInside() == term){
				result2+= 1;
				if(gameCells[i][j - 2].getInside() == term){
					result2+= 1;
					if(gameCells[i][j - 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameCells[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height-3; ++i){
		for(j = 0; j < width-3; ++j){

			if(gameCells[i + 1][j + 1].getInside() == term2){
				result += 1;
				if(gameCells[i + 2][j + 2].getInside() == term2){
					result+= 1;
					if(gameCells[i + 3][j + 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameCells[i + 1][j + 1].getInside() == term){
				result2+= 1;
				if(gameCells[i + 2][j + 2].getInside() == term){
					result2+= 1;
					if(gameCells[i + 3][j + 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameCells[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height-3; ++i){
		for(j = 0; j < width; ++j){

			if(gameCells[i + 1][j].getInside() == term2){
				result += 1;
				if(gameCells[i + 2][j].getInside() == term2){
					result+= 1;
					if(gameCells[i + 3][j].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameCells[i + 1][j].getInside() == term){
				result2+= 1;
				if(gameCells[i + 2][j].getInside() == term){
					result2+= 1;
					if(gameCells[i + 3][j].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameCells[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height; ++i){
		for(j = 0; j < width-3; ++j){

			if(gameCells[i][j + 1].getInside() == term2){
				result += 1;
				if(gameCells[i][j + 2].getInside() == term2){
					result+= 1;
					if(gameCells[i][j + 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameCells[i][j + 1].getInside() == term){
				result2+= 1;
				if(gameCells[i][j + 2].getInside() == term){
					result2+= 1;
					if(gameCells[i][j + 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameCells[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = height-1; i >= 0; --i){
		cout << "i = " << i << endl;
		for(j = width - 1; j >= 0; --j){
			cout << "j = " << j << endl;
			if(legality(i, j)){
				cout << "Before!" << endl;
				gameCells[i][j].setInside('O');
				cout << "After!" << endl; 
				return;
			}

		}
	}
}
int ConnectFour::legality(int coord_i, int coord_j){
	if(coord_i < height && coord_j < width && gameCells[coord_i][coord_j].getInside() == '.'){
		if(coord_i + 1 != height){
			if(gameCells[coord_i + 1][coord_j].getInside() != '.'){
				return 1;
			}
		}
		else{
			return 1;		
		}
	}
	return 0;
}
void ConnectFour::fileSave(){
	string filename;
	cin >> filename;
	ofstream inner(filename);
	int i = 0, j = 0, tturn = 0, hheight = 0, wwidth = 0;
	char game_mode;

	tturn = getTurn();
	hheight = getHeight();
	wwidth = getWidth();
	game_mode = getType();

	inner << game_mode << '\n' << tturn << '\n' << hheight << '\n' << wwidth << '\n';  	/* Writes the needed information to the file */

	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			inner << gameCells[i][j].getInside();				/* X and O's */
		}
		inner << "\n";
	}
	inner.close();	
}
void ConnectFour::fileLoad(){
	string filename;
	cin >> filename;
	ifstream outer(filename);
	if(outer.fail()){
		cerr << "File not found." << endl;	
		exit(1);
	}
	int i = 0, j = 0, tturn = 0, hheight = 0, wwidth = 0, turn = 0;
	char game_mode, temp;
	outer >> game_mode >> tturn >> hheight >> wwidth;			/* Information about the game */

	setTurn(tturn);
	setType(game_mode);
	setHeight(hheight);
	setWidth(wwidth);

	for(i=0; i<height; i++)
		for(j=0; j<width; j++){
			outer >> temp;	
			gameCells[i][j].setInside(temp);			/* X and O 's */
		}
	outer.close();
}
