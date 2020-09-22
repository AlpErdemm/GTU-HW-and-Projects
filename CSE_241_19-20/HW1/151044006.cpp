#include <iostream>


const int MAX = 9;
const int MAXPOINT = 999;
int lastOp = 0;
int loopCount = 1;
int bestGoal = 99;
int board [MAX][MAX];
int goal [MAX][MAX];

using namespace std;


int compare(int element, int indexI, int indexJ, int theBoard[][MAX], int size);
void printBoard(int theBoard[][MAX], int size);
int operation_L(int theSize);
int operation_R(int theSize);
int operation_D(int theSize);
int operation_U(int theSize);
int operation_I(int theSize);
void operation_SHUFFLE(int theSize);
void goalINIT(int theSize);
bool isSolvable(int theBoard[MAX][MAX], int theSize);
int getInverse(int arr[], int theSize);


int main(){
    srand (time(NULL));

    int boardsize = 0;
    int err_control = 0;

    cout << "Enter the size of the board (3x3, 4x4, 5x5....9x9) Tip: Type '3' for 3x3." << endl;
    cin >> boardsize;
    while(boardsize < 3 || boardsize > 9){
        cerr << "Try a number between 3 and 9." << endl;
        cin >> boardsize;
    }
    do{
        for (int i = 0; i < boardsize; i++){
            for(int j = 0; j < boardsize; j++){
                board[i][j] = 0;
            }
        }
        for (int i = 0; i < boardsize; i++){
            for(int j = 0; j < boardsize; j++){
                board[i][j] = rand() % (boardsize * boardsize);
                while(compare(board[i][j], i, j, board, boardsize) == 1){
                    board[i][j] = rand() % (boardsize * boardsize);
                }
            }
        }
    }while((isSolvable(board, boardsize) == 0));
    cout << "Your initial random board is" << endl;
    printBoard(board, boardsize);


    char move;
    goalINIT(boardsize);
    printBoard(goal, boardsize);
    while(1){ 
        cout << "Your move:" ;
        cin >> move;
        cout << endl;
        if(move == 'L'){
            operation_L(boardsize);
            printBoard(board, boardsize);
        }
        else if(move == 'R'){
            operation_R(boardsize);
            printBoard(board, boardsize);
        }        
        else if(move == 'U'){
            operation_U(boardsize);
            printBoard(board, boardsize);
        }
        else if(move == 'D'){
            operation_D(boardsize);
            printBoard(board, boardsize);
        }    
        else if(move == 'I'){
            operation_I(boardsize);
            printBoard(board, boardsize);
        }
        else if(move == 'S'){
            operation_SHUFFLE(boardsize);
            printBoard(board, boardsize);
        } 
        else if(move == 'Q'){
            exit(0);
        } 
    }

    return 0;
}
int compare(int element, int indexI, int indexJ, int theBoard[][MAX], int size){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(!(i == indexI && j == indexJ)){
                if(theBoard[i][j] == element)
                    return 1;
            }
        }
    }
    return 0;
}

void printBoard(int theBoard[][MAX], int size){
    for (int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(theBoard[i][j] == 0) cout << "  ";
            else
              cout << theBoard[i][j] << " ";
        }
        cout << endl;
    }
}

int operation_L(int theSize){
    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
            if(board[i][j] == 0){
                if(j == 0){
                    //cerr << "This move cannot be performed." << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i][j-1];
                    board[i][j-1] = 0;
                    //cout << "Succesfully performed." << endl;
                    return 1;
                }
            }
        }
    }
}

int operation_R(int theSize){
    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
            if(board[i][j] == 0){
                if(j == theSize-1){
                    //cerr << "This move cannot be performed." << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i][j+1];
                    board[i][j+1] = 0;
                    //cout << "Succesfully performed." << endl;
                    return 1;
                }
            }
        }
    }
}

int operation_U(int theSize){
    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
            if(board[i][j] == 0){
                if(i == 0){
                    //cerr << "This move cannot be performed." << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i-1][j];
                    board[i-1][j] = 0;
                    //cout << "Succesfully performed." << endl;
                    return 1;
                }
            }
        }
    }
}
int operation_D(int theSize){
    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
            if(board[i][j] == 0){
                if(i == theSize-1){
                    //cerr << "This move cannot be performed." << endl;
                    return 0;
                }
                else{
                    board[i][j] = board[i+1][j];
                    board[i+1][j] = 0;
                    //cout << "Succesfully performed." << endl;
                    return 1;
                }
            }
        }
    }
}

int operation_I(int theSize){
    int first = 0;
    int current = 0;
    int op = 0;
    int result = 0;
    int temp [theSize][theSize];

    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
            temp[i][j] = board[i][j];
        }
    }

    //-------------- 2 STEPS AT A TIME -------------------------------

    if(loopCount % 200 == 0){
        do{
            for (int i = 0; i < theSize; i++){
                for(int j = 0; j < theSize; j++){
                    board[i][j] = 0;
                }
            }
            for (int i = 0; i < theSize; i++){
                for(int j = 0; j < theSize; j++){
                    board[i][j] = rand() % (theSize * theSize);
                    while(compare(board[i][j], i, j, board, theSize) == 1){
                        board[i][j] = rand() % (theSize * theSize);
                    }
                }
            }
        }while((isSolvable(board, theSize) == 0));
    }
    else if(loopCount % 20 == 0){
        result = operation_L(theSize);
        if(result != 0){
            result = operation_U(theSize);
            for(int i = 0; i < theSize; i++){
                for(int j = 0; j < theSize; j++){
                    if(board[i][j] != 0){
                       if(board[i][j] != goal[i][j]){
                           current++;
                        }
                    }
                }
            }
        }
        first = current;
        current = 0;
        op = 1;
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_L(theSize);
        if(result != 0){
            result = operation_D(theSize);
            for(int i = 0; i < theSize; i++){
                for(int j = 0; j < theSize; j++){
                    if(board[i][j] != 0){
                       if(board[i][j] != goal[i][j]){
                           current++;
                        }
                    }
                }
            }
        }
        if(current < first){
            first = current;
            op = 2;
        }
        current = 0;
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_R(theSize);
        if(result != 0){
            result = operation_U(theSize);
            for(int i = 0; i < theSize; i++){
                for(int j = 0; j < theSize; j++){
                    if(board[i][j] != 0){
                       if(board[i][j] != goal[i][j]){
                           current++;
                        }
                    }
                }
            }
        }
        if(current < first){
            first = current;
            op = 3;
        }
        current = 0;
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        } 
        result = operation_R(theSize);
        if(result != 0){
            result = operation_D(theSize);
            for(int i = 0; i < theSize; i++){
                for(int j = 0; j < theSize; j++){
                    if(board[i][j] != 0){
                       if(board[i][j] != goal[i][j]){
                           current++;
                        }
                    }
                }
            }
        }
        if(current < first){
            first = current;
            op = 4;
        }
        current = 0;
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        if(op == 1){
            operation_L(theSize);
            operation_U(theSize);
        }
        else if (op == 2){
            operation_L(theSize);
            operation_D(theSize);
        }
        else if(op == 3){
           operation_R(theSize);
           operation_U(theSize);
        }
        else if (op == 4){
           operation_R(theSize);
           operation_D(theSize);
        }        
    }
    //----------------- 1 STEP AT A TIME ------------------------------
    else{        
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                temp[i][j] = board[i][j];
            }
        }
        result = operation_L(theSize);
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
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
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_R(theSize);
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
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
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_U(theSize);
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
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
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        result = operation_D(theSize);
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
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
        for(int i = 0; i < theSize; i++){
            for(int j = 0; j < theSize; j++){
                board[i][j] = temp[i][j];
            }
        }
        if(op == 1){
            operation_L(theSize);
        }
        else if (op == 2){
            operation_R(theSize);
        }
        else if(op == 3){
            operation_U(theSize);
        }
        else if (op == 4){
            operation_D(theSize);
        }
    }
    lastOp = op;

    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
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
    
    // Tüm operasyonları dene, h değeri en küçük olanı yap.
    // goal'e ulaşıldıysa 1 döndür.
}

void operation_SHUFFLE(int theSize){
    while(operation_I(theSize) == 0){
        printBoard(board, theSize);
    }
    cout << "Reached goal: " << endl;
    printBoard(board, theSize);
    // operation_I 1 döndürene kadar tekrarla.
    //sonucu yazdırç
    // tahtayı karıştır.
}
void goalINIT(int theSize){
    int count = 1;
    for(int i = 0; i < theSize; i++){
        for(int j = 0; j < theSize; j++){
            if(i == theSize-1 && j == theSize-1){
                goal[i][j] = 0;
            }
            else{  
                goal[i][j] = count;
                count++;
            }
        }
    }
}
int getInverse(int arr[], int theSize) 
{ 
    int count = 0; 
    for (int i = 0; i < (theSize * theSize) - 1; i++) 
        for (int j = i+1; j < (theSize * theSize); j++){
            if(arr[i] != 0 && arr[j] != 0)
                if (arr[i] > arr[j]) 
                  count++;             
        }
    return count; 
} 
bool isSolvable(int theBoard[MAX][MAX], int theSize) 
{ 
    int invCount = getInverse((int *)theBoard, theSize);

    return (invCount%2 == 0); 
} 
