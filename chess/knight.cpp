#include "knight.h"
#include "king.h"
#include "board.h"
//#include <iostream>
using namespace std;

Knight::Knight(char symbol, Position current, Board *b, Player* p): Piece(symbol, current, b, p) {};

void Knight::getmoves(){ // gets moves for knight
	//cout << "Knight's getmoves\n";
	moves.clear();
	int row = current.getRow();
	char column = current.getColumn();

	moves.push_back(Position(column-1, row+2, true));
	moves.push_back(Position(column+1, row+2, true));
	moves.push_back(Position(column-1, row-2, true));
	moves.push_back(Position(column+1, row-2, true));
	moves.push_back(Position(column+2, row+1, true));
	moves.push_back(Position(column+2, row-1, true));
	moves.push_back(Position(column-2, row+1, true));
	moves.push_back(Position(column-2, row-1, true));

	for(list<Position>::iterator it = moves.begin(); it != moves.end();){
		if(!valid_move(*it) || (grid->getP(*it) != NULL && grid->getP(*it)->getteam() == getteam()))
			it = moves.erase(it);
		else {
		//	cout << "Simulating move\n";
			if(mimic_move(*it, ownership->getKing()))
				it = moves.erase(it);
			else it++;
		}
	}
	//for(list<Position>::iterator it2 = moves.begin(); it2 != moves.end(); it2++)
	//	cout << "In knight class" << "Column: " << it2->getColumn() << "Row: " << it2->getRow() << endl;
	//cout << "IF YOU SEE THIS THEN YOU'RE IN KNIGHT'S GETMOVES FN \n";
};