/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package homework;
import java.awt.*;
/**
 *
 * @author mamik
 */
public class Solver {
    
        private int [][] info;
        private int [][][] corners;
        private int [][] result;
        private int resultSize;
        private int ArrSize;
        private int coordSysX;
        private int coordSysY;
        private int realI;
        private int realJ;
        private int curBuilding;
        private int latestMove;
        
        public Solver(){
        
        }
        public Solver(int arr[][], int size){
            info = new int [size][3];
            ArrSize = size;
            int i, j;
            for(i = 0; i < size; i++){
                for(j = 0; j < 3; j++){
                    info[i][j] = arr[i][j];
                } 
            }
            cornerCalc();
        }
        public int getResult(int a, int b){
            return result[a][b];
        }
        public int getResultSize(){
            return resultSize;
        }
        private void cornerCalc(){
            corners = new int [ArrSize][4][2];
            int i, j, width, height, position;
            for(i = 0; i < ArrSize; i++){
                width = info[i][0];
                height = info[i][1];
                position = info[i][2];
                
                corners[i][0][0] = position; //goes clockwise
                corners[i][0][1] = 0;
                
                corners[i][1][0] = position; //goes clockwise
                corners[i][1][1] = height;   
                
                corners[i][2][0] = position + width; //goes clockwise
                corners[i][2][1] = height; 
             
                corners[i][3][0] = position + width; //goes clockwise
                corners[i][3][1] = 0; 
                
            }            
            engine();
        }
        private void createSys(){
            int maxX = 0, maxY = 0, i, j;
            for(i = 0; i < ArrSize; i++){
                for(j = 0; j < 4; j++){
                    if(corners[i][j][0] > maxX) maxX = corners[i][j][0];
                    if(corners[i][j][1] > maxY) maxY = corners[i][j][1];
                }                
            }
            coordSysX = maxX;
            coordSysY = maxY;
        }
        private int isCorner(int a, int b){
            for(int i = 0; i < ArrSize; i++){
                for(int j = 0; j < 4; j++){
                    if(corners[i][j][0] == a && corners[i][j][1] == b){
                        return 1;
                    }
                }                
            }
            return 0;
        }
        private int isEdge(int a, int b){
            //if(isCorner(a, b) == 1) return 2;
            
            for(int i = 0; i < ArrSize; i++){
                if(corners[i][1][1] == b && corners[i][0][0] < a && corners[i][3][0] > a){
                    curBuilding = i;
                    return 1;
                }
                if(corners[i][0][0] == a && corners[i][0][1] < b && corners[i][1][1] > b){
                    curBuilding = i;
                    return 1;
                }
                if(corners[i][2][0] == a && corners[i][0][1] < b && corners[i][1][1] > b){
                    curBuilding = i;
                    return 1;
                }
            }           
            return 0;
        }
        private int isEdge2(int a, int b){
            if(isCorner(a, b) == 1) return 2;
            
            for(int i = 0; i < ArrSize; i++){
                if(i == curBuilding){
                    
                }
                else{
                    if(corners[i][1][1] == b && corners[i][0][0] < a && corners[i][3][0] > a){
                        curBuilding = i;
                        return 1;
                    }
                    if(corners[i][0][0] == a && corners[i][0][1] < b && corners[i][1][1] > b){
                        curBuilding = i;
                        return 1;
                    }
                    if(corners[i][2][0] == a && corners[i][0][1] < b && corners[i][1][1] > b){
                        curBuilding = i;
                        return 1;
                    }
                }
            }           
            return 0;
        }

        private void engine(){
            createSys();
            int count = 1, flag;
            
            for(int i = 0; i < coordSysX; i++){
                for(int j = 0; j < coordSysY; j++){
                    if(isCorner(i,j) == 1 && count == 1){realI = i; realJ = j;count++;break;}
                }
            }
            resultSize = 0;
            result = new int [1000][2];
            addCoord(realI, realJ); 
            while(realI != coordSysX){
                  flag = goUp();
                  if(flag != 1){
                      flag = goRight();
                      if(flag != 1){
                          flag = goDown();
                          if(flag == -2) goDown();
                      }
                  }
            }
            if(isCorner(realI, realJ - (corners[ArrSize-1][1][1] - corners[ArrSize-1][0][1])) == 1){
                addCoord(realI, realJ - (corners[ArrSize-1][1][1] - corners[ArrSize-1][0][1]));                
            }   
            
            for(int i = 0; i < resultSize; i++){
                System.out.print(result[i][0]);
                System.out.print(" , ");
                System.out.print(result[i][1]);
                System.out.println();
            }

        }
        private void addCoord(int a, int b){
            result[resultSize][0] = a;
            result[resultSize][1] = b;
            resultSize++;
        }
        private int isJunction(int a, int b){
            if(isEdge(a, b) == 1){
                if(isEdge2(a, b) == 1){
                    return 1;
                }
            }
            return 0;
        }
        private int isExisting(int a, int b){
            for(int i = 0; i < resultSize; i++){
                if(result[i][0] == a && result[i][1] == b){
                    return 1;
                }
            }
            return 0;
        }   
        private int goUp(){
            int tempJ = realJ;
            int tempI = realI;
            if(latestMove == 1) return 0;
            else if (isCorner(realI, realJ+1) == 1 ){
                    addCoord(tempI, tempJ+1);
                    latestMove = 0;
                    realI = tempI;
                    realJ = tempJ+1;
                    return 1;                
            }
            else if(isEdge(realI, realJ+1) != 1){
                return 0;
            }
            else{
                tempJ++;
                while(isCorner(tempI, tempJ) != 1 && isJunction(tempI, tempJ) != 1 && tempJ != coordSysY+1){
                    tempJ++;
                }
                if(isCorner(tempI, tempJ) == 1 || isJunction(tempI, tempJ) == 1){
                    if(isExisting(tempI, tempJ) == 1) return 0;
                    addCoord(tempI, tempJ);
                    latestMove = 0;
                    realI = tempI;
                    realJ = tempJ;
                    return 1;
                }
                return 0;
            }
        }
        private int goDown(){
            int tempJ = realJ;
            int tempI = realI;
            if (isCorner(realI, realJ-1) == 1){
                    if(divergent(realI, realJ-1) == 1){
                        realJ--;
                        return 0;
                    }
                    addCoord(tempI, tempJ-1);
                    latestMove = 1;
                    realI = tempI;
                    realJ = tempJ-1;
                    return 1;                
            }
            else if(isEdge(realI, realJ-1) != 1){
                return 0;
            }
            else{
                tempJ--;
                 while(isCorner(tempI, tempJ) != 1 && isJunction(tempI, tempJ) != 1 && tempJ != -1){
                    tempJ--;
                }
                if(isCorner(tempI, tempJ) == 1 || isJunction(tempI, tempJ) == 1){
                    if(divergent(tempI, tempJ) == 1) {realJ--; return (-2);}
                    addCoord(tempI, tempJ);
                    latestMove = 1;
                    realI = tempI;
                    realJ = tempJ;
                    return 1;
                }
                return 0;
            }
        }
        private int goRight(){
            int tempJ = realJ;
            int tempI = realI;
            if(isCorner(realI+1, realJ) == 1){
                    addCoord(tempI+1, tempJ);
                    latestMove = 0;
                    realI = tempI+1;
                    realJ = tempJ;
                    return 1;                
            }
            else if(isEdge(realI+1, realJ) != 1){               
                return 0;
            }
            else{
                tempI++;
                 while(isCorner(tempI, tempJ) != 1 && isJunction(tempI, tempJ) != 1 && tempI != coordSysX + 1){
                    tempI++;
                }
                if(isCorner(tempI, tempJ) == 1 || isJunction(tempI, tempJ) == 1){
                    addCoord(tempI, tempJ);
                    latestMove = 0;
                    realI = tempI;
                    realJ = tempJ;
                    return 1;
                }
                return 0;
            }
        }

    private int divergent(int a, int b) {
        if(isCorner(a,b) == 1){
            if(isEdge(a,b) == 1){
                return 1;
            }
        }
        return 0;
    }

}
