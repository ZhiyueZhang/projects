#include "rook.h"
#include "king.h"
#include "board.h"
//#include <iostream>
using namespace std;

Rook::Rook(char symbol, Position current, Board* b, Player* p, bool has_moved): 
	Piece(symbol, current, b, p), has_moved(has_moved) {}; // construct your rook (woulda worked better if we were calling them castles)

void Rook::getmoves(){ // get them moves
	//cout << "Rooks getmoves\n";
	moves.clear(); // gotta clear the old ones first, obviously
	// can YOU save the king (idk how an immobile tower is gonna do that but aight)
	if(ownership->getKing()->getChecked())
		intercept();
	// that's what I thought. He didn't need it. go get your other moves.
	else{
		addpositions(0, 1);		//north direction
		addpositions(0, -1);	//south direction
		addpositions(1, 0);		//east direction

		addpositions(-1, 0);		//west direction
	}
};

// is this immobile tower gonna come to life and save the king? let's find out.
void Rook::intercept(){
	list<Position> l = ownership->getKing()->getAttackPath();
	list<Position>::iterator it;

	// gotta check all the places that would help and see if you can go there
	for(it = l.begin(); it != l.end(); it++){
		if(it->getRow() == current.getRow() || it->getColumn() == current.getColumn())
			moves.push_back(*it);
	}
	for(it = moves.begin(); it != moves.end();){
		if(!canreach(*it, 1, 0) && !canreach(*it, -1, 0) && !canreach(*it, 0, 1) && !canreach(*it, 0, -1))
			it = moves.erase(it);
		else it++;
	}

	if(!moves.empty()){
		it = moves.begin();

		if(mimic_move(*it, ownership->getKing()))	//still in check
			moves.clear();	//cannot move
	}
}

//set to true when moved
void Rook::set_moved(bool moved){ has_moved = moved; };

//if true, cant castle
bool Rook::get_moved(){ return has_moved; };