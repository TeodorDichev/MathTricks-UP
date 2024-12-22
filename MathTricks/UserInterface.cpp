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
* Header: MathTricks User Interface Functions
*
*/

#include "UserInterface.h";


void mathTricks() {
    std::cout << "Welcome to MathTricks\n" <<
    "The game is created as a project for the course Introduction to Programming\n" <<
    "Press c to continue and q to quit\n";

    std::cout << std::endl;

    char input[MAX_SIZE]; // using static memory -> auto clear after method

    do {
        std::cin.getline(input, MAX_SIZE);
        std::cin.clear();

        if (getLength(input) != 1)
            std::cout << "Invalid input, please try again\n";
        else if (*input == QUIT_SYMBOL)
            return;
        else if (*input == CONTINUE_GAME_SYMBOL) {
            mainMenu();
            return;
        }
        else
            std::cout << "Invalid input, please try again\n";

    } while (true);
}

void mainMenu() {
    std::cout << std::endl;
    std::cout << "Main menu\n\n" <<
    "Press n for a new game, press c to continue, press q to quit\n" <<
    "The game is played using the numberPad:\n" <<
    "Press 1 to move down diagonally left\n" <<
    "Press 2 to move down\n" <<
    "Press 3 to move down diagonally right\n" <<
    "Press 4 to move left\n" <<
    "Press 6 to move right\n" <<
    "Press 7 to move up diagonally left\n" <<
    "Press 8 to move up\n" <<
    "Press 9 to move up diagonally right\n" <<
    "While playing press m to go back to the main menu\n\n";

    char input[MAX_SIZE]; // using static memory -> auto clear after method

    do {
        std::cin.getline(input, MAX_SIZE);
        std::cin.clear();

        if (getLength(input) != 1)
            std::cout << "Invalid input, please try again\n";
        else if (*input == QUIT_SYMBOL)
            return;
        else if (*input == NEW_GAME_SYMBOL) {
            newGameMenu();
            return;
        }
        else if (*input == CONTINUE_GAME_SYMBOL)
            return;
        else
            std::cout << "Invalid input, please try again\n";

    } while (true);
}

void newGameMenu() {
    std::cout << std::endl;
    system(CLEAR_CONSOLE_CMD);
    std::cout << "Enter grid dimensions [" << MIN_BOARD_SIZE << " - " << MAX_BOARD_SIZE << "] \n";

    char input[MAX_SIZE]; // using static memory -> auto clear after method

    do {
        std::cout << "Width: ";
        std::cin.getline(input, MAX_SIZE);
        std::cin.clear();
        unsigned width = myAtoi(input);

        std::cout << "Height: ";
        std::cin.getline(input, MAX_SIZE);
        std::cin.clear();
        unsigned height = myAtoi(input);

        if (width < MIN_BOARD_SIZE || width > MAX_BOARD_SIZE 
            || height < MIN_BOARD_SIZE || height > MAX_BOARD_SIZE)
            std::cout << "Invalid input, please try again\n";
        else
        {
            system(CLEAR_CONSOLE_CMD);
            fillBoard(width, height);
            printBoard(width, height);
            deleteBoardMemory(height);
            return;
        }

    } while (true);

}