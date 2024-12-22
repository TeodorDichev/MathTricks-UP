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
bool ** visited;
char ** operations;
unsigned ** values;

void fillBoard(unsigned width, unsigned height) {

    unsigned opCounts[4] = { 0, 0, 0, 0 }; // Track counts of each operation

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
                values[i][j] = std::rand() % ((width + height) / 4) + 1;
            else if (op == '*')
                values[i][j] = std::rand() % ((width + height) / 4 + 1);
            else
                values[i][j] = std::rand() % 10;

            // Count operations
            for (int k = 0; k < 4; ++k) {
                if (op == possibleOperations[k]) {
                    opCounts[k]++;
                    break;
                }
            }
        }
    }

    // Check if there is a missing operation
    // It will not change anything on the player starting cell because there is no sign
    for (int k = 0; k < 4; ++k) {
        if (opCounts[k] == 0) {
            unsigned i = std::rand() % height;
            unsigned j = std::rand() % width;
            operations[i][j] = possibleOperations[k];
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
            std::cout << operations[i][j];     // Operation
            std::cout << values[i][j]; // Number
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