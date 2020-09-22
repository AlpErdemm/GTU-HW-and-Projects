#include "cfabstract.h"

using namespace std;

namespace CFAbstract
{
	void ConnectFourAbstract::setHeight(int newHeight){
		height = newHeight;
	}
	int ConnectFourAbstract::getWidth() const{
		return width;
	}
	void ConnectFourAbstract::setWidth(int newWidth){
		width = newWidth;
	}
	int ConnectFourAbstract::getType() const{
		return gameType;
	}
	void ConnectFourAbstract::setType(int newType){
		gameType = newType;
	}
	int ConnectFourAbstract::getTurn() const{
		return turn;
	}
	void ConnectFourAbstract::setTurn(int newTurn){
		turn = newTurn;
	}
	void ConnectFourAbstract::incCOUNT(){
		globCOUNT+=1;
	}
	void ConnectFourAbstract::decCOUNT(){
		globCOUNT-=1;
	}
	/*void ConnectFourAbstract::playGame(){
		
	}*/
	int ConnectFourAbstract::gameSettings(){
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
		return 0;
	}
	void ConnectFourAbstract::fillBoard(){			// Board initializer
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

	void ConnectFourAbstract::drawBoard(){			// Print the board to screen
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

	void ConnectFourAbstract::gameLoop(){
		int control;
		setTurn(1);
		control = Loop();
		while(control ==-2){		// Player requested a load.
			fileLoad();
			control = Loop();
		}
	}
	int ConnectFourAbstract::Loop(){
		int winner_1 = 0, winner_2 = 0, last_i = 0, last_j = 0, control = 0, alive = 0, move;							
		if(gameType == 'P' || gameType == 'p')													/* If game type is 1, then the game will be versus computer */ 								
		{
			while(1){	

				while(getTurn() == 1){
					move = globCOUNT;
					drawBoard();
					control = play(getMove());
					while(control == -3 || control == -4){
						drawBoard();
						control = play(getMove());
					}
					incCOUNT();
					if(control == -1) return -2;
					winner_1 = winControl('X', last_i, last_j); /* Called win_control for player 2 */
					if(winner_1 == 1){
						game_over('X', last_i, last_j);			/* End-game procedures */
						cout << "\nPlayer One VICTORY, the game will be closed. To play again, restart the game." << "The current living Cells --> " << endl;
						drawBoard();
						return 0;
					}

					if(filledBoard()){						/* Checked if the board is filled with X and O's */
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}	
					if(move != globCOUNT)
						setTurn(2);
				};
				while(getTurn() == 2){
					move = globCOUNT;
					drawBoard();
					control = play(getMove());
					while(control == -3 || control == -4){
						drawBoard();
						control = play(getMove());
					}
					if(control == -1) return -2;
					incCOUNT();
					winner_2 = winControl('O', last_i, last_j);			/* Win control for player 2 */
					if(winner_2 == 1){
						game_over('O', last_i, last_j);			/* End-game procedures */
						cout << "\nPlayer Two Victory, the game will be closed. To play again, restart the game." << endl;		/* End-game procedures */
						drawBoard();
						return 0;
					}
					if(filledBoard()){
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}
						
					if(move != globCOUNT)
						setTurn(1);					
				}				
			}
		}
		else{
			while(1){

				if(getTurn() == 1){
					move = globCOUNT;
					drawBoard();
					control = play(getMove());				/* player_2 function is for player 2... it takes a character from the user with cin and makes a move */
					while(control == -3 || control == -4){
						drawBoard();
						control = play(getMove());
					}
					incCOUNT();
					if(control == -1) return -2;
					winner_1 = winControl('X', last_i, last_j); /* Called win_control for player 2 */
					if(winner_1 == 1){
						game_over('X', last_i, last_j);			/* End-game procedures */
						cout << "\nPlayer One VICTORY, the game will be closed. To play again, restart the game" << endl;
						drawBoard();
						return 0;
					}

					if(filledBoard()){						/* Checked if the board is filled with X and O's */
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}	

				}	
				setTurn(2);
				if(getTurn() == 2){
					move = globCOUNT;
					drawBoard();
					play();	/* This function contains everything the computer needs. It returns the decided coordinates.(coord_i and coord_j) */
					/* This function takes the coordinates that decide_mech_block4 created and makes its move */
					cout << endl << "Computer made its move." << endl << endl;
					winner_2 = winControl('O', last_i, last_j);	/* win_control function checks the board for a winner, I used it for every player */
					if(winner_2 == 1){							
						game_over('O', last_i, last_j);				/* If there is a winner then I call game_over function, it does the end-game procedures */
						cout << "\nComputer VICTORY, the game will be closed. To play again, restart the game."  << endl;
						drawBoard();					return 0;
					}
					if(filledBoard()){							/* I need to check the board after every move with board_is_filled function. It does what it says in its name */
						cout << "There is no winner, this match is DRAW.";
						return 0;
					}

				}
				setTurn(1);			
			}
		}
		return 0;
	}
	string ConnectFourAbstract::getMove(){				// Helper function that requests a move
		string locate;
		if(getTurn() == 1)	cout << "Player One! Make your move!\n";
		else if(getTurn() == 2)	cout << "Player Two! Make your move!\n";
		cin >> locate;	
		return locate;
	}
	int ConnectFourAbstract::play(string locate){
		int i = 0, j = 0, counter = 0, real_loc = 0, control = 1, countNoBlanks = 0;
		if(getObjType() == 'U' || getObjType() == 'u'){
			if(locate == "UNDO"){
				undoFunction();
				return -3;
			}
		}
		if(locate == "SAVE"){
			fileSave();
			return -4;
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
					gameBoard[i][real_loc].setCOUNT(globCOUNT);
					counter++;
					break;		
				}
				control++;
			}
			control = height - control;
			return control;
		}	
	}
	int ConnectFourAbstract::winControl(char term, int &last_i, int &last_j){
		int i = 0, j = 0, result = 0;
		cout << "OBJECT TYPE -> " << getObjType() << endl;
		if(getObjType() != 'D' && getObjType() != 'd'){
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
		}
		if(getObjType() != 'P' && getObjType() != 'p'){
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
		}
		if(getObjType() != 'D' && getObjType() != 'd'){
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
		}
		if(getObjType() != 'P' && getObjType() != 'p'){
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
		}
		if(getObjType() != 'D' && getObjType() != 'd'){
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
	}
	int ConnectFourAbstract::cont_left(char term, int coord_i, int coord_j){			
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
	int ConnectFourAbstract::cont_bottom_left(char term, int coord_i, int coord_j){
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
	int ConnectFourAbstract::cont_bottom(char term, int coord_i, int coord_j){
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
	int ConnectFourAbstract::cont_bottom_right(char term, int coord_i, int coord_j){
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
	int ConnectFourAbstract::cont_right(char term, int coord_i, int coord_j){
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
	void ConnectFourAbstract::game_over(int term, int last_i, int last_j){ 		// Switch them to lowercase if the game is ended
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
	int ConnectFourAbstract::filledBoard(){			// Draw case
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
	void ConnectFourAbstract::play(){				// Computer AI from HW3

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

				if((result == 3 || result2 == 3) && legality(temp_i, temp_j)){
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

				if((result == 3 || result2 == 3) && legality(temp_i, temp_j)){
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

				if((result == 3 || result2 == 3) && legality(temp_i, temp_j)){
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

				if((result == 3 || result2 == 3) && legality(temp_i, temp_j)){
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

				if((result == 3 || result2 == 3) && legality(temp_i, temp_j)){
					gameBoard[temp_i][temp_j].setInside('O');
					return;
				}
				result = 0;
			}
		}
		for(i = height-1; i >= 0; --i){
			for(j = width - 1; j >= 0; --j){
				if(gameBoard[i][j].getInside() == '.'){
					gameBoard[i][j].setInside('O');
					gameBoard[i][j].setCOUNT(globCOUNT);
					incCOUNT();
					return;
				}

			}
		}
	}
	int ConnectFourAbstract::legality(int coord_i, int coord_j){ 			// Checks the move's legality
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
	void ConnectFourAbstract::fileSave(){			// Called if user types 'save'
		string filename;
		cin >> filename;
		ofstream inner(filename);
		int i = 0, j = 0, tturn = 0, hheight = 0, wwidth = 0;
		char game_mode;

		tturn = getTurn();
		hheight = getHeight();
		wwidth = getWidth();
		game_mode = getType();

		inner << getObjType() << '\n' << game_mode << '\n' << tturn << '\n' << hheight << '\n' << wwidth << '\n';  	/* Writes the needed information to the file */

		for(i = 0; i < height; i++){
			for(j = 0; j < width; j++){
				inner << gameBoard[i][j].getInside();				/* X and O's */
			}
			inner << "\n";
		}
		inner.close();	
	}
	void ConnectFourAbstract::fileLoad(){			// Called if user types 'load'
		string filename;
		cin >> filename;
		ifstream outer(filename);
		if(outer.fail()){
			cerr << "File not found." << endl;	
			exit(1);
		}
		int i = 0, j = 0, tturn = 0, hheight = 0, wwidth = 0, turn = 0;
		char game_mode, temp, obj;
		outer >> obj >> game_mode >> tturn >> hheight >> wwidth;			/* Information about the game */
	
		setObjType(obj);
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
	void ConnectFourAbstract::undoFunction(){
		int i = 0, j = 0, count = 0;
	
		for(j = 0; j < width; j++)
		{
			if(gameBoard[height-1][j].getInside() == '.')
				count+=1;
		}
		if(count == width){
			cout << "There is no move to Undo. "<< endl;
			return;
		}
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{	
				if(getType() == 'C' || getType() == 'c'){
					cout << "YO! " << "[" << i << "][" << j << "]" << "-----" << " Index = " << gameBoard[i][j].getCOUNT() << "Glob -> " << globCOUNT << endl;
					if(gameBoard[i][j].getCOUNT() == globCOUNT){
						gameBoard[i][j].setInside('.');
						gameBoard[i][j].killCOUNT();
					}
					if(gameBoard[i][j].getCOUNT() == (globCOUNT-1)){
						gameBoard[i][j].setInside('.');
						gameBoard[i][j].killCOUNT();
					}
				}
				else if(gameBoard[i][j].getCOUNT() == globCOUNT){
					gameBoard[i][j].setInside('.');
					gameBoard[i][j].killCOUNT();
				}
			
			}
		}
		if(getType() == 'C' || getType() == 'c'){
			cout << "Waasuup! " << endl;
			decCOUNT();
			cout << globCOUNT;
			decCOUNT();
			cout << globCOUNT;
		}	
		else
			decCOUNT();
	}
}

