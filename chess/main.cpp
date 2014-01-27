#include <iostream>
#include <cstdlib>
#include "piece.h"
#include "board.h"
#include "king.h"

using namespace std;

/* No graphics display!
Affected: Board constructor, destructor, Board::clear, no Window class, no graphicsprint
*/ 

int main() {

    // make the board
    Board b = Board();

    // initialize the scores
    double p1score = 0;
    double p2score = 0;

    // create the two players
    b.addPlayer(true, 0 ,1);
    b.addPlayer(true, 0, 2);

    // get them in variables
    Player* p1 = b.getP1();
    Player* p2 = b.getP2();

    // are we in initialization mode?
    bool init = false;
    int currentturn;	

    // anybody goofed yet?
	bool made_mistake = false;
    
    // this is where the input goes.
    string input;

    // Introduction
    cout << "Welcome to Chess by Simon and Jack!" << endl << endl;
    cout << "Here's a sample board:" << endl << endl;
    cout << "8|| r | n | b | q | k | b | n | r |" << endl;
    cout << "7|| p | p | p | p | p | p | p | p |" << endl;
    cout << "6||   |   |   |   |   |   |   |   |" << endl;
    cout << "5||   |   |   |   |   |   |   |   |" << endl;
    cout << "4||   |   |   |   |   |   |   |   |" << endl;
    cout << "3||   |   |   |   |   |   |   |   |" << endl;
    cout << "2|| P | P | P | P | P | P | P | P |" << endl;
    cout << "1|| R | N | B | Q | K | B | N | R |" << endl;
    cout << "-----------------------------------" << endl;
    cout << " || a | b | c | d | e | f | g | h |" << endl << endl;
    cout << "Uppercase letters (R, N, B, P, etc.) are white pieces and lowercase letters (r, n, b, p, etc.) are lowercase pieces.";
    cout << endl << endl << "Enter \"setup\" to enter setup mode and get a game going." << endl << endl;
	cout << "Enter \"help\" for instructions on how to play" << endl << endl;

    // INPUT LOOP #1
	while (true) {
        getline(cin, input);

        if (input == "quit") {
            return 0;
        }

		else if(input == "help"){
			cout << "\n\nEvery game must be setup first by entering \"setup\" in the main menu\n \n"
				  "After game setup, start a game with the game command" 
				  "\n\nfollowed by the type of players human computer[1] computer[2] computer[3]\n \n"
				  "For example: 'game human computer[2]' starts a game where the White player"
				  "\n\nis human and the Black player is a Computer of level 2 difficulty\n \n"
				  "After every game each player's score counter is updated \n \n"
				  "To quit this program type in \"quit\"\n\n";
		}


        else if (input == "setup") {
            cout << endl << "Enter \"standard\" to automatically have a standard chess board like the one above set up for you." << endl << endl;
            cout << "Enter \"help\" to get command help." << endl << endl;

			currentturn = 1;	//by default White's turn.
			b.clear();	//start with a new board

            // INPUT LOOP #2
            while (true) {
                getline(cin, input);

                if (input == "help") {
                    cout << endl << "Command syntax is as follows:" << endl << endl;
                    cout << "{+, -, =, \"done\"} {(r, n, b, q, k, p, R, N, B, Q, K, P) | (\"black\", \"white\")} {unoccupied, valid space}" << endl << endl;
                    cout << "+ adds the specified piece to the specified place" << endl;
                    cout << "- removes the piece in the speicified location" << endl;
                    cout << "= set s the starting player. The default is white.";
                    cout << "done exits setup mode" << endl;
                    cout << "standard sets up the board like a standard chess board" << endl << endl;
                    cout << "Examples:" << endl << endl;
                    cout << "+ K e1 adds a white King to space e1." << endl;
                    cout << "- a8 removes the piece in a8. If there is no piece in a8 this command does nothing." << endl;
                    cout << "= black makes it black\'s turn first." << endl << endl;
                    cout << "Note that if \"standard\" is entered at any point during setup, it will earse the board and set it to the standard." << endl << endl;
                    cout << "You cannot leave setup mode unless you meet these conditions:" << endl << endl;
                    cout << "   1. There is exactly one black King and one white King" << endl;
                    cout << "   2. No pawns are in rows 1 or 8" << endl;
                    cout << "   3. No Kings can be in check or checkmate" << endl << endl;
                }

                else if (input == "standard") {
                    // clear the board first
                    b.clear();

                    // these are the starting locations
                    Position a1 = Position(1, 'a');
                    Position b1 = Position(1, 'b');
                    Position c1 = Position(1, 'c');
                    Position d1 = Position(1, 'd');
                    Position e1 = Position(1, 'e');
                    Position f1 = Position(1, 'f');
                    Position g1 = Position(1, 'g');
                    Position h1 = Position(1, 'h');
                    Position a2 = Position(2, 'a');
                    Position b2 = Position(2, 'b');
                    Position c2 = Position(2, 'c');
                    Position d2 = Position(2, 'd');
                    Position e2 = Position(2, 'e');
                    Position f2 = Position(2, 'f');
                    Position g2 = Position(2, 'g');
                    Position h2 = Position(2, 'h');
                    Position a8 = Position(8, 'a');
                    Position b8 = Position(8, 'b');
                    Position c8 = Position(8, 'c');
                    Position d8 = Position(8, 'd');
                    Position e8 = Position(8, 'e');
                    Position f8 = Position(8, 'f');
                    Position g8 = Position(8, 'g');
                    Position h8 = Position(8, 'h');
                    Position a7 = Position(7, 'a');
                    Position b7 = Position(7, 'b');
                    Position c7 = Position(7, 'c');
                    Position d7 = Position(7, 'd');
                    Position e7 = Position(7, 'e');
                    Position f7 = Position(7, 'f');
                    Position g7 = Position(7, 'g');
                    Position h7 = Position(7, 'h');

                    // now add the pieces
                    b.addPiece('r', 1, a1);
                    b.addPiece('n', 1, b1);
                    b.addPiece('b', 1, c1);
                    b.addPiece('q', 1, d1);
                    b.addPiece('k', 1, e1);
                    b.addPiece('b', 1, f1);
                    b.addPiece('n', 1, g1);
                    b.addPiece('r', 1, h1);
                    b.addPiece('p', 1, a2);
                    b.addPiece('p', 1, b2);
                    b.addPiece('p', 1, c2);
                    b.addPiece('p', 1, d2);
                    b.addPiece('p', 1, e2);
                    b.addPiece('p', 1, f2);
                    b.addPiece('p', 1, g2);
                    b.addPiece('p', 1, h2);
                    b.addPiece('r', 2, a8);
                    b.addPiece('n', 2, b8);
                    b.addPiece('b', 2, c8);
                    b.addPiece('q', 2, d8);
                    b.addPiece('k', 2, e8);
                    b.addPiece('b', 2, f8);
                    b.addPiece('n', 2, g8);
                    b.addPiece('r', 2, h8);
                    b.addPiece('p', 2, a7);
                    b.addPiece('p', 2, b7);
                    b.addPiece('p', 2, c7);
                    b.addPiece('p', 2, d7);
                    b.addPiece('p', 2, e7);
                    b.addPiece('p', 2, f7);
                    b.addPiece('p', 2, g7);
                    b.addPiece('p', 2, h7);

                    // now print it out
                    b.textprint();
                }

                else if (input == "clear") {
                    b.clear();
                    b.textprint();
                }

                // Add a new piece
				//Rewrite
				else if (input[0] == '+' && isspace(input[1]) && input.length() == 6) {
                    bool sole_king = true;
                    char sym, col;
                    int pno, row;

			//check for valid input
					while(input[5] < 49 || input[5] > 56 || input[4] < 'a' || input[4] > 'h'){
						cout << "Please enter command with valid coordinates" << endl;
						input.clear();
						getline(cin, input);
					}

                    // set the symbol equal to the given symbol
                    sym = input[2];

                    // figure out the piece owner based on piece case
                    if (isupper(sym)) {
                        pno = 1;
                    }
                    else pno = 2;

                    if (sym == 'K' && b.getHM('K') != 0) {
                        cout << "You cannot add more than one white king. Please remove the already existing one first." << endl << endl;
                        sole_king = false;
                    }
                    else if (sym == 'k' && b.getHM('k') != 0) {
                        cout << "You cannot add more than one black king. Please remove the already existing one first." << endl << endl;
                        sole_king = false;
                    }

			//check for invalid positions, chars
                    if (sole_king) {
                        row = input[5] - 48;
                        col = input[4];

                        // create the Position
                        Position pos = Position(row, col);

                        // was the position empty?
                        if (b.getP(pos) == NULL) 
                            b.addPiece(sym, pno, pos);
                        
                        // guess the position had something there
                        else {
                            b.deleteP(pos);
                            b.addPiece(sym, pno, pos);
                        }
					}

                    b.textprint();
                }

				else if (input[0] == '-' && isspace(input[1]) && input.length() == 4) {

			//check for valid input
					while(input[3] < 49 || input[3] > 56 || input[2] < 'a' || input[2] > 'h'){
						cout << "Please enter command with valid coordinates" << endl;
						input.clear();
						getline(cin, input);
					}

                    // get the column
                    char col = input[2];

                    // convert the row to an int
                    int row = input[3] - 48;

                    // make the position
                    Position pos = Position(row, col);

					// is there something there to delete?
                    if (b.getP(pos) != NULL) 
                        b.deleteP(pos);

                    // print it out
                    b.textprint();
                }

				else if (input[0] == '=' && isspace(input[1]) && input.length() == 7) {
                    string colour = input.substr(2, 5);

                    // change the flag for whose turn it is
                    if (colour == "black") {
                        currentturn = 2;
                        cout << "Current turn set to Black (player 2)" << endl << endl;
                    }
                    else if (colour == "white") {
                        currentturn = 1;
                        cout << "Current turn set to White (player 1)" << endl << endl;
                    }
                    // we only have monochrome players here
                    else {
                        cout << "This is not a valid player. Please try again." << endl << endl;
                    }

                }

                else if (input == "done") {
                    bool pawnissue = false;

					for (char index = 'a'; index != 'i'; index++) {
						if(b.getP(index, 1) != NULL && tolower(b.getP(index, 1)->getsymbol()) == 'p'){
							pawnissue = true;
							break;
						}
						if(b.getP(index, 8) != NULL && tolower(b.getP(index, 8)->getsymbol()) == 'p'){
							pawnissue = true;
							break;
						}
					}
                    
                    // find out if anybody's king is in check
                    if (p1->getKing() != NULL && p2->getKing() != NULL) {
                        p1->getKing()->isincheck();	//make sure p1's king isnt in check
                        p2->getKing()->isincheck();	//make sure p2's king isnt in check
                    }
                    
                    // make sure they each have exactly one king
                    if (b.getHM('K') != 1 || b.getHM('k') != 1) {
                        cout << "You must have exactly one black and one white King. Please rectify this and try again." << endl << endl;
                        init = false;
                    }

                    // got a king each? Can't have any pawns in the home rows.
                    else if (pawnissue) {
                        cout << "You must not have any pawns in rows 1 or 8. Please rectify this and try again." << endl << endl;
                        init = false;
                    }

                    // pawns not an issue? Can't have anybody in check or checkmate.
                    else if (p1->getKing()->getChecked() || p2->getKing()->getChecked()) {
                        cout << "Neither player may be in check or checkmate. Please rectify this and try again." << endl << endl;
                        init = false;
                    }

                    // got past all my rules, eh? fine.
                    else {
                        // here's your board
                        b.textprint();
                        // game initialized for the first time
                        init = true;
                        break;
                    }

                    // why am I here?
                    b.textprint();
                }

                // don't wanna play anymore? :(
                else if (input == "quit") {
                    return 0;
                }

                // come on man, type a real command.
                else {
                    cout << "This command is not recognized. Type \"help\" if you need help." << endl << endl;
                }
            }
        }

        // game time
        else if (init) {
		//game command
			//pawn promotion not included
            // fox wants to play
            if (input.substr(0, 4) == "game") {
                // is player 1 a human?
                if (input[5] == 'h') {
                    p1->setHuman(true);
                    p1->setDifficulty(0);
                    // is player 2 a human?
                    if (input[11] == 'h') {
                        p2->setHuman(true);
                        p2->setDifficulty(0);
                    }
                    // player 2 is a computer
                    else if (input[11] == 'c') {
                        p2->setHuman(false);
                        p2->setDifficulty(input[20] - 48);
                    }
                }
                // p1 is a computer
                else if (input[5] == 'c') {
                    p1->setHuman(false);
                    p1->setDifficulty(input[14] - 48);
                    // is p2 a human?
                    if (input[17] == 'h') {
                        p2->setHuman(true);
                        p2->setDifficulty(0);
                    }// p2 is a computer.
                    else if (input[17] == 'c') {
                        p2->setHuman(false);
                        p2->setDifficulty(input[26] - 48);
                    }
                }
		        // INPUT LOOP #3
                while (true) {
				  //   cout << "In the game" << endl;
                    cout << endl;
					// cout << "Is King in check?\n";
                    p1->getKing()->isincheck();	//set p1 King's incheck value
                    p2->getKing()->isincheck();	//set p2 King's incheck value
				   //  cout << "Checking whether both King's in check or not" << endl;
					// cout << "Getting moves\n";
                    // get them moves
					p1->getAllMoves();
                   //  cout << "Getting black moves\n";
					p2->getAllMoves();
				 //    cout << "Got both player's moves\n";

                    // we in a stalemate? gotta end, give em both a half point.
					if(b.check_stalemate()){
						cout << "Stalemate!" << endl;
						p1score += 0.5;
						p2score += 0.5;
                        cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
						init = false;
                        break;
					}

                    // white's turn
					if (currentturn == 1) {
                        cout << "White's turn." << endl << endl;

                        // is white in check?
                        if (p1->getKing()->getChecked()) {
                            bool checkmate = false;

                            vector<Piece*> vp = p1->getpieces();

						    //check for Checkmate
                            for (vector<Piece*>::size_type i = 0; i < vp.size(); i++) {
                                list<Position> pos = vp[i]->returnmoves();

                                if (!pos.empty()) {
                                    checkmate = false;
                                    break;
                                }
                                if (i == vp.size()-1 && pos.empty()) {
                                    checkmate = true;
                                }
                            }

                            // looks like white's in checkmate. That sucks.
                            if(checkmate) {
                                cout << "Checkmate! Player 2 (black) wins." << endl << endl;
                                p2score++;
                                cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
                                cout << "Before starting a new game, please enter setup mode again to set up a new board. This can be accomplished by typing \"setup\"" << endl << endl;
                                b.clear();
								init = false;
                                break;
                            }
                            // nah, not checkmate, just check.
                            else {
                                cout << "White is in check." << endl << endl;
                            }
						}

                        // is White a human?
						if (p1->ishuman()) {
                            // what's the fox say?
                            getline(cin, input);

                            // fox wants to quit
                            if (input == "quit") {
                                return 0;
                            }

                            // fox wants to move!
							if (input.substr(0, 4) == "move") {
                                int fr, dr;
                                char fc, dc;

                                // from position
                                fc = input[5];
                                fr = input[6] - 48;

                                // to position
                                dc = input[8];
                                dr = input[9] - 48;

                                // actually creating the positions
                                Position from = Position(fr, fc);
                                Position to = Position(dr, dc);
                                //cout << "From position: (" << from.getRow() << ", " << from.getColumn() << ")" << endl;
                                //cout << "To position: (" << to.getRow() << ", " << to.getColumn() << ")" << endl;
							
							    // Did you try to move something from an empty spot?
                                if (b.getP(from) == NULL) {
                                    cout << "There is no piece in the specified start location. Please try again." << endl << endl;
									made_mistake = true;
                                }

                                // guess not...
                                else if (b.getP(from) != NULL) {
                                    // is that piece even yours to move?
                                    if (b.getP(from)->getowner()->getPlayerNumber() != currentturn) {
                                        cout << "This piece in the specified start location does not belong to you. Please try again." << endl << endl;
										made_mistake = true;
                                    }

                                    // guess so
                                    else {
                                        // gotta make sure the move is legal
									    if(b.searchPosVector(b.getP(from)->returnmoves(), to)) {

                                            if (b.getP(from)->getsymbol() == 'P' && fr == 7) {
                                                if (input.size() == 12) {
                                                    if (input[11] != 'Q' && input[11] != 'N' && input[11] != 'R' && input[11] != 'B') {
                                                        made_mistake = true;
                                                        cout << "You must select one of Q, N, R, or B to promote your pawn to. Your command should have the form \"move [start] [finish] [symbol to upgrade to]\"." << endl << endl;
                                                    }
                                                    else {
                                                        char newsym = input[11];
                                                        b.moveP(from, to);
                                                        b.deleteP(to);
                                                        b.addPiece(newsym, 1, to);
                                                        //b.textprint();
                                                        currentturn = 2;
                                                    }
                                                }
                                                else {
                                                    made_mistake = true;
                                                    cout << "You must select one of Q, N, R, or B to promote your pawn to. Your command should have the form \"move [start] [finish] [symbol to upgrade to]\"." << endl << endl;
                                                }   
                                            }
                                            else {
                                                b.moveP(from, to);
                                                //b.textprint();
                                                currentturn = 2; // switch teh turn
                                            }
                                        }
                                        // that was a nice try.
										else {
                                            cout << "This is not a legal move. Please try again." << endl << endl;
											made_mistake = true;
                                        }
									}
                                }
								b.textprint();
                            }

                            // feeling like resigning I guess.
							else if (input == "resign") {
                                cout << "Player 1 (white) has resigned! Player 2 (black) is victorious!" << endl << endl;
                                p2score++;
                                cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
                                cout << "Before starting a new game, please enter setup mode again to set up a new board. This can be accomplished by typing \"setup\"" << endl << endl;
								b.clear();
                                init = false;
                                break;
                            }
                            // made a mistake typing, I don't know what you want
                            else {
                                cout << "Command not recognized." << endl << "Please type \"move [location1] [location2]\" to move a piece" << endl;
                                cout << "Or type \"resign\" to resign the game." << endl << endl;
								made_mistake = true;
                            }
                        }
                        // playing against the computer, eh?
                        else if (!(p1->ishuman())) {
                            // what do you want it to do?
                            getline(cin, input);

                            // want it to move, I see.
                            if (input == "move") {
                                // level one computer
                                if (p1->getDifficulty() == 1) {
									b.level_one_move(p1);
                                }
                                // level two computer
                                else if (p1->getDifficulty() == 2) {
                                    b.level_two_move(p1);
                                }
                                // level three computer
                                else if (p1->getDifficulty() == 3) {
                                    b.level_three_move(p1);
                                }
                                // level four computer
                                else if (p1->getDifficulty() == 4) {
                                    // L4
                                }

                                // print the board
                                b.textprint();
                                currentturn = 2;    //now its player 2's turn
                            }
                            // oh so you want the computer to be a quitter.
                            else if (input == "quit") {
                                return 0;
                            }
                            // computer's gonna resign? what?
                            else if (input == "resign") {
                                cout << "Player 1 (white) has resigned! Player 2 (black) is victorious!" << endl << endl;
                                p2score++;
                                cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
                                cout << "Before starting a new game, please enter setup mode again to set up a new board. This can be accomplished by typing \"setup\"" << endl << endl;
                                b.clear();
                                init = false;
                                break;
                            }
                            // learn to type
                            else {
                                cout << "Command not recognized. Please type \"move\" to command the computer to take its turn." << endl << endl;
								made_mistake = true;
                            }
                        }
                    }

                    // Black's turn
					else if (currentturn == 2) {
                        cout << "Black's turn." << endl << endl;
                        // we in check?
                        if (p2->getKing()->getChecked()) {
                            bool checkmate = false;
                            vector<Piece*> vp = p2->getpieces();
                            // we in checkmate?
							for (vector<Piece*>::size_type i = 0; i < vp.size(); i++) {
                                list<Position> pos = vp[i]->returnmoves();
                                if (!pos.empty()) {
                                    checkmate = false;
                                    break;
                                }
                                if (i == vp.size()-1 && pos.empty()) {
                                    checkmate = true;
                                }
                            }
                            // crap we got checkmated
                            if(checkmate) {
                                cout << "Checkmate! Player 1 (white) wins." << endl << endl;
                                p1score++;
                                cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
                                cout << "Before starting a new game, please enter setup mode again to set up a new board. This can be accomplished by typing \"setup\"" << endl << endl;
								b.clear();
                                init = false;
                                break;
                            }
                            // nah just check
                            else {
                                cout << "Black is in check." << endl << endl;
                            }
                        }
                        // we human or no?
                        if (p2->ishuman()) {
                            // what does the fox say?
                            getline(cin, input);

                            // gotta quit
                            if (input == "quit") {
                                return 0;
                            }
                            
                            // gonna make our move 
                            if (input.substr(0, 4) == "move") {
                                int fr, dr;
                                char fc, dc;

                                // from position
                                fc = input[5];
                                fr = input[6] - 48;

                                // to position
                                dc = input[8];
                                dr = input[9] - 48;

                                // actually making the positions
                                Position from = Position(fr, fc);
                                Position to = Position(dr, dc);

                                // is there a piece there?
                                if (b.getP(from) == NULL) {
                                    cout << "There is no piece in the specified start location. Please try again." << endl << endl;
									made_mistake = true;
                                }

                                // suppose so
                                else if (b.getP(from) != NULL) {

                                    // is it your piece?
                                    if (b.getP(from)->getowner()->getPlayerNumber() != currentturn) {
                                        cout << "This piece in the specified start location does not belong to you. Please try again." << endl << endl;
										made_mistake = true;
                                    }
                                    // good
                                    else {
                                        // is it a legal move?
                                        if(b.searchPosVector(b.getP(from)->returnmoves(), to)) {

                                            if (b.getP(from)->getsymbol() == 'p' && fr == 2) {
                                                if (input.size() == 12) {
                                                    if (input[11] != 'q' && input[11] != 'n' && input[11] != 'r' && input[11] != 'b') {
                                                        made_mistake = true;
                                                        cout << "You must select one of Q, N, R, or B to promote your pawn to. Your command should have the form \"move [start] [finish] [symbol to upgrade to]\"." << endl << endl;
                                                    }
                                                    else {
                                                        char newsym = input[11];
                                                        b.moveP(from, to);
                                                        b.deleteP(to);
                                                        b.addPiece(newsym, 2, to);
                                                        //b.textprint();
                                                        currentturn = 1;
                                                    }
                                                }
                                                else {
                                                    made_mistake = true;
                                                    cout << "You must select one of q, n, r, or b to promote your pawn to. Your command should have the form \"move [start] [finish] [symbol to upgrade to]\"." << endl << endl;
                                                } 
                                            }
                                            else {
                                                b.moveP(from, to);
                                                //b.textprint();
                                                currentturn = 1;    //now its player 1's turn
                                            }
                                        }
                                        // hah it wasn't
                                        else cout << "This is not a legal move. Please try again." << endl << endl;        
                                    }
                                }
								b.textprint();
							}
                            // Player 2 resigns
                            else if (input == "resign") {
                                cout << "Player 2 (black) has resigned! Player 1 (white) is victorious!" << endl << endl;
                                p1score++;
                                cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
                                cout << "Before starting a new game, please enter setup mode again to set up a new board. This can be accomplished by typing \"setup\"" << endl << endl;
                                b.clear();
								init = false;
                                break;
                            }
                            // no you just messed up your typing
                            else {
                                cout << "Command not recognized." << endl << "Please type \"move [location1] [location2]\" to move a piece" << endl;
                                cout << "Or type \"resign\" to resign the game." << endl << endl;
                            }
                        }
                        // oh so we're a computer.
                        else if (!(p2->ishuman())) {
                            getline(cin, input);

                            // gotta quit
                            if (input == "quit") {
                                return 0;
                            }
                            
							else if (input == "move") {
                                // level one
                                if (p2->getDifficulty() == 1) {
									b.level_one_move(p2);
                                }
                                // level two
                                else if (p2->getDifficulty() == 2) {
                                    b.level_two_move(p2);
                                }
                                // level three
                                else if (p2->getDifficulty() == 3) {
                                    b.level_three_move(p2);
                                }
                                // level four
                                else if (p2->getDifficulty() == 4) {
                                    // L4
                                }

                                // priiiint
                                b.textprint();
                                currentturn = 1;    //now its player 1's turn
                            }

                            // givin up
                            else if (input == "resign") {
                                cout << "Player 2 (black) has resigned! Player 1 (white) is victorious!" << endl << endl;
                                p1score++;
                                cout << "Game score:" << endl << "   White: " << p1score << endl << "   Black: " << p2score << endl << endl;
                                cout << "Before starting a new game, please enter setup mode again to set up a new board. This can be accomplished by typing \"setup\"" << endl << endl;
                                b.clear();
                                init = false;
                                break;
                            }

                            // cant type
                            else cout << "Command not recognized. Please type \"move\" to command the computer to take its turn." << endl << endl;              
                        }
                    }
                }
            }
		}
        else if (init == false && input.substr(0, 4) == "game") 
            cout << "You must enter setup mode before starting a new game." << endl << endl;

		else {
			cout << "Command not recognized" << endl << endl;
			continue;
		}
    }
    return 0;
}