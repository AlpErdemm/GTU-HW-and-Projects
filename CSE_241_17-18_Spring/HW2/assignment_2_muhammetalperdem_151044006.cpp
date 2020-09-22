#include <iostream>
#include <vector>

using namespace std;

const int cardHeight = 6; //A tile's height.
const int cardCount = 12;	//How many tiles are going to be created in the game.
const int cardSize = 8;		//Number of ports in a tile
const int boardHeight = 20; //The board's height
const int boardSize = 3;	// How many tiles can fit in the board 3 x 3


class Tsuro{			// Mother class.
public:
	void playGame();	// Game loop.
	void initBoard();	// Initializes an empty board.
	void printBoard();	// Prints the current board onto the screen.
	void applyCard(int slotX, int slotY, int cardNum);	// Places the the chosen cart to the board.
	void turnCard(int cardNum, int times);	// Rotates a tile
	void placeTokens(int player);		// Places player tokens to the board randomly
	void dealCards();		// Gives players three tiles.
	void showCards(int player);	// Prints a player's current cards
	void proceed(char token); 	// Makes a move and calculates the results
	int winControl();		// Any winner?
	int boardController(int coord1, int coord2);	// Checks the miniBoard if there is a tile on [coord1][coord2] location.
	void applyBoard(int coord1, int coord2, int index);	// Filles the miniBoard's chosen location with the card number.
	void vacuum(int startpointX, int startpointY, int cardNo, char token); 	// Every tile checks its surrondings for a token and takes it.
	int searchPair(int x, int cardNo);	// Tooks a port and finds the connected port of it.
	void initMiniBoard();		// Initializes the miniBoard with -1 s.
	void finalvacuum(char token);	// The board itself applies the vacuum procedure.
private:
	class Player{
	public:
		inline int getLeft(){return cardsLeft;}
		inline void setLeft(int newOne){cardsLeft = newOne;}
		inline void incLeft(){cardsLeft+=1;}
		inline void decLeft(){cardsLeft-=1;}
		inline void setS(int i, int newOne){cardStorage[i] = newOne;}
		inline int getS(int i){return cardStorage[i];}
	private:
		int cardsLeft;		// How many cards left in this player's store.
		int cardStorage[3];	// Contains card numbers.
	};
	Player p1, p2;

	class Cards{
	public:
		void createCard();
		inline int getC(int i, int j) {return ins[i][j];}
		inline void setC(int i, int j, int newOne) {ins[i][j] = newOne;}
		inline int getMis(){return missingPort;}
		inline void setMis(int newOne){missingPort = newOne;}
	private:
		int ins[cardSize][2]; 	// The card itself(ports).
		int missingPort;	//If there is a token on this tile then this variable holds the former local.
	};
	Cards Cd[cardCount];
	int miniBoard[boardSize][boardSize];
	char tokens[4] = {'X', 'Y', 'Z', 'T'};
	char Board[boardHeight][boardHeight * 2];
	int firstX[2], firstY[2];
	int cardQ;
};

int main(){
	Tsuro init;
	init.playGame();
	return 0;
}

void Tsuro::playGame(){		// Functions will be explained in their implementation lines.
	int coord1, coord2, tile, times, wg;
	char rotate;
	cout << "Welcome to the game 'Tsuro', the game can be played with two player." << endl << "Initializing board..." << endl;
	initBoard();
	cout << "Creating cards..." << endl;
	for(int i = 0; i < cardCount; i++) Cd[i].createCard();	
	cout << "This is your the board you are going to play --> " << endl;
	placeTokens(1);
	placeTokens(2);
	cout << "Choosing a spot for your tokens..." << endl;
	printBoard();
	cout << "How to place a tile? -> Think the board as 9 pieces and give your selection as a pair of integers." << endl;
	cout << "Example: [x][y] --> Enter 0 and 0 for top-left[0][0], 1 and 0 for top-mid [1][0]." << endl;
	cardQ = 0;
	p1.setLeft(0);
	p2.setLeft(0);
	dealCards();
	initMiniBoard();
	while(1){
		cout << "You are ready to start Player One!" << endl;
		while(p1.getLeft() == 0){
			cerr << "No cards left, dealing again" << endl;
			dealCards();
		}
		cout << "These are your tiles >> " << endl;
		showCards(1); 
		cout << "Spot your token and think wisely, which tile would you like to place? " << endl;
		cin >> tile;
		while(tile > p1.getLeft() || tile < 1){
			cerr << "Try again." << endl;
			cin >> tile;
		}
		cout << "Please read 'How to place a tile?' and enter two coordinates." << endl;
		cin >> coord1 >> coord2;
		while(coord1 >= boardSize || coord2 >= boardSize){
			cerr << "You have entered a coordinate out of bounds, try to choose integers smaller than " << boardSize << "." << endl;
			cin >> coord1 >> coord2;
		}
		while(!boardController(coord1, coord2)){
			cerr << "That spot is not empty! Try again." << endl;
			cin >> coord1 >> coord2;
		}
		applyCard(coord1,coord2,p1.getS(tile-1));	
		applyBoard(coord1, coord2, p1.getS(tile-1));	
		p1.decLeft(); // One card in Player 1's storage is gone.
		printBoard();
		cout << "It's not over yet! Would you like to rotate your card? Y for Yes, N for No." << endl;
		cin >> rotate;
		if(rotate == 'Y' || rotate == 'y') {
			cout << "No problem. How many times we should rotate it clockwise? 1 times = 90 degree, 2 times = 180 degree etc." << endl;
			cin >> times;
			turnCard(p1.getS(tile-1),times); applyCard(coord1, coord2, p1.getS(tile-1)); // Rotates and applies the changes.
		}
		proceed('X');	// Proceed function for Player 1.	
		wg = winControl();	// Starts winner control procedures.
		if(wg == 1){printBoard();cout << "Player 2 win." << endl; return;}
		else if(wg == 0){printBoard();cout << "Player 1 win." << endl; return;}
		else if(wg == 2){printBoard();cout << "This match is draw." << endl; return;}
		proceed('Y');
		printBoard();
		cout << "Your turn Player Two! Go for it! " << endl;	// Same stuff for Player 2.
		while(p2.getLeft() == 0){
			cerr << "No cards left, dealing again" << endl;
			dealCards();
		}
		cout << "These are your tiles >> " << endl;
		showCards(2);
		cout << "Spot your token and think wisely, which tile would you like to place? " << endl;
		cin >> tile;
		while(tile > p2.getLeft() || tile < 1){
			cerr << "Try again." << endl;
			cin >> tile;
		}
		cout << "Please read 'How to place a tile?' and enter two coordinates." << endl;
		cin >> coord1 >> coord2;
		while(coord1 >= boardSize || coord2 >= boardSize){
			cerr << "You have entered a coordinate out of bounds, try to choose integers smaller than " << boardSize << "." << endl;
			cin >> coord1 >> coord2;
		}
		while(!boardController(coord1, coord2)){
			cerr << "That spot is not empty! Try again." << endl;
			cin >> coord1 >> coord2;
		}
		applyCard(coord1,coord2,p2.getS(tile-1));
		applyBoard(coord1, coord2, p2.getS(tile-1));
		p2.decLeft();
		printBoard();
		cout << "It's not over yet! Would you like to rotate your card? Y for Yes, N for No." << endl;
		cin >> rotate;
		if(rotate == 'Y' || rotate == 'y') {
			cout << "No problem. How many times we should rotate it clockwise? 1 times = 90 degree, 2 times = 180 degree etc." << endl;
			cin >> times;
			turnCard(p2.getS(tile-1),times); applyCard(coord1, coord2, p2.getS(tile-1));
		}
		proceed('Y');	// Proceed function for Player 1.	
		wg = winControl();	// Starts winner control procedures.
		if(wg == 1){printBoard();cout << "Player 2 win." << endl; return;}
		else if(wg == 0){printBoard();cout << "Player 1 win." << endl; return;}
		else if(wg == 2){printBoard();cout << "This match is draw." << endl; return;}
		proceed('X');
		printBoard();

	}
}
void Tsuro::initBoard(){ 	//Basicly, creates a multidimensional array using the given example in pdf.
	for(int i = 0; i < boardHeight; i++){
		for(int j = 0; j < boardHeight * 2; j++){
			Board[i][j] = ' ';
		}
	}
	int tracker = 1, whileFlag = boardSize;
	while(whileFlag){
		for(int i = 0; i < cardHeight; i++){
			if(i == 2 || i == 3){
				Board[tracker][0] = 'o'; Board[tracker][boardHeight * 2 -1] = 'o';
			}
			else{
				Board[tracker][0] = '|'; Board[tracker][boardHeight * 2 -1] = '|';	
			}
			tracker++;
		}
		whileFlag--;
	}
	tracker = 2;
	whileFlag = boardSize;
	Board[0][0] = '-'; Board[0][1] = '-'; Board[boardHeight-1][0] = '-'; Board[boardHeight-1][1]= '-';
	Board[0][boardHeight * 2 -1] = '-'; Board[0][boardHeight * 2 -2] = '-';	Board[boardHeight-1][boardHeight * 2 -1] = '-'; 
	Board[boardHeight-1][boardHeight * 2 -2] = '-';
	while(whileFlag){
		for(int i = 0; i < cardHeight * 2; i++){
			if(i == 4 || i == 7){
				Board[0][tracker] = 'o'; Board[boardHeight-1][tracker] = 'o';
			}
			else{
				Board[0][tracker] = '-'; Board[boardHeight-1][tracker] = '-';	
			}
			tracker++;
		}
		whileFlag--;
	}
}
void Tsuro::printBoard(){ 
	for(int i = 0; i < boardHeight; i++){
		for(int j = 0; j < boardHeight * 2; j++){
			cout << Board[i][j];
		}
		cout << endl;
	}
}
void Tsuro::Cards::createCard(){		//Creates a tile randomly.
	vector <int> v;
	int num, flag = 1;
	while(flag){
		num = 5 + (rand() % 4);
		for(int i = 0; i < v.size();i++){
			if(v[i] == num) flag = 2;
		}
		if(flag != 2) v.push_back(num);
		flag = 1;
		if(v.size() == 4) flag = 0;
	}

	for(int i = 0; i < 4; i++){
		ins[i][0] = i;
		ins[i][1] = v[i];
	}
	for(int i = 0; i < 4; i++){
		ins[v[i]-1][1] = i + 1;
		ins[v[i]-1][0] = v[i]-1;
	}
}

void Tsuro::applyCard(int slotX, int slotY, int cardNum){

	int startPointX = 2 + (slotX * cardHeight * 2);	// startPointX is x coordinate of the left-top point of the tile.
	int startPointY = 1 + (slotY * cardHeight); // startPointY is y coordinate of the left-top point of the tile.
	int countI = 0, countJ = 0, countNum = 0, count = 0;
	char temp = '0';
	int numbers[] = {Cd[cardNum].getC(0,0)+1,Cd[cardNum].getC(1,0)+1,Cd[cardNum].getC(7,0)+1,Cd[cardNum].getC(2,0)+1,Cd[cardNum].getC(6,0)+1,
		Cd[cardNum].getC(3,0)+1,Cd[cardNum].getC(5,0)+1,Cd[cardNum].getC(4,0)+1};  // This is a speacial order to make the algorithm faster.

	for(int i = startPointY; i < startPointY + cardHeight; i++)
	{
		for(int j = startPointX; j < startPointX + (cardHeight * 2); j++){		
			if((countJ != 4 && countJ != 7) && (countI == 0 || countI == cardHeight-1)) Board[i][j] = '.'; // Creates the dots.

			else if((countJ == 4 || countJ == 7) && (countI == 0 || countI == cardHeight-1)) {	// Creates the ports.
				temp = '0';
				temp += numbers[countNum];
				Board[i][j] = temp ; 
				countNum++;
			}

			else if((countI != 2 && countI != 3)&& (countJ == 0 || countJ == cardHeight * 2 -1)) Board[i][j] = ':';	// Creates the colons.

			else if((countI == 2 || countI == 3)&& (countJ == 0 || countJ == cardHeight * 2 -1)){		// Creates the ports.
				temp = '0';
				temp += numbers[countNum];
				Board[i][j] = temp ; 
				countNum++;
			}
			countJ++;
		}
		countI++;
		countJ = 0;
	}
	for(int i = startPointY; i < startPointY + cardHeight; i++)
	{
		for(int j = startPointX; j < startPointX + (cardHeight * 2); j++){		// Creates the connected ports.

			if(i == startPointY || i ==  (startPointY + cardHeight -1) || j == startPointX || j == (startPointX + (cardHeight * 2) - 1)){
				if(i == startPointY && j == startPointX + 4){
					temp = '0'; temp+= Cd[cardNum].getC(0,1);
					Board[i+1][j] = temp;
					count++;
				}
				else if(i == startPointY && j == startPointX + 7){
					temp = '0'; temp+= Cd[cardNum].getC(1,1);
					Board[i+1][j] = temp;
					count++;
				}
				else if(i == startPointY + 2 && j == startPointX + (cardHeight*2 -1)){
					temp = '0'; temp+= Cd[cardNum].getC(2,1);
					Board[i][j-4] = temp;
					count++;
				}
				else if(i == startPointY + 3 && j == startPointX + (cardHeight*2 -1)){
					temp = '0'; temp+= Cd[cardNum].getC(3,1);
					Board[i][j-4] = temp;;
					count++;
				}
				else if(i == startPointY + cardHeight -1 && j == startPointX + 7){
					temp = '0'; temp+= Cd[cardNum].getC(4,1);
					Board[i-1][j] = temp;
					temp = '0';
					count++;
				}
				else if(i == startPointY + cardHeight -1 && j == startPointX + 4){
					temp = '0'; temp+= Cd[cardNum].getC(5,1);
					Board[i-1][j] = temp;
					count++;
				}
				else if(i == startPointY + 3 && j == startPointX){
					temp = '0'; temp+= Cd[cardNum].getC(6,1);
					Board[i][j+4] = temp;
					count++;
				}
				else if(i == startPointY + 2 && j == startPointX){
					temp = '0'; temp+= Cd[cardNum].getC(7,1);
					Board[i][j+4] = temp;
					count++;
				}
			}
			if(count == cardSize) break;
		}
	}
}
void Tsuro::turnCard(int cardNum, int times){ 	//In order to rotate a card, the ports can be slided two units to the right.
	int temp[cardSize][2];
	while(times){
		for(int i = 0; i < cardSize; i++){
			if(i == 6){
				temp[0][0] = Cd[cardNum].getC(i, 0);
				temp[0][1] = Cd[cardNum].getC(i, 1);
			}
			else if(i == 7){
				temp[1][0] = Cd[cardNum].getC(i, 0);
				temp[1][1] = Cd[cardNum].getC(i, 1);
			}
			else{
				temp[i+2][0] = Cd[cardNum].getC(i, 0);
				temp[i+2][1] = Cd[cardNum].getC(i, 1);
			}
		}
		for(int i = 0; i < cardSize; i++){
			Cd[cardNum].setC(i,0,temp[i][0]);
			Cd[cardNum].setC(i,1,temp[i][1]);
		}
		times--;
	}

}
void Tsuro::placeTokens(int player){	// Randomly pick a location and place the token for the current player.
	int i, j;
	for(i = rand() % boardHeight; i < boardHeight; i++){
		for(j = 0; j < boardHeight * 2 -1; j++){
			if(Board[i][j] == 'o'){
				if(player ==1){firstX[0] = i; firstX[1] = j;}
				else if(player ==2){firstY[0] = i; firstY[1] = j;}
				Board[i][j] = tokens[player-1];
				return;
			}
		}	
	}
	srand(time(NULL));
}
void Tsuro::dealCards(){		// Gives three tiles for each.
	int i = 0;
	while(p1.getLeft()!= 3){
		p1.setS(i,cardQ);
		p1.incLeft();
		i++; cardQ++;
	}
	i = 0;
	cout << endl;
	while(p2.getLeft()!= 3){
		p2.setS(i,cardQ);
		p2.incLeft();
		i++; cardQ++;
	}
}

void Tsuro::showCards(int player){	// Prints the ports of the tiles to inform the player.
	if(player == 1){
		int count = p1.getLeft();
		while(count){
			cout << "Your " << count << ". card's ports are shown below -->" << endl;
			for(int i = 0; i < cardSize; i++){
				cout << Cd[p1.getS(count-1)].getC(i,0)+1  << " Port is connected to " << Cd[p1.getS(count-1)].getC(i,1) << " port." << endl;
			}
			count--;
			cout << endl;
		}
		cout << endl;
	}
	else if(player == 2){
		int count = p2.getLeft();
		while(count){
			cout << "Your " << count << ". card's ports are shown below -->" << endl;
			for(int i = 0; i < cardSize; i++){
				cout << Cd[p2.getS(count-1)].getC(i,0)+1  << " Port is connected to " << Cd[p2.getS(count-1)].getC(i,1) << " port." << endl;
			}
			count--;
			cout << endl;
		}
		cout << endl;
	}
	
}
void Tsuro::proceed(char token){	// I used a function named vacuum to do the job, this function locates the tiles on the board and gives vacuum some info.
	int startpointX, startpointY, loop = 0;

	for(int k = 0; k < 3; k++)
		for(int t = 0; t < 3; t++)
			if(miniBoard[t][k] >= 0 && miniBoard[t][k] < 9) loop++;

	while(loop){
		for(int i = 0; i < boardSize; i++){
			for(int j = 0; j < boardSize; j++){
				if(miniBoard[i][j] >= 0 && miniBoard[i][j] < 9){
					switch(i){
						case 0:
							switch(j){
								case 0:
									startpointX = 2; startpointY = 1;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								case 1:
									startpointX = 14; startpointY = 1;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								case 2:
									startpointX = 26; startpointY = 1;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								
							}
							break;
						case 1:
							switch(j){
								case 0:
									startpointX = 2; startpointY = 7;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								case 1:
									startpointX = 14; startpointY = 7;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								case 2:
									startpointX = 26; startpointY = 7;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								
							}
							break;
						case 2:
							switch(j){
								case 0:
									startpointX = 2; startpointY = 13;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								case 1:
									startpointX = 14; startpointY = 13;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								case 2:
									startpointX = 26; startpointY = 13;
									vacuum(startpointX, startpointY, miniBoard[i][j], token);
									break;
								
							}
							break;					

					}
				}
			}
		}
	loop--;
	}
	finalvacuum(token);
}
int Tsuro::boardController(int coord1, int coord2){		// Players can't place a tile if there is already a tile.
	if(miniBoard[coord2][coord1] >= 0 && miniBoard[coord2][coord1] < 9) return 0;
	return 1;
}
void Tsuro::applyBoard(int coord1, int coord2, int index){	// Leave a mark on miniBoard when a tile is placed, in order to use it later.
	miniBoard[coord2][coord1] = index;
}
int Tsuro::winControl(){	//Basic controls while searching for a winner.
	for(int i = 0; i < boardHeight; i++){
		for(int j = 0; j < boardHeight * 2; j++){
			if(Board[i][j] == 'X')
				if(Board[i+1][j] == 'Y' || Board[i-1][j] == 'Y' || Board[i][j+1] == 'Y' || Board[i][j-1] == 'Y') return 2; //Draw
		}
	}

	for(int i = 0; i < boardHeight; i++){
		for(int j = 0; j < boardHeight * 2; j++){
			if(Board[i][j] == 'X' || Board[i][j] == 'Y'){
				if(Board[i+1][j] == 'o' || Board[i-1][j] == 'o' || Board[i+1][j] == '|' || Board[i-1][j] == '|' || 
					Board[i][j+3] == 'o' || Board[i][j-3] == 'o' || Board[i][j+1] == '-' || Board[i][j-1] == '-'){
					if(Board[i][j] == 'X')
						if(firstX[0] != i || firstX[1] != j) return 1;	// P2 wins.
					else if(Board[i][j] == 'Y')
						if(firstY[0] != i || firstY[1] != j) return 0; 	// P1 wins.
				}
			}
		}
	}
}
void Tsuro::vacuum(int startpointX, int startpointY, int cardNo, char token){
	int pairInt, i, j, temp;
	char pair;
	if(Board[startpointY-1][startpointX+4] == token){ //Inpects the top-left port.
		Board[startpointY-1][startpointX+4] = 'o';
		temp = Board[startpointY][startpointX+4] - '0';
		pairInt = searchPair(temp, cardNo); // Takes the connected port.
		pair = '0' + pairInt;	// Four different loops for different edges. They searches for the connected port.
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); // Takes the port located there to not miss it.
					Board[i][j] = token;	// Places the token.
				}
		}									// And the same procedure goes on for the rest of the edges.
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}			
	}
	else if(Board[startpointY-1][startpointX+7] == token){ //Inpects the top-right port.
		Board[startpointY-1][startpointX+7] = 'o';
		temp = Board[startpointY][startpointX+7] - '0';
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
	}
	else if(Board[startpointY+2][startpointX+12] == token){ //Inpects the right-top port.
		Board[startpointY+2][startpointX+12] = 'o';
		temp = Board[startpointY+2][startpointX+11] - '0';
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
	}
	else if(Board[startpointY+3][startpointX+12] == token){ //Inpects the right-bottom port.
		Board[startpointY+3][startpointX+12] = 'o';
		temp = Board[startpointY+3][startpointX+11] - '0';		
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
	}
	else if(Board[startpointY+6][startpointX+7] == token){//Inpects the bottom-right port.
		Board[startpointY+6][startpointX+7] = 'o';
		temp = Board[startpointY+5][startpointX+7] - '0';	
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
	}
	else if(Board[startpointY+6][startpointX+4] == token){ //Inpects the bottom-left port.
		Board[startpointY+6][startpointX+4] = 'o';
		temp = Board[startpointY+5][startpointX+4] - '0';			
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
	}
	else if(Board[startpointY+3][startpointX-2] == token){//Inpects the left-bottom port.
		Board[startpointY+3][startpointX-2] = 'o';
		temp = Board[startpointY+3][startpointX] - '0';	
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
	}
	else if(Board[startpointY+2][startpointX-2] == token){ //Inpects the left-top port.
		Board[startpointY+2][startpointX-2] = 'o';
		temp = Board[startpointY+2][startpointX] - '0';	
		pairInt = searchPair(temp, cardNo); 
		pair = '0' + pairInt;
		i = startpointY;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		i = startpointY + cardHeight- 1;
		for(j = startpointX; j < startpointX + (cardHeight * 2); j++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}
		j = startpointX + (cardHeight * 2) - 1;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]); 
					Board[i][j] = token;
				}
		}	
		j = startpointX;
		for(i = startpointY; i < startpointY + (cardHeight * 2); i++){
				if(Board[i][j] == pair){
					Cd[cardNo].setMis(Board[i][j]);
					Board[i][j] = token;
				}
		}
	}
}

int Tsuro::searchPair(int x, int cardNo){	//Takes a port and returns the connected port.
	for(int i = 0; i < cardSize; i++)
		if(Cd[cardNo].getC(i,0) == (x-1)) return (Cd[cardNo].getC(i,1));
}
void Tsuro::initMiniBoard(){	// Fill the miniBoard with -1 s.
	for(int i = 0; i < boardSize; i++){
		for(int j = 0; j < boardSize; j++){
			miniBoard[i][j] = -1;
		}
	}
}
void Tsuro::finalvacuum(char token){	// Vacuum function for the board itself(the edges).
	int i, j;
	i = 0;
	for(j = 0; j < boardHeight * 2; j++){
		if(Board[i][j] == 'o' && j < (boardHeight*2)/3){
			if(Board[i+1][j] == token){
				Board[i][j] = token;
				Board[i+1][j] = Cd[miniBoard[0][0]].getMis();
			}
		} 
		else if(Board[i][j] == 'o' && j < (boardHeight*4)/3){
			if(Board[i+1][j] == token){
				Board[i][j] = token;
				Board[i+1][j] = Cd[miniBoard[0][1]].getMis();
			}
		}
		else if(Board[i][j] == 'o' && j > (boardHeight*4)/3){
			if(Board[i+1][j] == token){
				Board[i][j] = token;
				Board[i+1][j] = Cd[miniBoard[0][2]].getMis();
			}
		}				
	}
	i = boardHeight-1;
	for(j = 0; j < boardHeight * 2; j++){
		if(Board[i][j] == 'o' && j < (boardHeight*2)/3){
			if(Board[i+1][j] == token){
				Board[i][j] = token;
				Board[i+1][j] = Cd[miniBoard[2][0]].getMis();
			}
		} 
		else if(Board[i][j] == 'o' && j < (boardHeight*4)/3){
			if(Board[i+1][j] == token){
				Board[i][j] = token;
				Board[i+1][j] = Cd[miniBoard[2][1]].getMis();
			}
		}
		else if(Board[i][j] == 'o' && j > (boardHeight*4)/3){
			if(Board[i+1][j] == token){
				Board[i][j] = token;
				Board[i+1][j] = Cd[miniBoard[2][2]].getMis();
			}
		}				
	}
	j = 0;
	for(i = 0; i < boardHeight; i++){
		if(Board[i][j] == 'o' && j < boardHeight/3){
			if(Board[i][j+2] == token){
				Board[i][j] = token;
				Board[i][j+2] = Cd[miniBoard[0][0]].getMis();
			}
		} 
		else if(Board[i][j] == 'o' && j < (boardHeight*2)/3){
			if(Board[i][j+2] == token){
				Board[i][j] = token;
				Board[i][j+2] = Cd[miniBoard[1][0]].getMis();
			}
		}
		else if(Board[i][j] == 'o' && j > (boardHeight*2)/3){
			if(Board[i][j+2] == token){
				Board[i][j] = token;
				Board[i][j+2] = Cd[miniBoard[2][0]].getMis();
			}
		}				
	}
	j = (boardHeight * 2) -1;
	for(i = 0; i < boardHeight; i++){
		if(Board[i][j] == 'o' && j < boardHeight/3){
			if(Board[i][j-2] == token){
				Board[i][j] = token;
				Board[i][j-2] = Cd[miniBoard[0][2]].getMis();
			}
		} 
		else if(Board[i][j] == 'o' && j < (boardHeight*2)/3){
			if(Board[i][j-2] == token){
				Board[i][j] = token;
				Board[i][j-2] = Cd[miniBoard[1][2]].getMis();
			}
		}
		else if(Board[i][j] == 'o' && j > (boardHeight*2)/3){
			if(Board[i][j-2] == token){
				Board[i][j] = token;
				Board[i][j-2] = Cd[miniBoard[2][2]].getMis();
			}
		}				
	}
}

