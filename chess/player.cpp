#include "player.h"
#include "piece.h"
#include "king.h"
//#include <iostream>
using namespace std;

Player::Player(bool human, int difficulty, int playernumber)
: human(human), difficulty(difficulty), playernumber(playernumber), yourking(NULL) {}; // constructor with all its defaults

//Return human variable
bool Player::ishuman()const{ return human; }; // getter for human

//Return difficulty variable
int Player::getDifficulty()const{ return difficulty; }; // getter for difficulty

//Return playernumber variable
int Player::getPlayerNumber() const{ return playernumber; }; // getter for player number

//This function will return all the info we need:
vector<int> Player::getinfo(){
	vector<int> info(3);

	info[0] = human;
	info[1] = difficulty;
	info[2] = playernumber;

	return info;
};

//Return pieces vector... this is return by value!
vector<Piece*> Player::getpieces(){ 
//	cout << "In Player::getpieces() fn\n";
//	for(vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++)
//		cout << (*it)->getsymbol() << endl;
	return pieces; };

//Add new piece to pieces vector
void Player::addPiece(Piece* p){ pieces.push_back(p); };

//Remove Piece with Position pos from pieces vector
//Deletes the piece
void Player::removePiece(Position pos){
	for(vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++){
		if((*it)->getcurrent() == pos){
			delete (*it);
			pieces.erase(it);			//make sure this deletes the Piece, not just removing
			break;						//it from the vector
		}
	}
};

King* Player::getKing() { return yourking; }; // getter for player king

void Player::setKing(King *k){ yourking = k;}; // setter for player king

void Player::setHuman(bool b) { human = b; } // setter for human

void Player::setDifficulty(int a) { difficulty = a; } // setter for difficulty

void Player::getAllMoves(){ // gets moves for all of a player's pieces
	for(vector<Piece*>::iterator it = pieces.begin(); it != pieces.end(); it++)
		(*it)->getmoves();
};

void Player::clearAllMoves(){ // clears all of a player's pieces' moves
	pieces.clear();
};