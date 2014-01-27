#include "position.h"

Position::Position(int row, char col):row(row), column(col), isoccupied(false) {}; // nondefault constructor 1

Position::Position(char col, int row, bool isoccupied):row(row), column(col), isoccupied(isoccupied) {}; // nondefault constructor 2

Position::Position():row(0), column(0), isoccupied(0) {}; // default constructor!

Position::Position(const Position& rhs): row(rhs.getRow()), column(rhs.getColumn()) {};

int Position::getRow()const { return row; }; // getter for row

char Position::getColumn()const { return column; }; // getter for column

bool Position::getOccupied()const { return isoccupied; }; // getter for occupied

void Position::setRow(int row) { this->row = row; }; // setter for row

void Position::setColumn(char column) { this->column = column;}; // setter for column

void Position::setOccupied(bool isoccupied) { this->isoccupied = isoccupied;}; // setter for occupied

bool Position::operator ==(const Position &rhs){ // == operator for positions
	return((this->getRow()==rhs.getRow()) && (this->getColumn()==rhs.getColumn()));
};

Position& Position::operator=(const Position& rhs){ // assignment operator for positions
	this->row = rhs.getRow();
	this->column = rhs.getColumn();
	this->isoccupied = rhs.getOccupied();
	return *this;
};