#include "pawn.h"
#include "king.h"
#include "board.h"
#include "player.h"
//#include <iostream>
using namespace std;

Pawn::Pawn(char symbol, Position current, Board *b, Player* p, bool has_moved)
: has_moved(has_moved), Piece(symbol, current, b, p) {}; // constructor with all its defaults

void Pawn::set_moved() { has_moved = true; };	// sets if a piece has moved this turn

void Pawn::getmoves(){
	//cout << "Pawns getmoves \n";

	// clears the preexisting list of moves
	moves.clear();
	int row = current.getRow();
	char column = current.getColumn();

	//add moves due to en passant
	for(int i = 0; i < (int)passant.size(); i++)
		moves.push_back(passant[i]);
	
	passant.clear();
	
	// gets the team (white/black)
	if(getteam() == 1){
		if(row+1 <= 8){

			// can it move forward one piece?
			if(!grid->getB(column, row+1)->getOccupied()){
				// has it moved yet? If not, can it move forward two pieces?
				if(row+2 <= 8 && !has_moved && !grid->getB(column, row+2)->getOccupied())	//double 
					moves.push_back(Position(column, row+2, false));
				moves.push_back(Position(column, row+1, false));
			}

			// check to see if it's not in the left column
			if(column-1 >= 'a'){
				// is up 1 and left 1 occupied?
				if(grid->getB(column-1, row+1)->getOccupied()){ 
					// does the piece belong to the enemy
					if(grid->getP(column-1, row+1)->getteam() != 1)
						moves.push_back(Position(column-1, row+1, false));
				}
			}

			// check to see if it's not in the right column
			if(column+1 <= 'h'){
				// is up 1 and right 1 occupied?
				if(grid->getB(column+1, row+1)->getOccupied()){ 
					// does the piece belong to the enemy?
					if(grid->getP(column+1, row+1)->getteam() != 1)
						moves.push_back(Position(column+1, row+1, false));
				}
			}
		}
	}

	// same as above for other team, so it's all down 1 row instead
	else{
		if(row-1 >= 1){
			if(!grid->getB(column, row-1)->getOccupied()){
				if(row-2 >= 1 && !has_moved && !grid->getB(column, row-2)->getOccupied())	//double 
					moves.push_back(Position(column, row-2, false));
				moves.push_back(Position(column, row-1, false));
			}
			if(column-1 >= 'a'){
				if(grid->getB(column-1, row-1)->getOccupied()){ 
					if(grid->getP(column-1, row-1)->getteam() != 2)
						moves.push_back(Position(column-1, row-1, false));
				}
			}
			if(column+1 <= 'h'){
				if(grid->getB(column+1, row-1)->getOccupied()){ 
					if(grid->getP(column+1, row-1)->getteam() != 2)
						moves.push_back(Position(column+1, row-1, false));
				}
			}
		}
	}

	// makes sure none of them put the king in check, removes the move if it would
	for(list<Position>::iterator it = moves.begin(); it != moves.end();){
		if(mimic_move(*it, ownership->getKing()))
			it = moves.erase(it);
		else it++;
	}
//cout << "Checking pawn movement" << endl;
//cout << "Pawn: " << this->getcurrent().getColumn() << this->getcurrent().getRow() << endl;
	///for(list<Position>::iterator it = moves.begin(); it != moves.end(); it++)
		//cout << "Column: " << it->getColumn() << " Row: " << it->getRow() <<endl;
}

void Pawn::enpassant(Position enemy){
	if(this->getteam() == 1){	//this team is white, move upwards
		Position add = Position(enemy.getRow()+1, enemy.getColumn());
		passant.push_back(add);
	}
	else{
		Position add = Position(enemy.getRow()-1, enemy.getColumn());
		passant.push_back(add);
	}
}