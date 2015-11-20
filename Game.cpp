/*
Game.cpp
	authors:
	Rohan Bhansali		rohanbhansali@wustl.edu
	Michael Heavner		maheavner@wustl.edu
	Federico Rozenberg	frozenberg@wustl.edu	

	Defines methods for base Game class
*/

#include "stdafx.h"
#include <iostream>
#include "Game.h"
#include "TicTacToe.h"
#include "Gomoku.h"

//necessary default constructor
Game::Game(){}


//returns the height of the game board
unsigned int Game::getHeight() const{
	return height;
}


//returns the width of the game board
unsigned int Game::getWidth() const{
	return width;
}


//switches the players
void Game::switchPlayer() {
	playerOne = !playerOne;
}


//gets a specific piece's from the pieces vector
game_piece Game::getPiece(int x,int y) const{
	return pieces[(width*y) + x];
}


//sets the specified piece to the display string of the current player
void Game::setPiece(int x, int y){
	pieces[(width*y) + x].img = getPlayer();
	if (getPlayer().length() + SPACING > longestStr){
		longestStr = getPlayer().length() + SPACING;
	}
}


//prompts the player until a valid input is entered or the player quits
int Game::prompt(unsigned int &x, unsigned int &y){
	string s;
	unsigned int checkX, checkY;
	unsigned int errCheck;
	//repeatedly prompt until cin == "quit"
	while (s != "quit"){
		int comma = s.find(',');		//checks for correct format of cin
		if (comma != -1){
			s[comma] = ' ';
			istringstream iss(s);
			iss >> checkY >> checkX;
			if (iss >> errCheck){
				return INPUT_NOT_VALID;
			}
			//check if coordinates are valid
			if (checkX >= FIRST_ROW && checkY >= FIRST_COLUMN && checkX < getWidth() - 1 && checkY < getHeight() - 1){
				//check another piece exists in that location
				if (getPiece(checkX, checkY).img == EMPTY_PIECE){
					x = checkX;
					y = checkY;
					return SUCCESS;
				}
				cout << "That piece has already been played. Please select another location." << endl;
			}
		}
		cout << "Please enter two valid coordinates (example: 1,1) or the word quit:" << endl;
		cin >> s;
		cout << endl;
	}
	return QUIT;
}


//prints a single line with all the previous moves by the current player
void Game::printPlayerMoves(){
	cout << "Player " << getPlayer() << ": ";
	for (unsigned int i = FIRST_COLUMN; i < getHeight() - 1; i++){
		for (unsigned int j = FIRST_ROW; j < getWidth() - 1; j++){
			if (getPiece(i, j).img == getPlayer()){
				cout << "(" << j << "," << i << ") ";
			}
		}
	}
}

//keeps playing the game until a draw/win/quit
int Game::play(){
	print();
	unsigned int maxMoves = (getWidth() - PADDING)*(getHeight() - PADDING);
	while (true){
		cout << endl;

		//check if any player has won
		if (done()){
			cout << endl << "Player " << getPlayer() << " wins" << endl << "Game Over" << endl;
			return SUCCESS;
		}

		//check if the game is a draw
		switchPlayer();

		if (stalemate() ||  moves >= maxMoves){
			printPlayerMoves(); //displays other players move
			cout << endl << endl << "There are "<< (maxMoves-moves) <<" possible moves left. The game is tied." << endl << "Game Over" << endl;
			return DRAW_GAME;
		}
		cout << "_______________________" << endl << endl << "There are " << (maxMoves - moves) << " moves left." << endl << endl;
		
		//checks if player has quit
		if (turn() == QUIT){
			cout << "Player " << getPlayer() << " has quit the game with " << (maxMoves - moves) << " moves remaining." << endl << "Game Over" << endl;
			return QUIT_GAME;
		}
	}
	return FAILURE;
}


//makes a derived class of Game as specified by command line argument
Game* Game::makeGame(int argc, char* argv[]){

	if (argc == MAX_COMMANDS){
		if (strcmp(argv[GAME_NAME], "TicTacToe") == 0){
			return new TicTacToe();
		}
		if (strcmp(argv[GAME_NAME], "Gomoku") == 0){
			return new Gomoku();
		}
	}
	else if (argc == OPTIONAL_1){
		if (strcmp(argv[GAME_NAME], "Gomoku") == 0){
			int dim;
			try{
				dim = stoi(argv[OPTIONAL_1 - 1]);
			}
			catch (invalid_argument& e){
				return 0;
			}
			if (dim > 1){
				return new Gomoku(dim);
			}
		}
	}
	else if (argc == OPTIONAL_2){
		if (strcmp(argv[GAME_NAME], "Gomoku") == 0){
			int dim, toWin;
			try{
				dim = stoi(argv[OPTIONAL_2 - 2]);
				toWin = stoi(argv[OPTIONAL_2 - 1]);
			}
			catch (invalid_argument& e){
				return 0;
			}
			if (dim >= 1 && toWin >2){
				return new Gomoku(dim, toWin);
			}
		}
	}
	return 0;
}