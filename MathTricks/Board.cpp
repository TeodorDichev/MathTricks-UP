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
char ** board;

void drawBoard(unsigned width, unsigned height){
    unsigned opCounts[4] = { 0, 0, 0, 0 }; // Track counts of each operation

    // Seed random generator
    std::srand(std::time(0));

    // Allocate the grid
    board = new char* [height];
    for (unsigned i = 0; i < height; ++i)
        board[i] = new char[width * 2]; // 2 characters per cell (operation and number) ADJUST IF NEEDED

    // Fill the grid
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            if ((i == 0 && j == 0) || (i == height - 1 && j == width - 1)) {
                board[i][j * 2] = ' ';
                board[i][j * 2 + 1] = ' ';
                continue;
            }

            // Randomly select an operation
            char op = operations[std::rand() % 4];

            // Prioritize smaller numbers for * and /
            unsigned num = (op == '*' || op == '/') ? 
                (std::rand() % ((width + height) / 4)) : // is * or /
                (std::rand() % 10); // is + or -

            // Store operation and number in the grid
            board[i][j * 2] = op;             // Operation
            board[i][j * 2 + 1] = num + '0';  // Number as a character

            // Count operations
            for (int k = 0; k < 4; ++k) {
                if (op == operations[k]) {
                    opCounts[k]++;
                    break;
                }
            }
        }
    }

    // Ensure at least one of each operation is present
    for (int k = 0; k < 4; ++k) {
        if (opCounts[k] == 0) {
            // Randomly place the missing operation in the grid
            unsigned i = std::rand() % height;
            unsigned j = std::rand() % width;
            board[i][j * 2] = operations[k];
        }
    }

    // Draw the grid
    for (unsigned i = 0; i < height; ++i) {
        // Top border
        for (unsigned j = 0; j < width; ++j)
            std::cout << "+--+ ";

        std::cout << "\n";

        // Content
        for (unsigned j = 0; j < width; ++j) {
            std::cout << "|";
            std::cout << board[i][j * 2];     // Operation
            std::cout << board[i][j * 2 + 1]; // Number
            std::cout << "| ";
        }

        std::cout << "\n";
    }

    // Bottom border
    for (unsigned j = 0; j < width; ++j)
        std::cout << "+--+ ";
    std::cout << "\n";

    // Deallocate the grid
    for (unsigned i = 0; i < height; ++i)
        delete[] board[i];
    delete[] board;
}
