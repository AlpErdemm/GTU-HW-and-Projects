#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define MAX 9  // Max board size (No global variables were allowed)
#define MAXLINE 100  // Size of buffer.
#define MAXPOINT 999

class NPuzzle {     // AI algorithm is quite slow, finds the solution eventually.
public:
    int get_sizeI();
    int get_sizeJ();
    int get_theBoard(int i, int j);
    void mainLoop();    // Asks for moves like HW2, the only function called in main! (Line 587)
    void print();       // Calls Board class to print the board (HW4!) Uses the new overloaded operator!
    void printReport();     // Report same as HW2   
    void readFromFile(string filename);     // Calls Board class to load from file
    void writeToFile(string filename);      // Calls Board class to save to file
    void shuffle(int n);    // Makes n random moves as asked in the pdf
    void reset();       // u
    void setsize(int i, int j);     // Unused! Sets the board size, my output in setsize.png
    void moveRandom();      // Makes a random move
    void moveIntelligent();     // Calls operation_V_jr  
    void move(char m);      // Same as HW2
    void solvePuzzle();     // Calls operation_V
    friend ostream & operator << (ostream & output, NPuzzle & n); // ostream operator overload (asked in HW4)
    friend istream & operator >> (istream & input, NPuzzle n); // İstream operator overload (asked in HW4)
private:
    class Board {
        public:
            inline Board(){
                sizeI = 0;
                sizeJ = 0;
            }
            int get_sizeI();
            int get_sizeJ();
            int get_theBoard(int i, int j);
            void print();       // Prints the board
            void readFromFile(string filename);     // Loads from file
            void writeToFile(string filename);      // Saves to file
            void reset();   // u    
            void setSize(int i, int j);  //Unused! Sets the board size, my output in setsize.png
            void move(char m);  // Same as HW2
            int isSolved();     // Checks if the 
            void goalINIT();    // Initializes the goal-board
            int operation_L();  // Switch to the left
            int operation_R();  // Switch to the right
            int operation_U();  // Switch upwards
            int operation_D();  // Switch downwards
            void operation_V(); // Makes intelligent moves in a loop, same as HW2
            int operation_V_jr();   // Makes an intelligent move, same as HW2  
            int exist_Board(); // Checks if the board is initiated yet 
            int loopCount = 1;  // How many loops have been. (asked in HW4)
            int lastOp = 0; // Recent used operator.(asked in HW4)
            int bestGoal = 99; // Same as HW2
            int operator() (int i, int j); // () operator overload (asked in HW4)
            bool operator == (const Board &b);  // == operator overload (asked in HW4)
        private:
            int sizeI = 0;
            int sizeJ = 0;
            vector<vector <int>> theBoard;  // New 2d vector board
            vector<vector<int>> goal;       // new 2d vector goal board
    };
    vector <Board> b;   // New Board object vector
};
void NPuzzle::mainLoop(){
    char move;
    while(1){   
        cout << "Your move:" ;
        cin >> move;
        cout << endl;
        if (move != 'o' && move != 'O' && !b[0].exist_Board()){
            cout << "No board, try loading one. (enter 'o') " << endl;
        }
        else{
            if(move == 'L'|| move == 'l'){
                b[0].move('l');
            }
            else if(move == 'R' || move == 'r'){
                b[0].move('r');
            }        
            else if(move == 'U'|| move == 'u'){
                b[0].move('u');
            }
            else if(move == 'D'|| move == 'd'){
                b[0].move('d');
            }    
            else if(move == 'I'|| move == 'i'){
                b[0].move('v');
            }
            else if(move == 'S'|| move == 's'){
                int random;
                cout << "How many random moves?" << endl;
                cin >> random;
                cout << endl;
                while(random < 0){
                    cout << "Error, how many random moves?" << endl;
                    cin >> random;
                    cout << endl;
                }
                shuffle(random);
                print();
            } 
            else if(move == 'V' || move == 'v'){
                solvePuzzle();
                print();
            }
            else if(move == 'E' || move == 'e'){
                string filename;
                cout << "Saving initiated, enter a file name." << endl;
                cin >> filename;
                writeToFile(filename);
            }
            else if(move == 'O' || move == 'o'){
                string filename;
                cout << "Loading initiated, enter a file name." << endl;
                cin >> filename;
                readFromFile(filename);
            }
            else if(move == 'T' || move == 't'){
                printReport();
            }
            else if(move == 'Q'){
                exit(0);
            } 
        }
    }   
}
void NPuzzle::print(){
    cout << this;   // Uses the new overloaded operator!
}

void NPuzzle::printReport(){
    cout << "Report: " << endl;
    cout << "How many moves: " << b[0].loopCount << endl;
    if(b[0].isSolved() == 1) 
        cout << "Solution is found." << endl;
    else
        cout << "Solution is not found." << endl;
}
void NPuzzle::readFromFile(string filename){
    b.resize(1);
    b[0].readFromFile(filename);
}
void NPuzzle::writeToFile(string filename){
    b[0].writeToFile(filename);
}

void NPuzzle::shuffle(int n){
    b.resize(1);
    int loop = n;
    while(loop != 0){
        loop--;
        moveRandom();
    }
}
void NPuzzle::reset(){
    b.resize(0);
    b[0].reset();
}

void NPuzzle::setsize(int i, int j){
    b[0].setSize(i, j);
}

void NPuzzle::moveRandom(){
    b.resize(1);
    int op = 1 + rand() % 3;
    if(op == 1){
        b[0].operation_L();
    }
    else if (op == 2){
        b[0].operation_R();
    }
    else if(op == 3){
        b[0].operation_U();
    }
    else if (op == 4){
        b[0].operation_D();
    }    
}

void NPuzzle::moveIntelligent(){
    b[0].move('v');
}

void NPuzzle::move(char m){
    b.resize(1);
    b[0].move(m);
}

void NPuzzle::solvePuzzle(){
    b[0].operation_V();
}
ostream & operator << (ostream & output, NPuzzle & n){
    for (int i = 0; i < n.get_sizeI(); i++){
        for(int j = 0; j < n.get_sizeJ(); j++){
            if(n.get_theBoard(i, j) == -1) cout << "   ";
            else{
                if(n.get_theBoard(i,j) < 10) output << n.get_theBoard(i,j) << "  ";
                else output << n.get_theBoard(i,j) << " ";
            }
        }
        output << endl;
    }
    return output;
}
int NPuzzle::get_sizeI(){
    return b[0].get_sizeI();
}
int NPuzzle::get_sizeJ(){
      return b[0].get_sizeJ();
}
int NPuzzle::get_theBoard(int i, int j){
      return b[0].get_theBoard(i, j);
}
int NPuzzle::Board::get_sizeI(){
    return sizeI;
}
int NPuzzle::Board::get_sizeJ(){
    return sizeJ;
}
int NPuzzle::Board::get_theBoard(int i, int j){
    return theBoard[i][j];
}
istream & operator >> (istream & input, NPuzzle n){
    /*
    for(int i = 0; i < n.get_sizeI(); i++){
        for(int j = 0; j < n.get_sizeJ(); j++){
            input >> data;
            if((int)(data[0] - '0') != 50)
                theBoard[i][j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
            else
                theBoard[i][j] = -1;
        }
    }*/
    return input;
}
void NPuzzle::Board::print(){
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
void NPuzzle::Board::readFromFile(string filename){
    char data[MAXLINE];
    ifstream file(filename);
    string str;

    getline(file, str);
    sizeI = 1;
    sizeJ = str.length() / 3;
    
    while(!file.eof()){
        sizeI++;
        getline(file, str);
    }
    cout << "Lines -> " << sizeI << endl;
    cout << "Columns -> " << sizeJ << endl;

    theBoard.resize(sizeI);
    for(int i = 0; i < sizeI; i++){
        theBoard[i].resize(sizeJ);
    }

    file.clear();
    file.seekg(0, ios::beg);
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            file >> data;
            if((int)(data[0] - '0') != 50)
                theBoard[i][j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
            else
                theBoard[i][j] = -1;
        }
    }
    cout << "Loaded from file: " << filename <<  endl;
    file.close();   
    print();
}
void NPuzzle::Board::writeToFile(string filename){
    ofstream file(filename);
    string str;
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(i == sizeI-1 && j == sizeJ-1){
                if(theBoard[i][j] == -1){
                    file << "bb";
                }
                else if(theBoard[i][j] < 10){
                    file << '0' << theBoard[i][j];
                }
                else{
                    file << theBoard[i][j];
                }
            }
            else{
                if(theBoard[i][j] == -1){
                    file << "bb ";
                }
                else if(theBoard[i][j] < 10){
                    file << '0' << theBoard[i][j] << " ";
                }
                else{
                    file << theBoard[i][j] << " ";
                }
            }
        }
        if(i != sizeI-1)
            file << '\n';
    }
    cout << "Saved to file: " << filename << endl;
    file.close();
}
void NPuzzle::Board::reset(){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            theBoard[i][j] = goal[i][j];
        }
    }
}

void NPuzzle::Board::setSize(int i, int j){
    sizeI = i;
    sizeJ = j;
    goalINIT();
    reset();
}

void NPuzzle::Board::move(char m){
    if(m == 'L'|| m == 'l'){
        operation_L();
        print();
    }
    else if(m == 'R' || m == 'r'){
        operation_R();
        print();
    }        
    else if(m == 'U'|| m == 'u'){
        operation_U();
        print();
    }
    else if(m == 'D'|| m == 'd'){
        operation_D();
        print();
    } 
}

int NPuzzle::Board::isSolved(){
    goalINIT();
    int current = 0;  
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] != 0){
                if(theBoard[i][j] != goal[i][j]){
                    current++;
                }
            }
        }
    }
    if(current == 0)return 1;
    else return 0;
}

void NPuzzle::Board::goalINIT(){
    goal.resize(sizeI);
    int count = 1;
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            goal[i].resize(sizeJ);
            if(i == sizeI-1 && j == sizeJ-1){
                goal[i][j] = -1;
            }
            else if(theBoard[i][j] == 0)
                goal[i][j] = 0;
            else{  
                goal[i][j] = count;
                count++;
            }
        }
    }
}
int NPuzzle::Board::operation_L(){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] == -1){
                if(j == 0){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if (theBoard[i][j-1] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;    
                }
                else{
                    theBoard[i][j] = theBoard[i][j-1];
                    theBoard[i][j-1] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int NPuzzle::Board::operation_R(){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] == -1){
                if(j == sizeJ-1){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if(theBoard[i][j+1] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;
                }
                else{
                    theBoard[i][j] = theBoard[i][j+1];
                    theBoard[i][j+1] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }
    return 0;   
}

int NPuzzle::Board::operation_U(){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] == -1){
                if(i == 0){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if(theBoard[i-1][j] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;
                }
                else{
                    theBoard[i][j] = theBoard[i-1][j];
                    theBoard[i-1][j] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }   
    return 0; 
}

int NPuzzle::Board::operation_D(){
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] == -1){
                if(i == sizeI-1){
                    //cerr << "This move cannot be performed.1" << endl;
                    return 0;
                }
                else if(theBoard[i+1][j] == 0){
                    //cerr << "This move cannot be performed.2" << endl;
                    return 0;
                }
                else{
                    theBoard[i][j] = theBoard[i+1][j];
                    theBoard[i+1][j] = -1;
                    //cout << "Succesfully performed." << endl;
                    loopCount++;
                    return 1;
                }
            }
        }
    }    
    return 0;
}

int NPuzzle::Board::operation_V_jr(){
    
    int first = 0;
    int current = 0;
    int op = 0;
    int result = 0;
    int temp [MAX][MAX];
    
    goalINIT();

    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            temp[i][j] = theBoard[i][j];
        }
    }
    if(loopCount % 5 == 0){
        op = 1 + rand() % 4;
    }
    else{
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                temp[i][j] = theBoard[i][j];
            }
        }
        result = operation_L();
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(theBoard[i][j] != 0){
                    if(theBoard[i][j] != goal[i][j]){
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
                theBoard[i][j] = temp[i][j];
            }
        }
        result = operation_R();
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(theBoard[i][j] != 0){
                    if(theBoard[i][j] != goal[i][j]){
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
                theBoard[i][j] = temp[i][j];
            }
        }
        result = operation_U();
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(theBoard[i][j] != 0){
                    if(theBoard[i][j] != goal[i][j]){
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
                theBoard[i][j] = temp[i][j];
            }
        }
        result = operation_D();
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(theBoard[i][j] != 0){
                    if(theBoard[i][j] != goal[i][j]){
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
                theBoard[i][j] = temp[i][j];
            }
        }
    }
        if(op == 1){
            operation_L();
        }
        else if (op == 2){
            operation_R();
        }
        else if(op == 3){
            operation_U();
        }
        else if (op == 4){
            operation_D();
        }
        lastOp = op;
    
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] != 0){
                if(theBoard[i][j] != goal[i][j]){
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
void NPuzzle::Board::operation_V(){
    loopCount = 0;
    while(operation_V_jr() == 0){
        print();
    }
    cout << "Reached goal: " << endl;
    print();
}

int NPuzzle::Board::exist_Board(){
    if(sizeI == 0 || sizeJ == 0){
        return 0;
    }
    return 1;
}
int NPuzzle::Board::operator() (int i, int j){
    return theBoard[i][j]; // returns the cell content i, j.
}
bool NPuzzle::Board::operator== (const Board& b){   // compares two boards.
    for(int i = 0; i < sizeI; i++){
        for(int j = 0; j < sizeJ; j++){
            if(theBoard[i][j] != b.theBoard[i][j]){
                return false;
            }
        }
    }
    return true;
}
int main(int argc, char *argv[]){   // Main function
    srand (time(NULL));
    NPuzzle n;
    n.mainLoop();
    return 0;
}