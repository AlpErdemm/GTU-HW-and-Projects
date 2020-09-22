#ifndef __SPARSEMATRIX_H
#define __SPARSEMATRIX_H

#include <fstream>
#include <string>

using namespace std;

class SparseMatrix{
public:
	SparseMatrix();
	SparseMatrix(int rowSize, int columnSize);
	SparseMatrix(string filename);
	SparseMatrix transpose();

	friend ostream& operator<<(ostream& os, const SparseMatrix & m1); 

	//	Getter and Setters (inline)

	inline void setMatrix(int i, int j, int value){
		matrixArr[i][j] = value;
	}
	inline double getMatrix(int i, int j) const{
		return matrixArr[i][j];
	}
	inline int getRows() const{
		return rows;
	}
	inline int getColumns(int i) const{
		return columns[i];
	}
private:
	int rows, *columns;
	double ** matrixArr;
};

// Constructors of SparseMatrix

SparseMatrix :: SparseMatrix(){
	rows = 0;
	columns = new int [1];
	columns[0] = 0;
}

SparseMatrix :: SparseMatrix(int rowSize, int columnSize){
	rows = rowSize;
	columns = new int [rowSize];
	for(int i = 0; i < rowSize; i++){
		columns[i] = 0;
	}
}

SparseMatrix :: SparseMatrix(string filename){

	string  buffer;
	ifstream file;
	int count = 0;

	file.open(filename);

	while(getline(file, buffer)){
		count++;
	}
	rows = count;
	columns = new int [count];
	matrixArr = new double * [count];
	file.close();
	file.open(filename);

	int point = 2, order = 0, order2 = 0, order3 = 0;
	double carry, base = 0, base1 = 0;
	string temp;
	string temp2;

	for(int r = 0; r < count; r++){
		vector <double> fs;
		columns[r] = 0;
		getline(file, buffer);
		fs.push_back(buffer[0] - '0');
		(columns[r])++;
		for(int i = 2;; i++){
			if(buffer[i] == ' ' || buffer[i] == '\0'){
				for(int j = point; j < i; j++){
					temp+= buffer[j];
				}
				for(int k = 0; temp[k] != '\0'; k++){
					if(temp[k] == ':'){
						for(int y = k-1; temp[y] >= '0' && temp[y] <= '9'; y--){
							base += ((temp[y] - '0') * (pow(10, order2)));
							order2++;
						}
						fs.push_back(base);
						(columns[r])++;
						base = 0;
						order2 = 0;
						for(int t = k+1; temp[t] != '\0'; t++){
							temp2+= temp[t];
						}
						for(int y = 0; temp2[y] != '\0'; y++){
							if(temp2[y] == '.'){
								order++;
								for(int t = y-1; temp2[t] >= '0' && temp2[t] <= '9'; t--){
									base += (temp2[t] - '0') * (pow(10, order2));
									order2++;
								}
								order2 = 0;
								for(int t = y+1; temp2[t] >= '0' && temp2[t] <= '9'; t++){
									order2++;
								}
								order3 = order2;
								base1 = 0;
								for(int t = y+1; temp2[t] >= '0' && temp2[t] <= '9'; t++){
									carry = ((temp2[t] - '0') * (pow(10, order2-1)));
									base1+=  carry;
									order2--;
								}
								base1 = base1 / (pow(10, order3));
								base = base + base1;
								fs.push_back(base);
								(columns[r])++;
								base = 0;

							}
						}
						if(order == 0){
							order2 = 0;
							for(int y = 0; temp2[y] != '\0'; y++){
								order2++;
							}
							for(int y = 0; temp2[y] != '\0'; y++){
								order2--;
								fs.push_back((temp2[y] - '0') * (pow(10, order2)));
								(columns[r])++;
							}
						}	
						matrixArr[r] = new double [columns[r]];
						for(int y = 0; y < columns[r]; y++){
							matrixArr[r][y] = fs[y];
						}
						base = 0;
						order = 0;
						order2 = 0;
						temp2 = "";
					}
				}
				point = i+1;
			}
		if(buffer[i] == '\0') break;
		temp = "";
		} 
	}
	file.close();
}

////////////////////////////////

SparseMatrix SparseMatrix :: transpose(){
	SparseMatrix M;
	return *this;
}

ostream& operator<<(ostream& os, const SparseMatrix & m1){
	for(int i = 0; i < m1.getRows(); i++){
		for(int j = 0; j < m1.getColumns(i); j++){
			if(j == 0)os << m1.getMatrix(i, j) << ' ';
			else if(j % 2 == 1) os << m1.getMatrix(i, j) << ':';
			else if(j % 2 == 0) os << m1.getMatrix(i, j) << ' ';
		}
		os << '\n';
	}
	return os;
}

#endif
