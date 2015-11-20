/*
TicTacToe.h
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		maheavner@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu

	Declares TicTacToe (derived from Game) class member variables and methods
*/

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "Game.h"

class TicTacToe : public Game{

	friend ostream & operator<< (ostream &, const TicTacToe &);

public:
	TicTacToe();
	virtual void print();
	string getPlayer();
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
};


#endif TICTACTOE_H