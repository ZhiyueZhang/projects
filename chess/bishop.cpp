#include "bishop.h"
#include "king.h"
#include "board.h"
#include<stdlib.h>
//#include <iostream>
using namespace std;

Bishop::Bishop(char symbol, Position current, Board* b, Player* p): Piece(symbol, current, b, p) {};


void Bishop::getmoves(){
	//cout << "Bishop's getmoves\n";
	moves.clear();	//start fresh

	if(ownership->getKing()->getChecked())
		intercept();
	else{
		addpositions(1, 1);		//northeast direction
		addpositions(-1, 1);	//northwest direction
		addpositions(-1, -1);	//southwest direction
		addpositions(1, -1);	//southeast direction
	}
};

// attempts to block or take piece that is checking the king
void Bishop::intercept(){
	list<Position> l = ownership->getKing()->getAttackPath();
	list<Position>::iterator it;
	for(it = l.begin(); it != l.end(); it++){
		if(abs(current.getColumn()- it->getColumn()) == abs(current.getRow() - it->getRow()))
			moves.push_back(*it);	//can be reached
	}

	// checks to make sure the king won't get put in check
	for(it = moves.begin(); it != moves.end();){
		if(!canreach(*it, 1, 1) && !canreach(*it, 1, -1) && !canreach(*it, -1, 1) && !canreach(*it, -1, -1))
			it = moves.erase(it);
		else it++;
	}
	
//	cout << "In Bishop's Intercept method\n";

//	for(it = moves.begin(); it != moves.end(); it++)
//		cout << it->getColumn() << it->getRow() << endl;

	if(!moves.empty()){
		it = moves.begin();
		if(mimic_move(*it, ownership->getKing()))	//still in check
			moves.clear();	//cannot move
	}
}