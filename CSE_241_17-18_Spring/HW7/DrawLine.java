/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package homework;

import java.awt.*;
import javax.swing.*;
 
public class DrawLine extends JPanel {
    
    private int arr1[][];
    private int arrSize;
    
    public DrawLine(int arr[][], int size){
        arr1 = new int [size][2];
        arrSize = size;
        for(int i = 0; i < size; i++){
            arr1[i][0] = arr[i][0];
            arr1[i][1] = arr[i][1];
        }
    }
 
    public void paint(Graphics g) {
        int coord1 = arr1[0][0], coord2 = arr1[0][1];
        for(int i = 1; i < arrSize; i++){
            g.drawLine(coord1 * 20, 500 - coord2*20, arr1[i][0]*20, 500 - arr1[i][1]*20);
            coord1 = arr1[i][0];
            coord2 = arr1[i][1];
        }
 
    }
}