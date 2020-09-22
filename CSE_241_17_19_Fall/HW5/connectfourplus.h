#ifndef CONNECTFOURPLUS_H
#define	CONNECTFOURPLUS_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "cfabstract.h"

using namespace std;

namespace CFAbstract{
	class ConnectFourPlus: public ConnectFourAbstract{
	public:
		void gameSetP();
	};	

}
#endif
