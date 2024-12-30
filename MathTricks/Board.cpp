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
* Header: MathTricks Board Functions
*
*/

#include "Board.h";

char** operations;
unsigned** visited;
unsigned** values;

unsigned boardWidth;
unsigned boardHeight;

unsigned p1CurrCellX;
unsigned p1CurrCellY;
unsigned p2CurrCellX;
unsigned p2CurrCellY;

int p1CurrScore;
int p2CurrScore;
bool isFirstPlayer;

void fillBoard(unsigned width, unsigned height) {
	bool addition = false, subtraction = false, multByZero = false, multByTwo = false, divByTwo = false;
	p1CurrCellX = 0;
	p1CurrCellY = 0;
	p2CurrCellX = width - 1;
	p2CurrCellY = height - 1;
	p1CurrScore = 0;
	p2CurrScore = 0;
	isFirstPlayer = true;
	boardWidth = width;
	boardHeight = height;

	std::srand(std::time(0));

	visited = new unsigned* [height];
	values = new unsigned* [height];
	operations = new char* [height];

	for (unsigned i = 0; i < height; ++i) {
		visited[i] = new unsigned[width]; // Allocate each row
		operations[i] = new char[width]; // Allocate each row
		values[i] = new unsigned[width]; // Allocate each row
	}

	for (unsigned i = 0; i < width; i++)
		for (unsigned j = 0; j < height; j++)
			visited[i][j] = 0;

	for (unsigned i = 0; i < height; ++i) {
		for (unsigned j = 0; j < width; ++j) {
			if (i == 0 && j == 0) {
				visited[i][j] = FIRST_PLAYER_COLOR;
				operations[i][j] = ' ';
				values[i][j] = 0;
				continue;
			}
			else if (i == height - 1 && j == width - 1) {
				visited[i][j] = SECOND_PLAYER_COLOR;
				operations[i][j] = ' ';
				values[i][j] = 0;
				continue;

			}

			char op = possibleOperations[std::rand() % possibleOperationsSize];
			operations[i][j] = op;

			if (op == '/')
			{
				if (!divByTwo) // Still random as div. cell is chosen randomly
				{
					values[i][j] = 2;
					divByTwo = true;
				}
				else
					values[i][j] = std::rand() % ((width + height) / VALUE_DIVISOR) + 1; // So as to not have /0
			}
			else if (op == '-')
			{
				values[i][j] = std::rand() % ((width + height) / VALUE_DIVISOR) + 1; // So as to not have -0
				subtraction = true;
			}
			else if (op == '*') // Still random as mult. cell is chosen randomly
			{
				if (!multByZero)
				{
					values[i][j] = 0;
					multByZero = true;
				}
				else if (!multByTwo)
				{
					values[i][j] = 2;
					multByTwo = true;
				}
				else
					values[i][j] = std::rand() % ((width + height) / VALUE_DIVISOR + 1);
			}
			else
			{
				values[i][j] = std::rand() % 10;
				addition = true;
			}
		}
	}
}

void printBoard(unsigned width, unsigned height) {

	for (unsigned i = 0; i < height; ++i) {

		for (unsigned j = 0; j < width; ++j)
			std::cout << "+--+ ";

		std::cout << "\n";

		for (unsigned j = 0; j < width; ++j) {
			std::cout << "|";

			HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if (visited[i][j])
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR + visited[i][j] * 16);

			if (i == p1CurrCellX && j == p1CurrCellY)
			{
				SetConsoleTextAttribute(hConsole, 6 + FIRST_PLAYER_COLOR * 16);
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}
			else if (i == p2CurrCellX && j == p2CurrCellY)
			{
				SetConsoleTextAttribute(hConsole, 6 + SECOND_PLAYER_COLOR * 16);
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}
			else
			{
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}

			SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
			std::cout << "| ";
		}

		std::cout << "\n";
	}

	for (unsigned j = 0; j < width; ++j)
		std::cout << "+--+ ";
	std::cout << "\n";

	printNextTurn(p1CurrCellX, p1CurrCellY, p1CurrScore, p2CurrCellX, p2CurrCellY, p2CurrScore, isFirstPlayer);
}

void deleteBoardMemory(unsigned height) {
	if (visited) {
		for (unsigned i = 0; i < height; ++i)
			delete[] visited[i];

		delete[] visited;
		visited = nullptr;
	}

	if (operations) {
		for (unsigned i = 0; i < height; ++i)
			delete[] operations[i];

		delete[] operations;
		operations = nullptr;
	}

	if (values) {
		for (unsigned i = 0; i < height; ++i)
			delete[] values[i];

		delete[] values;
		values = nullptr;
	}
}

bool isValidMove(unsigned x, unsigned y) {
	if (isFirstPlayer)
		return !(x > boardWidth || y > boardHeight || visited[x][y] || (x == p1CurrCellX && y == p1CurrCellY));
	else
		return !(x > boardWidth || y > boardHeight || visited[x][y] || (x == p2CurrCellX && y == p2CurrCellY));
}

// TO DO
bool noValidMoves() {
	return false;
}

void playTurn(unsigned x, unsigned y) {

	if (isFirstPlayer) {
		p1CurrCellX = x;
		p1CurrCellY = y;
		visited[x][y] = FIRST_PLAYER_COLOR;
		calculateScore(x, y, p1CurrScore);
	}
	else {
		p2CurrCellX = x;
		p2CurrCellY = y;
		visited[x][y] = SECOND_PLAYER_COLOR;
		calculateScore(x, y, p2CurrScore);

		// In order for the game to be fair we wait for the second player to complete their turn
		if (noValidMoves())
		{
			printWinScreen(p1CurrScore, p2CurrScore);
			return;
		}
	}

	isFirstPlayer = !isFirstPlayer;
	return;
}

void calculateScore(unsigned x, unsigned y, int& score) {
	switch (operations[x][y])
	{
	case '+':
		score += values[x][y];
		return;
	case '-':
		score -= values[x][y];
		return;
	case '*':
		score *= values[x][y];
		return;
	case '/':
		score /= values[x][y];
		return;
	default:
		return;
	}

}