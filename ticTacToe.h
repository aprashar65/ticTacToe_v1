//Author: Amit Prashar

#ifndef _TICTACTOE_H
#define _TICTACTOE_H

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <algorithm>


class Game {
	
	enum Marker {
		none = '~',
		computer ='O',
		player = 'X'
	};

	enum Size {
		height = 3,
		width = 3
	};

	struct Move {
		int row = -1; 
		int col = -1;		
	};

	Marker gameBoard[Size::width][Size::height];

public:
	Game();
	std::string instructions();
	std::ostream& getTitle(std::ostream& os, std::string& name);
	void drawBoard(std::string name);
	void play();
	void getPlayerMove();
	bool isWin(Marker marker);
	bool isTie();
	void aiMove(Move& ai);
	int maxSearch();
	int minSearch();
};




#endif // !_TICTACTOE_H
