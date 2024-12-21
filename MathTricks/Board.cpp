/**
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

void drawBoard(unsigned width, unsigned height){

    // Dynamically allocate a 2D array
    char ** grid = new char* [height];
    for (unsigned i = 0; i < height; ++i) {

        grid[i] = new char[width];
        for (unsigned j = 0; j < width; ++j)
            grid[i][j] = ' '; 
    }

    // Draw the grid
    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j)
            std::cout << "+--+ ";

        std::cout << "\n";

        // Draw the content for each cell
        for (unsigned j = 0; j < width; ++j) {
            std::cout << "|";
            std::cout << std::setw(2) << grid[i][j];// TO REPLACE WITH SING + NUMBER 
            std::cout << "| ";
        }
        std::cout << "\n";
    }

    // Draw the bottom border for the last row
    for (unsigned j = 0; j < width; ++j)
        std::cout << "+--+ ";
    std::cout << "\n";

    // Deallocate memory
    for (unsigned i = 0; i < height; ++i)
        delete[] grid[i];
    delete[] grid;
}
