/*
Gomoku.cpp
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		maheavner@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu

	Defines Gomoku (derived from Game) methods
*/

#include "stdafx.h"
#include "Gomoku.h"

Gomoku::Gomoku(){
	width = 19+PADDING;
	height = 19+PADDING;
	moves = 0;
	
	for (unsigned int i = 0; i < height * width; i++){
		game_piece *p = new game_piece();
		pieces.push_back(*p);
	}
	longestStr = 1;
	victoryAmt = 5;
}
Gomoku::Gomoku(int size, int toWin){
	width = size + PADDING;
	height = size + PADDING;
	moves = 0;

	for (unsigned int i = 0; i < height * width; i++){
		game_piece *p = new game_piece();
		pieces.push_back(*p);
	}
	longestStr = 1;
	victoryAmt = toWin;
}

//saves the cout format of the class to the ostream reference
ostream & operator << (ostream & o, const Gomoku & game){

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
		o << endl;
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
void Gomoku::print(){
	cout << *this;
}

//return string representation of current player
string Gomoku::getPlayer(){ 
	return (playerOne ? "B" : "W"); 
}

//check if either player has won
bool Gomoku::done(){

	//not possible to win before either player has played the necessary amount of pieces
	//for a win
	if (moves < (victoryAmt*2) - 1){
		return false;
	}

	//each of the following checks follows this logic:
	//	for each piece, look forward the number of pieces needed to win - 1
	//	if that piece matches the first piece, check and count the pieces in between
	//	else continue to the next piece

	//check rows
	for (unsigned int i = FIRST_ROW; i < getHeight(); i++){
		for (unsigned int j = FIRST_COLUMN; j < getWidth() - (victoryAmt - 1); j++){
			
			int c = 1;
			string currPiece = getPiece(i, j).img;

			if (currPiece != EMPTY_PIECE && getPiece(i, j + (victoryAmt - 1)).img == currPiece){
				c++;
				for (unsigned int k = j + 1; k < j + (victoryAmt - 1); k++){
					if (getPiece(i, k).img == currPiece){
						c++;
					}
					else{
						//if any piece between the first and victoryAmt'th 
						//piece is of different color, break and continue the search from there
						j = k;
						break;
					}
				}
				if (c == (victoryAmt)){
					return true;
				}
			}
		}
	}

	//check cols
	for (unsigned int j = FIRST_COLUMN; j < getWidth(); j++){
		for (unsigned int i = FIRST_ROW; i < getHeight() - (victoryAmt - 1); i++){
			int c = 1;
			string currPiece = getPiece(i, j).img;
			if (currPiece != EMPTY_PIECE && getPiece(i + (victoryAmt - 1), j).img == currPiece){
				c++;
				for (unsigned int k = i + 1; k < i + (victoryAmt - 1); k++){
					if (getPiece(k, j).img == currPiece){
						c++;
					}
					else{
						i = k;
						break;
					}
				}
				if (c == (victoryAmt)){
					return true;
				}
			}
		}
	}

	//check diagonals of positive slope
	for (unsigned int i = FIRST_ROW; i < getHeight() - (victoryAmt - 1); i++){
		for (unsigned int j = FIRST_COLUMN; j < getWidth() - (victoryAmt - 1); j++){
			int c = 1;
			string currPiece = getPiece(i, j).img;
			if (currPiece != EMPTY_PIECE && getPiece(i + (victoryAmt - 1), j + (victoryAmt - 1)).img == currPiece){
				c++;
				for (unsigned int k = 1; k < (victoryAmt - 1); k++){
					if (getPiece(i + k, j + k).img == currPiece){
						c++;
					}
					else{
						break;
					}
				}
				if(c == (victoryAmt)){
					return true;
				}
			}
		}
	}

	//check diagonals of negative slope
	for (unsigned int i = (victoryAmt - 1) + PADDING; i < getHeight(); i++){
		for (unsigned int j = FIRST_COLUMN; j < getWidth() - (victoryAmt - 1); j++){
			int c = 1;
			string currPiece = getPiece(i, j).img;
			if (currPiece != EMPTY_PIECE && getPiece(i - (victoryAmt - 1), j + (victoryAmt - 1)).img == currPiece){
				c++;
				for (unsigned int k = 1; k < (victoryAmt - 1); k++){
					if (getPiece(i - k, j + k).img == currPiece){
						c++;
					}
					else{
						break;
					}
				}
				if (c == (victoryAmt)){
					return true;
				}
			}
		}
	}
	return false; 
}


//check if a stalemate has been reached
bool Gomoku::stalemate(){ 

	if (done()){
		return false;
	}
	unsigned int maxMoves = (width - PADDING)*(height - PADDING);

	//if board is full a stalemate must have been reached
	if (moves == maxMoves){
		return true;
	}

	//check cols for possible winning combination
	for (unsigned int j = victoryAmt; j < getHeight()-1; j++){
		for (unsigned int i = FIRST_COLUMN; i < getWidth()-1; i++){

			int c = 1;
			string currPiece = getPiece(j, i).img;

			for (unsigned int k = 1; k < victoryAmt; k++){

				if (currPiece == EMPTY_PIECE){
					currPiece = getPiece(j - k, i).img;
				}

				if (getPiece(j - k, i).img == EMPTY_PIECE || getPiece(j - k, i).img == currPiece){
					c++;
				}
			}
			if (c == victoryAmt){
				//useful debug message:
				//cout << "col down possible at (" << i << "," << j << ") == " << currPiece << endl;
				return false;
			}
		}
	}

	//check rows
	for (unsigned int j = FIRST_ROW; j < getHeight() - 1; j++){
		for (unsigned int i = victoryAmt; i < getWidth() - 1; i++){

			int c = 1;
			string currPiece = getPiece(j, i).img;

			for (unsigned int k = 1; k < victoryAmt; k++){

				if (currPiece == EMPTY_PIECE){
					currPiece = getPiece(j, i - k).img;
				}

				if (getPiece(j, i - k).img == EMPTY_PIECE || getPiece(j, i - k).img == currPiece){
					c++;
				}
			}
			if (c == victoryAmt){
				//useful debug message:
				//cout << "row left possible at (" << i << "," << j << ") == " << currPiece << endl;
				return false;
			}
		}
	}

	//check diagonals of positive slope
	for (unsigned int j = victoryAmt; j < getHeight() - 1; j++){
		for (unsigned int i = victoryAmt; i < getWidth() - 1; i++){

			int c = 1;
			string currPiece = getPiece(j, i).img;

			for (unsigned int k = 1; k < victoryAmt; k++){
				if (currPiece == EMPTY_PIECE){
					currPiece = getPiece(j - k, i - k).img;
				}

				if (getPiece(j - k, i - k).img == EMPTY_PIECE || getPiece(j - k, i - k).img == currPiece){
					c++;
				}
			}
			if (c == victoryAmt){
				//useful debug message:
				//cout << "diagPos possible at (" << i << "," << j << ") == " << currPiece << endl;
				return false;
			}
		}
	}

	//check diagonals of negative slope
	for (unsigned int j = FIRST_ROW; j < getHeight() - victoryAmt; j++){
		for (unsigned int i = victoryAmt; i < getWidth() - 1; i++){

			int c = 1;
			string currPiece = getPiece(j, i).img;

			for (unsigned int k = 1; k < victoryAmt; k++){

				if (currPiece == EMPTY_PIECE){
					currPiece = getPiece(j - k, i + k).img;
				}

				if (getPiece(j + k, i - k).img == EMPTY_PIECE || getPiece(j + k, i - k).img == currPiece){
					c++;
				}
			}

			if (c == victoryAmt){
				//useful debug message:
				//cout << "diagNeg possible at (" << i << "," << j << ") == " << currPiece << endl;
				return false;
			}
		}
	}
	return true; 
}

//prompts the correct player and prints the board
int Gomoku::turn(){
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
