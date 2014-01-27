#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <string>
#include <list>
#include "position.h"

class Player;
class Board;
class King;


class Piece{
    char symbol;
protected:
	Player* ownership;
	std::list<Position> moves;
    Position current;	//you will always keep this as your current
	Piece* original;		//this is the original Piece in the Piece array
    Board* grid; // gotta keep track of that grid
	void addpositions(int, int);	//Add Positions along a direction
	bool canreach(Position, int, int);
	std::vector<Piece*> attacking_pieces; //this must be reset after every turn, does that
	void check_diagonal(int, int);	//checks for enemy pieces in given direction
	void check_straight(int, int); // checks for enemies in straight directinos
	void check_knights();	//checks for enemy knights
	void check_king();		//check for king in surrounding area *this is to make it impossible for king to come in contact with another king
public:
	bool mimic_move(Position, King*); // mimics a move with a king as an argument
    Piece(char, Position, Board*, Player*, bool has_moved=false);	// constructor
    char getsymbol(); // getter for symbol
    Position getcurrent(); // getter for current location
    Player* getowner(); // getter for owner (daddy, if you've read the comments in piece.cc)
    virtual void getmoves()=0;	//set vector<Position> moves
	int getteam(); // getter for team (there's no "i" in team)
	bool valid_move(const Position&); // is that a valid move?
	//int abs(int); // because the one in <cstdlib> and <cmath> were just not good enough
	std::list<Position> returnmoves(); // returns the moves vector
	void setcurrent(Position); // setter for current
	bool avoid_capture(); // avoids capture for a computer
};

#endif // PIECE_H