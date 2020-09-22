#include <iostream>
#include "cfabstract.h"
#include "cell.h"
#include "connectfourplus.h"
#include "connectfourplusundo.h"
#include "connectfourdiag.h"

using namespace CFAbstract;

int main(){
	char objectType;
		int obj, control;	
		cout << "P for PLus, D for Diagonal and U for Undo." << endl;
		cin >> objectType;

		if(objectType == 'P' || objectType == 'p'){
			ConnectFourPlus origin;
			origin.setObjType(objectType);
			origin.gameSetP();
		}
		else if(objectType == 'U' || objectType == 'u'){
			ConnectFourPlusUndo origin;
			//origin.setGLOB(1);
			origin.setObjType(objectType);
			origin.gameSetU();
		}
		else if(objectType == 'D' || objectType == 'd'){
			ConnectFourDiag origin;
			origin.setObjType(objectType);
			origin.gameSetD();
		}
		else{
			cout << "Woops!" << endl;
		}
	return 0;
}




