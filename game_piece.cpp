/*
game_piece.cpp
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		maheavner@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu

	Defines constructor and functions for game pieces
	Defines conversion from piece_color to string and vice versa
*/

#include "stdafx.h"
#include "game_piece.h"


//default constructor, useful for making empty game pieces
game_piece::game_piece(){
	this->color = none;
	this->name = "";
	this->img = EMPTY_PIECE;
}

//a little more specific
game_piece::game_piece(piece_color color, string name, string img){
	this->color = color;
	this->name = name;
	this->img = img;
}

static void toLowerCase(string &str){
	for (unsigned int i = 0; i < str.size(); i++){
		if (str.at(i) <= 90){ //if char at i is uppercase
			str.at(i) += 32;  //conversion to lowercase
		}
	}
}

piece_color str_to_color(string str){
	toLowerCase(str);
	if (str == "red"){
		return piece_color::red;
	}
	else if (str == "black"){
		return piece_color::black;
	}
	else if (str == "white"){
		return piece_color::white;
	}
	else if (str == " "){
		return piece_color::none;
	}
	else{
		return piece_color::invalid;
	}
}

string toString(piece_color color){
	if (color == piece_color::red){
		return "red";
	}
	else if (color == piece_color::black){
		return "black";
	}
	else if (color == piece_color::white){
		return "white";
	}
	else if (color == piece_color::none){
		return "none";
	}
	else{
		return "invalid";
	}
}

