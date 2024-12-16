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
* Header: MathTricks User Interface Functions
*
*/

#include "UserInterface.h";
#include "Constants.h";
#include <iostream>;

void printCentered(const char* text) {
    int length = 0;
    while (text[length]) {
        length++;
    }

    int padding = (consoleWidth - length) / 2;
    std::cout << std::setw(padding + length) << text;
}

int getlen(const char* text) {
    int length = 0;
    while (text[length]) {
        length++;
    }
    return length;
}

void MathTricks() {
    printCentered("Welcome to MathTricks\n");
    printCentered("The game is created as a project for the course Introduction to Programming\n");
    printCentered("Press p to play and q to quit\n");

    std::cout << std::endl;

    char* input = new char[1024] ;

    do {
        printCentered(" ");

        std::cin.getline(input, 1024);

        if (getlen(input) != 1)
            printCentered("Invalid input, please try again\n");
        else if (*input == 'q') {
            delete[] input;
            return;
        }
        else if (*input == 'p') {
            delete[] input;
            return;
        }
        else
            printCentered("Invalid input, please try again\n");

        std::cin.clear();

    } while (*input != '\0');
}