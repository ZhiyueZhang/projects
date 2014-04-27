#include "board.h"
#include "piece.h"
#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "knight.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <stdlib.h>

using namespace std;

Board::Board() // Board constructor, remember that you initialize XWindow here!
{
    int r;
    char c;

    // loop which initializes the board array
    for (int i = 0; i <= 7; i++) {
        r = 8 - i;

    	for (int j = 0; j <= 7; j++) {
           c = j + 97;

            // add new position
            board[i][j] = new Position(r, c);
    	}
    }

    // loop to initialize pieces array
    for (int i = 0; i <= 7; i++) {
    	for (int j = 0; j <= 7; j++) {
    		pieces[i][j] = NULL;
    	}
    }

    // loop to initialize the howmany array to 0
    for (int i = 0; i <= 1; i++) {
    	for (int j = 0; j <= 5; j++) {
    		howmany[i][j] = 0;
    	}
    }

 //   window = new Xwindow();
}

Board::~Board() // Board destructor
{
    for (int i = 0; i <= 7; i++) {
    	for (int j = 0; j <= 7; j++) {
    		delete board[i][j];
            board[i][j] = NULL;
    	}
    }

    for (int i = 0; i <= 7; i++) {
    	for (int j = 0; j <= 7; j++) {
            delete pieces[i][j];
            pieces[i][j] = NULL;
    	}
    }

    // delete the players
    delete p1;
    delete p2;

    //delete window;
}

/*
// Prints graphics using Xwindow
void Board::graphicsprint() {

//Makes the Board
    for (int y = 7; y >= 0; y--){
        for(int x = 0; x < 8; x++){
            if((x+y)%2==1)
                window->fillRectangle(x*50+50, y*50, 50, 50, 0);
            else window->fillRectangle(x*50+50, y*50, 50, 50);
        }
    }

//print column numbers
    char ch = 'a';
    stringstream ss;

    for(int i = 0; i < 8; i++){
        ss.str("");
        ss << ch;
        window->drawString(50*i+70, 420, ss.str());
        ch++;
    }

//print row numbers
    for(int i = 1; i <= 8; i++){
        int row = 8 - i;
        ss.str("");
        ss << i;
        window->drawString(20, row*50+20, ss.str());
    }

//White Player
    vector<Piece*> temp = p1->getpieces();

    for(vector<Piece*>::iterator it = temp.begin(); it != temp.end(); it++){
        Position current = (*it)->getcurrent();
        int row = current.getRow();
        char col = current.getColumn();
        char symbol = (*it)->getsymbol();
        ss.str("");
        ss << symbol;
        if((row+col)%2==1)  //col + row is odd, square is black
            window->drawString((col-97)*50+70, (8-row)*50+20, ss.str(), Xwindow::Cyan);
        else window->drawString((col-97)*50+70, (8-row)*50+20, ss.str(), Xwindow::Blue);
    }

//Black Player
    temp = p2->getpieces();

    for(vector<Piece*>::iterator it = temp.begin(); it != temp.end(); it++){
        Position current = (*it)->getcurrent();
        int row = current.getRow();
        char col = current.getColumn();
        char symbol = (*it)->getsymbol();
        ss.str("");
        ss << symbol;
        window->drawString((col-97)*50+70, (8-row)*50+20, ss.str(), Xwindow::Red);
    }
}
*/

// prints the board in text to the console
void Board::textprint() {
    
    cout << endl;

    int r;
    char c;

    // boolean for end of line stuff
    bool eol;

    // loop that does the printing
	for (int i = 0; i <= 7; i++) {
       r = 8 - i;

        // give us the row number and a separator
        cout << r << "||";

        // print the contents of each row
        for (int j = 0; j <= 7; j++) {
			c = 97 + j;
            
			if(j == 0)
				eol = false;
			
			if(j == 7)
				eol = true;

            cout << " ";

            // check if there's a piece in the spot, print the symbol if there is
            if (pieces[i][j] != NULL) {
                cout << pieces[i][j]->getsymbol();
            }

            // if not just another space
            else {
                cout << " ";
            }

            // another space and a pipe to make it look like a board
            cout << " |";

            // newline if it's time for a new row
            if (eol) {
                cout << endl;
            }
        }
    }

    // bottom of the board
    cout << "-----------------------------------" << endl;
    cout << " || a | b | c | d | e | f | g | h |" << endl << endl;

}

// Gets how many of a certain price remains on the board
//int Board::getHM(int bw, int p) {
	//return howmany[bw][p];
//}

// Gets how many of a certain piece remains given a character
int Board::getHM(char c) {

    // simple switch for the character
    switch (c) {
        case 'p':
            return howmany[1][0];
        case 'r':
            return howmany[1][1];
        case 'n':
            return howmany[1][2];
        case 'b':
            return howmany[1][3];
        case 'q':
            return howmany[1][4];
        case 'k':
            return howmany[1][5];
        case 'P':
            return howmany[0][0];
        case 'R':
            return howmany[0][1];
        case 'N':
            return howmany[0][2];
        case 'B':
            return howmany[0][3];
        case 'K':
            return howmany[0][5];
        default:
            return howmany[0][4];
    }
}

// returns a pointer to the position in the board array with same coords as the given position
Position* Board::getB(Position p) {	
	return board[8- p.getRow()][p.getColumn()- 97]; 
}

// same as above function but has given lookup numbers
Position* Board::getB(char col, int row) { 
	return board[8-row][col - 97]; 
}

// gets a pointer to the piece at position with same coords as given position
Piece* Board::getP(Position p) { 
	return pieces[8 - p.getRow()][p.getColumn() - 97]; 
}

// same as above but with lookup numbers
Piece* Board::getP(char col, int row) { 
	return pieces[8-row][col-97]; 
}

// deletes a piece
void Board::deleteP(Position p) {

	int r = 8 - p.getRow();
	int c = p.getColumn() - 97;

	char sym = pieces[r][c]->getsymbol();

    int hmindex, pno;

    switch(tolower(sym)) {	// get the second value for the howmany array
        case 'p':
            hmindex = 0;
            break;
        case 'r':
            hmindex = 1;
            break;
        case 'n':
            hmindex = 2;
            break;
        case 'b':
            hmindex = 3;
            break;
        case 'q':
            hmindex = 4;
            break;
        case 'k':
            hmindex = 5;
            break;
    }

    // gets first value for howmany array
    if (islower(sym)) 
        pno = 1;

    else pno = 0;

    // decrements the howmany array
    howmany[pno][hmindex]--;

    board[r][c]->setOccupied(false);	//sets original position to unoccupied in board array

    // removes the piece
    if (pno == 0) 
		p1->removePiece(p);

    else if (pno == 1)
		p2->removePiece(p);
    
    pieces[r][c] = NULL;		//sets position to null in piece array

	if(sym == 'k')
		p2->setKing(0);
	if(sym == 'K')
		p1->setKing(0);
}

// clears the board of all pieces
void Board::clear() {

    // NULLs the pieces array
    for (int i = 0; i <= 7; i++) {
        for (int j = 0; j <= 7; j++) {
            board[i][j]->setOccupied(false);
            delete pieces[i][j];
            pieces[i][j] = NULL;
        }
    }

    // resets howmany to 0s
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 5; j++) {
            howmany[i][j] = 0;
        }
    }

    // clears moves in player class
	p1->clearAllMoves();
	p2->clearAllMoves();

	p1->setKing(0);
	p2->setKing(0);

    // calls graphicsprint to update the graphical display (no text update needed)
    // graphicsprint();
}

//sets Position p in pieces array to NULL
void Board::setP(Position p, bool n) {
    int r = 8 - p.getRow();
	int c = p.getColumn() - 97;

    if (n)
        board[r][c]->setOccupied(false);
    
    pieces[r][c] = NULL;
}

void Board::setP(Piece* piece, Position p) { 
	pieces[8 - p.getRow()][p.getColumn() - 97] = piece; 
}


void Board::moveP(Position initial, Position final) {
    Piece* p = getP(initial);	//grabs piece from initial position f, which should be queen

	if(getB(final)->getOccupied())	//if enemy piece is there
		deleteP(final);				//remove piece

	else if(p->getsymbol() == 'P'){
		Position p2 = Position(final.getRow()-1, final.getColumn());

		if(getB(p2)->getOccupied() && getP(p2)->getsymbol() == 'p')	//en passant
			deleteP(p2);
	}

	else if(p->getsymbol() == 'p'){
		Position p1 = Position(final.getRow()+1, final.getColumn());

		if(getB(p1)->getOccupied() && getP(p1)->getsymbol() == 'P')	//en passant
			deleteP(p1);
	}


    setP(initial, true);	//nulls Position f in Piece array, sets it to unoccupied in board array
    setP(p, final);			//sets that piece to final position t
	p->setcurrent(final);	//sets current position of Piece p to Position t
	getB(final)->setOccupied(true);	//set new position to occupied!!!

	if(tolower(p->getsymbol()) == 'p'){
		dynamic_cast<Pawn*>(p)->set_moved();	//if pawn, it has moved
		
		if(abs(initial.getRow() - final.getRow()) == 2){	//pawn moved 2
			Position left = Position(final.getRow(), final.getColumn() - 1);
			Position right = Position(final.getRow(), final.getColumn() + 1);
			Piece *l =0, *r = 0;
			if(final.getColumn() - 1 >= 'a' && getP(left)) l = getP(left);
			if(final.getColumn() + 1 <= 'h' && getP(right)) r = getP(right);

			if(l && tolower(l->getsymbol()) == 'p' && l->getteam() != p->getteam())
				dynamic_cast<Pawn*>(l)->enpassant(final);
			
			if(r && tolower(r->getsymbol()) == 'p' && r->getteam() != p->getteam())
				dynamic_cast<Pawn*>(r)->enpassant(final);
		}
	}

	pawn_promote(final);

	if(tolower(p->getsymbol()) == 'r')
		dynamic_cast<Rook*>(p)->set_moved(true);

	if(tolower(p->getsymbol()) == 'k'){
		dynamic_cast<King*>(p)->set_moved(true);

		if(final.getColumn() - initial.getColumn() == 2){	//moved 2 right
			for(char ch = final.getColumn()+1; ch <= 'h'; ch++){
				if(getB(ch, final.getRow())->getOccupied()){

					p = getP(ch, final.getRow());
					Position rook_final = Position(final.getRow(), final.getColumn()-1);
					setP(p, rook_final);	//point to new location
					setP(Position(final.getRow(), ch), true);	//set original to null
					getB(rook_final)->setOccupied(true);	//set new occupancy to true
					p->setcurrent(rook_final);
					break;
				}
			}
		}
		if(initial.getColumn() - final.getColumn() == 2){
			for(char ch = final.getColumn()-1; ch >= 'a'; ch--){	//moved 2 left
				if(getB(ch, final.getRow())->getOccupied()){

					p = getP(ch, final.getRow());
					Position rook_final = Position(final.getRow(), final.getColumn()+1);
					setP(p, rook_final);	//point to new location
					setP(Position(final.getRow(), ch), true);	//set original to null
					getB(rook_final)->setOccupied(true);	//set new occupancy to true
					p->setcurrent(rook_final);
					break;
				}
			}
		}
	}
}


// Gets the pointer for player 1
Player* Board::getP1() {
    return p1;
}

// Gets the pointer for player 2
Player* Board::getP2() {
    return p2;
}

// adds piece to location
void Board::addPiece(char ch, int pno, Position p) {
	int r = 8 - p.getRow();
	int c = p.getColumn() - 97;

    int hmindex;

    // gets second index for howmany
    switch(tolower(ch)) {
        case 'p':
            hmindex = 0;
            break;
        case 'r':
            hmindex = 1;
            break;
        case 'n':
            hmindex = 2;
            break;
        case 'b':
            hmindex = 3;
            break;
        case 'q':
            hmindex = 4;
            break;
        case 'k':
            hmindex = 5;
            break;
    }

    // does work for if player is white
    if (pno == 1) {
        switch(tolower(ch)) {
            case 'p':
                pieces[r][c] = new Pawn(toupper(ch), p, this, p1);
                break;
            case 'r':
                pieces[r][c] = new Rook(toupper(ch), p, this, p1);
                break;
            case 'n':
                pieces[r][c] = new Knight(toupper(ch), p, this, p1);
                break;
            case 'b':
                pieces[r][c] = new Bishop(toupper(ch), p, this, p1);
                break;
            case 'q':
                pieces[r][c] = new Queen(toupper(ch), p, this, p1);
                break;
            case 'k':
                pieces[r][c] = new King(toupper(ch), p, this, p1);
                break;
        }

        // adds piece
		p1->addPiece(pieces[r][c]);
    }

    // if player is black
    else if (pno == 2) {
        switch(tolower(ch)) {
            case 'p':
                pieces[r][c] = new Pawn(tolower(ch), p, this, p2);
                break;
            case 'r':
                pieces[r][c] = new Rook(tolower(ch), p, this, p2);
                break;
            case 'n':
                pieces[r][c] = new Knight(tolower(ch), p, this,p2);
                break;
            case 'b':
                pieces[r][c] = new Bishop(tolower(ch), p, this, p2);
                break;
            case 'q':
                pieces[r][c] = new Queen(tolower(ch), p, this, p2);
                break;
            case 'k':
                pieces[r][c] = new King(tolower(ch), p, this, p2);
                break;
        }

        // adds the piece
		p2->addPiece(pieces[r][c]);
    }

    // increments howmany
    howmany[pno-1][hmindex]++;

    // sets board spot to occupied
    board[r][c]->setOccupied(true);
}

//Performs a random move
void Board::level_one_move(Player *p){
    vector<Piece*> copy_pieces = p->getpieces();
                                
    //Remove pieces with no moves
    for(vector<Piece*>::iterator it = copy_pieces.begin(); it != copy_pieces.end();){
        if((*it)->returnmoves().empty())
            it = copy_pieces.erase(it);
        else it++;
        }

		srand((unsigned)time(NULL));
        int which_piece = rand() % copy_pieces.size();
        Piece *picked = copy_pieces[which_piece];

        Position from = picked->getcurrent();
        list<Position> picked_moves = picked->returnmoves();
        int which_move = rand() % picked_moves.size();  //from 0 to size-1
        list<Position>::iterator it;
        int index = 0;

        for(it = picked_moves.begin(); index != which_move; it++, index++);

        this->moveP(from, *it);
};

//prefers checks over capture
void Board::level_two_move(Player *p){
        vector<Piece*> copy_pieces = p->getpieces();    //pieces of every single player
        bool make_move = false;     //assumes you cant make a level two move
        vector<Piece*>::iterator it;	
        list<Position>::iterator it_list;
        Piece *parse;
        list<Position> parse_moves;
        Position from, to;

        for(it = copy_pieces.begin(); it != copy_pieces.end(); it++){   //parse each piece
            parse = *it;
            parse_moves = parse->returnmoves();

            //cout << "Checking for pieces to capture\n";
            for(it_list = parse_moves.begin(); it_list != parse_moves.end(); it_list++){    //parse each move of each piece
                if(this->getB(*it_list)->getOccupied()){
                    if(this->getP(*it_list)->getteam() != parse->getteam()){    //enemy piece
                        make_move = true;
                        from = parse->getcurrent();
                        to = *it_list;
                    }
                }
            }
        }

        for(it = copy_pieces.begin(); it != copy_pieces.end(); it++){   //parse each piece
            parse = *it;
            parse_moves = parse->returnmoves();
            //cout << "Checking for King check\n";
            for(it_list = parse_moves.begin(); it_list != parse_moves.end(); it_list++){    //parse each move of each piece
                if(p->getPlayerNumber() == 1){  //player 1 will attempt to capture player 2's king
                    if(parse->mimic_move(*it_list, p2->getKing())){ //check if moving piece to *it_list puts p2's king in check
                        make_move = true;
                        from = parse->getcurrent();
                        to = *it_list;
                    }
                }
                else{   //player 2 will attempt to capture player 1's king
                    if(parse->mimic_move(*it_list, p1->getKing())){
                        make_move = true;
                        from = parse->getcurrent();
                        to = *it_list;
                    }
                }
            }
        }
        //cout << "Attempting to make move\n";
        if(make_move)
            this->moveP(from, to);

        else this->level_one_move(p);
}

//Fixed level 3!
void Board::level_three_move(Player* p){
    bool Q_danger = false;  //9
    bool R_danger = false;  //5
    bool B_danger = false;  //4
    bool N_danger = false;  //3
    bool P_danger = false;  //1
    Piece *queen, *rook, *bishop, *knight, *pawn;
    vector<Piece*> copy_pieces = p->getpieces();    //pieces of player p
    vector<Piece*> enemy_pieces;
    Position from, to;      //this will make the move if any piece is in danger

    if(p->getPlayerNumber() == 1)
        enemy_pieces = p2->getpieces();
    else enemy_pieces = p1->getpieces();

//Parsing every move of each enemy piece to see if any of them
//can get to one of this player's pieces
    for(vector<Piece*>::iterator it = enemy_pieces.begin(); it != enemy_pieces.end(); it++){
        list<Position> moves = (*it)->returnmoves();

        for(list<Position>::iterator it_moves = moves.begin(); it_moves != moves.end(); it_moves++){
            if(this->getB(*it_moves)->getOccupied()){   //must be your own if true
                if(this->getP(*it_moves)->getsymbol() == 'q' || this->getP(*it_moves)->getsymbol() == 'Q'){
                    Q_danger = true;
                    queen = this->getP(*it_moves);
                }
                if(this->getP(*it_moves)->getsymbol() == 'r' || this->getP(*it_moves)->getsymbol() == 'R'){
                    R_danger = true;
                    rook = this->getP(*it_moves);
                }
                if(this->getP(*it_moves)->getsymbol() == 'b' || this->getP(*it_moves)->getsymbol() == 'B'){
                    B_danger = true;
                    bishop = this->getP(*it_moves);
                }
                if(this->getP(*it_moves)->getsymbol() == 'n' || this->getP(*it_moves)->getsymbol() == 'N'){
                    N_danger = true;
                    knight = this->getP(*it_moves);
                }
                if(this->getP(*it_moves)->getsymbol() == 'p' || this->getP(*it_moves)->getsymbol() == 'P'){
                    P_danger = true;
                    pawn = this->getP(*it_moves);
                }
            }
        }
    }

    if(Q_danger && this->evasive_move(queen)){}
	else if(R_danger && this->evasive_move(rook)){}
    else if(B_danger && this->evasive_move(bishop)){}
    else if(N_danger && this->evasive_move(knight)){}
    else if(P_danger && this->evasive_move(pawn)){}
    else this->level_two_move(p);
}



void Board::addPlayer(bool human, int diff, int pno) {
    if (pno == 1) {
        p1 = new Player(human, diff, pno);
    }
    if (pno == 2) {
        p2 = new Player(human, diff, pno);
    }
}

bool Board::check_stalemate(){  //2 kings can also cause stalemate
    bool no_moves_p1 = false;
    bool no_moves_p2 = false; 
    vector<Piece*> copy1 = p1->getpieces();
    vector<Piece*> copy2 = p2->getpieces();

    if(copy1.size() == 1 && copy2.size() == 1)  //only 2 kings
        return true;

    if(!p1->getKing()->getChecked() && !p2->getKing()->getChecked()){   //neither player can be in check for stalemate
        for(vector<Piece*>::iterator it = copy1.begin(); it != copy1.end(); it++){
            if((*it)->returnmoves().size() != 0){   //one of p1's piece has at least one move
                no_moves_p1 = true;
                break;
            }
        }
        for(vector<Piece*>::iterator it = copy2.begin(); it != copy2.end(); it++){
            if((*it)->returnmoves().size() != 0){   //one of p2's piece has at least one move
                no_moves_p2 = true;
                break;
            }
        }
        return (!no_moves_p1 || !no_moves_p2);
    }
    else return false;
};

bool Board::evasive_move(Piece *moving_piece){
        Position destination;
        list<Position> moves = moving_piece->returnmoves();	//this is YOUR piece
        bool danger = true;

//this parses through every single move of your piece
        for(list<Position>::iterator it = moves.begin(); it != moves.end(); it++){
			Position temp = moving_piece->getcurrent();	//keep original position
			Piece *original_piece = this->getP(*it);	//keep original piece
			moving_piece->setcurrent(*it);	//temporarily change current position
			this->getB(temp)->setOccupied(false);	//temporarily unoccupy old position
			this->getB(*it)->setOccupied(true);	//temporarily occupy new position
			this->setP(moving_piece, *it);	//new position
			this->setP(temp);	//old position is unfilled

			if(moving_piece->avoid_capture()){
                danger = false;
                destination = *it;
            }

//reset to original conditions
			moving_piece->setcurrent(temp);	//reset current position to original
			this->getB(*it)->setOccupied(false);	//reset new position to unoccupied
			this->getB(temp)->setOccupied(true);	//reset old position to occupied
			this->setP(moving_piece, temp);	//reset to old Piece
			this->setP(original_piece, *it);	//reset to original piece

			if(!danger)
				break;
        }

        if(!danger){
			this->moveP(moving_piece->getcurrent(), destination);
            return true;
        }
        else return false;
}

void Board::pawn_promote(Position it){
	//cout << "Issue with pawn promotion\n";
	char promoted[4] = {'q', 'r', 'b', 'n'};
	srand((unsigned int)time(NULL));
	char rand_piece = promoted[rand()%4];

        if(this->getP(it)->getsymbol() == 'p'){
            if(it.getRow() == 1){
                this->deleteP(it);
                this->addPiece(rand_piece, 2, it);
            }
        }
        if(this->getP(it)->getsymbol() == 'P'){
            if(it.getRow() == 8){
                this->deleteP(it);
                this->addPiece(toupper(rand_piece), 1, it);
            }
        }
}

// checks if given position is an element of given vector of positions
bool Board::searchPosVector(vector<Position> v, Position p) {
	for(vector<Position>::iterator it = v.begin(); it != v.end(); it++){
		if(*it == p)
			return true;
	}
	return false;
}

// same as above but with a list instead of a vector
bool Board::searchPosVector(list<Position> v, Position p) {
	for(list<Position>::iterator it = v.begin(); it != v.end(); it++){
		if(*it == p)
			return true;
	}
    return false;
}