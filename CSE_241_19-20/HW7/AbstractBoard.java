import java.io.*;
import java.util.Scanner;

public class AbstractBoard {

    protected String filename;
    protected int sizeI;
    protected int sizeJ;
    protected char lastM;
    protected int movesSum = 0;
    protected int boardCount = 0;

    AbstractBoard(String fileN){    // Constructor
        filename = fileN;
    }

    public void moveLoop(){
        while(true) {
            System.out.println("Choose a move to make... {l, r, u, d} and q to quit");
            Scanner sc = new Scanner(System.in);
            char m1 = sc.next().charAt(0);
            if (m1 == 'q' || m1 == 'Q') {
                return;
            }
            move(m1);
            movesSum++;
            myToString();
        }
    }
    public void myToString(){ // Changed its name from toString since there is already a same named method in the library.

    }
    public void readFromFile() throws IOException {

    }
    public void writeToFile(String outfile) throws IOException {

    }
    public void setSize(int i, int j){
        sizeI = i;
        sizeJ = j;
    }
    public void reset(){

    }
    public int move(char m){
        return 0;
    }
    public boolean isSolved(){
        return true;
    }
    public int cell(int i, int j){
        return 0;
    }
    public boolean Equals(int index1, int index2){
        return true;
    }
    public int NumberOfBoards(){
        return boardCount;
    }
    public char lastMove(){
        return lastM;
    }
    public int numberOfMoves(){
        return movesSum;
    }

    public boolean checkSol() {
        return isSolved();
    }
}
