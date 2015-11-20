/*
TicTacToe.cpp
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		heavnerm@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu

	Defines TicTacToe (derived from Game) methods
*/

#include "stdafx.h"
#include "TicTacToe.h"
#include "enums.h"

//default constructor for TicTacToe game
TicTacToe::TicTacToe(){
	width = 3+PADDING;
	height = 3+PADDING;
	moves = 0;
	longestStr = 1;
	for (unsigned int i = 0; i < height * width; i++){
		game_piece *p = new game_piece();
		pieces.push_back(*p);
	}
}

//saves the cout format of the class to the ostream reference
ostream & operator << (ostream & o, const TicTacToe & game){

	auto space = setw(game.longestStr);
	
	for (signed int i = game.height - 1; i >= MINIMUM; i--){
		

		if (i == MINIMUM || i == game.height - 1){
			o << space;
		}
		else{
			o << to_string(i);
		}

		

		for (unsigned int j = MINIMUM; j < game.width - 1; j++){
			o << game.getPiece(i, j).img << space;
		}
		o << endl << endl;
	}
	o << space << space;

	for (unsigned int j = MINIMUM; j < game.width; j++){ //index of columns at base
		if (j != MINIMUM && j != game.width - 1){
			o << to_string(j);
			o << space;
		}
		else{
			for (unsigned int k = MINIMUM; k < game.longestStr; k++){
				o << " ";
			}
		}
		
	}
	o << endl;
	return o;
}

//pass *this into ostream
void TicTacToe::print(){
	cout << *this;
}

//return string representation of current player
string TicTacToe::getPlayer(){
	return ((playerOne) ? "x" : "o");

}

//checks if either of the players has won the game
bool TicTacToe::done(){
	// check each column
	for (unsigned int i = FIRST_COLUMN; i < getWidth() - 1; i++){
		string piece = getPiece(FIRST_ROW, i).img; //first piece in column
		if (piece != EMPTY_PIECE){
			bool flag = true; //assumed true until incorrect piece found
			for (unsigned int j = FIRST_ROW; j < getHeight() - 1 && flag; j++){
				if (getPiece(j, i).img != piece){
					flag = false;
				}
			}
			if (flag){
				return flag;
			}
		}
	}
	//check each row
	for (unsigned int i = FIRST_ROW; i < getHeight() - 1; i++){
		string piece = getPiece(i, FIRST_COLUMN).img; //first piece in row
		if (piece != EMPTY_PIECE){
			bool flag = true; //assumed true until incorrect piece found
			for (unsigned int j = FIRST_COLUMN; j < getWidth() - 1 && flag; j++){
				if (getPiece(i, j).img != piece){
					flag = false;
				}
			}
			if (flag){
				return flag;
			}
		}
	}

	string piece = getPiece(CENTER, CENTER).img; //piece in center

	if (piece != EMPTY_PIECE){
		//check top left to bottom right diagonal
		bool flag = true;
		for (unsigned int i = FIRST_ROW; i < getHeight(); i++){
			for (unsigned int j = FIRST_COLUMN; j < getWidth() - 1 && i + j <= 4 && flag; j++){
				if (i + j == getWidth() - 1 && getPiece(i, j).img != piece){ //all cordinates should add up to 4 = (1,3) (2,2) (3,1)
					flag = false;
				}
			}
		}
		if (flag){
			return flag;
		}

		//check bottom left to top right diagonal
		flag = true; //reset flag
		for (unsigned int i = FIRST_ROW; i < getHeight() - 1; i++){
			if (getPiece(i, i).img != piece){ // all cordinates should have the same x and y = (1,1) (2,2) (3,3)
				flag = false;
			}
		}
		if (flag){
			return flag;
		}
	}
	return false;
}



//checks if the game has ended in a draw
bool TicTacToe::stalemate(){
	if (done()){
		return false;
	}
	//checks if any board piece is still empty
	for (unsigned int i = FIRST_ROW; i < getHeight() - 1; i++){
		for (unsigned int j = FIRST_COLUMN; j < getWidth() - 1; j++){
			if (getPiece(i, j).img == EMPTY_PIECE){
				return false;
			}
		}
	}
	return true;
}



//prompts the correct player and prints the board
int TicTacToe::turn(){
	unsigned int x, y;
	cout << "*-----------------*" << endl << "| Player " << getPlayer() << "'s turn |" << endl << "*-----------------*" << endl;
	while (prompt(x, y) != QUIT){
		setPiece(x, y);
		moves++;
		cout << *this << endl;
		printPlayerMoves();
		return SUCCESS;
	}
	return QUIT;
}
