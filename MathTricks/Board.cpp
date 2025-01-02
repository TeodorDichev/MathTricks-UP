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

    // Fix: Allocate arrays with the correct dimensions (height x width)
    visited = new unsigned* [height];
    values = new unsigned* [height];
    operations = new char* [height];

    for (unsigned i = 0; i < height; ++i) {
        visited[i] = new unsigned[width]; // Allocate each row
        operations[i] = new char[width]; // Allocate each row
        values[i] = new unsigned[width]; // Allocate each row
    }

    // Initialize visited array with 0
    for (unsigned i = 0; i < height; ++i)
        for (unsigned j = 0; j < width; ++j)
            visited[i][j] = 0;

    // Corrected loop order and indexing to reflect proper dimensions
    for (unsigned y = 0; y < height; ++y) {  // y is height, going from top to bottom
        for (unsigned x = 0; x < width; ++x) { // x is width, going from left to right
            if (y == 0 && x == 0) {
                visited[y][x] = FIRST_PLAYER_COLOR;
                operations[y][x] = ' ';
                values[y][x] = 0;
                continue;
            }
            else if (y == height - 1 && x == width - 1) {
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
                    values[y][x] = std::rand() % ((width + height) / VALUE_DIVISOR) + 1; // So as to not have /0
            }
            else if (op == '-')
            {
                values[y][x] = std::rand() % ((width + height) / VALUE_DIVISOR) + 1; // So as to not have -0
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
                    values[y][x] = std::rand() % ((width + height) / VALUE_DIVISOR + 1);
            }
            else
            {
                values[y][x] = std::rand() % 10;
                addition = true;
            }
        }
    }
}

void printBoard(unsigned width, unsigned height) {
    system(CLEAR_CONSOLE_CMD);

    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j)
            std::cout << "+--+ ";

        std::cout << "\n";

        for (unsigned j = 0; j < width; ++j) {
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

    for (unsigned j = 0; j < width; ++j)
        std::cout << "+--+ ";
    std::cout << "\n";
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

bool isMoveValid(unsigned x, unsigned y) {
    // Directions for moving in 8 directions (horizontal, vertical, and diagonal)
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    unsigned currX = isFirstPlayer ? p1CurrCellX : p2CurrCellX;
    unsigned currY = isFirstPlayer ? p1CurrCellY : p2CurrCellY;

    // Check if the move is within bounds
    if (x >= boardWidth || y >= boardHeight) {
        return false;
    }

    // Check if the cell has already been visited
    if (visited[y][x] != 0) {
        return false;
    }

    // Check if the move is to an adjacent cell
    for (int i = 0; i < 8; ++i) {
        if (x == currX + dx[i] && y == currY + dy[i]) {
            return true;
        }
    }

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
        if (nx >= 0 && nx < boardWidth && ny >= 0 && ny < boardHeight && visited[ny][nx] == 0) {
            return true;
        }
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
    printBoard(boardWidth, boardHeight);
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
