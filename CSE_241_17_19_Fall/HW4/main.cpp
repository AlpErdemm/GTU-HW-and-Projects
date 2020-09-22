#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ConnectFour{
public:
	ConnectFour();		//ConnectFour 5x5 constructor
	ConnectFour(const int newHeight, const int newWidth);	//ConnectFour newHeight x newWidth constructor
	ConnectFour(string filename);		//ConnectFour constructor that takes a board file
	void playGame();		// Single object main function
	int gameLoop();			// Single object game's loop caller
	int Loop();				// The actual loop
	int playGameM();		// Multi object main function	
	int playM();			// Multi object subfunction
	void play();			// Computer move maker
	int play(string locate);// User move maker

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
	void fileLoad();				// Load a board

	bool operator==(const ConnectFour other);
	bool operator!=(const ConnectFour other);
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
		bool operator==(const Cell other);
		bool operator!=(const Cell other);
		ostream & operator<<(ostream & out);
		istream & operator>>(istream & input);	
		Cell & operator++();
		Cell operator++(int);

	private:
		char position;			// a,b,c?
		int row;				// 0,1,2?
		char inside;			// user1, user2 or empty .
	};
	Cell ** gameBoard;
};
int ConnectFour::alive = 0;

int main(){
	ConnectFour Init;
	Init.playGame();
	return 0;
}
void ConnectFour::playGame(){
	char mo;
	int obj, control;
	string filename;	
	ConnectFour M1, M2, M3, M4, M5;
	cout << "Welcome to Connect Four! Choose your Game Mode! M for MultiObject, S for SingleObject!" << endl;
	cin >> mo;
	if(mo == 'S' || mo == 's'){			// Single object mode
		cout << "Please send a txt with a board in it." << endl;
		cin >> filename;
		ConnectFour M0(filename);
		M0.gameLoop();
	}
	else if(mo == 'M' || mo == 'm'){	// Multi object mode
		cout << "1.object >> \n";
		cin >> filename;
		ConnectFour M1(filename);
		M1.playGameM();		
		cout << "2.object >> \n";
		cin >> filename;
		ConnectFour M2(filename);	
		M2.playGameM();
		cout << "3.object >> \n";
		cin >> filename;
		ConnectFour M3(filename);
		M3.playGameM();
		cout << "4.object >> \n";
		cin >> filename;
		ConnectFour M4(filename);
		M4.playGameM();
		cout << "5.object >> \n";
		cin >> filename;
		ConnectFour M5(filename);
		M5.playGameM();
		while(1){
			cout << "Which object?" << endl;
			cin >> obj;
			switch(obj){
				case 1:
					control = M1.playM();		// Loops are for loading from a txt
					while(control ==-2){		
						fileLoad();
						control = M1.playM();
					}
					break;
				case 2:
					control = M2.playM();
					while(control ==-2){	
						fileLoad();
						control = M2.playM();
					}
					break;
				case 3:
					control = M3.playM();
					while(control ==-2){		
						fileLoad();
						control = M3.playM();
					}
					break;
				case 4:
					control = M4.playM();
					while(control ==-2){		
						fileLoad();
						control = M4.playM();
					}
					break;
				case 5:
					control = M5.playM();
					while(control ==-2){	
						fileLoad();
						control = M5.playM();
					}
					break;
				default:
					cout << "Something went wrong. Try again." << endl;		// No object chosen		
					exit(1);
			}
		}
	}
	else{
		cout << "Well sorry about that..." << endl;
	}	
}
bool ConnectFour::operator==(const ConnectFour other){ 		// Overloaded  compare function for ConnectFour object
	if(height == other.height && width == other.width && gameType == other.gameType)
		return true;
	else
		return false;
}
bool ConnectFour::operator!=(const ConnectFour other){		// Overloaded  compare function for ConnectFour object
	if(height == other.height && width == other.width && gameType == other.gameType)
		return false;
	else
		return true;
}
ConnectFour::Cell & ConnectFour::Cell::operator++(){		// Overloaded  increment operator for Cell object
	if(inside == 'O') inside = '.';
	else if(inside == 'O') inside = 'O';
	else if(inside == 'X') inside = 'O';
	else if(inside == '.') inside = 'X';
	return *this;
}
ConnectFour::Cell ConnectFour::Cell::operator++(int){		// Overloaded  increment operator for Cell object
	Cell temp = *this;	
	if(temp.getInside() == 'O') temp.setInside('.');
	else if(temp.getInside() == 'O') temp.setInside('O');
	else if(temp.getInside() == 'X') temp.setInside('O');
	else if(temp.getInside() == '.') temp.setInside('X');
	return temp;
}

bool ConnectFour::Cell::operator==(const Cell other){		// Overloaded  compare operator for Cell object
	if(inside == other.getInside())
		return true;
	else
		return false;
}
bool ConnectFour::Cell::operator!=(const Cell other){		// Overloaded  compare operator for Cell object
	if(inside == other.getInside())
		return false;
	else
		return true;
}
ostream & ConnectFour::Cell::operator<<(ostream & out){		// Overloaded  insertion operator for ConnectFour object
	out << "Position-> " << position << "Row-> " << row << "Data Inside-> " << inside;
	return out;
}
istream & ConnectFour::Cell::operator>>(istream & input){	// Overloaded  extraction operator for ConnectFour object
	cout << "Requesting a position:" << endl;
	input >> position;
	cout << "Row:" << endl;
	input >> row;
	cout << "Data inside:" << endl;
	input >> inside;
	return input;
}
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
	setHeight(5);
	setWidth(5);
}
ConnectFour::ConnectFour(const int newHeight, const int newWidth){
	setHeight(newHeight);
	setWidth(newWidth);
}
ConnectFour::ConnectFour(string filename){
	ifstream inp(filename);
	if(inp.fail()){
		cerr << "File not found." << endl;	
		exit(1);
	}
	int i = 0, j = 0, k = 0, rows = 0, sizeMax = 0, count = 0;
	char game_mode, temp;
	string carrier;			// carrier variable that carries a single line
	while(getline(inp, carrier)){
		for(i = 0; i < carrier.size();i++){
			if(carrier[i] == '*')	count++;						
			if(sizeMax < count)	sizeMax = count;		// This loop is for calculating the longest row
		}
		rows++;
		count = 0;
	}
	gameBoard = new Cell * [rows];
	for(i = 0; i < rows; ++i)
		gameBoard[i] = new Cell[sizeMax];

	inp.clear();							// File pointer points the EOF so we need to return it back to beginning of the file
	inp.seekg(0, ios::beg);

	while(getline(inp, carrier)){			// This loop creates a loop with column length and maximum row length
		for(i = 0; i < sizeMax; i++){
			if(carrier[i] == '*'){
				gameBoard[k][i].setRow(i);
				gameBoard[k][i].setPosition('a'+j);
				gameBoard[k][i].setInside('.');
			}
			else{
				gameBoard[k][i].setRow(i);				// Blanks part will be represented with 'B'
				gameBoard[k][i].setPosition('a'+j);
				gameBoard[k][i].setInside('B');					
			}
		}
		k++;
	}
	setHeight(rows);
	setWidth(sizeMax);
	inp.close();
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

int ConnectFour::getCells(){
	return alive;
}
void ConnectFour::setCells(){
	alive = alive + 1;
}
int ConnectFour::gameLoop(){
	int control = 0;		
	char game_type;

	cout << "Please type C for versus computer; P for two player game.";
	cin >> game_type;
	while(game_type != 'P' && game_type != 'C' && game_type != 'c' && game_type != 'p'){								/* This condition checks for game type errors */
		cerr << "You entered a wrong game type, Please type C for versus computer; P for two player game!" << endl;
		cin >> game_type;
	}
	setType(game_type);
	control = Loop();
	while(control ==-2){		// Player requested a load.
		fileLoad();
		control = Loop();
	}
	return 0;
}
int ConnectFour::playGameM(){			// Multi object game initalizer
	char game_type;
	cout << "Please enter a game type(P or C)" << endl;
	cin >> game_type;
	setType(game_type);
	return 0;
}

int ConnectFour::playM(){			// A single game step for multi object game

	int winner_1 = 0, winner_2 = 0, last_i = 0, last_j = 0, turn = 1, control = 0, alive = 0;							
	if(gameType == 'P' || gameType == 'p')																
	{

		if(turn == 1){
			drawBoard();
			setTurn(1);
			control = play(getMove());
			while(control == -3 || control == -4)
				control = play(getMove());
			if(control == -1) return -2;
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
		setTurn(2);
		if(turn == 2){
			drawBoard();
			control = play(getMove());
			if(control == -1) return -2;
			setCells();
			winner_2 = winControl('O', last_i, last_j);			/* Win control for player 2 */
			if(winner_2 == 1){
				game_over('O', last_i, last_j);			/* End-game procedures */
				cout << "\nPlayer Two Victory, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;		/* End-game procedures */
				drawBoard();
				return 0;
			}
			if(filledBoard()){
				cout << "There is no winner, this match is DRAW.";
				return 0;
			}			
		}
		turn = 1;
		cout << "The current living Cells --> " << getCells() << endl;				
	}
	else{

		if(turn == 1){
			drawBoard();
			setTurn(1);
			control = play(getMove());				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
			while(control == -3 || control == -4)
				control = play(getMove());
			if(control == -1) return -2;
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
		setTurn(2);
		if(turn == 2){
			drawBoard();
			play();	/* This function contains everything the computer needs. It returns the decided coordinates.(coord_i and coord_j) */
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
				return 0;
			}
		}
		turn = 1;
		cout << "The current living Cells --> " << getCells() << endl;		
	}
	return 0;
}
int ConnectFour::Loop(){
	int winner_1 = 0, winner_2 = 0, last_i = 0, last_j = 0, turn = 1, control = 0, alive = 0;							
	if(gameType == 'P' || gameType == 'p')													/* If game type is 1, then the game will be versus computer */ 								
	{
		while(1){	

			if(turn == 1){
				drawBoard();
				setTurn(1);
				control = play(getMove());
				while(control == -3 || control == -4)
					control = play(getMove());
				if(control == -1) return -2;
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
			setTurn(2);
			if(turn == 2){
				drawBoard();
				control = play(getMove());
				if(control == -1) return -2;
				setCells();
				winner_2 = winControl('O', last_i, last_j);			/* Win control for player 2 */
				if(winner_2 == 1){
					game_over('O', last_i, last_j);			/* End-game procedures */
					cout << "\nPlayer Two Victory, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;		/* End-game procedures */
					drawBoard();
					return 0;
				}
				if(filledBoard()){
					cout << "There is no winner, this match is DRAW.";
					return 0;
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
				setTurn(1);
				control = play(getMove());				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
				while(control == -3 || control == -4)
					control = play(getMove());
				if(control == -1) return -2;
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
			setTurn(2);
			if(turn == 2){
				drawBoard();
				play();	/* This function contains everything the computer needs. It returns the decided coordinates.(coord_i and coord_j) */
				/* This function takes the coordinates that decide_mech_block4 created and makes its move */
				cout << endl << "Computer made its move." << endl << endl;
				winner_2 = winControl('O', last_i, last_j);	/* win_control function checks the board for a winner, I used it for every player */
				setCells();
				if(winner_2 == 1){							
					game_over('O', last_i, last_j);				/* If there is a winner then I call game_over function, it does the end-game procedures */
					cout << "\nComputer VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << getCells() << endl;
					drawBoard();					return 0;
				}
				if(filledBoard()){							/* I need to check the board after every move with board_is_filled function. It does what it says in its name */
					cout << "There is no winner, this match is DRAW.";
					return 0;
				}
			}
			turn = 1;
			cout << "The current living Cells --> " << getCells() << endl;		
		}
	}
	return 0;
}
void ConnectFour::fillBoard(){			// Board initializer
	int i, j;
	gameBoard = new Cell * [height];
	for(i = 0; i < height; ++i)
		gameBoard[i] = new Cell[width];

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			gameBoard[i][j].setRow(i);
			gameBoard[i][j].setPosition('a'+j);
			gameBoard[i][j].setInside('.');
		}
	}
}
void ConnectFour::drawBoard(){			// Print the board to screen
	int i, j;
	for(i = 0; i < width; i++)
		cout << (char)('A'+i) << " ";
	cout << endl;

	for(i = 0; i < height; ++i){
		for(j = 0; j < width; ++j){
			if(gameBoard[i][j].getInside() == 'B') cout << " ";
			else cout << gameBoard[i][j].getInside() << " ";
		}
		cout << endl;
	}
}
string ConnectFour::getMove(){				// Helper function that requests a move
	string locate;
	if(getTurn() == 1)	cout << "Player One! Make your move!\n";
	else if(getTurn() == 2)	cout << "Player Two! Make your move!\n";
	cin >> locate;	
	return locate;
}
int ConnectFour::play(string locate){
	int i = 0, j = 0, counter = 0, real_loc = 0, control = 1, countNoBlanks = 0;
	if(locate == "SAVE"){
		fileSave();
		return control;
	}
	else if(locate == "LOAD"){
		return -1;
	}
	
	else{

		real_loc = locate[0] - 'a';					/* The location trasformed to use in array, like a = 0, b = 1 */

		if(real_loc < 0 || real_loc > 26){			/* Checks for Caps and turnes them into lower case. User friendly. */
			real_loc += 'a' - 'A';
		}

		for(i = height - 1; i >= 0; --i){					// Counts the legal locations
			if(gameBoard[i][real_loc].getInside() != 'B'){
				countNoBlanks++;
			}
		}
		if(gameBoard[height-countNoBlanks][real_loc].getInside() != '.'){
			cerr << "That column is full. Please choose another one." << endl;
			return -3;
		}
		for(i = height-1; i >= 0; --i)
		{
			if(gameBoard[i][real_loc].getInside() == '.' && counter == 0)			/* Scans the selected column bottom to top and puts an X to the first dot. */
			{	
				if(getTurn() == 1)	gameBoard[i][real_loc].setInside('X');
				else if(getTurn() == 2)	 gameBoard[i][real_loc].setInside('O'); 
				counter++;
				break;		
			}
			control++;
		}
		control = height - control;
		return control;
	}	
}
int ConnectFour::winControl(char term, int &last_i, int &last_j){
	int i = 0, j = 0, result = 0;

	for(i = 0; i < height; ++i){					// Checks for terms right to left
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
	for(i = 0; i < height -3; ++i){					// Checks for terms to bottom left
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
			result = cont_bottom(term, i, j);		// Checks for terms to bottom
			if(result == 3){
				last_i = i;
				last_j = j;
				winStyle = 3;
				return 1;
			}
		}
	}
	
	result = 0;
	for(i = 0; i < height-3; ++i){					// Checks for terms to bottom right
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
	for(i = 0; i < height; ++i){					// Checks for terms left to right
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
	if(gameBoard[coord_i][coord_j].getInside() == term){	
		if(gameBoard[coord_i][coord_j-1].getInside() == term){
			result += 1;
			if(gameBoard[coord_i][coord_j-2].getInside() == term){
				result += 1;
				if(gameBoard[coord_i][coord_j-3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int ConnectFour::cont_bottom_left(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameBoard[coord_i][coord_j].getInside() == term){	
		if(gameBoard[coord_i+1][coord_j-1].getInside() == term){
			result += 1;
			if(gameBoard[coord_i+2][coord_j-2].getInside() == term){
				result += 1;
				if(gameBoard[coord_i+3][coord_j-3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int ConnectFour::cont_bottom(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameBoard[coord_i][coord_j].getInside() == term){	
		if(gameBoard[coord_i+1][coord_j].getInside() == term){
			result += 1;
			if(gameBoard[coord_i+2][coord_j].getInside() == term){
				result += 1;
				if(gameBoard[coord_i+3][coord_j].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}	
}
int ConnectFour::cont_bottom_right(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameBoard[coord_i][coord_j].getInside() == term){	
		if(gameBoard[coord_i+1][coord_j+1].getInside() == term){
			result += 1;
			if(gameBoard[coord_i+2][coord_j+2].getInside() == term){
				result += 1;
				if(gameBoard[coord_i+3][coord_j+3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
int ConnectFour::cont_right(char term, int coord_i, int coord_j){
	int result = 0;
	if(gameBoard[coord_i][coord_j].getInside() == term){	
		if(gameBoard[coord_i][coord_j+1].getInside() == term){
			result += 1;
			if(gameBoard[coord_i][coord_j+2].getInside() == term){
				result += 1;
				if(gameBoard[coord_i][coord_j+3].getInside() == term){
					result += 1;
					return result;
				}
			}

		}
	}
}
void ConnectFour::game_over(int term, int last_i, int last_j){ 		// Switch them to lowercase if the game is ended
	int lower = 0, i = 0, j = 0;


	lower = 'a' - 'A';	

	switch (winStyle) {
		case 1:																		/* Left */
			gameBoard[last_i][last_j].setInside(term+lower);
			gameBoard[last_i][last_j-1].setInside(term+lower);
			gameBoard[last_i][last_j-2].setInside(term+lower);
			gameBoard[last_i][last_j-3].setInside(term+lower);
			break;
		case 2:																		/* Bottom - Left */
			gameBoard[last_i][last_j].setInside(term+lower);
			gameBoard[last_i+1][last_j-1].setInside(term+lower);
			gameBoard[last_i+2][last_j-2].setInside(term+lower);
			gameBoard[last_i+2][last_j-2].setInside(term+lower);
			break;			
		case 3:																		/* Bottom */
			gameBoard[last_i][last_j].setInside(term+lower);
			gameBoard[last_i+1][last_j].setInside(term+lower);
			gameBoard[last_i+2][last_j].setInside(term+lower);
			gameBoard[last_i+3][last_j].setInside(term+lower);
			break;
		case 4:																		/* Bottom - Right */
			gameBoard[last_i][last_j].setInside(term+lower);
			gameBoard[last_i+1][last_j+1].setInside(term+lower);
			gameBoard[last_i+2][last_j+2].setInside(term+lower);
			gameBoard[last_i+3][last_j+3].setInside(term+lower);
			break;		
		case 5:																		/* Right */
			gameBoard[last_i][last_j].setInside(term+lower);
			gameBoard[last_i][last_j+1].setInside(term+lower);
			gameBoard[last_i][last_j+2].setInside(term+lower);
			gameBoard[last_i][last_j+3].setInside(term+lower);
			break;
	}
																					/* And turnes the X(or 0, depended on the term variable)'s to lower case just to make them outstanding */


}
int ConnectFour::filledBoard(){			// Draw case
	int i = 0, j = 0;
	
	for(i = 0; i < height + 1; i++)
	{
		for(j = 0; j < width; j++)
		{
			if(gameBoard[i][j].getInside() == '.');
				return 0;
		}
	}
	return 1;
}
void ConnectFour::play(){				// Computer AI from HW3

int i = 0, j = 0, result = 0, result2 = 0, temp_i = 0, temp_j = 0;
char term = 'X', term2 = 'O';

	for(i = 0; i < height-3; ++i){
		for(j = 3; j < width; ++j){
			if(gameBoard[i + 1][j - 1].getInside() == term2){
				result += 1;
				if(gameBoard[i + 2][j - 2].getInside() == term2){
					result+= 1;
					if(gameBoard[i + 3][j - 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameBoard[i + 1][j - 1].getInside() == term){
				result2+= 1;
				if(gameBoard[i + 2][j - 2].getInside() == term){
					result2+= 1;
					if(gameBoard[i + 3][j - 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameBoard[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height; ++i){
		for(j = 3; j < width; ++j){

			if(gameBoard[i][j - 1].getInside() == term2){
				result += 1;
				if(gameBoard[i][j - 2].getInside() == term2){
					result+= 1;
					if(gameBoard[i][j - 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameBoard[i][j - 1].getInside() == term){
				result2+= 1;
				if(gameBoard[i][j - 2].getInside() == term){
					result2+= 1;
					if(gameBoard[i][j - 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameBoard[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height-3; ++i){
		for(j = 0; j < width-3; ++j){

			if(gameBoard[i + 1][j + 1].getInside() == term2){
				result += 1;
				if(gameBoard[i + 2][j + 2].getInside() == term2){
					result+= 1;
					if(gameBoard[i + 3][j + 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameBoard[i + 1][j + 1].getInside() == term){
				result2+= 1;
				if(gameBoard[i + 2][j + 2].getInside() == term){
					result2+= 1;
					if(gameBoard[i + 3][j + 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameBoard[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height-3; ++i){
		for(j = 0; j < width; ++j){

			if(gameBoard[i + 1][j].getInside() == term2){
				result += 1;
				if(gameBoard[i + 2][j].getInside() == term2){
					result+= 1;
					if(gameBoard[i + 3][j].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameBoard[i + 1][j].getInside() == term){
				result2+= 1;
				if(gameBoard[i + 2][j].getInside() == term){
					result2+= 1;
					if(gameBoard[i + 3][j].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameBoard[temp_i][temp_j].setInside('O');
				return;
			}
			result = 0;
		}
	}
	for(i = 0; i < height; ++i){
		for(j = 0; j < width-3; ++j){

			if(gameBoard[i][j + 1].getInside() == term2){
				result += 1;
				if(gameBoard[i][j + 2].getInside() == term2){
					result+= 1;
					if(gameBoard[i][j + 3].getInside() == term2){
						result+=1;
						temp_i = i;
						temp_i = j;
					}	
				}			
			}
			else if(gameBoard[i][j + 1].getInside() == term){
				result2+= 1;
				if(gameBoard[i][j + 2].getInside() == term){
					result2+= 1;
					if(gameBoard[i][j + 3].getInside() == term){
						result2+=1;
						temp_i = i;
						temp_i = j;
					}
				}
			}

			if(result == 3 || result2 == 3 && legality(temp_i, temp_j)){
				gameBoard[temp_i][temp_j].setInside('O');
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
				gameBoard[i][j].setInside('O');
				cout << "After!" << endl; 
				return;
			}

		}
	}
}
int ConnectFour::legality(int coord_i, int coord_j){ 			// Checks the move's legality
	if(coord_i < height && coord_j < width && gameBoard[coord_i][coord_j].getInside() == '.'){
		if(coord_i + 1 != height){
			if(gameBoard[coord_i + 1][coord_j].getInside() != '.'){
				return 1;
			}
		}
		else{
			return 1;		
		}
	}
	return 0;
}
void ConnectFour::fileSave(){			// Called if user types 'save'
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
			inner << gameBoard[i][j].getInside();				/* X and O's */
		}
		inner << "\n";
	}
	inner.close();	
}
void ConnectFour::fileLoad(){			// Called if user types 'load'
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
			gameBoard[i][j].setInside(temp);			/* X and O 's */
		}
	outer.close();
}
