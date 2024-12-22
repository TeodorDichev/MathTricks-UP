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

bool** visited;
char** operations;
unsigned** values;

unsigned p1CurrCellX;
unsigned p1CurrCellY;
unsigned p2CurrCellX;
unsigned p2CurrCellY;

void fillBoard(unsigned width, unsigned height) {
    bool addition = false , subtraction = false, multByZero = false, multByTwo = false, divByTwo = false;
    p1CurrCellX = 0;
    p1CurrCellY = 0;
    p2CurrCellX = width - 1;
    p2CurrCellY = height - 1;

    std::srand(std::time(0));

    visited = new bool * [height];
    operations = new char * [height];
    values = new unsigned * [height];

    for (unsigned i = 0; i < height; ++i) {
        visited[i] = new bool[width]; // Allocate each row
        operations[i] = new char[width]; // Allocate each row
        values[i] = new unsigned[width]; // Allocate each row
    }

    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            if ((i == 0 && j == 0) || (i == height - 1 && j == width - 1)) {
                visited[i][j] = true;
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
        // Top border
        for (unsigned j = 0; j < width; ++j)
            std::cout << "+--+ ";

        std::cout << "\n";

        // Content
        for (unsigned j = 0; j < width; ++j) {
            std::cout << "|";

            HANDLE  hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            if (i == p1CurrCellX && j == p1CurrCellY)
            {
                SetConsoleTextAttribute(hConsole, 1);
                std::cout << operations[i][j];
                std::cout << values[i][j];
                SetConsoleTextAttribute(hConsole, 15);
            }
            else if (i == p2CurrCellX && j == p2CurrCellY)
            {
                SetConsoleTextAttribute(hConsole, 2);
                std::cout << operations[i][j];
                std::cout << values[i][j];
                SetConsoleTextAttribute(hConsole, 15);
            }
            else 
            {
                std::cout << operations[i][j];
                std::cout << values[i][j];
            }

            std::cout << "| ";
        }

        std::cout << "\n";
    }

    // Bottom border
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