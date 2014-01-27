#include "king.h"
#include "player.h"
#include "board.h"
#include "rook.h"
#include <iostream>
using namespace std;

//Constructor
King::King(char symbol, Position current, Board* b, Player *p, bool incheck, bool has_moved): 
	incheck(incheck), has_moved(has_moved), Piece(symbol, current, b, p) 
	{
		p->setKing(this);
	}; 

// checks if the king is in check
void King::isincheck(){
	attacking_pieces.clear();	//start fresh

	//cout << "CHECKING DIAGONALS IN isincheck" << endl;
	// check all diagonal directions
	check_diagonal(1, 1);	//northeast
	check_diagonal(1, -1);	//southeast
	check_diagonal(-1, 1);	//northwest
	check_diagonal(-1, -1);	//southwest

	//cout << "CHECKING STRAIGHTS IN isincheck" << endl;
	//cout << "CHECKING NORTH\n";

	// check all straight directions
	check_straight(0, 1);	//north

	//cout << "CHECKING SOUTH\n";
	check_straight(0, -1);	//south

//	cout << "CHECKING EAST\n";
	check_straight(1, 0);	//east

	//cout << "CHECKING WEST\n";
	check_straight(-1, 0);	//west

	//cout<< "CHECKING KNIGHTS IN isincheck" << endl;
	// check knight positions
	check_knights();	//check 8 possible knight positions
	//cout << "CHECKING KINGS IN isincheck" << endl;
	// make sure the kings aren't somehow checking each other
	check_king();		//running this will ensure one king will never check the other

	// are there any pieces checking the king?
	if(attacking_pieces.empty())
		incheck = false;
	else incheck = true;

//	cout << "SET ATTACK PATH" << endl;
};



void King::getmoves(){
	//cout << "King's getmoves\n";
	moves.clear();	//start fresh
	//the King is special, you must change its ***current*** position
	Position original_pos = current;		//for the King
	int row = current.getRow();
	int column = current.getColumn();

	list<Position>::iterator it;
	bool original_ischecked = incheck;	//for the king
	vector<Piece*> attack_original = attacking_pieces;	//for the king

	moves.push_back(Position(column, row+1, false));
	moves.push_back(Position(column, row-1, false));
	moves.push_back(Position(column-1, row, false));
	moves.push_back(Position(column+1, row, false));
	moves.push_back(Position(column+1, row+1, false));
	moves.push_back(Position(column+1, row-1, false));
	moves.push_back(Position(column-1, row+1, false));
	moves.push_back(Position(column-1, row-1, false));

//Filter out moves not in board and moves that would result in capturing your own piece
	for(it = moves.begin(); it != moves.end();){
		if(!valid_move(*it) || (grid->getP(*it) != NULL && grid->getP(*it)->getteam() == getteam()))
			it = moves.erase(it);
		else it++;
	}
//We keep making hypothetical moves, we should move it into a single method
	for(it = moves.begin(); it != moves.end();){
		original = grid->getP(*it);		//get that piece *, if any								
		bool old_pos = grid->getB(*it)->getOccupied();	//keep trach of old value
		grid->getB(*it)->setOccupied(true);	//set new position as occupied
		grid->getB(original_pos)->setOccupied(false);	//set old position as unoccupied
		grid->setP(this, *it);	//set Piece array to point to this
		grid->setP(original_pos);	//remove current from board
		current = *it;	//the current must change since this is the King

		isincheck();
		bool checked = incheck;
		
		//reset to original grid settings
		grid->getB(*it)->setOccupied(old_pos);
		grid->getB(original_pos)->setOccupied(true);
		grid->setP(this, original_pos);
		grid->setP(original, *it);

		if(checked)		//either it's a blocking piece or it can't protect King
			it = moves.erase(it);
		else it++;
	}

	attacking_pieces = attack_original;	//set back to original
	incheck = original_ischecked;	//set back to original
	current = original_pos;
	set_attack_path();
	castle();
};


//This attack vector is needed in order to determine the
//intercept method all other classes will have
//But if the king sets it, this method might be depreciated...
void King::attack(Piece *p){ attacking_pieces.push_back(p); };

void King::setcheck(bool check) { incheck = check; };	//must be called every turn
												//might only be called for hypothetical, restore to original
bool King::getChecked() { return incheck; };

void King::resetattack() { attacking_pieces.clear(); };	//you call it at the end of your turn

vector<Piece*> King::getAttackVector() { return attacking_pieces; };

void King::setAttackVector(std::vector<Piece*>attack) { attacking_pieces = attack; };

void King::setAttackPath(list<Position> path){
	attack_path = path;
}; 

list<Position> King::getAttackPath() { return attack_path; }; // getter for attack path

void King::set_attack_path(){ // setter for attack path
	attack_path.clear();	//start fresh every turn
	
	if(attacking_pieces.size() == 1){
		Piece *p = attacking_pieces[0];
		char symbol = p->getsymbol();
		if(symbol == 'p' || symbol == 'P' || symbol == 'N' || symbol == 'n')
			attack_path.push_back(p->getcurrent());	//the only way to "intercept" is to capture

		else {	
			Position enemy_location = p->getcurrent();
			int row = enemy_location.getRow();
			char column = enemy_location.getColumn();

//either the row differs, the column differs or both.
			if(enemy_location.getRow() == current.getRow()){			//Rook or Queen
				while(column > current.getColumn()){	//above
					attack_path.push_back(Position(column, row, false));
					column--;
				}
				while(column < current.getColumn()){	//below
					attack_path.push_back(Position(column, row, false));
					column++;
				}
				column = enemy_location.getColumn();	//set back to original
			}
			else if(enemy_location.getColumn() == current.getColumn()){	//wait but then this would execute...
				while(row > current.getRow()){
					attack_path.push_back(Position(column, row, false));
					row--;
				}
				while(row < current.getRow()){
					attack_path.push_back(Position(column, row, false));
					row++;
				}

				row = enemy_location.getRow();	//set back to original
			}
			else if(enemy_location.getColumn() > current.getColumn()){//diagonal
				while(row > current.getRow()){	//above
					attack_path.push_back(Position(column, row, false));
					row--;
					column--;
				}
				while(row < current.getRow()){ //below
					attack_path.push_back(Position(column, row, false));
					row++;
					column--;
				}

				row = enemy_location.getRow();
				column = enemy_location.getColumn();
			}
			else{
				while(row > current.getRow()){	//above
					attack_path.push_back(Position(column, row, false));
					row--;
					column++;
				}
				while(row < current.getRow()){
					attack_path.push_back(Position(column, row, false));
					row++;
					column++;
				}
			}
		}
	}
}

//set to true when moved
void King::set_moved(bool moved){ has_moved = moved; };

//if true, cant castle
bool King::get_moved(){ return has_moved; };

//adds ability to castle
void King::castle(){
//	cout << "Issue with castling\n";

	if(!has_moved && !incheck){	//cant have moved and cant be in check
		int current_row = current.getRow();
		char current_col = current.getColumn();
		Rook *left_rook = 0;
		Rook *right_rook = 0;
		bool left_incheck = false;
		bool right_incheck = false;

		//search left for rook
		for(char ch = current_col-1; ch >= 'a'; ch--){
			if(grid->getB(Position(current_row, ch))->getOccupied()){
				char sym = grid->getP(ch, current_row)->getsymbol();
				
				if((tolower(sym) == 'r') && grid->getP(ch, current_row)->getteam() == this->getteam()
					&& current_col - ch > 2)
					left_rook = dynamic_cast<Rook*>(grid->getP(ch, current_row));
				
				break;
			}
		}

		//repeat for right rook
		for(char ch = current_col+1; ch <= 'h'; ch++){
			if(grid->getB(Position(current_row, ch))->getOccupied()){
				char sym = grid->getP(ch, current_row)->getsymbol();
				
				if((tolower(sym) == 'r') && grid->getP(ch, current_row)->getteam() == this->getteam()
					&& ch - current_col > 2)
					right_rook = dynamic_cast<Rook*>(grid->getP(ch, current_row));
				
				break;
			}
		}

		//check if any position would put the king in check

		if(left_rook != 0 && !left_rook->get_moved()){
			Position left = left_rook->getcurrent();

			for(char ch = current_col-2; ch < current_col; ch++){
				left_rook->setcurrent(Position(current_row, ch));
				grid->getB(ch, current_row)->setOccupied(true);

				if(!left_rook->avoid_capture())
					left_incheck = true;	//this position would put the King in check
				
				grid->getB(ch, current_row)->setOccupied(false);
			}
			
			left_rook->setcurrent(left);	//reset back to original Position
			grid->getB(left)->setOccupied(true);	//reset original Position to occupied
		}

		if(right_rook != 0 && !right_rook->get_moved()){
			Position right = right_rook->getcurrent();

			for(char ch = current_col+2; ch > current_col; ch--){
				right_rook->setcurrent(Position(current_row, ch));
				grid->getB(ch, current_row)->setOccupied(true);

				if(!right_rook->avoid_capture())
					right_incheck = true;	//this position would put the King in check

				grid->getB(ch, current_row)->setOccupied(false);
			}
			
			right_rook->setcurrent(right);	//reset back to original Position
			grid->getB(right)->setOccupied(true);
		}

		if(left_rook != 0 && !left_incheck)
			moves.push_back(Position(current_row, current_col-2));

		if(right_rook != 0 && !right_incheck)
			moves.push_back(Position(current_row, current_col+2));
	}
}



