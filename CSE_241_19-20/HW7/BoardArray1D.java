import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class BoardArray1D extends AbstractBoard{

    List<int[]> list1d = new ArrayList<>(100);
    private int [] Board1D;
    private int [][] Goal;

    BoardArray1D(String fileN) {    // Constructor
        super(fileN);
    }
    public void myToString(){ // Override //  Prints as a string
        for(int i = 0; i < sizeI; i++) {
            for (int j = 0; j < sizeJ; j++) {
                System.out.print(Board1D[(i * sizeJ) + j] + " ");
            }
            System.out.println();
        }
    }

    public void readFromFile() throws IOException {     //Override
        int MAXLINE = 999;
        char[] data = new char [MAXLINE];

        BufferedReader r1;

        try {       // Counts the lines and columns and prepares the array
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

        Board1D = new int[sizeI * sizeJ];
        list1d.add(Board1D);
        boardCount = 1;

        FileInputStream in = null;

        try{    // Fills the array
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
                        Board1D[i*sizeJ + j] = element;
                    else
                        Board1D[i*sizeJ + j] = -1;
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
                if(Board1D[i*sizeJ + j] == -1){
                    out.write('b');
                    out.write('b');
                    out.write(' ');
                }
                else if(Board1D[i*sizeJ + j] < 10){
                    out.write('0');
                    out.write('0'+Board1D[i*sizeJ + j]);
                    out.write(' ');
                }
                else{
                    out.write('0'+Board1D[i*sizeJ + j]/10);
                    out.write('0'+Board1D[i*sizeJ + j]%10);
                    out.write(' ');
                }
            }
            if(i != sizeI-1)
                out.write('\n');
        }
    }
    public int cell(int i, int j){  // Override
        return Board1D[i*sizeJ + j];
    }
    public void goalINIT() {    // Initialized the Goal board with proper sizes.
        Goal = new int[sizeI][sizeJ];
        int count = 1;
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(i == sizeI-1 && j == sizeJ-1){
                    Goal[i][j] = -1;
                }
                else if(Board1D[i*sizeJ + j]== 0)
                    Goal[i][j] = 0;
                else{
                    Goal[i][j] = count;
                    count++;
                }
            }
        }
    }
    public boolean isSolved(){      // Checks if the current board is equal to the solution.
        goalINIT();
        int current = 0;
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(Board1D[i*sizeJ + j] != 0){
                    if(Board1D[i*sizeJ + j] != Goal[i][j]){
                        current++;
                    }
                }
            }
        }
        if(current == 0)return true;
        else return false;
    }
    public void reset(){             // Turns the board into the solution.
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                Board1D[i * sizeJ + j] = Goal[i][j];
            }
        }
    }
    public int move(char m){        // Basic movements, was used in a loop (moveLoop).
        lastM = m;
        int [] temp = new int [sizeI*sizeJ];
        if(m == 'L'|| m == 'l'){
            for(int i = 0; i < sizeI; i++){
                for(int j = 0; j < sizeJ; j++){
                    if(Board1D[i*sizeJ + j] == -1){
                        if(j == 0){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if (Board1D[i*sizeJ + j-1] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board1D[i*sizeJ + j] = Board1D[i*sizeJ + j - 1];
                            Board1D[i*sizeJ + j-1] = -1;
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
                    if(Board1D[i*sizeJ + j] == -1){
                        if(j == sizeJ-1){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if(Board1D[i*sizeJ + j+1] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board1D[i*sizeJ + j] = Board1D[i*sizeJ + j+1];
                            Board1D[i*sizeJ + j+1] = -1;
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
                    if(Board1D[i*sizeJ + j] == -1){
                        if(i == 0){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if(Board1D[(i-1)*sizeJ + j] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board1D[i*sizeJ + j] = Board1D[(i-1)*sizeJ + j];
                            Board1D[(i-1)*sizeJ + j] = -1;
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
                    if(Board1D[i*sizeJ + j] == -1){
                        if(i == sizeI-1){
                            //cerr << "This move cannot be performed.1" << endl;
                            return 0;
                        }
                        else if(Board1D[(i+1)*sizeJ + j] == 0){
                            //cerr << "This move cannot be performed.2" << endl;
                            return 0;
                        }
                        else{
                            Board1D[i * sizeJ + j] = Board1D[(i+1)*sizeJ + j];
                            Board1D[(i+1)*sizeJ + j] = -1;
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
                temp[i*sizeJ + j] = Board1D[i*sizeJ + j];
            }
        }
        list1d.add(temp);
        boardCount++;
        return 0;
    }
    public boolean Equals(int index1, int index2){          // Compares two boards.
        for(int i = 0; i < sizeI; i++){
            for(int j = 0; j < sizeJ; j++){
                if(list1d.get(index1)[i*sizeJ + j] != list1d.get(index2)[i*sizeJ + j])
                    return false;
            }
        }
        return true;
    }
}
