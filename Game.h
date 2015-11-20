/*
Game.h
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		maheavner@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu

	Declares Game class member variables and methods
	Contains important enum values for referring to board locations
*/

#ifndef GAME_H
#define GAME_H

#include "enums.h"
#include "game_piece.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Game{

protected:
	Game();
	unsigned int width;
	unsigned int height;
	unsigned int moves;
	bool playerOne;
	vector<game_piece> pieces;
	unsigned int longestStr;
	unsigned int victoryAmt; //how many pieces in sequence needed to win (if applicable)

public:
	//accessors
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	virtual string getPlayer() = 0;
	game_piece getPiece(int x, int y) const;

	//mutators
	void setPiece(int x, int y);
	void switchPlayer();

	//non-static functions
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int & x, unsigned int & y);
	virtual int turn() = 0;
	void printPlayerMoves();
	int play();
	virtual void print() = 0;

	//static functions
	static Game* makeGame(int argc, char* argv[]);
};


//to be used as replacements for values in the coordinate  vector
enum BoardValues{
	MINIMUM = 0,
	CENTER = 2,
	PADDING = 2, //MUST BE EVEN NUMBER
	HALFPADDING = (PADDING/2),
	FIRST_COLUMN = HALFPADDING,
	FIRST_ROW = HALFPADDING,
	SPACING = 2
};


#endif /*GAME_H*/