#include "piece.h"
//#include <iostream>
#include "player.h"
#include "board.h"
#include "king.h"

using namespace std;

Piece::Piece(char symbol, Position current, Board *b, Player* ownership, bool has_moved)
: symbol(symbol), current(current), grid(b), ownership(ownership){};

char Piece::getsymbol() { return symbol; }; // get the symbol

Position Piece::getcurrent(){ return current; }; // where are you, piece?

void Piece::getmoves() {}; // doesn't actually seem to do anything, why do you exist?

int Piece::getteam(){ return ownership->getPlayerNumber(); }; // returns the player number

bool Piece::valid_move(const Position& p){ // is that a valid move?
	return (p.getColumn() >= 'a' && p.getColumn() <= 'h' && p.getRow() >= 1 && p.getRow() <= 8);
};

Player* Piece::getowner(){ return ownership; }; // who's your daddy, piece?

void Piece::setcurrent(Position p) { current = p; }; // put the piece in its place

//Add to vector of moves
void Piece::addpositions(int col_direction, int row_direction){
	Position move = current;
	move.setColumn(move.getColumn() + col_direction);
	move.setRow(move.getRow() + row_direction);
	list<Position> temp;	//merge this to original list at the end

	// while the move is valid,if it's not occupied by someone on the same team, add the spot
	while(valid_move(move)){
		if(grid->getB(move)->getOccupied()){	//if that Position is occupied
			if(grid->getP(move)->getteam() == getteam())	//same team
				break;
			else {
				temp.push_back(move);
				break;
			}
		}
		else {
			temp.push_back(move);
			move.setColumn(move.getColumn() + col_direction);
			move.setRow(move.getRow() + row_direction);
		}
	}
	if(!temp.empty()){
		list<Position>::iterator it = temp.begin();

		if(mimic_move(*it, ownership->getKing()))	//if this piece puts its own king in check, not allowed to move
			temp.clear();
		moves.splice(moves.end(), temp);	//add these Positions to the vector
	}
};

//now it works for any King
bool Piece::mimic_move(Position final, King *yourking){	//returns true if King is in check after move
	//King* yourking = ownership->getKing();	

//cout << "Setting preconditions\n";
//Preconditions to mimic move
	bool occupied = grid->getB(final)->getOccupied();
	grid->getB(final)->setOccupied(true);
	grid->getB(current)->setOccupied(false);
	original = grid->getP(final);
	grid->setP(current);
	grid->setP(this, final);

//cout << "Keeping original values\n";
//keeping original values
	bool original_ischecked = yourking->getChecked();	//copy incheck value
	vector<Piece*> attack_vector = yourking->getAttackVector();	//copy attack vector
	list<Position> attack_path = yourking->getAttackPath();		//copy attack path

//cout << "Calling isincheck()\n";
	yourking->isincheck();
	bool checked = yourking->getChecked();

//cout << "revert to old positions\n";
	//REVERT TO ORIGINAL POSITIONS
	grid->getB(current)->setOccupied(true);	//set original position to occupied
	grid->getB(final)->setOccupied(occupied);	//set hypothetical position to w.e it was before
	grid->setP(this, current);		//set this piece back in piece array
	grid->setP(original, final);		//set the piece that was moved if any back to original position

//cout << "Revert to king's original conditions\n";
	//REVERT TO KING'S ORIGINAL CONDITIONS
	yourking->setcheck(original_ischecked);	//reset original ischeck value
	yourking->setAttackVector(attack_vector);	//reset original set of checking pieces, if any
	yourking->setAttackPath(attack_path);	//reset original path of attacking pieces, if any

	return checked;
};
/*
int Piece::abs(int x){ // because apparently the abs() function included in <cmath> wasn't good enough
	if(x < 0)
		return (-1)*x;
	else return x;
};
*/ 
bool Piece::canreach(Position destination, int col_direction, int row_direction){ // can you reach that spot, piece?
	//assumes path is valid

	int row = current.getRow();
	char col = current.getColumn();
	Position p(col, row, false);
	row += row_direction;
	col += col_direction;
	p.setRow(row);
	p.setColumn(col);

	while(valid_move(p) && !(p == destination)){	//while the path is valid and not at destination
	//	cout << "Valid: " << p.getColumn() << p.getRow() << endl;
		if(grid->getB(p)->getOccupied())	//if one position in path is occupied, cant get there
			return false;
		row += row_direction;
		col += col_direction;
		p.setRow(row);
		p.setColumn(col);
	}
	
	//either its an ally and you cant get there or its an enemy and you take it!!!
	if(valid_move(destination) && p == destination){
		if(!grid->getB(destination)->getOccupied())	//entire path thus far is unoccupied and valid
			return true;
		else if(grid->getP(destination)->getteam() != getteam())	//enemy piece
			return true;
		else return false;	//either invalid destination OR ally piece
	}
	else return false;
}

list<Position> Piece::returnmoves() { return moves; } // where did you come from? where did you go? where did you come from, cotton eyed Joe?
													  // actually just returns the moves. But that was funny. So laugh.

//This wil check diagonals
//split this for pawns? Simple fix.
void Piece::check_diagonal(int col_direction, int row_direction){
//	cout << "Checking Diagonal" << endl;
	Position move = current;
	int team = ownership->getPlayerNumber();	//you need to know your team
	move.setColumn(move.getColumn() + col_direction);
	move.setRow(move.getRow() + row_direction);
	Piece *p;

//check pawns in this direction
	if(valid_move(move) && grid->getB(move)->getOccupied()){	//some diagonal position is occupied
			p = grid->getP(move);

			if(team == 1){
				if(p->getsymbol() == 'p'){
				//	cout << "Attacked by black pawn" << p->getcurrent().getColumn() << p->getcurrent().getRow() << endl; 
					attacking_pieces.push_back(p);
				}
			}

			else{
				if(p->getsymbol() == 'P'){
				//	cout << "Attacked by white pawn" << p->getcurrent().getColumn() << p->getcurrent().getRow() << endl; 
					attacking_pieces.push_back(p);
				}
			}
	}

//accomodate pawns better
	while(valid_move(move)){
		if(grid->getB(move)->getOccupied()){	//some diagonal position is occupied
			p = grid->getP(move);

			if(team == 1 && ((p->getsymbol() == 'q')||(p->getsymbol() == 'b'))){
				//	cout << "Attacked by black queen/bisop" << p->getcurrent().getColumn() << p->getcurrent().getRow() << endl; 
					attacking_pieces.push_back(p);
					break;
			}

			else if(team == 2 && ((p->getsymbol() == 'Q')||(p->getsymbol() == 'B'))){	//doesnt matter
				//	cout << "Attacked by white queen/bishop" << p->getcurrent().getColumn() << p->getcurrent().getRow() << endl; 
					attacking_pieces.push_back(p);
					break;
			}
			else break;		//friendly piece or piece that can't hurt the King
		}					//could be enemy pawn or king but that has been checked for.
	
		else{
			move.setColumn(move.getColumn() + col_direction);
			move.setRow(move.getRow() + row_direction);
		}
	}
};

void Piece::check_straight(int col_direction, int row_direction){
//	cout << "CHECKING STRAIGHT" << endl;
	Position move = current;
	int team = ownership->getPlayerNumber();	//you need to know your team
	move.setColumn(move.getColumn() + col_direction);
	move.setRow(move.getRow() + row_direction);

	while(valid_move(move)){	//go until end of board or we hit a piece
		//cout << "Column: " << move.getColumn() << " Row: " << move.getRow() << endl;
		if(grid->getB(move)->getOccupied()){
			Piece *p = grid->getP(move);

			if(p->getteam() == 2 && team == 1){	//if not on same team
				if(p->getsymbol() == 'q' || p->getsymbol() == 'r'){
				//	cout << "Attacked by black rook/queen" << p->getcurrent().getColumn() << p->getcurrent().getRow() << endl; 
					attacking_pieces.push_back(p);
					break;
				}
				else break;	//piece is an enemy pawn, bishop or knight
			}
			else if(p->getteam() == 1 && team == 2){
				if(p->getsymbol() == 'Q' || p->getsymbol() == 'R'){
				//	cout << "Attacked by white rook/queen" << p->getcurrent().getColumn() << p->getcurrent().getRow() << endl; 
					attacking_pieces.push_back(p);
					break;
				}
				else break;
			}
			else break;	//piece is one of ours
		}
		else{
		//	cout << "keep moving" << endl;
			move.setColumn(move.getColumn() + col_direction);
			move.setRow(move.getRow() + row_direction);
		}
	}
};

void Piece::check_knights(){
	//cout << "CHECKING KNIGHTS" << endl;
	int row = current.getRow();
	char column = current.getColumn();
	list<Position> temp;
	int team = ownership->getPlayerNumber();
	//cout << "Pushing positions\n";
	temp.push_back(Position(column-1, row+2, true));
	temp.push_back(Position(column+1, row+2, true));
	temp.push_back(Position(column-1, row-2, true));
	temp.push_back(Position(column+1, row-2, true));
	temp.push_back(Position(column+2, row+1, true));
	temp.push_back(Position(column+2, row-1, true));
	temp.push_back(Position(column-2, row+1, true));
	temp.push_back(Position(column-2, row-1, true));
	
	for(list<Position>::iterator it = temp.begin(); it != temp.end(); it++){
	//	cout << "Column: " << it->getColumn() << "Row: " << it->getRow() << endl;
	}

	//cout << "1st iteration\n";
	for(list<Position>::iterator it = temp.begin(); it != temp.end();){
		if(!valid_move(*it)){
		//	cout << "Erasing element" << endl;
			it = temp.erase(it);
			//cout << "Did it erase?\n";
		
		}
		else it++;
	//	cout << "In the loop...\n";
	};

//	cout << "CHECK_KNIGHTS 2ND ITERATION\n";
	for(list<Position>::iterator it = temp.begin(); it != temp.end(); it++){
		if(grid->getB(*it)->getOccupied()){
		//	cout <<"This only runs when occupied\n";
			if(grid->getP(*it)->getteam() != team){
				if(team == 1 && grid->getP(*it)->getsymbol() == 'n'){	//enemy of White
					//cout << "Attacked by black knight" << grid->getB(*it)->getColumn() 
					//	<< grid->getB(*it)->getRow() << endl;
					attacking_pieces.push_back(grid->getP(*it));	//only at most 1 knight can check a king
					break;
				}
				if(team == 2 && grid->getP(*it)->getsymbol() == 'N'){	//enemy of Black
				//	cout << "Attacked by white knight" << grid->getB(*it)->getColumn() 
					//	<< grid->getB(*it)->getRow() << endl;
					attacking_pieces.push_back(grid->getP(*it));
					break;
				}
			}
		}
	}
};

void Piece::check_king(){
	list<Position> temp;
	int column = current.getColumn();
	int row = current.getRow();

	temp.push_back(Position(column, row+1, false));
	temp.push_back(Position(column, row-1, false));
	temp.push_back(Position(column-1, row, false));
	temp.push_back(Position(column+1, row, false));
	temp.push_back(Position(column+1, row+1, false));
	temp.push_back(Position(column+1, row-1, false));
	temp.push_back(Position(column-1, row+1, false));
	temp.push_back(Position(column-1, row-1, false));

	for(list<Position>::iterator it = temp.begin(); it != temp.end();){
		if(!valid_move(*it))
			it = temp.erase(it);
		else it++;
	}
	for(list<Position>::iterator it = temp.begin(); it != temp.end(); it++){
		//cout << "Checking" << ownership->getPlayerNumber() << "king's surroundings\n";
		//cout << it->getColumn() << it->getRow() << endl;
		if(grid->getB(*it)->getOccupied()){
			if(grid->getP(*it)->getsymbol() == 'k' || grid->getP(*it)->getsymbol() == 'K'){
					//cout << "Attacked by king" << grid->getB(*it)->getColumn() 
					//	<< grid->getB(*it)->getRow() << endl;
				if(grid->getP(*it)->getteam() != this->getteam())
					attacking_pieces.push_back(grid->getP(*it));	//only at most 1 enemy king
					break;
			}
		}
	}
};

//returns true if this Position allows avoid capture
bool Piece::avoid_capture(){
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

	if(attacking_pieces.empty())
		return true;
	return false;
};