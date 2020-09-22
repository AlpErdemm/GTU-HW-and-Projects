#ifndef CONNECTFOURUNDO_H
#define	CONNECTFOURUNDO_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "cfabstract.h"

using namespace std;

namespace CFAbstract{
	class ConnectFourPlusUndo: public ConnectFourAbstract{
	public:
		void gameSetU();
	};	
}
#endif
