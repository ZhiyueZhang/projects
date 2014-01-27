#ifndef ROOK_H
#define ROOK_H
#include "piece.h"

class Board;


class Rook: public Piece{
	void intercept();		//gets valid positions when the King is in check
	bool has_moved;
public:
	Rook(char, Position, Board*, Player*, bool has_moved=false); // constructor
	void getmoves(); // get moves
	void set_moved(bool);
	bool get_moved();
};

#endif