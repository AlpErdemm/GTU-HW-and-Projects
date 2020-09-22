// Object Oriented Programming Homework-1, Muhammetalp Erdem 151044006
#include <iostream>
#include <string>
using namespace std;
// The inputs must be entered as it was given in homework pdf. Stod function sometimes can't work efficently when you enter 170 instead of 170.0
// Based on your speech in the class, I assumed that the user always enters acceptable input.
// This is the struct I'll be using to hold all the data.
struct Object{
	int orderObj, orderPri; // These are variable that keeps 'objects' and 'prices' in track.
	string * objects;	// Bicycle etc.(dinamic)
	double result, * prices; // Result: the double contains the sum of prices. prices: Keeps the prices of every part(dinamic)
	int * usage;	// usage is 'number of parts' for example keeps 2 for 2*Wheel.(dinamic)
}obj = {1,1};

void splitMultiObject(string str, int u); //Only works when user enters a part that contains several fractions.(if there is '+' in the string)
void whatIs(string str, int u);	   // The recursive main function that does most of the job, works with splitMultiObject recursively.
void spacekiller(string & str);	   // Takes a string and erases the spaces.
int invesstar(string str);	   // Returns 1 if there is a star(*) in the string, 0 otherwise.
int invesplus(string str);         // Returns 1 if there is a plus(+) in the string, 0 otherwise.
int splitStar(string & str);	   // Example-> If the taken string is 2*Wheel. The function erases the 2* part from the string and returns 2.
void expand();

int main()
{
	cout << "Define the object: " << endl;
	char ch[100];
	string temp;
	cin.getline(ch, sizeof(ch));
	for(int i = 0; ch[i] != '\0';i++) temp.push_back(ch[i]);
 	spacekiller(temp);

	string realObject = "1*"; // It was necessary to help the recursion work(example: 1*Bicycle);
	realObject += temp;

	obj.result = 0;

	obj.objects = new string [1];	// There is no unneccessary allocation in the code so I took the minimum size.
	obj.prices = new double [1];
	obj.usage = new int [1];

	whatIs(realObject, 1);		// This is the function that is going to make all the calculations.

	for(int i = 0; i < obj.orderObj-1; i++) obj.result += (obj.prices[i] * obj.usage[i]);	// Multiplies the price of the part by the mumber of the part. Then, sums them into 'result' variable.
	cout << "Total cost of " << temp << " is :" << obj.result << endl;

	return 0;
}
void splitMultiObject(string str, int u){
	int i, j;
	string temp, base;
	spacekiller(str);
	for(i = 0; i < str.size(); i++){
		if(str[i] == '+'){		// If there is '+' in the string; the function tooks the characters before that '+' and sends new string to whatIs function. Meanwhile it erases that part to search the rest of the string.
			for(j = 0; j < i; j++) temp.push_back(str[j]);		
			for(j = i+1; j < str.size(); j++) base.push_back(str[j]);
			whatIs(temp, u);
			splitMultiObject(base, u);
			return;
		}	
	
	}
	whatIs(str,u); 	//If there is no '+' in the string, send it to whatIs just to be sure.
}
void whatIs(string str, int u){
	int count;
	if(invesstar(str) == 0){  	// Works if the input string is a price.
		double dob;
		dob = stod(str);
		obj.prices[obj.orderPri - 1] = dob;
	}
	else if(invesstar(str) == 1){
		if(invesplus(str) == 1) splitMultiObject(str, u);	// Works if the input string contains multiple fractions.
		else if(invesplus(str) == 0){			// Works if the input string is a part.(example:2*Wheel)
			count = splitStar(str);			// Count holds the number of the part.(example: 2 of 2*Wheel)
			count = count * u;
			obj.usage[obj.orderObj - 1] = count;
			cout << "What is " << str << "?" << endl;
			obj.objects[obj.orderObj-1] += str;
			obj.orderPri = obj.orderObj;
			obj.orderObj++;
			expand();				// Expand is an essential function that enlarges the dinamic arrays by 1.
			char ch[100];
			string temp;
			cin.getline(ch, sizeof(ch));
			for(int i = 0; ch[i] != '\0';i++) temp.push_back(ch[i]);
			spacekiller(temp);
			whatIs(temp,count);				// Then the new input string goes to whatIs again.			
		}
	}
}
void expand(){
	string * temp = new string[obj.orderObj + 1];		//Expands objects array.
	for(int i = 0; i < obj.orderObj; i++){
		temp[i] += obj.objects[i];
	}
	delete [] obj.objects;
	obj.objects = temp;

	double * pri = new double[obj.orderPri + 1];		//Expands prices array.
	for(int i = 0; i < obj.orderPri; i++){
		pri[i] = obj.prices[i];
	}
	delete [] obj.prices;
	obj.prices = pri;	

	int * num = new int[obj.orderPri + 1];			//Expands usage array.
	for(int i = 0; i < obj.orderPri; i++){
		num[i] = obj.usage[i];
	}
	delete [] obj.usage;
	obj.usage = num;
}
void spacekiller(string & str){			// In order to erase the spaces, this function gathers all of the characters exept space(' ') and assigns this string to the input string.
	string temp;
	for(int i = 0; i < str.size(); i++){	
		if(str[i] != ' '){
			temp.push_back(str[i]);
		}
	}
	str = temp;
}
int invesstar(string str){		// Searches for a star symbol(*).
	for(int i = 0; i < str.size(); i++){
		if(str[i] == '*') return 1;
	}
	return 0;
}
int invesplus(string str){		// Searches for a plus symbol(+).
	for(int i = 0; i < str.size(); i++){
		if(str[i] == '+') return 1;
	}
	return 0;
}
int splitStar(string & str){
	int count;
	string ct, temp;
	for(int i = 0; i < str.size(); i++){
		if(str[i] == '*'){
			for(int j = 0; j < i; j++) ct.push_back(str[j]);	// Takes the number part-
			count = stoi(ct);					// -and turns it into an integer.
			for(int j = i+1; j < str.size(); j++) temp.push_back(str[j]);	// Takes the part's name.
			str = temp;		
		}
	}
	return count;
}



