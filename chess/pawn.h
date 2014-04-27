#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
class Board;

//Double Moves, move forward, en passant, 
class Pawn: public Piece{
	bool has_moved;		//needed for initial 2-step
	std::vector<Position> passant;	//Positions to add due to en passant
public:
	Pawn(char, Position, Board*, Player*, bool has_moved=false);
	void getmoves();
	void set_moved();	//changes has_moved to true if Pawn has moved
	void enpassant(Position); 
};

#endif

//pawn promotion( handle by board, check for first and last rows)
//board must also check if a pawn is moved, since then pawn can no longer perform double step