#include <iostream>
#include <fstream>

using namespace std;


class Base{
public:
	Base(){countDirect = 0; headD = nullptr;}
	void init();
	int reader();
	void command();
	void commandsHandler(string temp);
	void commandCD(string A);
	void commandNEW(string A);
	void commandMOVE(string A);
	void commandCOPY(string A);
	void commandDELETE(string A);
	void Calc(string temp);
	void initCalc(string temp);
	void initHandler(string buffer, int count);
	void initFandler(string buffer, int count);
	void addD(string buffer);
	int searchDirectory(string inp);
	int countSlash(string buffer);
	string cutD(string buffer, int flag);
	void addition(string temp, int keep);
	string grabD(string buffer, int i);
	void addFile(string buffer, int i);
	void headSwitch(string buffer);

	int countDirect;

private:
	class Directory; 
	Directory * headD;
};

class Base::Directory{
public:
	class File;
	void Dinit();
	Directory(){countFile = 0; name = ""; link = nullptr; headF = nullptr;}
	Directory(string theName){countFile = 0; name = theName; link = nullptr; headF = nullptr;}
	Directory(string theName, Directory * theLink){countFile = 0; name = theName; link = theLink; headF = nullptr;}
	Directory * getLink() const {return link;}
	string getName(){return name;}
	void setName(string theName){name = theName;}
	void setLink(Directory * theLink){link = theLink;}
	void initFileP(string buffer);
	File * getHeaderF(){return headF;}
	void createLink(string buffer);
	void handleFile(Directory & head);
	int countFile;
private:
	string name;
	Directory * link;
	File * headF;
};

class Base::Directory::File{
public:
	File(){name = ""; link = nullptr;}
	File(string theName){name = theName; link = nullptr;}
	File(string theName, File * theLink){name = theName; link = theLink;}
	File * getLink() const {return link;}
	string getName(){return name;}
	void setName(string theName){name = theName;}
	void setLink(File * theLink){link = theLink;}
private:
	string name;
	File * link;
};

int main(){
	Base b;
	b.init();

	return 0;
}

void Base::init(){
	reader();
	command();
}
int Base::reader(){
	string temp;
	ifstream fp;

	int count = 0;

	fp.open("files.txt");

	while(getline(fp, temp)){
		if(count == 0) initCalc(temp);
		else addD(temp);
		count++;
	} 

	fp.close();

	return 0;
}

void Base::command(){
	string temp;
	ifstream fp;

	fp.open("commands.txt");

	while(getline(fp, temp)){
		commandsHandler(temp);
	} 

	fp.close();	
}

void Base::commandsHandler(string temp){
	string holder = "";
	holder += temp[0]; holder += temp[1];

	if(holder.compare("cd") == 0){
		commandCD(temp);
	}
	else{
		holder+= temp[2];
		if(holder.compare("new") == 0){
			commandNEW(temp);
		}
		else{
			holder+= temp[3];
			if(holder.compare("move") == 0){
				commandMOVE(temp);
			}
			else if(holder.compare("copy") == 0){
				commandCOPY(temp);
			}
			else{
				holder+= temp[4];holder+=temp[5];
				if(holder.compare("delete") == 0){
					commandDELETE(temp);
				}
				else{
					cout << "Woops!" << endl;
				}
			}
		}
	}
}
void Base::commandCD(string A){

}
void Base::commandNEW(string A){

}
void Base::commandMOVE(string A){

}
void Base::commandCOPY(string A){

}
void Base::commandDELETE(string A){

}


void Base::initCalc(string temp){
	string buffer;
	int iter = 0, count = 0;
	while(temp[iter] != '\0'){
		if(temp[iter] != '/'){
			buffer += temp[iter];
			iter++;
			if(temp[iter] == '\0'){
				initFandler(buffer, count);
				count++;
				buffer = "";
				iter++;				
			}
		}
		else{
			initHandler(buffer, count);
			count++;
			buffer = "";
			iter++;
		}
	}
}

void Base::initHandler(string buffer, int count){
	int newcount = count-1;

	if(count == 0){
		headD = new Directory;
		headD->setName(buffer);
		headD->setLink(nullptr);
	}
	else{
		Directory * temp;
		temp = headD;
		while(count){
			temp = temp->getLink();
			count--;
		}
		temp = new Directory;
		temp->setName(buffer);
		temp->setLink(nullptr);

		Directory * temp2;
		temp2 = headD;
		while(newcount){
			temp2 = temp2->getLink();
			newcount--;
		}
		temp2->setLink(temp);
	}
}
void Base::initFandler(string buffer, int count){
	Directory * t;
	t = headD;
	while(t->getLink() != nullptr) t = t->getLink();
	t->initFileP(buffer);
}

int Base::searchDirectory(string inp){
	Directory * d1;
	int i = 0;
	d1 = headD;
	while(d1 != nullptr){
		if(inp.compare(d1->getName()) == 0) return i;
		d1 = d1->getLink();
		i++;
	}	
	return 0;
}
void Base::addD(string buffer){
	int countS = countSlash(buffer);
	int i, keep, flag = -1, repeatS = countS;
	string temp, newtemp;
	for(i = 1; i <= repeatS; i++){
		if(keep = searchDirectory(grabD(buffer, i)) != 0){
			flag = i-1;
			break;
		} 
	}
	if(countS == 1){
		addFile(cutD(buffer, 1), keep);
	}
	else if(countS == 2){
		if(flag == 0) addFile(cutD(buffer, 2), keep);
		else{
			headSwitch(grabD(buffer, 1));
			addFile(cutD(buffer, 2), keep);
		}
	}

}
void Base::headSwitch(string buffer){
	Directory * d;
	d = new Directory;
	d->setName(headD->getName());
	d->setLink(headD->getLink());
	d->handleFile(*headD);
	headD->setName(buffer);
	headD->setLink(d);
}
void Base::addFile(string buffer, int i){
	Directory * d;
	d = headD;
	while(i){
		d=d->getLink();
		i--;
	}
	d->createLink(buffer);
}
void Base::Directory::handleFile(Directory & head){
	Directory * temp;
	temp = &head;
	File * Ftemp, * Ftemp2;
	Ftemp = temp-> headF;
	Ftemp2 = this-> headF;
	while(Ftemp != nullptr){
		Ftemp2->setName(Ftemp->getName());
		Ftemp2->setLink(Ftemp->getLink());
		Ftemp = Ftemp->getLink();
	}
	
}
int Base::countSlash(string buffer){
	int count = 0;
	for(int i = 0; buffer[i] != '\0'; i++){
		if(buffer[i] == '/') count++;
	}
	return count;
}
string Base::grabD(string buffer, int i){
	string temp = "", newtemp = "";
	int count = 0;
	for(int j = 0; buffer[j] != '\0'; j++){
		temp += buffer[j];
		if(buffer[j] == '/'){
			count++;
			if(count == i){
				return newtemp;
			} 
			else{
				temp = "";
			}
		}
		if(buffer[j] == '\0') return temp;
		newtemp = temp;		
	}
}
string Base::cutD(string buffer, int flag){
	int count = 0, sign = -1;
	string temp = "";
	for(int i = 0; buffer[i] != '\0'; i++){
		if(buffer[i] == '/'){
			count++;
			if(count == flag){
				sign = i;
				break;
			}
		}
	}
	if(sign == -1) return buffer;

	for(int i = sign+1; buffer[i] != '\0'; i++){
		temp += buffer[i];
	}
	return temp;
}
void Base::addition(string temp, int keep){
}

void Base::Directory::initFileP(string buffer){
	headF = new File;
	headF->setName(buffer);
	headF->setLink(nullptr);
}
void Base::Directory::createLink(string buffer){
	if(this->headF == nullptr){
		this->headF = new File;
		(this->headF)->setName(buffer);
		(this->headF)->setLink(nullptr);
	}
	else{
		File * f;
		f = this->headF;
		while(f != nullptr) f = f->getLink();
		f = new File;
		f->setName(buffer);
		f->setLink(nullptr);
	}
}