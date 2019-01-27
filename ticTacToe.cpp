//Author: Amit Prashar

#include "ticTacToe.h"

Game::Game() {
	for (int row = 0; row < Size::width; row++) {
		for (int col = 0; col < Size::height; col++) {
			gameBoard[row][col] = Marker::none;
		}
	}
}

std::string Game::instructions() {
	std::string name;
	char ready = 0;
	std::cout << "hello and welcome to tic tac toe!" << '\n' << '\n';
	std::cout << "you will be playing as x!" << '\n';
	std::cout << "in order to make a move: " << '\n' << "\tplease enter a number to indicate the row followed by a letter to indicate the column." << '\n';
	std::cout << "\tnote: character must be Uppercase" << '\n';
	std::cout << "ready?? (y/n) ";
	std::cin >> ready;
	if (ready == 'y' || ready == 'y') {
		std::cout << "\tgreat! goodluck" << "\n\n";
	}
	else {
		std::cout << "\ttoo bad!!" << "\n\n";
	}
	
	std::cout << "Enter 10 Character Username to Continue: ";
	std::cin >> name;
	if (name.length() < 10) {
		name.resize(name.length());
	}
	else {
		name.resize(10);
	}
	return name;
}

std::ostream& Game::getTitle(std::ostream& os, std::string& name) {
	int length = name.length();
	int width = ((20 - (length+6)) / 2) + length;
	os << std::setw(width) << name << " VS AI\n\n";
	return os;
}

void Game::drawBoard(std::string name) {

	getTitle(std::cout, name);
	std::cout << std::setw(5) << "A" << std::setw(6) << "B" << std::setw(6) << "C" << '\n';
	std::cout << " +-----+-----+-----+" << '\n';
	std::cout << "0" << "|" << std::setw(3) << static_cast<char>(gameBoard[0][0]) << std::setw(3) << "|" << std::setw(3) << static_cast<char>(gameBoard[0][1]) << std::setw(3) << "|" << std::setw(3) << static_cast<char>(gameBoard[0][2]) << std::setw(3) << "|" << '\n';
	std::cout << " +-----+-----+-----+" << '\n';
	std::cout << "1" << "|" << std::setw(3) << static_cast<char>(gameBoard[1][0]) << std::setw(3) << "|" << std::setw(3) << static_cast<char>(gameBoard[1][1]) << std::setw(3) << "|" << std::setw(3) << static_cast<char>(gameBoard[1][2]) << std::setw(3) << "|" << '\n';
	std::cout << " +-----+-----+-----+" << '\n';
	std::cout << "2" << "|" << std::setw(3) << static_cast<char>(gameBoard[2][0]) << std::setw(3) << "|" << std::setw(3) << static_cast<char>(gameBoard[2][1]) << std::setw(3) << "|" << std::setw(3) << static_cast<char>(gameBoard[2][2]) << std::setw(3) << "|" << '\n';
	std::cout << " +-----+-----+-----+" << '\n' << '\n';
}

void Game::getPlayerMove() {
	int row = -1;
	char col = 0;
	bool end = false;

	do
	{
		std::cout << "Please Make a Valid Move: ";
		std::cin >> row >> col;
		if (std::cin.fail()) {
			std::cin.clear();
			row = -1;
			col = 0;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if (row < 0 || row > 2 || col < 'A' || col > 'C') {
			std::cout << "Invalid input please enter a valid coordinate!" << '\n';
		}
		else if(gameBoard[row][col-'A'] != Marker::none){
			std::cout << "Play a spot that has not been played!" << '\n';
		}
		else {
			end = true;
		}

	} while (!end);

	gameBoard[row][col - 'A'] = Marker::player;

}

bool Game::isWin(Marker marker) {
	bool isWin = false;
	
	for (int search = 0; search < Size::width; search++) {
		int compare = 0;

		//vertical win search by column and compare the rows
		if (gameBoard[compare][search] == marker && gameBoard[compare + 1][search] == marker && gameBoard[compare + 2][search] == marker)
			isWin = true;

		//horizontal win search by row and compare the columns
		if (gameBoard[search][compare] == marker && gameBoard[search][compare + 1] == marker && gameBoard[search][compare + 2] == marker)
			isWin = true;
	}

	int search{ 1 }, compare{ 1 };

	//diagonal win (0,0) (1,1) (2,2)
	if (gameBoard[search - 1][compare - 1] == marker && gameBoard[search][compare] == marker && gameBoard[search + 1][compare + 1] == marker)
		isWin = true;

	//diagonal win (0,2) (1,1) (2,0)
	if (gameBoard[search - 1][compare + 1] == marker && gameBoard[search][compare] == marker && gameBoard[search + 1][compare - 1] == marker)
		isWin = true;

	return isWin;
}

bool Game::isTie() {
	bool isTie = true;

	for (int row = 0; row < Size::width; row++) {
		for (int col = 0; col < Size::height; col++) {
			if (gameBoard[row][col] == Marker::none) {
				isTie = false;
			}
		}
	}

	return isTie;
}

void Game::aiMove(Game::Move& ai) {

	//goal is for the computer to get the highest possible score
	//Therefore; AI is Maximizer and Player is Minimizer
	//Thus; AI is maxsearch goal is score has to be maximized

	int score = std::numeric_limits<int>::min(); 

	for (int row = 0; row < Size::width; row++) {
		for (int col = 0; col < Size::height; col++) {
			if (gameBoard[row][col] == Marker::none) {
				
				gameBoard[row][col] = Marker::computer;

				int result = minSearch();

				if (result > score) {
					score = result;
					ai.row = row;
					ai.col = col;
				}

				gameBoard[row][col] = Marker::none;
			}
		}
	}

}

int Game::maxSearch() {
	
	if (isWin(Marker::player))
		return -10;
	else if (isWin(Marker::computer))
		return 10;
	else if (isTie())
		return 0;

	int score = std::numeric_limits<int>::min();

	for (int row = 0; row < Size::width; row++) {
		for (int col = 0; col < Size::height; col++) {
			if (gameBoard[row][col] == Marker::none) {

				gameBoard[row][col] = Marker::computer;
				score = std::max(score, minSearch()); 
				gameBoard[row][col] = Marker::none;
			}
		}
	}

	return score;
}

int Game::minSearch() {

	if (isWin(Marker::player))
		return -10;
	else if (isWin(Marker::computer))
		return 10;
	else if (isTie())
		return 0;

	int score = std::numeric_limits<int>::max();

	for (int row = 0; row < Size::width; row++) {
		for (int col = 0; col < Size::height; col++) {
			if (gameBoard[row][col] == Marker::none) {

				gameBoard[row][col] = Marker::player;
				score = std::min(score, maxSearch());
				gameBoard[row][col] = Marker::none;
			}
		}
	}

	return score;
}

void Game::play() {
	std::string name; 
	bool end = false;
	name = instructions();

	do
	{
		system("cls");
		drawBoard(name);
		getPlayerMove();	
		if (isWin(Marker::player)) {
			system("cls");
			drawBoard(name);
			std::cout << "\n\tYOU WIN!!!\n";
			end = true;
		}
		else if (isTie()) {
			system("cls");
			drawBoard(name);
			std::cout << "\n\tDRAW!!!\n";
			end = true;
		}
		else {
			Move ai;
			aiMove(ai);
			gameBoard[ai.row][ai.col] = Marker::computer;

			if (isWin(Marker::computer)) {
				system("cls");
				drawBoard(name);
				std::cout << "\n\tYOU LOSE!!!\n";
				end = true;
			}
		}

	} while (!end);

}
