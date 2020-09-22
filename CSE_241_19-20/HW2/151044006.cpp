#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAXPOINT = 999; // Top bound
const int MAX = 15; // Max board size (need to be increased if necessary!)
const int MAXLINE = 100; // Size of buffer.
int board [MAX][MAX]; // The gameboard.
int goal [MAX][MAX]; // The board that we strive to reach.
int lastOp = 0; // Recent used operator.
int loopCount = 1;  // How many loops have been.
int bestGoal = 99;  
int found = 0; // Found a solution or not.
int boardJ = 0; // Columns.
int boardI = 0; // Lines.

void printBoard(int theBoard[][MAX], int sizeI, int sizeJ); // Prints the given board
int operation_L(int sizeI, int sizeJ);  // Switch to Left operation
int operation_R(int sizeI, int sizeJ);  // Switch to right operation
int operation_D(int sizeI, int sizeJ);  // Switch downwards operation
int operation_U(int sizeI, int sizeJ);  // Switch upwards operation
int operation_I(int sizeI, int sizeJ);  // Old intelligent move (may take a while, to see the steps, 
                                        // passing output to a file recommended.)
int operation_V_jr(int sizeI, int sizeJ);   // New intelligent move 
int operation_V(int sizeI, int sizeJ);  // New intelligent move (may take a while, to see the steps, 
                                        // passing output to a file recommended.)
int operation_Y(int sizeI, int sizeJ);  // Load from file
int operation_E(int sizeI, int sizeJ);  // Save to file
int operation_T();  // Report
void operation_SHUFFLE(int sizeI, int sizeJ);   // Shuffle
void goalINIT(int sizeI, int sizeJ);    // Initialize the goal sitution.


int main(int argc, char *argv[]){

    // Basic execution rules:
    // 1. Simply execute the makefile.
    // 2. Or, give another filename as a main argument.

    if(argc == 2){ // If filename is given, open the file and fill the board array with it.
        cout << argv[1] << endl;
        ifstream file("example.txt");
        string str;
        char data[MAXLINE];
        getline(file, str);
        boardI++;
        boardJ = str.length() / 3;
        while(!file.eof()){
            boardI++;
            getline(file, str);
        }
        cout << "Lines -> " << boardI << endl;
        cout << "Columns -> " << boardJ << endl;

        file.clear();
        file.seekg(0, ios::beg);
        for(int i = 0; i < boardI; i++){
            for(int j = 0; j < boardJ; j++){
                file >> data;
                if((int)(data[0] - '0') != 50)
                    board[i][j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
                else
                    board[i][j] = -1;
            }
        }
        file.close();
        printBoard(board, boardI, boardJ);
    }
    else{ // If there is no arguments given, execute load operation.
            operation_Y(boardI, boardJ);
            printBoard(board, boardI, boardJ);
    }
    char move;
    goalINIT(boardI, boardJ);

    while(1){   // Main loop, asks for moves.
        cout << "Your move:" ;
        cin >> move;
        cout << endl;
        if(move == 'L'|| move == 'l'){
            operation_L(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }
        else if(move == 'R' || move == 'r'){
            operation_R(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }        
        else if(move == 'U'|| move == 'u'){
            operation_U(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }
        else if(move == 'D'|| move == 'd'){
            operation_D(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }    
        else if(move == 'I'|| move == 'i'){
            operation_I(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }
        else if(move == 'S'|| move == 's'){
            operation_SHUFFLE(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        } 
        else if(move == 'V' || move == 'v'){
            operation_V(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }
        else if(move == 'E' || move == 'e'){
            operation_E(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }
        else if(move == 'Y' || move == 'y'){
            operation_Y(boardI, boardJ);
            printBoard(board, boardI, boardJ);
        }
        else if(move == 'T' || move == 't'){
            operation_T();
            //printBoard(board, boardI, boardJ);
        }
        else if(move == 'Q'){
            exit(0);
        } 
    }

    return 0;
}
void printBoard(int theBoard[][MAX], int sizeI, int sizeJ){
    for (int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] == -1) cout << "   ";
            else{
                if(theBoard[i][j] < 10) cout << theBoard[i][j] << "  ";
                else cout << theBoard[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int operation_L(int sizeI, int sizeJ){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(board[i][j] == -1){
                if(j == 0){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if (board[i][j-1] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;    
                }
                else{
                    board[i][j] = board[i][j-1];
                    board[i][j-1] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }
}

int operation_R(int sizeI, int sizeJ){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(board[i][j] == -1){
                if(j == sizeJ-1){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if(board[i][j+1] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i][j+1];
                    board[i][j+1] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }
}

int operation_U(int sizeI, int sizeJ){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(board[i][j] == -1){
                if(i == 0){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if(board[i-1][j] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i-1][j];
                    board[i-1][j] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }
}
int operation_D(int sizeI, int sizeJ){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(board[i][j] == -1){
                if(i == sizeI-1){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if(board[i+1][j] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i+1][j];
                    board[i+1][j] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }
}

int operation_I(int sizeI, int sizeJ){
    int first = 0;
    int current = 0;
    int op = 0;
    int result = 0;
    int temp [sizeI][sizeJ];
    loopCount = 0;

    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            temp[i][j] = board[i][j];
        }
    }

        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                temp[i][j] = board[i][j];
            }
        }
        result = operation_L(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 2){
            current = MAXPOINT;
        }
        first = current;
        current = 0;    
        op = 1;
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_R(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 1){
            current = MAXPOINT;
        }
        if(current < first){
            first = current;
            op = 2;
        }
        current = 0;    
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_U(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 4){
            current = MAXPOINT;
        }
        if(current < first){
            first = current;
            op = 3;
        }
        current = 0;    
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_D(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 3){
            current = MAXPOINT;
        }
        if(current < first){
            first = current;
            op = 4;
        }
        current = 0;    
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        if(op == 1){
            operation_L(sizeI, sizeJ);
        }
        else if (op == 2){
            operation_R(sizeI, sizeJ);
        }
        else if(op == 3){
            operation_U(sizeI, sizeJ);
        }
        else if (op == 4){
            operation_D(sizeI, sizeJ);
        }
    lastOp = op;

    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(board[i][j] != 0){
                if(board[i][j] != goal[i][j]){
                    current++;
                }
            }
        }
    }
    if(bestGoal > current) bestGoal = current;
    cout << "Misplaced tiles left: " << current << endl;
    loopCount++;
    found = 0;
    if(current == 0){found = 1; return 1;}
    else return 0;
    
    // Tüm operasyonları dene, h değeri en küçük olanı yap.
    // goal'e ulaşıldıysa 1 döndür.
}

void operation_SHUFFLE(int sizeI, int sizeJ){
    while(operation_I(sizeI, sizeJ) == 0){
        printBoard(board, sizeI, sizeJ);
    }
    cout << "Reached goal: " << endl;
    printBoard(board, sizeI, sizeJ);
}

void goalINIT(int sizeI, int sizeJ){
    int count = 1;
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(i == sizeI-1 && j == sizeJ-1){
                goal[i][j] = -1;
            }
            else if(board[i][j] == 0)
                goal[i][j] = 0;
            else{  
                goal[i][j] = count;
                count++;
            }
        }
    }
}
int operation_V_jr(int sizeI, int sizeJ){
 int first = 0;
    int current = 0;
    int op = 0;
    int result = 0;
    int temp [sizeI][sizeJ];

    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            temp[i][j] = board[i][j];
        }
    }
    if(loopCount % 5 == 0){
        op = 1 + rand() % 4;
    }
    else{
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                temp[i][j] = board[i][j];
            }
        }
        result = operation_L(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 2){
            current = MAXPOINT;
        }
        first = current;
        current = 0;    
        op = 1;
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_R(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 1){
            current = MAXPOINT;
        }
        if(current < first){
            first = current;
            op = 2;
        }
        current = 0;    
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_U(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 4){
            current = MAXPOINT;
        }
        if(current < first){
            first = current;
            op = 3;
        }
        current = 0;    
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_D(sizeI, sizeJ);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(board[i][j] != 0){
                    if(board[i][j] != goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(result == 0 || lastOp == 3){
            current = MAXPOINT;
        }
        if(current < first){
            first = current;
            op = 4;
        }
        current = 0;    
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                board[i][j] = temp[i][j];
            }
        }
    }
        if(op == 1){
            operation_L(sizeI, sizeJ);
        }
        else if (op == 2){
            operation_R(sizeI, sizeJ);
        }
        else if(op == 3){
            operation_U(sizeI, sizeJ);
        }
        else if (op == 4){
            operation_D(sizeI, sizeJ);
        }
        lastOp = op;

    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(board[i][j] != 0){
                if(board[i][j] != goal[i][j]){
                    current++;
                }
            }
        }
    }
    if(bestGoal > current) bestGoal = current;
    cout << "Misplaced tiles left: " << current << endl;
    loopCount++;
    if(current == 0) return 1;
    else return 0;    
}
int operation_V(int sizeI, int sizeJ){
    loopCount = 0;
    while(operation_V_jr(sizeI, sizeJ) == 0){
        printBoard(board, sizeI, sizeJ);
    }
    cout << "Reached goal: " << endl;
    printBoard(board, sizeI, sizeJ);
}
int operation_T(){
    cout << "Report: " << endl;
    cout << "How many moves: " << loopCount << endl;
    if(found == 1) 
        cout << "Solution is found." << endl;
    else
        cout << "Solution is not found." << endl;
    return 0;
}
int operation_E(int sizeI, int sizeJ){
    string filename;
    cout << "Save protocol initiated, enter a filename." << endl;
    cin >> filename;
    ofstream file(filename);
    string str;
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(i == sizeI-1 && j == sizeJ-1){
                if(board[i][j] == -1){
                    file << "bb";
                }
                else if(board[i][j] < 10){
                    file << '0' << board[i][j];
                }
                else{
                    file << board[i][j];
                }
            }
            else{
                if(board[i][j] == -1){
                    file << "bb ";
                }
                else if(board[i][j] < 10){
                    file << '0' << board[i][j] << " ";
                }
                else{
                    file << board[i][j] << " ";
                }
            }
        }
        if(i != sizeI-1)
            file << '\n';
    }
    cout << "Saved to file: " << filename << endl;
    file.close();
}
int operation_Y(int sizeI, int sizeJ){
    string filename;
    cout << "Load protocol initiated, enter a filename." << endl;
    cin >> filename;
    char data[MAXLINE];
    ifstream file(filename);
    string str;

    getline(file, str);
    boardI = 0;
    boardI++;
    boardJ = str.length() / 3;

    while(!file.eof()){
        boardI++;
        getline(file, str);
    }
    cout << "Lines -> " << boardI << endl;
    cout << "Columns -> " << boardJ << endl;

    file.clear();
    file.seekg(0, ios::beg);

    for(int i = 0; i < boardI; i++){
        for(int j = 0; j < boardJ; j++){
            file >> data;
            if((int)(data[0] - '0') != 50)
                board[i][j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
            else
                board[i][j] = -1;
        }
    }
    cout << "Loaded from file: " << filename <<  endl;
    file.close();   
}
