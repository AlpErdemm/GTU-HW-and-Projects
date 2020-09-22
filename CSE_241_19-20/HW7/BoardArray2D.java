import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class BoardArray2D extends AbstractBoard{

    private int [][] Board2D;
    private int boardCount = 0;
    List<int[][]> list2d = new ArrayList<>(100);
    private int [][] Goal;

    BoardArray2D(String fileN) {    // Constructor
        super(fileN);
    }
    // Override
    public void myToString(){   //  Prints as a string
        for(int i = 0; i < sizeI; i++) {
            for (int j = 0; j < sizeJ; j++) {
                System.out.print(Board2D[i][j] + " ");
            }
            System.out.println();
        }
    }
    //Override
    public void readFromFile() throws IOException {
        int MAXLINE = 999;
        char[] data = new char [MAXLINE];

        BufferedReader r1;

        try {           // Counts the lines and columns and prepares the array
            r1 = new BufferedReader(new FileReader(filename));
            String line = r1.readLine();
            sizeI = 0;
            sizeJ = line.length() / 3 + 1;
            while (line != null) {
                sizeI++;
                System.out.println(line);
                line = r1.readLine();
            }
            System.out.println("Lines -> " + sizeI);
            System.out.println("Columns -> " + sizeJ);

            r1.close();
        } catch (IOException e){
            e.printStackTrace();
        }

        Board2D = new int[sizeI][sizeJ];
        list2d.add(Board2D);
        boardCount = 1;

        FileInputStream in = null;

        try{            // Fills the array
            in = new FileInputStream(filename);

            int element , temp, space, newline;
            for(int i = 0; i < sizeI; i++){
                for(int j = 0; j < sizeJ; j++){
                    element = 0;
                    temp = in.read() - '0';
                    element += 10 * temp;
                    temp = in.read() - '0';
                    element += temp;
                    space = in.read();
                    if(element != 550)
                        Board2D[i][j] = element;
                    else
                        Board2D[i][j] = -1;
                }
                newline = in.read();
            }
        }finally {
            if(in != null){
                in.close();
            }
        }
        myToString();
    }
    public void writeToFile(String outfile) throws IOException {
        FileOutputStream out = new FileOutputStream(outfile);
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(Board2D[i][j] == -1){
                    out.write('b');
                    out.write('b');
                    out.write(' ');
                }
                else if(Board2D[i][j] < 10){
                    out.write('0');
                    out.write('0'+Board2D[i][j]);
                    out.write(' ');
                }
                else{
                    out.write('0'+Board2D[i][j]/10);
                    out.write('0'+Board2D[i][j]%10);
                    out.write(' ');
                }
            }
            if(i != sizeI-1)
                out.write('\n');
        }
    }
    public int cell(int i, int j){  // Override
        return Board2D[i][j];
    }
    public boolean isSolved(){      // Checks if the current board is equal to the solution.
        goalINIT();
        int current = 0;
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(Board2D[i][j] != 0){
                    if(Board2D[i][j] != Goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(current == 0)return true;
        else return false;
    }
    public void goalINIT() {        // Initialized the Goal board with proper sizes.
        Goal = new int[sizeI][sizeJ];
        int count = 1;
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(i == sizeI-1 && j == sizeJ-1){
                    Goal[i][j] = -1;
                }
                else if(Board2D[i][j]== 0)
                    Goal[i][j] = 0;
                else{
                    Goal[i][j] = count;
                    count++;
                }
            }
        }
    }
    public void reset(){        // Turns the board into the solution.
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                Board2D[i][j] = Goal[i][j];
            }
        }
    }
    public int move(char m){        // Basic movements, was used in a loop (moveLoop).
        lastM = m;
        int [][] temp = new int [sizeI][sizeJ];
        if(m == 'L'|| m == 'l'){
            for(int i = 0; i < sizeI; i++){
                for(int j = 0; j < sizeJ; j++){
                    if(Board2D[i][j] == -1){
                        if(j == 0){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if (Board2D[i][j-1] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board2D[i][j] = Board2D[i][j-1];
                            Board2D[i][j-1] = -1;
                            //cout << "Succesfully performed." << endl;
                            lastM = m;
                            return 1;
                        }
                    }
                }
            }
        }
        else if(m == 'R' || m == 'r'){
            for(int i = 0; i < sizeI; i++){
                for(int j = 0; j < sizeJ; j++){
                    if(Board2D[i][j] == -1){
                        if(j == sizeJ-1){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if(Board2D[i][j+1] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board2D[i][j] = Board2D[i][j+1];
                            Board2D[i][j+1] = -1;
                            //cout << "Succesfully performed." << endl;
                            lastM = m;
                            return 1;
                        }
                    }
                }
            }
        }
        else if(m == 'U'|| m == 'u'){
            for(int i = 0; i < sizeI; i++){
                for(int j = 0; j < sizeJ; j++){
                    if(Board2D[i][j] == -1){
                        if(i == 0){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if(Board2D[i-1][j] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board2D[i][j] = Board2D[i-1][j];
                            Board2D[i-1][j] = -1;
                            //cout << "Succesfully performed." << endl;
                            lastM = m;
                            return 1;
                        }
                    }
                }
            }

        }
        else if(m == 'D'|| m == 'd'){
            for(int i = 0; i < sizeI; i++){
                for(int j = 0; j < sizeJ; j++){
                    if(Board2D[i][j] == -1){
                        if(i == sizeI-1){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if(Board2D[i+1][j] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board2D[i][j] = Board2D[i+1][j];
                            Board2D[i+1][j] = -1;
                            //cout << "Succesfully performed." << endl;
                            lastM = m;
                            return 1;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j  < sizeJ; j++){
                temp[i][j] = Board2D[i][j];
            }
        }
        list2d.add(temp);
        boardCount++;
        return 0;
    }
    public boolean Equals(int index1, int index2){      // Compares two boards.
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(list2d.get(index1)[i][j] != list2d.get(index2)[i][j])
                    return false;
            }
        }
        return true;
    }
}
