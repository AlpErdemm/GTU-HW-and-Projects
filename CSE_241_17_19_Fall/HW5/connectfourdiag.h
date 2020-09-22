#ifndef CONNECTFOURDIAG_H
#define	CONNECTFOURDIAG_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "cfabstract.h"

namespace CFAbstract{
	class ConnectFourDiag: public ConnectFourAbstract{
	public:
		void gameSetD();
	};
}
#endif
