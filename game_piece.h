/*
game_piece.h
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		heavnerm@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu
	
	Contains enum declarations of valid piece colors and a struct
	representation of a game piece
	Declares game piece functions
*/

#ifndef GAME_PIECE_H
#define GAME_PIECE_H

#include "enums.h"

const string EMPTY_PIECE = "";

enum piece_color{
	red,
	black,
	white,
	none,
	invalid
};


struct game_piece{
	piece_color color;
	string name;
	string img;
	game_piece();
	game_piece(piece_color color, string name, string img);
};




piece_color str_to_color(string);
string toString(piece_color);



#endif
