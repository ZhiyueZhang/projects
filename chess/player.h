#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <vector>
#include "position.h"

class Piece;
class King;

class Player {
	bool human;
	int difficulty, playernumber;
	std::vector<Piece*> pieces;
	King *yourking;		//Every piece must know where its King is
public:
	Player(bool human=true, int difficulty=0, int playernumber=1); // constructor
	bool ishuman() const;			//return human
	int getDifficulty() const; // difficulty getter
	int getPlayerNumber() const; // player # getter
	std::vector<int> getinfo();		//Possibly unnecessary
	std::vector<Piece*> getpieces(); // pieces getter
	void addPiece(Piece*); // adds a piece for the player
	void removePiece(Position); // removes a player's piece
	King *getKing(); // king getter
	void setKing(King*); // king setter
	void setHuman(bool); // ishuman setter
	void setDifficulty(int); // difficulty setter
	void getAllMoves();	//calls getmoves() for every piece
	void clearAllMoves(); // clears all of a player's pieces' moves
};									
#endif