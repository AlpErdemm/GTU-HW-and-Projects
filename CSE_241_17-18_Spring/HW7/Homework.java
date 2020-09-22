/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package homework;
import java.io.*;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
import java.util.Scanner;
import java.awt.*;
import javax.swing.*;


/**
 *
 * @author mamik
 */
public class Homework {

    /**
     * @param args the command line arguments
     * @throws java.io.IOException
     */
    public static void main(String[] args) throws IOException {
		File file = new File("data.txt");
		Scanner inner = new Scanner(file);
                int count = 0, i = 0, j = 0;
                int [][] arr = new int[100][3];	
		while (inner.hasNext()){
                    arr[i][j] = inner.nextInt();
                    j++;
                    if(j == 3){j = 0; i++; count++;}                   
		}
                Solver s = new Solver(arr, count);
                
                count = s.getResultSize();
                
                JFrame.setDefaultLookAndFeelDecorated(true);
                JFrame frame = new JFrame("Draw Line");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setBackground(Color.white);
                frame.setSize(600, 1000);

                int [][] sn = new int[s.getResultSize()][2];
                
                for(i = 0; i < s.getResultSize(); i++){
                    sn[i][0] = s.getResult(i, 0);
                    sn[i][1] = s.getResult(i, 1);
                }
                               
                DrawLine panel = new DrawLine(sn, s.getResultSize());

                frame.add(panel);

                frame.setVisible(true);
	}
    
}
