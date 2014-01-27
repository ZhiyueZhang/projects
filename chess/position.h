#ifndef __POSITION_H__
#define __POSITION_H__


class Position {	//make this a class, enforce encapsulation, have accessor and setter methods
	int row;
	bool isoccupied;
	char column;
public:
	Position(char, int, bool); // if you know it's gonna be occupied or not
	Position(int, char);
	Position();
	Position(const Position& rhs);
	int getRow() const; // fetch the row
	bool getOccupied() const; // fetch the occupation (hah)
	char getColumn() const; // fetch the column
	void setRow(int); // set the row
	void setColumn(char); // set the column
	void setOccupied (bool); // set the occupation (if only it were as easy as a few lines of code to get an occupation IRL, eh?)
	bool operator==(const Position&); // because the default one sucks and isn't versatile
	Position& operator=(const Position&); // see above
};

#endif // POSITION_H