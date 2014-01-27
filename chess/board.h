#ifndef BOARD_H
#define BOARD_H
#include "player.h"
#include <list>
//#include "window.h"

class Piece;


class Board {
	Player *p1, *p2;			//Add these in?
	Position* board[8][8];	//Quick access to Position on board BUT we can convert it ourselves	
	Piece* pieces[8][8];
	int howmany [2][6];
	std::vector<Position> checkplaces; // list of positions where the current player's king would be in  check
	//void textprint();		//combine both print functions?
	//void graphicsprint();	//no need to call each individual piece to draw itself
	//Xwindow* window;
public:
	void textprint(); // TEMPORARY. will be moved to private after the << operator is overloaded
	Board(); // constructor
	~Board(); // destructor
	bool searchPosVector(std::list<Position>, Position);// checks if a given position is an element of given list of positions
	bool searchPosVector(std::vector<Position>, Position); // checks if a given position is an element of given vector of positions
	//int getHM(int, int); // returns how many of a given piece there are, with array coords for debugging
	int getHM(char); // returns how many of a given piece there are
	Position* getB(Position); // returns a pointer to the Position in the given spot in the board
	Position* getB(char, int); //returns a pointer to Position corresponding to row and column
	Piece* getP(Position); // returns a pointer to the piece given the spot in the pieces vector
	Piece* getP(char, int); // returns a pointer to the piece in the given spot defined by column and row
	void setP(Piece*, Position); // sets spot in pieces vector to this piece
	void setP(Position, bool n=false); // NULLs the given spot in the pieces vector
	void clear(); // clears board entirely
	void deleteP(Position); // deletes a piece entirely
	Player* getP1(); //Return Player* to player #1 (white)
	Player* getP2(); //Return Player* to player #2 (black)
	void addPiece(char, int, Position); // adds a piece to the given position
	void addPlayer(bool, int, int); // adds a player
	void moveP(Position, Position); // moves a piece from one spot to another
	void level_one_move(Player*); // move for level one computer
	void level_two_move(Player*); // move for level two computer
	void level_three_move(Player*); // move for level three computer
	bool check_stalemate(); // checks for stalemate
	bool evasive_move(Piece*); // computer make an evasive move
	void pawn_promote(Position); // computer pawn promotion
};

#endif