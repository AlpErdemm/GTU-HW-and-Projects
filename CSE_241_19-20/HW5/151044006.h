#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define MAX 9  // Max board size (No global variables were allowed)
#define MAXLINE 100  // Size of buffer.
#define MAXPOINT 999
/* ----- "HOW TO USE" FOR HW5 ----------
I've implemented three modes for AbstractBoard class which can be activated by:

    AbstractBoard b(0); Stores the board in BoardVector class.
    AbstractBoard b(1); Stores the board in BoardArray1D class.
    AbstractBoard b(2); Stores the board in BoardArray2D class.

----------------------------------------- */
namespace hw5space{
class BoardVector;
class BoardArray1D;
class BoardArray2D;
class AbstractBoard {     // AI algorithm is quite slow, finds the solution eventually.
public: //-> Functions that are added for HW5
    AbstractBoard();
    AbstractBoard(int mode);

    void readFromFileVec(string filename, BoardVector & vec);     // Calls Board class to load from file(new!)(For BoardVector!)
    void readFromFile1D(string filename, BoardArray1D & d1);     // Calls Board class to load from file(new!)(For BoardArray1D!)
    void readFromFile2D(string filename, BoardArray2D & d2);     // Calls Board class to load from file(new!)(For BoardArray2D!)

    void writeToFileVec(string filename, BoardVector & vec);      // Calls Board class to save to file(new!)(For BoardVector!)
    void writeToFile1D(string filename, BoardArray1D & d1);      // Calls Board class to save to file(new!)(For BoardArray1D!)
    void writeToFile2D(string filename, BoardArray2D & d2);      // Calls Board class to save to file(new!)(For BoardArray2D!)
   
    void resetVec(BoardVector & vec);                           // (new!)
    void reset1D(BoardArray1D & d1);                           // (new!)
    void reset2D(BoardArray2D & d2);                           // (new!)

    void setsize(int i, int j);             // (new!)
    void move(char m);                      // Makes a move, same as HW2 (for HW5!)

    void printVec(BoardVector & vec);       // Print for BoardVector class
    void print1D(BoardArray1D & d1);        // Print for BoardArray1D class
    void print2D(BoardArray2D & d2);        // Print for BoardArray2D class

    void goalINITVec(BoardVector & vec);    // Initializes the goal-board
    void goalINIT1D(BoardArray1D & d1);    // Initializes the goal-board
    void goalINIT2D(BoardArray2D & d2);    // Initializes the goal-board

    bool isSolvedVec(BoardVector & vec);    // Checks if the solution is found
    bool isSolved1D(BoardArray1D & d1);     // Checks if the solution is found
    bool isSolved2D(BoardArray2D & d2);     // Checks if the solution is found

    void setsizeVec(int i, int j, BoardVector & vec);   // Sets the size of the board
    void setsize1D(int i, int j, BoardArray1D & d1);    // Sets the size of the board
    void setsize2D(int i, int j, BoardArray2D & d2);    // Sets the size of the board

    int moveVec(char m, BoardVector & vec);
    int move1D(char m, BoardArray1D & d1);
    int move2D(char m, BoardArray2D & d2);

    // Other asked functions (including the overloads) will be implemented in three Board classes.
    // <- End of functions that are added for HW5

public: // Old functions
    int get_sizeI();
    int get_sizeJ();
    int get_theBoard(int i, int j);
    void mainLoop();    // Asks for moves like HW2, the only function called in main! (Line 587)
    void printReport();     // Report same as HW2   
    void shuffle(int n);    // Makes n random moves as asked in the pdf
    void moveRandom();      // Makes a random move
    void moveIntelligent();     // Calls operation_V_jr  
    void solvePuzzle();     // Calls operation_V
    friend ostream & operator << (ostream & output, AbstractBoard & n); // ostream operator overload (asked in HW4)
    friend istream & operator >> (istream & input, AbstractBoard n); // İstream operator overload (asked in HW4)
    // End of old functions

    int storemode;

    vector <BoardVector> b;   // New Board object vector
   // BoardArray1D b1;
   // BoardArray2D b2;

};

class BoardVector : public  AbstractBoard{
public:
    int sizeI = 0;
    int sizeJ = 0;
    vector<vector <int>> theBoard;  // New 2d vector board
    vector<vector<int>> goal;       // new 2d vector goal board
};

class BoardArray1D : public  AbstractBoard{
public:
    int sizeI = 0;
    int sizeJ = 0;
    int * theBoard;
    vector<vector<int>> goal;       // new 2d vector goal board
};

class BoardArray2D : public  AbstractBoard{
public:
    int sizeI = 0;
    int sizeJ = 0;    
    int ** theBoard;
    vector<vector<int>> goal;       // new 2d vector goal board
};
}