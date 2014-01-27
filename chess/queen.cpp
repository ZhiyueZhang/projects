#include "queen.h"
#include "king.h"
#include "board.h"
#include<stdlib.h>
//#include <iostream>

using namespace std;

Queen::Queen(char symbol, Position current, Board *b, Player* p): Piece(symbol, current, b, p) {}; // construct your queen

void Queen::getmoves(){ // get her moves
	//cout << "Queen's getmoves\n";
	moves.clear();

	// can you protect your king (that's kinda backwards, isn't it?)
	if(ownership->getKing()->getChecked())
		intercept();

	// you can't? well damn
	else{
		addpositions(0, 1);		//north direction
		addpositions(0, -1);	//south direction
		addpositions(1, 0);		//east direction
		addpositions(-1, 0);	//west direction
		addpositions(1, 1);		//northeast direction
		addpositions(-1, 1);	//northwest direction
		addpositions(-1, -1);	//southwest direction
		addpositions(1, -1);	//southeast direction
	}
}

// let's see if you're going to be useful in protecting your king or not
void Queen::intercept(){
	//cout << "Queens intercept\n";
	list<Position> l = ownership->getKing()->getAttackPath();
	list<Position>::iterator it;

	// gotta check to see if you can do it
	for(it = l.begin(); it != l.end(); it++){
	//	cout << it->getColumn() << it->getRow() << endl;

		if(abs(current.getColumn()- it->getColumn()) == abs(current.getRow() - it->getRow()))
			moves.push_back(*it);	//can be reached

		if(it->getRow() == current.getRow() || it->getColumn() == current.getColumn())
			moves.push_back(*it);
	}
//	cout << "These moves are diagonal or straight from Queen\n";
//	for(it=moves.begin(); it != moves.end(); it++)
	//	cout << it->getColumn() << it->getRow() << endl;

//If this is too slow, I can optimize it
	for(it = moves.begin(); it != moves.end();){
		if(!canreach(*it, 1, 0) && !canreach(*it, -1, 0) && !canreach(*it, 0, 1) && !canreach(*it, 0, -1) &&
		   !canreach(*it, 1, 1) && !canreach(*it, 1, -1) && !canreach(*it, -1, 1) && !canreach(*it, -1, -1))
			it = moves.erase(it);
		else it++;
	}

//	cout << "In Queen's Intercept\n";
	//for(it = moves.begin(); it != moves.end(); it++)
//		cout << it->getColumn() << it->getRow() << endl;

	if(!moves.empty()){
		it = moves.begin();

		if(mimic_move(*it, ownership->getKing()))	//still in check
			moves.clear();	//cannot move
	}
}