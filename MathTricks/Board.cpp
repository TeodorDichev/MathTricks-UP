/*
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
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

unsigned p1CurrRow;
unsigned p1CurrCol;
unsigned p2CurrRow;
unsigned p2CurrCol;

int p1CurrScore;
int p2CurrScore;
bool isFirstPlayer;

int serializeLastTurn() {
	std::ofstream outputFile("lastGame.txt");
	if (outputFile.is_open()) {
		outputFile << "board\n";
		outputFile << boardCols << '\n';
		outputFile << boardRows << '\n';

		outputFile << "\nplayer1\n";
		outputFile << p1CurrRow << '\n';
		outputFile << p1CurrCol << '\n';
		outputFile << p1CurrScore << '\n';

		outputFile << "\nplayer2\n";
		outputFile << p2CurrRow << '\n';
		outputFile << p2CurrCol << '\n';
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

void deleteBoardMemory() {
	if (visited) {
		for (unsigned i = 0; i < boardRows; ++i)
			delete[] visited[i];

		delete[] visited;
		visited = nullptr;
	}

	if (operations) {
		for (unsigned i = 0; i < boardRows; ++i)
			delete[] operations[i];

		delete[] operations;
		operations = nullptr;
	}

	if (values) {
		for (unsigned i = 0; i < boardRows; ++i)
			delete[] values[i];

		delete[] values;
		values = nullptr;
	}
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
				p1CurrRow = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p1CurrCol = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p1CurrScore = atoi(input);
			}
			if (!myStrCmp(input, "player2")) {
				inputFile.getline(input, MAX_SIZE_INPUT);
				p2CurrRow = atoi(input);
				inputFile.getline(input, MAX_SIZE_INPUT);
				p2CurrCol = atoi(input);
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
		printBoard(boardRows, boardCols);
		printNextTurn(p1CurrRow, p1CurrCol, p1CurrScore, p2CurrRow, p2CurrCol, p2CurrScore, isFirstPlayer);
		return 0;
	}
	else
		return -1;
}

void playTurn(unsigned row, unsigned col) {
	if (isFirstPlayer) {
		p1CurrRow = row;
		p1CurrCol = col;
		visited[row][col] = FIRST_PLAYER_COLOR;
		calculateScore(row, col, p1CurrScore);
	}
	else {
		p2CurrRow = row;
		p2CurrCol = col;
		visited[row][col] = SECOND_PLAYER_COLOR;
		calculateScore(row, col, p2CurrScore);
	}

	isFirstPlayer = !isFirstPlayer;
	serializeLastTurn();
	printBoard(boardRows, boardCols);
	printNextTurn(p1CurrRow, p1CurrCol, p1CurrScore, p2CurrRow, p2CurrCol, p2CurrScore, isFirstPlayer);
}

bool isMoveValid(unsigned row, unsigned col) {
	if (row < 0 || col < 0 || row >= boardRows || col >= boardCols)
		return false;

	if (visited[row][col] != 0)
		return false;

	// Directions for moving in 8 directions (horizontal, vertical, and diagonal)
	int drows[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dcols[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	unsigned currRow = isFirstPlayer ? p1CurrRow : p2CurrRow;
	unsigned currCol = isFirstPlayer ? p1CurrCol : p2CurrCol;

	// Check if the move is to an adjacent cell
	for (int i = 0; i < 8; ++i)
		if (row == currRow + drows[i] && col == currCol + dcols[i])
			return true;

	return false;
}

void fillBoard(unsigned rows, unsigned cols) {
	bool addition = false, subtraction = false, multByZero = false, multByTwo = false, divByTwo = false;
	p1CurrRow = 0;
	p1CurrCol = 0;
	p2CurrRow = rows - 1;
	p2CurrCol = cols - 1;
	p1CurrScore = 0;
	p2CurrScore = 0;
	isFirstPlayer = true;
	boardRows = rows;
	boardCols = cols;
	
	std::srand(std::time(0));

	// Memory initialization
	visited = new unsigned* [rows];
	values = new int* [rows];
	operations = new char* [rows];

	for (unsigned i = 0; i < rows; ++i) {
		visited[i] = new unsigned[cols];
		operations[i] = new char[cols];
		values[i] = new int[cols];
	}

	for (unsigned i = 0; i < rows; ++i)
		for (unsigned j = 0; j < cols; ++j) {
			visited[i][j] = 0;
			operations[i][j] = ' ';
			values[i][j] = 0;
		}

	visited[0][0] = FIRST_PLAYER_COLOR;
	visited[rows - 1][cols - 1] = SECOND_PLAYER_COLOR;

	// Seeding the necessary operation
	if (!addition) {
		randomlyPlaceOperation(ADD_SYMBOL, -1); // To place value correctly must know indexes
		addition = true;
	}
	if (!subtraction) {
		randomlyPlaceOperation(SUB_SYMBOL, -1); // To place value correctly must know indexes
		subtraction = true;
	}
	if (!divByTwo) {
		randomlyPlaceOperation(DIV_SYMBOL, 2);
		divByTwo = true;
	}
	if (!multByTwo) {
		randomlyPlaceOperation(MUL_SYMBOL, 2);
		multByTwo = true;
	}
	if (!multByZero) {
		randomlyPlaceOperation(MUL_SYMBOL, 0);
		multByZero = true;
	}

	// Seeding the rest of the operations
	for (unsigned i = 0; i < rows; ++i) {
		for (unsigned j = 0; j < cols; ++j) {

			char op = possibleOperations[std::rand() % possibleOperationsSize];
			if (operations[i][j] != ' ' || (i == 0 && j == 0) || (i == rows - 1 && j == cols - 1))
				continue;

			operations[i][j] = op;

			// Random values increased when approaching the center
			unsigned coefficient = (rows + cols) / VALUE_DIVISOR;
			if (op == ADD_SYMBOL)
				values[i][j] = (std::rand() % (coefficient + 1)) + coefficient * euclideanProxiScore(i, j, rows, cols);
			if (op == SUB_SYMBOL)
				values[i][j] = (std::rand() % (coefficient + 1)) + coefficient * euclideanProxiScore(i, j, rows, cols);
			if (op == DIV_SYMBOL)
				values[i][j] = (std::rand() % (coefficient + 1)) + euclideanProxiScore(i, j, rows, cols) + 1;
			if (op == MUL_SYMBOL)
				values[i][j] = (std::rand() % (coefficient + 1)) + euclideanProxiScore(i, j, rows, cols);
		}
	}
}

void randomlyPlaceOperation(char op, int val) {
	while (true) {
		unsigned randRow = std::rand() % boardRows;
		unsigned randCol = std::rand() % boardCols;

		if (operations[randRow][randCol] != ' ' || (randRow == 0 && randCol == 0) || (randRow == boardRows - 1 && randCol == boardCols - 1))
			continue;

		operations[randRow][randCol] = op;

		if (val == -1) {
			unsigned coefficient = (randRow + randCol) / VALUE_DIVISOR;
			values[randRow][randCol] = std::rand() % (coefficient + 1) + 
				coefficient * euclideanProxiScore(randRow, randCol, boardRows, boardCols);
		}
		else {
			values[randRow][randCol] = val;
		}

		break;
	}
}

void printBoard(unsigned rows, unsigned cols) {
	system(CLEAR_CONSOLE_CMD);

	std::cout << "   ";
	for (unsigned i = 0; i < cols; ++i) {
		if (i < 10)
			std::cout << " ";
		std::cout << i << ".  ";
	}

	std::cout << "\n";

	for (unsigned i = 0; i < rows; ++i) {
		std::cout << "   ";
		for (unsigned j = 0; j < cols; ++j)
			std::cout << "+--+ ";
		std::cout << "\n";

		if (i < 10)
			std::cout << " ";
		std::cout << i << ".";

		for (unsigned j = 0; j < cols; ++j) {
			std::cout << "|";

			HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			if (visited[i][j])
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR + visited[i][j] * 16);
			else
				SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

			if (i == p1CurrRow && j == p1CurrCol) {
				SetConsoleTextAttribute(hConsole, 6 + FIRST_PLAYER_COLOR * 16);
				std::cout << operations[i][j];
				std::cout << values[i][j];
			}
			else if (i == p2CurrRow && j == p2CurrCol) {
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

	std::cout << "   ";
	for (unsigned j = 0; j < cols; ++j)
		std::cout << "+--+ ";
	std::cout << "\n";
}

bool hasValidMoveForPlayer(unsigned row, unsigned col) {
	// Directions for moving in 8 directions (horizontal, vertical, and diagonal)
	int drows[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	int dcols[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int i = 0; i < 8; ++i) {
		int nrow = row + drows[i];
		int ncol = col + dcols[i];

		// Check if the neighboring cell is within bounds and not visited
		if (nrow >= 0 && nrow < boardRows && ncol >= 0 && ncol < boardCols && visited[nrow][ncol] == 0)
			return true;
	}
	return false;
}

void calculateScore(unsigned row, unsigned col, int& score) {
	switch (operations[row][col]) {
	case ADD_SYMBOL:
		score += values[row][col];
		return;
	case SUB_SYMBOL:
		score -= values[row][col];
		return;
	case MUL_SYMBOL:
		score *= values[row][col];
		return;
	case DIV_SYMBOL:
		score /= values[row][col];
		return;
	default:
		return;
	}
}
