#ifndef __SPARSEVECTOR_H
#define __SPARSEVECTOR_H


using namespace std;

class SparseVector{
public:
	SparseVector();
	SparseVector(int size);
	SparseVector(string filename);
	friend double dot(const SparseVector & s1, const SparseVector & s2);
	friend SparseVector operator + (const SparseVector & s1, const SparseVector & s2);
	friend SparseVector operator - (const SparseVector & s1, const SparseVector & s2);
	void operator = (const SparseVector & s2);

 	friend ostream& operator<<(ostream& os, const SparseVector & s1);  
	//  Getter and Setters (inline)

	inline void setVector(int value){
		size++;
		vectorArr[size-1] = value;
	}
	inline double getVector(int i) const{
		return vectorArr[i];
	}
	inline int getSize() const{
		return size;
	}
private:
	double * vectorArr;
	int size;

};
// Constructors of SparseVector

SparseVector :: SparseVector(){
	size = 0;
}
SparseVector :: SparseVector(int siz){
	size = siz;
}
SparseVector :: SparseVector(string filename){

	size = 0;
	string buffer;
	ifstream file;
	int count = 0;

	file.open(filename);

	getline(file, buffer);

	for(int i = 0; buffer[i] != '\0'; i++){
		if(buffer[i] == ':') count++;
	}
	vectorArr = new double [count*2];

	int point = 0, order = 0, order2 = 0, order3 = 0, order4 = 0, flag = 0;
	double carry, base;
	string temp;
	string temp2;

	for(int i = 0;flag != -1; i++){
		if(buffer[i] == ' ' || buffer[i] == '\0'){
			order4++;
			for(int j = point; j < i; j++){
				temp+= buffer[j];
			}
			for(int k = 0; temp[k] != '\0'; k++){
				if(temp[k] == ':'){
					for(int y = k-1; temp[y] >= '0' && temp[y] <= '9'; y--){
						base += (temp[y] - '0') * (pow(10, order2));
						order2++;
					}
					setVector(base);
					base = 0;
					order2 = 0;
					for(int t = k+1; temp[t] != '\0'; t++){
						temp2+= temp[t];
					}
					for(int y = 0; temp2[y] != '\0'; y++){
						if(temp2[y] == '.'){
							order++;
							for(int t = y-1; temp2[t] >= '0' && temp2[t] <= '9'; t--){
								base+= (temp2[t] - '0') * (pow(10, order2));
								order2++;
							}
							order2 = 0;
							for(int t = y+1; temp2[t] >= '0' && temp2[t] <= '9'; t++){
								order2++;
							}
							order3 = order2;
							for(int t = y+1; temp2[t] >= '0' && temp2[t] <= '9'; t++){
								carry = ((temp2[t] - '0') * (pow(10, order2-1)));
								carry = carry / (pow(10, order3));
								base+=  carry;
								order2--;
							}
						}
					}
					if(order == 0){
						order2 = 0;
						for(int y = 0; temp2[y] != '\0'; y++){
							order2++;
						}
						for(int y = 0; temp2[y] != '\0'; y++){
							order2--;
							base+= ((temp2[y] - '0') * (pow(10, order2)));
						}
					}				
					setVector(base);
					base = 0;
					order = 0;
					order2 = 0;
					temp2 = "";
				}
			}
			temp = "";
			point = i+1;
			if(buffer[i] == '\0' || order4 == count){
				delete [] vectorArr;
				flag = -1;
				break;
			}
		}
	}
	file.close();

}

////////////////////////////////

double dot(const SparseVector & s1, const SparseVector & s2){
	double result = 0;
	if(s1.getSize() >= s2.getSize()){
		for(int i = 0; i < s1.getSize(); i++){
			if(i % 2 == 0 && s1.getVector(i) == s2.getVector(i)){
				result += s1.getVector(i+1) * s2.getVector(i+1);
			}
		}
	}
	else{
		for(int i = 0; i < s2.getSize(); i++){
			if(i % 2 == 0 && s2.getVector(i) == s1.getVector(i)){
				result += s1.getVector(i+1) * s2.getVector(i+1);
			}
		}
	}
	return result;
}	
SparseVector operator + (const SparseVector & s1, const SparseVector & s2){
	SparseVector s3;
	if(s1.getSize() >= s2.getSize()){
		for(int i = 0; i < s1.getSize(); i++){
			if(i % 2 == 0 && s1.getVector(i) == s2.getVector(i)){
				s3.setVector(i);
				s3.setVector(s1.getVector(i+1) + s2.getVector(i+1));
			}
		}
	}
	else{
		for(int i = 0; i < s2.getSize(); i++){
			if(i % 2 == 0 && s1.getVector(i) == s2.getVector(i)){
				s3.setVector(i);
				s3.setVector(s1.getVector(i+1) + s2.getVector(i+1));
			}
		}
	}
	return s3;
}

SparseVector operator - (const SparseVector & s1, const SparseVector & s2){
	SparseVector s3;
	if(s1.getSize() >= s2.getSize()){
		for(int i = 0; i < s1.getSize(); i++){
			if(i % 2 == 0 && s1.getVector(i) == s2.getVector(i)){
				s3.setVector(i);
				s3.setVector(s1.getVector(i+1) - s2.getVector(i+1));
			}
		}
	}
	else{
		for(int i = 0; i < s2.getSize(); i++){
			if(i % 2 == 0 && s1.getVector(i) == s2.getVector(i)){
				s3.setVector(i);
				s3.setVector(s1.getVector(i+1) - s2.getVector(i+1));
			}
		}
	}
	return s3;
}
void SparseVector :: operator = (const SparseVector & s2){

	this->size = 0;
	delete [] this->vectorArr;
	this->vectorArr = new double [s2.getSize() * 2];
	for(int i = 0; i < s2.getSize(); i++){
		this->setVector(s2.getVector(i));
	}
}

ostream& operator<<(ostream& os, const SparseVector & s1){
	for(int i = 0; i < s1.getSize(); i++){
		if(i % 2 == 0) os << s1.getVector(i);
		else if(i % 2 == 1) os << ':' << s1.getVector(i) << ' ';
	}
	return os;
}

#endif
