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

#include "Board.h"

char** operations;
unsigned** visited;
int** values;

unsigned boardCols;
unsigned boardRows;

unsigned p1CurrCellX;
unsigned p1CurrCellY;
unsigned p2CurrCellX;
unsigned p2CurrCellY;

int p1CurrScore;
int p2CurrScore;
bool isFirstPlayer;

void fillBoard(unsigned cols, unsigned rows) {
	bool addition = false, subtraction = false, multByZero = false, multByTwo = false, divByTwo = false;
	p1CurrCellX = 0;
	p1CurrCellY = 0;
	p2CurrCellX = cols - 1;
	p2CurrCellY = rows - 1;
	p1CurrScore = 0;
	p2CurrScore = 0;
	isFirstPlayer = true;
	boardCols = cols;
	boardRows = rows;

	std::srand(std::time(0));

	//Allocate arrays with the correct dimensions (cols x rows)
	visited = new unsigned* [rows];
	values = new int* [rows];
	operations = new char* [rows];

	for (unsigned i = 0; i < rows; ++i) {
		visited[i] = new unsigned[cols]; // Allocate each row
		operations[i] = new char[cols]; // Allocate each row
		values[i] = new int[cols]; // Allocate each row
	}

	for (unsigned i = 0; i < rows; ++i)
		for (unsigned j = 0; j < cols; ++j)
			visited[i][j] = 0;

	for (unsigned y = 0; y < rows; ++y) {
		for (unsigned x = 0; x < cols; ++x) {
			if (y == 0 && x == 0) {
				visited[y][x] = FIRST_PLAYER_COLOR;
				operations[y][x] = ' ';
				values[y][x] = 0;
				continue;
			}
			else if (y == rows - 1 && x == cols - 1) {
				visited[y][x] = SECOND_PLAYER_COLOR;
				operations[y][x] = ' ';
				values[y][x] = 0;
				continue;
			}

			char op = possibleOperations[std::rand() % possibleOperationsSize];
			operations[y][x] = op;

			if (op == '/')
			{
				if (!divByTwo) {
					values[y][x] = 2;
					divByTwo = true;
				}
				else
					values[y][x] = std::rand() % ((cols + rows) / VALUE_DIVISOR) + 1; // So as to not have /0
			}
			else if (op == '-')
			{
				values[y][x] = std::rand() % ((cols + rows) / VALUE_DIVISOR) + 1; // So as to not have -0
				subtraction = true;
			}
			else if (op == '*') {
				if (!multByZero)
				{
					values[y][x] = 0;
					multByZero = true;
				}
				else if (!multByTwo)
				{
					values[y][x] = 2;
					multByTwo = true;
				}
				else
					values[y][x] = std::rand() % ((cols + rows) / VALUE_DIVISOR + 1);
			}
			else
			{
				values[y][x] = std::rand() % 10;
				addition = true;
			}
		}
	}
}

void printBoard(unsigned cols, unsigned rows) {
	system(CLEAR_CONSOLE_CMD);

	for (unsigned i = 0; i < rows; ++i) {
		for (unsigned j = 0; j < cols; ++j)
			std::cout << "+--+ ";

		std::cout << "\n";

		for (unsigned j = 0; j < cols; ++j) {
			std::cout << "|";

			HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if (visited[i][j])
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR + visited[i][j] * 16);
			else
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

			if (i == p1CurrCellY && j == p1CurrCellX) {
				SetConsoleTextAttribute(hConsole, 6 + FIRST_PLAYER_COLOR * 16);
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}
			else if (i == p2CurrCellY && j == p2CurrCellX) {
				SetConsoleTextAttribute(hConsole, 6 + SECOND_PLAYER_COLOR * 16);
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}
			else {
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}

			SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
			std::cout << "| ";
		}

		std::cout << "\n";
	}

	for (unsigned j = 0; j < cols; ++j)
		std::cout << "+--+ ";
	std::cout << "\n";
}

void deleteBoardMemory(unsigned rows) {
	if (visited) {
		for (unsigned i = 0; i < rows; ++i)
			delete[] visited[i];

		delete[] visited;
		visited = nullptr;
	}

	if (operations) {
		for (unsigned i = 0; i < rows; ++i)
			delete[] operations[i];

		delete[] operations;
		operations = nullptr;
	}

	if (values) {
		for (unsigned i = 0; i < rows; ++i)
			delete[] values[i];

		delete[] values;
		values = nullptr;
	}
}

bool isMoveValid(unsigned x, unsigned y) {
	// Directions for moving in 8 directions (horizontal, vertical, and diagonal)
	int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

	unsigned currX = isFirstPlayer ? p1CurrCellX : p2CurrCellX;
	unsigned currY = isFirstPlayer ? p1CurrCellY : p2CurrCellY;

	if (x >= boardCols || y >= boardRows)
		return false;

	if (visited[y][x] != 0)
		return false;

	// Check if the move is to an adjacent cell
	for (int i = 0; i < 8; ++i)
		if (x == currX + dx[i] && y == currY + dy[i])
			return true;

	return false;
}

bool hasValidMoveForPlayer(unsigned x, unsigned y) {
	// Directions for moving in 8 directions (horizontal, vertical, and diagonal)
	int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

	for (int i = 0; i < 8; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		// Check if the neighboring cell is within bounds and not visited
		if (nx >= 0 && nx < boardCols && ny >= 0 && ny < boardRows && visited[ny][nx] == 0)
			return true;
	}
	return false;
}

void playTurn(unsigned x, unsigned y) {
	if (isFirstPlayer) {
		p1CurrCellX = x;
		p1CurrCellY = y;
		visited[y][x] = FIRST_PLAYER_COLOR;
		calculateScore(x, y, p1CurrScore);
	}
	else {
		p2CurrCellX = x;
		p2CurrCellY = y;
		visited[y][x] = SECOND_PLAYER_COLOR;
		calculateScore(x, y, p2CurrScore);
	}

	isFirstPlayer = !isFirstPlayer;
	serializeLastTurn();
	printBoard(boardCols, boardRows);
	printNextTurn(p1CurrCellX, p1CurrCellY, p1CurrScore, p2CurrCellX, p2CurrCellY, p2CurrScore, isFirstPlayer);
}

void calculateScore(unsigned x, unsigned y, int& score) {
	switch (operations[y][x]) {
	case '+':
		score += values[y][x];
		return;
	case '-':
		score -= values[y][x];
		return;
	case '*':
		score *= values[y][x];
		return;
	case '/':
		score /= values[y][x];
		return;
	default:
		return;
	}
}

int serializeLastTurn() {
	std::ofstream outputFile("lastGame.txt");
	if (outputFile.is_open()) {
		outputFile << "board\n";
		outputFile << boardCols << '\n';
		outputFile << boardRows << '\n';

		outputFile << "\nplayer1\n";
		outputFile << p1CurrCellX << '\n';
		outputFile << p1CurrCellY << '\n';
		outputFile << p1CurrScore << '\n';

		outputFile << "\nplayer2\n";
		outputFile << p2CurrCellX << '\n';
		outputFile << p2CurrCellY << '\n';
		outputFile << p2CurrScore << '\n';

		outputFile << "\nisFirstPlayer\n";
		outputFile << isFirstPlayer << '\n';

		outputFile << "\noperations\n";
		for (unsigned i = 0; i < boardRows; ++i) {
			for (unsigned j = 0; j < boardCols; ++j)
				outputFile << operations[i][j];
			outputFile << '\n';
		}

		outputFile << "\nvisited\n";
		for (unsigned i = 0; i < boardRows; ++i) {
			for (unsigned j = 0; j < boardCols; ++j)
				outputFile << visited[i][j];
			outputFile << '\n';
		}

		outputFile << "\nvalues\n";
		for (unsigned i = 0; i < boardRows; ++i) {
			for (unsigned j = 0; j < boardCols; ++j)
				outputFile << values[i][j];
			outputFile << '\n';
		}

		outputFile.close();
		return 0;
	}

	return -1;
}

int deserializeLastGame() {
	std::ifstream inputFile("lastGame.txt");
	char input[MAX_SIZE_INPUT]; // using static memory -> auto clear after method

	if (inputFile.is_open()) {
		while (inputFile.getline(input, MAX_SIZE_INPUT)) {
			if (!myStrCmp(input, "board")) {
				inputFile.getline(input, MAX_SIZE_INPUT);
				boardCols = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				boardRows = atoi(input);
			}
			if (!myStrCmp(input, "player1")) {
				inputFile.getline(input, MAX_SIZE_INPUT);
				p1CurrCellX = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p1CurrCellY = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p1CurrScore = atoi(input);
			}
			if (!myStrCmp(input, "player2")) {
				inputFile.getline(input, MAX_SIZE_INPUT);
				p2CurrCellX = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p2CurrCellY = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p2CurrScore = atoi(input);
			}
			if (!myStrCmp(input, "isFirstPlayer")) {
				inputFile.getline(input, MAX_SIZE_INPUT);
				isFirstPlayer = atoi(input);
			}
			if (!myStrCmp(input, "operations")) {
				operations = new char* [boardRows];

				for (unsigned i = 0; i < boardRows; ++i) {
					operations[i] = new char[boardCols]; // Allocate each row

					for (unsigned j = 0; j < boardCols; ++j) {
						char c = inputFile.get();
						while (c == '\n')
							c = inputFile.get();

						operations[i][j] = c;
					}
				}
			}
			if (!myStrCmp(input, "visited")) {
				visited = new unsigned* [boardRows];

				for (unsigned i = 0; i < boardRows; ++i) {
					visited[i] = new unsigned[boardCols]; // Allocate each row

					for (unsigned j = 0; j < boardCols; ++j) {
						char c = inputFile.get();
						while (c == '\n')
							c = inputFile.get();

						if (charToDigit(c) < 0) 
							return -1;
						else
							visited[i][j] = charToDigit(c);
					}
				}
			}
			if (!myStrCmp(input, "values")) {
				values = new int* [boardRows];

				for (unsigned i = 0; i < boardRows; ++i) {
					values[i] = new int[boardCols]; // Allocate each row

					for (unsigned j = 0; j < boardCols; ++j) {
						char c = inputFile.get();
						while (c == '\n')
							c = inputFile.get();

						values[i][j] = charToDigit(c);
					}
				}
			}
		}

		inputFile.close();
		printBoard(boardCols, boardRows);
		printNextTurn(p1CurrCellX, p1CurrCellY, p1CurrScore, p2CurrCellX, p2CurrCellY, p2CurrScore, isFirstPlayer);
		return 0;
	}
	else
		return -1;
}
