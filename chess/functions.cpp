#include "functions.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <list>
#include <string>
#include <sstream>
#include "position.h"

using namespace std;

/*
// checks if given position is an element of given vector of positions
bool searchPosVector(vector<Position> v, Position p) {
	for(vector<Position>::iterator it = v.begin(); it != v.end(); it++){
		if(*it == p)
			return true;
	}
	return false;
}

// same as above but with a list instead of a vector
bool searchPosVector(list<Position> v, Position p) {
	for(list<Position>::iterator it = v.begin(); it != v.end(); it++){
		if(*it == p)
			return true;
	}
    return false;
}


// converts a character to an integer.
//int chartoint(char s) {
  //  return s - 48;
//}
*/