import java.io.FileNotFoundException;
import java.io.IOException;

public class mainClass {
    public static boolean checkSolution(AbstractBoard ab){
        if(ab.checkSol()){
            return true;
        }
        return false;
    }

    public static void main(String [] args) throws IOException {    // Output of this exact code is given as a jpeg. (output image)

        if(args.length == 0){       // Input filename control.
            System.out.println("This program needs a input file name as main argument.");
            return;
        }
        System.out.println("File:" + args[0]); // Should be called with exact path (ex: src/example.txt).
        AbstractBoard a1 = new BoardArray1D(args[0]);
        AbstractBoard a2 = new BoardArray2D(args[0]);
        System.out.println("-------------------------------------------------");
        System.out.println("Reading from the file: " + args[0]);
        a1.readFromFile();
        System.out.println("-------------------------------------------------");
        System.out.println("Checking if the 1D Board is Solved...");
        System.out.println(a1.isSolved());
        System.out.println("Running the static function to find out if the board is solved...");
        System.out.println(checkSolution(a1));
        System.out.println("Resetting the board to the solution...");
        a1.reset();
        System.out.println("Checking if the 1D Board is Solved...");
        System.out.println(a1.isSolved());
        System.out.println("Running the static function to find out if the board is solved...");
        System.out.println(checkSolution(a1));

        System.out.println("-------------------------------------------------");
        System.out.println("Reading from the file: " + args[0]);
        a2.readFromFile();
        System.out.println("-------------------------------------------------");
        System.out.println("Writing to the file: output.txt");
        a2.writeToFile("output.txt");
        System.out.println("-------------------------------------------------");
        System.out.println("Requesting moves from the users in a loop...");
        a2.moveLoop();
        System.out.println("Printing the last move that is made...");
        System.out.println(a2.lastMove());
        System.out.println("Printing how many moves have been done..");
        System.out.println(a2.numberOfMoves());
        System.out.println("Comparing the equal boards with each other...");
        System.out.println(a2.Equals(0, 0));
    }
}
