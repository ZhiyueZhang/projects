#ifndef KING_H
#define KING_H
#include "piece.h"

class Board;


class King: public Piece{
	bool incheck, has_moved;	//reset this after every turn
	std::list<Position> attack_path;	//set of positions that would block attacking piece
	void set_attack_path();				//sets attack_path
	void castle();
public:
	King(char, Position, Board*, Player*, bool incheck=false, bool has_moved=false);
	void attack(Piece*);	//sets attacking_pieces vector
	void getmoves(); // gets list of possible moves
	void isincheck();	//if King is checked, sets incheck var and attack vector
	void setcheck(bool);	//set incheck to given parameter
	bool getChecked();	//get the incheck variable
	void resetattack();	//call this at the end of your turn, no longer needed
	std::vector<Piece*> getAttackVector();	//this and the one below are reset methods...
	void setAttackVector(std::vector<Piece*>);
	std::list<Position> getAttackPath();	//retrieve list of all positions that would block attacking piece
	void setAttackPath(std::list<Position>);
	void set_moved(bool);
	bool get_moved();

};					

#endif