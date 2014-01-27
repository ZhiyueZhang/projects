#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"

class Board;

class Queen: public Piece{
private:
	void intercept();		//gets valid positions when the King is in check
public:
	Queen(char, Position, Board*, Player*); // constructor
	void getmoves(); // gets all possible moves
};

#endif