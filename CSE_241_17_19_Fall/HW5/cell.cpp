#include "cell.h"

using namespace std;

namespace CFAbstract{
	char Cell::getPosition() const{
		return position;
	}
	int Cell::getRow() const{
		return row;
	}
	char Cell::getInside() const{
		return inside;
	}
	void Cell::setPosition(char newPosition){
		position = newPosition;
	}
	void Cell::setRow(int newRow){
		row = newRow;
	}
	void Cell::setInside(char newInside){
		inside = newInside;
	}
	int Cell::getCOUNT()const{
		return moveCOUNT;
	}
}
