#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"

class Board;

class Bishop: public Piece{
private:
	void intercept();		//gets valid positions to try to intercept or capture piece checking king
public:
	Bishop(char, Position, Board*, Player*); // constructor
	void getmoves(); // gets moves, uses intercept()
};

#endif