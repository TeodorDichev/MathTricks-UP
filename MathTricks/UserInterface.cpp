/*
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Teodor Dichev
* @idnumber 7MI0600424
* @compiler VC
*
* Header: MathTricks User Interface Functions
*
*/

#include "UserInterface.h";


void mathTricks() {
	std::cout << "Welcome to MathTricks\n" <<
		"The game is created as a project for the course Introduction to Programming\n" <<
		"Press c to continue and q to quit\n";

	std::cout << std::endl;

	char input[MAX_SIZE]; // using static memory -> auto clear after method

	do {
		std::cin.getline(input, MAX_SIZE);
		std::cin.clear();

		if (getLength(input) != 1)
			std::cout << "Invalid input, please try again\n";
		else if (*input == QUIT_SYMBOL)
			return;
		else if (*input == CONTINUE_GAME_SYMBOL) {
			mainMenu();
			return;
		}
		else
			std::cout << "Invalid input, please try again\n";

	} while (true);
}

void mainMenu() {
	std::cout << std::endl;
	std::cout << "Main menu\n\n" <<
		"Press n for a new game, press c to continue, press q to quit.\n" <<
		"The game is played by entering the coordinates of the tile you want to move to.\n" <<
		"The game finishes when one of the players has no more valid moves.\n" <<
		"The player with the greater score is the winner. Good luck!\n\n";

	char input[MAX_SIZE]; // using static memory -> auto clear after method

	do {
		std::cin.getline(input, MAX_SIZE);
		std::cin.clear();

		if (getLength(input) != 1)
			std::cout << "Invalid input, please try again\n";
		else if (*input == QUIT_SYMBOL)
			return;
		else if (*input == NEW_GAME_SYMBOL) {
			newGameMenu();
			return;
		}
		else if (*input == CONTINUE_GAME_SYMBOL)
		{
			newGameMenu(); // TO DO
			return;
		}
		else
			std::cout << "Invalid input, please try again\n";

	} while (true);
}

void newGameMenu() {
	std::cout << std::endl;
	system(CLEAR_CONSOLE_CMD);
	std::cout << "Enter grid dimensions [" << MIN_BOARD_SIZE << " - " << MAX_BOARD_SIZE << "] \n";

	char input[MAX_SIZE]; // using static memory -> auto clear after method

	do {
		std::cout << "Width: ";
		std::cin.getline(input, MAX_SIZE);
		std::cin.clear();
		unsigned width = myAtoi(input);

		std::cout << "Height: ";
		std::cin.getline(input, MAX_SIZE);
		std::cin.clear();
		unsigned height = myAtoi(input);

		if (width < MIN_BOARD_SIZE || width > MAX_BOARD_SIZE
			|| height < MIN_BOARD_SIZE || height > MAX_BOARD_SIZE)
			std::cout << "Invalid input, please try again\n";
		else
		{
			system(CLEAR_CONSOLE_CMD);
			fillBoard(width, height);
			printBoard(width, height);
			deleteBoardMemory(height);
			return;
		}

	} while (true);

}

void printNextTurn(unsigned p1CurrCellX, unsigned p1CurrCellY, int p1CurrScore,
	unsigned p2CurrCellX, unsigned p2CurrCellY, int p2CurrScore, bool isFirstPlayer) {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
	std::cout << "Player 1 is currently on [" << p1CurrCellX << ", " << p1CurrCellY
		<< "], and has " << p1CurrScore << " points\n";

	SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
	std::cout << "Player 2 is currently on [" << p2CurrCellX << ", " << p2CurrCellY
		<< "], and has " << p2CurrScore << " points\n";

	char input[MAX_SIZE];
	unsigned x, y;
	if (isFirstPlayer) {
		SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
		std::cout << "Waiting for player 1...\n";
	}
	else {
		SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
		std::cout << "Waiting for player 2...\n";
	}

	std::cout << "X: ";
	std::cin.getline(input, MAX_SIZE);
	x = myAtoi(input);
	std::cin.clear();

	std::cout << "Y: ";
	std::cin.getline(input, MAX_SIZE);
	y = myAtoi(input);
	std::cin.clear();

	// Repeat until valid move
	while (!isValidMove(x, y))
	{
		std::cout << "Invalid input, please try again\n";

		std::cout << "X: ";
		std::cin.getline(input, MAX_SIZE);
		x = myAtoi(input);
		std::cin.clear();

		std::cout << "Y: ";
		std::cin.getline(input, MAX_SIZE);
		y = myAtoi(input);
		std::cin.clear();
	}

	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
	playTurn(x, y);
}

void printWinScreen(int p1CurrScore, int p2CurrScore) {
	return;
}