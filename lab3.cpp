// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include "enums.h"
#include "Game.h"
#include "TicTacToe.h"
#include "Gomoku.h"



int usage(char * filename){		//provides user with correct input
	cout << "usage: " << filename << " GameName "  << "[boardDim] [piecesToWin]" << endl;
	return INPUT_NOT_VALID;
}


int main(int argc, char* argv[]){

	Game *g = Game::makeGame(argc, argv);

	shared_ptr<Game> p(g);

	if (g == 0){
		return usage(argv[FILE_NAME]);
	}

	return g->play();
}

