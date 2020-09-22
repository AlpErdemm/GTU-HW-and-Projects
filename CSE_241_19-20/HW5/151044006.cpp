#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "151044006.h"                // The headerfile that is asked for in HW5 pdf.(Seperation of Implementations and Declerations)

using namespace std;
using namespace hw5space;       // The namespace that is asked for in HW5 pdf.

/* ----- "HOW TO USE" FOR HW5 ----------
    
    I've implemented three modes for AbstractBoard class which can be activated by:

    AbstractBoard b(0); Stores the board in BoardVector class.
    AbstractBoard b(1); Stores the board in BoardArray1D class.
    AbstractBoard b(2); Stores the board in BoardArray2D class.

    1. Inheritance achieved.
    2. Header File created.
    3. Namespace hw5space.
    4. Dynamic Allocation is done for store classes.
    5. Screeenshots of Save and Load for every class.

----------------------------------------- */
AbstractBoard::AbstractBoard(){
    // left blank
}
AbstractBoard::AbstractBoard(int mode){
    storemode = mode;
}
void AbstractBoard::printVec(BoardVector & vec){
    for (int i = 0; i < vec.sizeI; i++){
        for(int j = 0; j < vec.sizeJ; j++){
            if(vec.theBoard[i][j] == -1) cout << "   ";
            else{
                if(vec.theBoard[i][j] < 10) cout << vec.theBoard[i][j] << "  ";
                else cout << vec.theBoard[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void AbstractBoard::print1D(BoardArray1D & d1){
    for (int i = 0; i < d1.sizeI; i++){
        for(int j = 0; j < d1.sizeJ; j++){
            if(d1.theBoard[i*d1.sizeJ + j] == -1) cout << "   ";
            else{
                if(d1.theBoard[i*d1.sizeJ + j] < 10) cout << d1.theBoard[i*d1.sizeJ + j] << "  ";
                else cout << d1.theBoard[i*d1.sizeJ + j] << " ";
            }
        }
        cout << endl;
    }
}
void AbstractBoard::print2D(BoardArray2D & d2){
    for (int i = 0; i < d2.sizeI; i++){
        for(int j = 0; j < d2.sizeJ; j++){
            if(d2.theBoard[i][j] == -1) cout << "   ";
            else{
                if(d2.theBoard[i][j] < 10) cout << d2.theBoard[i][j] << "  ";
                else cout << d2.theBoard[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void AbstractBoard::readFromFileVec(string filename, BoardVector & vec){
    char data[MAXLINE];
    ifstream file(filename);
    string str;

    getline(file, str);
    vec.sizeI = 1;
    vec.sizeJ = str.length() / 3;
    
    while(!file.eof()){
        vec.sizeI++;
        getline(file, str);
    }
    cout << "Lines -> " << vec.sizeI << endl;
    cout << "Columns -> " << vec.sizeJ << endl;

    vec.theBoard.resize(vec.sizeI);
    for(int i = 0; i < vec.sizeI; i++){
        vec.theBoard[i].resize(vec.sizeJ);
    }

    file.clear();
    file.seekg(0, ios::beg);
    for(int i = 0; i < vec.sizeI; i++){
        for(int j = 0; j < vec.sizeJ; j++){
            file >> data;
            if((int)(data[0] - '0') != 50)
                vec.theBoard[i][j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
            else
                vec.theBoard[i][j] = -1;
        }
    }
    cout << "Loaded from file: " << filename <<  endl;
    file.close();   
    printVec(vec);
}

void AbstractBoard::readFromFile1D(string filename, BoardArray1D & d1){
    char data[MAXLINE];
    ifstream file(filename);
    string str;

    getline(file, str);
    d1.sizeI = 1;
    d1.sizeJ = str.length() / 3;
    
    while(!file.eof()){
        d1.sizeI++;
        getline(file, str);
    }
    cout << "Lines -> " << d1.sizeI << endl;
    cout << "Columns -> " << d1.sizeJ << endl;

    d1.theBoard = new int [d1.sizeI * d1.sizeJ];     // Dynamic Allocation

    file.clear();
    file.seekg(0, ios::beg);
    for(int i = 0; i < d1.sizeI; i++){
        for(int j = 0; j < d1.sizeJ; j++){
            file >> data;
            if((int)(data[0] - '0') != 50)
                d1.theBoard[i*d1.sizeJ + j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
            else
                d1.theBoard[i*d1.sizeJ + j] = -1;
        }
    }
    cout << "Loaded from file: " << filename <<  endl;
    file.close();   
    print1D(d1);
}

void AbstractBoard::readFromFile2D(string filename, BoardArray2D & d2){
    char data[MAXLINE];
    ifstream file(filename);
    string str;

    getline(file, str);
    d2.sizeI = 1;
    d2.sizeJ = str.length() / 3;
    
    while(!file.eof()){
        d2.sizeI++;
        getline(file, str);
    }
    cout << "Lines -> " << d2.sizeI << endl;
    cout << "Columns -> " << d2.sizeJ << endl;

    d2.theBoard = new int * [d2.sizeI];     // Dynamic Allocation
    for(int i = 0; i < d2.sizeI; i++){
        d2.theBoard[i] = new int [d2.sizeJ];
    }

    file.clear();
    file.seekg(0, ios::beg);
    for(int i = 0; i < d2.sizeI; i++){
        for(int j = 0; j < d2.sizeJ; j++){
            file >> data;
            if((int)(data[0] - '0') != 50)
                d2.theBoard[i][j] = (int)(data[0] - '0') * 10 + (int)(data[1] - '0');
            else
                d2.theBoard[i][j] = -1;
        }
    }
    cout << "Loaded from file: " << filename <<  endl;
    file.close();   
    print2D(d2);
}

void AbstractBoard::writeToFileVec(string filename, BoardVector & vec){
  ofstream file(filename);
    string str;
    for(int i = 0; i < vec.sizeI; i++){
        for(int j = 0; j < vec.sizeJ; j++){
            if(i == vec.sizeI-1 && j == vec.sizeJ-1){
                if(vec.theBoard[i][j] == -1){
                    file << "bb";
                }
                else if(vec.theBoard[i][j] < 10){
                    file << '0' << vec.theBoard[i][j];
                }
                else{
                    file << vec.theBoard[i][j];
                }
            }
            else{
                if(vec.theBoard[i][j] == -1){
                    file << "bb ";
                }
                else if(vec.theBoard[i][j] < 10){
                    file << '0' << vec.theBoard[i][j] << " ";
                }
                else{
                    file << vec.theBoard[i][j] << " ";
                }
            }
        }
        if(i != vec.sizeI-1)
            file << '\n';
    }
    cout << "Saved to file: " << filename << endl;
    file.close();    
}

void AbstractBoard::writeToFile1D(string filename, BoardArray1D & d1){
  ofstream file(filename);
    string str;
    for(int i = 0; i < d1.sizeI; i++){
        for(int j = 0; j < d1.sizeJ; j++){
            if(i == d1.sizeI-1 && j == d1.sizeJ-1){
                if(d1.theBoard[i*d1.sizeJ + j] == -1){
                    file << "bb";
                }
                else if(d1.theBoard[i*d1.sizeJ + j] < 10){
                    file << '0' << d1.theBoard[i*d1.sizeJ + j];
                }
                else{
                    file << d1.theBoard[i*d1.sizeJ + j];
                }
            }
            else{
                if(d1.theBoard[i*d1.sizeJ + j] == -1){
                    file << "bb ";
                }
                else if(d1.theBoard[i*d1.sizeJ + j] < 10){
                    file << '0' << d1.theBoard[i*d1.sizeJ + j] << " ";
                }
                else{
                    file << d1.theBoard[i*d1.sizeJ + j] << " ";
                }
            }
        }
        if(i != d1.sizeI-1)
            file << '\n';
    }
    cout << "Saved to file: " << filename << endl;
    file.close();  
}

void AbstractBoard::writeToFile2D(string filename, BoardArray2D & d2){
  ofstream file(filename);
    string str;
    for(int i = 0; i < d2.sizeI; i++){
        for(int j = 0; j < d2.sizeJ; j++){
            if(i == d2.sizeI-1 && j == d2.sizeJ-1){
                if(d2.theBoard[i][j] == -1){
                    file << "bb";
                }
                else if(d2.theBoard[i][j] < 10){
                    file << '0' << d2.theBoard[i][j];
                }
                else{
                    file << d2.theBoard[i][j];
                }
            }
            else{
                if(d2.theBoard[i][j] == -1){
                    file << "bb ";
                }
                else if(d2.theBoard[i][j] < 10){
                    file << '0' << d2.theBoard[i][j] << " ";
                }
                else{
                    file << d2.theBoard[i][j] << " ";
                }
            }
        }
        if(i != d2.sizeI-1)
            file << '\n';
    }
    cout << "Saved to file: " << filename << endl;
    file.close();  
}
void AbstractBoard::resetVec(BoardVector & vec){
    vec.goalINITVec(vec);
    for(int i = 0; i < vec.sizeI; i++){
        for(int j = 0; j < vec.sizeJ; j++){
            vec.theBoard[i][j] = vec.goal[i][j];
        }
    }
}
void AbstractBoard::reset1D(BoardArray1D & d1){
    for(int i = 0; i < d1.sizeI; i++){
        for(int j = 0; j < d1.sizeJ; j++){
            d1.theBoard[i * d1.sizeJ + j] = d1.goal[i][j];
        }
    }
}
void AbstractBoard::reset2D(BoardArray2D & d2){
    for(int i = 0; i < d2.sizeI; i++){
        for(int j = 0; j < d2.sizeJ; j++){
            d2.theBoard[i][j] = d2.goal[i][j];
        }
    }
}

void AbstractBoard::setsizeVec(int i, int j,  BoardVector & vec){
    vec.sizeI = i;
    vec.sizeJ = j;
    vec.goalINITVec(vec);
    vec.resetVec(vec);
}

void AbstractBoard::setsize1D(int i, int j,  BoardArray1D & d1){
    d1.sizeI = i;
    d1.sizeJ = j;
    d1.goalINIT1D(d1);
    d1.reset1D(d1);
}

void AbstractBoard::setsize2D(int i, int j,  BoardArray2D & d2){
    d2.sizeI = i;
    d2.sizeJ = j;
    d2.goalINIT2D(d2);
    d2.reset2D(d2);
}

int AbstractBoard::move2D(char m, BoardArray2D & d2){
    if(m == 'L'|| m == 'l'){
        for(int i = 0; i < d2.sizeI; i++){
            for(int j = 0; j < d2.sizeJ; j++){
                if(d2.theBoard[i][j] == -1){
                    if(j == 0){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if (d2.theBoard[i][j-1] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;    
                    }
                    else{
                        d2.theBoard[i][j] = d2.theBoard[i][j-1];
                        d2.theBoard[i][j-1] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }
    }
    else if(m == 'R' || m == 'r'){
        for(int i = 0; i < d2.sizeI; i++){
            for(int j = 0; j < d2.sizeJ; j++){
                if(d2.theBoard[i][j] == -1){
                    if(j == d2.sizeJ-1){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if(d2.theBoard[i][j+1] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;
                    }
                    else{
                        d2.theBoard[i][j] = d2.theBoard[i][j+1];
                        d2.theBoard[i][j+1] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }
    }        
    else if(m == 'U'|| m == 'u'){
        for(int i = 0; i < d2.sizeI; i++){
            for(int j = 0; j < d2.sizeJ; j++){
                if(d2.theBoard[i][j] == -1){
                    if(i == 0){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if(d2.theBoard[i-1][j] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;
                    }
                    else{
                        d2.theBoard[i][j] = d2.theBoard[i-1][j];
                        d2.theBoard[i-1][j] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }
   
    }
    else if(m == 'D'|| m == 'd'){
        for(int i = 0; i < d2.sizeI; i++){
            for(int j = 0; j < d2.sizeJ; j++){
                if(d2.theBoard[i][j] == -1){
                    if(i == d2.sizeI-1){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if(d2.theBoard[i+1][j] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;
                    }
                    else{
                        d2.theBoard[i][j] = d2.theBoard[i+1][j];
                        d2.theBoard[i+1][j] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }  
    }
    return 0;
}

int AbstractBoard::moveVec(char m, BoardVector & vec){
    if(m == 'L'|| m == 'l'){
        for(int i = 0; i < vec.sizeI; i++){
            for(int j = 0; j < vec.sizeJ; j++){
                if(vec.theBoard[i][j] == -1){
                    if(j == 0){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if (vec.theBoard[i][j-1] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;    
                    }
                    else{
                        vec.theBoard[i][j] = vec.theBoard[i][j-1];
                        vec.theBoard[i][j-1] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }
    }
    else if(m == 'R' || m == 'r'){
        for(int i = 0; i < vec.sizeI; i++){
            for(int j = 0; j < vec.sizeJ; j++){
                if(vec.theBoard[i][j] == -1){
                    if(j == vec.sizeJ-1){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if(vec.theBoard[i][j+1] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;
                    }
                    else{
                        vec.theBoard[i][j] = vec.theBoard[i][j+1];
                        vec.theBoard[i][j+1] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }
    }        
    else if(m == 'U'|| m == 'u'){
        for(int i = 0; i < vec.sizeI; i++){
            for(int j = 0; j < vec.sizeJ; j++){
                if(vec.theBoard[i][j] == -1){
                    if(i == 0){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if(vec.theBoard[i-1][j] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;
                    }
                    else{
                        vec.theBoard[i][j] = vec.theBoard[i-1][j];
                        vec.theBoard[i-1][j] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }
   
    }
    else if(m == 'D'|| m == 'd'){
        for(int i = 0; i < vec.sizeI; i++){
            for(int j = 0; j < vec.sizeJ; j++){
                if(vec.theBoard[i][j] == -1){
                    if(i == vec.sizeI-1){
                        //cerr << "This move cannot be performed.1" << endl;
                        return 0;
                    }
                    else if(vec.theBoard[i+1][j] == 0){
                        //cerr << "This move cannot be performed.2" << endl;
                        return 0;
                    }
                    else{
                        vec.theBoard[i][j] = vec.theBoard[i+1][j];
                        vec.theBoard[i+1][j] = -1;
                        //cout << "Succesfully performed." << endl;
                        return 1;
                    }
                }
            }
        }  
    }
    return 0;
}

bool AbstractBoard::isSolvedVec(BoardVector & vec){
    vec.goalINITVec(vec);
    int current = 0;  
    for(int i = 0; i < vec.sizeI; i++){
        for(int j = 0; j < vec.sizeJ; j++){
            if(vec.theBoard[i][j] != 0){
                if(vec.theBoard[i][j] != vec.goal[i][j]){
                    current++;
                }
            }
        }
    }
    if(current == 0)return true;
    else return false;
}
bool AbstractBoard::isSolved1D(BoardArray1D & d1){
    d1.goalINIT1D(d1);
    int current = 0;  
    for(int i = 0; i < d1.sizeI; i++){
        for(int j = 0; j < d1.sizeJ; j++){
            if(d1.theBoard[i * d1.sizeJ + j] != 0){
                if(d1.theBoard[i * d1.sizeJ + j] != d1.goal[i][j]){
                    current++;
                }
            }
        }
    }
    if(current == 0)return true;
    else return false;
}
bool AbstractBoard::isSolved2D(BoardArray2D & d2){
    d2.goalINIT2D(d2);
    int current = 0;  
    for(int i = 0; i < d2.sizeI; i++){
        for(int j = 0; j < d2.sizeJ; j++){
            if(d2.theBoard[i][j] != 0){
                if(d2.theBoard[i][j] != d2.goal[i][j]){
                    current++;
                }
            }
        }
    }
    if(current == 0)return true;
    else return false;
}

void AbstractBoard::goalINITVec(BoardVector & vec){
    vec.goal.resize(vec.sizeI);
    int count = 1;
    for(int i = 0; i < vec.sizeI; i++){
        for(int j = 0; j < vec.sizeJ; j++){
            vec.goal[i].resize(vec.sizeJ);
            if(i == vec.sizeI-1 && j == vec.sizeJ-1){
                vec.goal[i][j] = -1;
            }
            else if(vec.theBoard[i][j] == 0)
                vec.goal[i][j] = 0;
            else{  
                vec.goal[i][j] = count;
                count++;
            }
        }
    }
}

void AbstractBoard::goalINIT1D(BoardArray1D & d1){
    d1.goal.resize(d1.sizeI);
    int count = 1;
    for(int i = 0; i < d1.sizeI; i++){
        for(int j = 0; j < d1.sizeJ; j++){
            d1.goal[i].resize(d1.sizeJ);
            if(i == d1.sizeI-1 && j == d1.sizeJ-1){
                d1.goal[i][j] = -1;
            }
            else if(d1.theBoard[i * d1.sizeJ + j] == 0)
                d1.goal[i][j] = 0;
            else{  
                d1.goal[i][j] = count;
                count++;
            }
        }
    }
}

void AbstractBoard::goalINIT2D(BoardArray2D & d2){
    d2.goal.resize(d2.sizeI);
    int count = 1;
    for(int i = 0; i < d2.sizeI; i++){
        for(int j = 0; j < d2.sizeJ; j++){
            d2.goal[i].resize(d2.sizeJ);
            if(i == d2.sizeI-1 && j == d2.sizeJ-1){
                d2.goal[i][j] = -1;
            }
            else if(d2.theBoard[i][j]== 0)
                d2.goal[i][j] = 0;
            else{  
                d2.goal[i][j] = count;
                count++;
            }
        }
    }
}

bool glob(AbstractBoard * ab){

}

int main(int argc, char *argv[]){   // Main function
    srand (time(NULL));


    BoardVector b0;
    b0.readFromFileVec("example.txt", b0);
    b0.writeToFileVec("vecSave.txt", b0);
    b0.resetVec(b0);
    cout << b0.isSolvedVec(b0) << endl;
    b0.printVec(b0);

    /*

    b0.moveVec('u', b0);     // Move Up for VectorBoard
    b0.printVec(b0);
    b0.moveVec('l', b0);      // Move Left for VectorBoard
    b0.printVec(b0);

    BoardArray1D b1;
    b1.readFromFile1D("example.txt", b1);  
    b1.writeToFile1D("d1Save.txt", b1);

    BoardArray2D b2;
    b2.readFromFile2D("example.txt", b2);
    b2.writeToFile2D("d2Save.txt", b2);

    b2.move2D('u', b2);     // Move Up for Array2D
    b2.print2D(b2);
    b2.move2D('r', b2);      // Move Right for Array2D
    b2.print2D(b2);

    */

    return 0;
}
