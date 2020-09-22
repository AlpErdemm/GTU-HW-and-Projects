#ifndef CELL_H
#define	CELL_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

namespace CFAbstract{
	class Cell{
		public:
			int getCOUNT() const;
			inline void setCOUNT(int glob){
				moveCOUNT = glob;
			}
			inline void killCOUNT(){
				moveCOUNT = 0;
			}
			char getPosition() const;
			int getRow() const;
			char getInside() const;
			void setPosition(char newPosition);
			void setRow(int newRow);
			void setInside(char newInside);

		private:	
			int moveCOUNT;
			char position;			// a,b,c?
			int row;				// 0,1,2?
			char inside;			// user1, user2 or empty .

	};	

}
#endif
