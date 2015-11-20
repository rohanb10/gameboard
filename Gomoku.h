/*
Gomoku.h
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		maheavner@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu

	Declares Gomoku (derived from Game) class member variables and methods
*/

#ifndef GOMOKU_H
#define GOMOKU_H

#include "enums.h"
#include "Game.h"

class Gomoku : public Game{

	friend ostream & operator<< (ostream &, const Gomoku &);

public:
	Gomoku();
	Gomoku(int size, int toWin=5);
	virtual void print();
	string getPlayer();
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
};



#endif GOMOKU_H