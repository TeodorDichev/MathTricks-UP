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


void MathTricks() {
    printCentered("Welcome to MathTricks\n");
    printCentered("The game is created as a project for the course Introduction to Programming\n");
    printCentered("Press c to continue and q to quit\n");

    std::cout << std::endl;

    char* input = new char[1024] ;

    do {
        printCentered(" ");

        std::cin.getline(input, 1024);

        if (getLength(input) != 1)
            printCentered("Invalid input, please try again\n");
        else if (*input == QUIT_SYMBOL) {
            delete[] input;
            return;
        }
        else if (*input == CONTINUE_GAME_SYMBOL) {
            delete[] input;
            mainMenu();
            return;
        }
        else
            printCentered("Invalid input, please try again\n");

        std::cin.clear();

    } while (*input != '\0');
}

void mainMenu() {
    std::cout << std::endl;
    printCentered("Main menu\n");
    printCentered("Press n for a new game, press c to continue, press q to quit\n");
    printCentered("The game is played using the numberPad:\n");
    printCentered("Press 1 to move down diagonally left\n");
    printCentered("Press 2 to move down\n");
    printCentered("Press 3 to move down diagonally right\n");
    printCentered("Press 4 to move left\n");
    printCentered("Press 6 to move right\n");
    printCentered("Press 7 to move up diagonally left\n");
    printCentered("Press 8 to move up\n");
    printCentered("Press 9 to move up diagonally right\n");
    printCentered("While playing press m to go back to the main menu\n");

    std::cout << std::endl;

    char* input = new char[1024];

    do {
        printCentered(" ");

        std::cin.getline(input, 1024);

        if (getLength(input) != 1)
            printCentered("Invalid input, please try again\n");
        else if (*input == QUIT_SYMBOL) {
            delete[] input;
            return;
        }
        else if (*input == NEW_GAME_SYMBOL) {
            delete[] input;
            newGameMenu();
            return;
        }
        else if (*input == CONTINUE_GAME_SYMBOL) {
            delete[] input;
            return;
        }
        else
            printCentered("Invalid input, please try again\n");

        std::cin.clear();

    } while (*input != '\0');
}

void newGameMenu() {
    std::cout << std::endl;
    system("cls");
    printCentered("Enter grid dimensions [4 - 16]");

    char* input = new char[1024];

    do {
        printCentered("Width: ");

        std::cin.getline(input, 1024);

        if (getLength(input) < 1 && getLength(input) > 2)
            printCentered("Invalid input, please try again\n");
        else
            printCentered("Invalid input, please try again\n");

        std::cin.clear();

    } while (*input != '\0');

}