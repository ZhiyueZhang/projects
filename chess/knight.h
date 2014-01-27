#ifndef KNIGHT_H
#define KNIGHT_H
#include "piece.h"

class Board;

class Knight: public Piece{
public:
	Knight(char, Position, Board*, Player*); // constructor
	void getmoves(); // gets list of possible moves
};

#endif