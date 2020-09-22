#include <stdio.h>
#include <string.h>
#define Bytes 8 

int hextodec(int buff1, int buff2);  /*Takes a hexadecimal number as two integers and converts to decimal, returns the decimal as an integer */
int power(int a, int i);	/* My own power function, similar with pow() from math.h */
int toBin(int inp);		/* Takes a decimal number and converts it to binary, returns the binary as an integer */
void printRow(int buffer[4]);  /* Manipulates then prints a single row of pixels */

int Image_width;	/* Width of the image */


int main(int argc, char ** argv){
	FILE * pFile;
	char buffer[255] = "", type[2] = "";
	int store[4], a = 8, b = 0, i = 0, tag = 0, width = 0, height = 0, sOff = 0, buff1 = 0, buff2 = 0, buff3 = 0, buff4 = 0;
	pFile = fopen ( argv[1] , "rb" );
	
	if(pFile == NULL){ printf("Can't open the file.\n"); return 0;}
	
	fread(buffer, 1, 2, pFile);	/* Reading the type */
	strcpy(type, buffer);
	fread(buffer, 1, 2, pFile);	/* Reading the number 42 */
	fread(buffer, 1, 4, pFile);   	/* Reading the Offset of 0th IFD */
	b = (int) buffer[3];

	fseek(pFile, b, SEEK_SET);  /* Seeking the Offset of 0th */
	
	fread(buffer, 1, 2, pFile);	/* Reading the count */

	a = (int) buffer[1];
	for(i = 0; i < a; i++){
		fread(buffer, 12, 1, pFile);	/* 0th IFD (12 BYTES) */
		tag = hextodec((int)buffer[0], (int)buffer[1]);
		if(tag == 256){ 		/* Specific tag for width */
			width = (int) buffer[9];
			Image_width = width;
		}
		else if(tag == 257){ 		/* Specific tag for height */
			height = (int) buffer[9];
		}
		else if(tag == 273){ 		/* Specific tag for StripOffsets */
			sOff = (int) buffer[11];
		}
	}
	printf("Width : %d\n", width);
	printf("Height : %d\n", height);
	if(type[0] == 'M' && type[1] == 'M') printf("Byte Order : Motorola\n");
	else if(type[0] == 'I' && type[1] == 'I') printf("Byte Order : Intel\n");

	fseek(pFile, sOff, SEEK_SET); /* Seeking the StripOffsets' */

	for(i = 0; i < height; i++){
		fread(buffer, 1, 4, pFile); /* Reading the pixels */
		buff1 = buffer[0];buff2 = buffer[1];buff3 = buffer[2];buff4 = buffer[3];	
		if(buff1 < 0) buff1+= 256;
		if(buff2 < 0) buff2+= 256; 
		if(buff3 < 0) buff3+= 256;
		if(buff4 < 0) buff4+= 256;
		store[0] = buff1;store[1] = buff2;store[2] = buff3;store[3] = buff4;	/* This whole process is to create proper integers from the numbers in buffer */
		printRow(store); /* Printing a single row */		
	}	
	fclose (pFile);
	return 0;

}
int hextodec(int buff1, int buff2){
	int result = 0;
	result += buff1 * 256;
	if(buff2 > 16) buff2 -= 6;
	if(buff2 < 10) result += buff2;
	else{
		result += buff2 % 10;
		result += ((buff2 / 10) * 16);
	}
	return result;
}
int power(int a, int i){
	int j, result = 1;
	for(j = 0; j < i; j++){
		result *= a;
	}
	return result;
}
void printRow(int buffer[4]){
	int i = 0;
	char row[4*Bytes] = "", temp[8] = "";
	for(i = 0; i < 4; i++){		/* This loop creates the necessary format given in the hw pdf */
		if(buffer[i] == 0) {strcat(row,"00000000");}
		else if(buffer[i] == 1) {strcat(row, "00000001");}
		else if(buffer[i] <= 3) {strcat(row, "000000");sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}	
		else if(buffer[i] <= 7) {strcat(row, "00000");sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}
		else if(buffer[i] <= 15) {strcat(row, "0000");sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}
		else if(buffer[i] <= 31) {strcat(row, "000");sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}
		else if(buffer[i] <= 63) {strcat(row, "00");sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}
		else if(buffer[i] <= 127) {strcat(row, "0");sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}
		else {sprintf(temp, "%d", toBin(buffer[i]));strcat(row, temp);}
	}
	for(i = 0; i < Image_width; i++){	/* Then prints the nicely formatted character array */
		printf("%c", row[i]);
	}
	printf("\n");
}
int toBin(int inp){
    if(inp == 0) return 0;
    if(inp == 1) return 1;                    
    return (inp % 2) + 10 * toBin(inp / 2);
}







