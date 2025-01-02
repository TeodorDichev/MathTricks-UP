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
        "Press c to continue and q to quit\n\n";

    char input[MAX_SIZE_INPUT]; // using static memory -> auto clear after method

    do {
        std::cin.getline(input, MAX_SIZE_INPUT);
        std::cin.clear();

        if (getLength(input) != 1)
            std::cout << ERROR_MESSAGE;
        else if (*input == QUIT_SYMBOL)
            return;
        else if (*input == CONTINUE_GAME_SYMBOL) {
            std::cout << '\n';
            mainMenu();
            return;
        }
        else
            std::cout << ERROR_MESSAGE;

    } while (true);
}

void mainMenu() {
    std::cout << "Main menu\n\n" <<
        "Press n for a new game, press c to continue last game, press q to quit.\n" <<
        "The game is played by entering the coordinates of the tile you want to move to.\n" <<
        "The game finishes when one of the players has no more valid moves.\n" <<
        "The player with the greater score is the winner. Good luck!\n\n";

    char input[MAX_SIZE_INPUT];

    do {
        std::cin.getline(input, MAX_SIZE_INPUT);
        std::cin.clear();

        if (getLength(input) != 1)
            std::cout << ERROR_MESSAGE;
        else if (*input == QUIT_SYMBOL)
            return;
        else if (*input == NEW_GAME_SYMBOL) {
            newGameMenu();
            return;
        }
        else if (*input == CONTINUE_GAME_SYMBOL)
        {
            if (deserializeLastGame() == -1)
                std::cout << "Unable to load last game\n";
            else return;
        }
        else
            std::cout << ERROR_MESSAGE;

    } while (true);
}

void newGameMenu() {
    std::cout << std::endl;
    system(CLEAR_CONSOLE_CMD);
    std::cout << "Enter grid dimensions [" << MIN_BOARD_SIZE << " - " << MAX_BOARD_SIZE << "] \n";

    char input[MAX_SIZE_INPUT];

    do {
        std::cout << "Cols: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        std::cin.clear();
        unsigned cols = myAtoi(input);

        std::cout << "Rows: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        std::cin.clear();
        unsigned rows = myAtoi(input);

        if (cols < MIN_BOARD_SIZE || cols > MAX_BOARD_SIZE
            || rows < MIN_BOARD_SIZE || rows > MAX_BOARD_SIZE)
            std::cout << ERROR_MESSAGE;
        else
        {
            system(CLEAR_CONSOLE_CMD);
            fillBoard(cols, rows);
            printBoard(cols, rows);
            serializeLastTurn(); // initial save
            printNextTurn(0, 0, 0, cols - 1, rows - 1, 0, true); // initial turn
            return;
        }

    } while (true);

}

void printNextTurn(unsigned p1CurrCellX, unsigned p1CurrCellY, int p1CurrScore,
    unsigned p2CurrCellX, unsigned p2CurrCellY, int p2CurrScore, bool isFirstPlayer) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
    std::cout << "Player 1 is currently on [" << p1CurrCellX << ", " << p1CurrCellY
        << "], and has " << p1CurrScore << " points\n";

    SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
    std::cout << "Player 2 is currently on [" << p2CurrCellX << ", " << p2CurrCellY
        << "], and has " << p2CurrScore << " points\n";

    // In order for the game to be fair we wait for the second player to complete their turn if they have a valid move
    if (!hasValidMoveForPlayer(p1CurrCellX, p1CurrCellY) || !hasValidMoveForPlayer(p2CurrCellX, p2CurrCellY) &&
        (isFirstPlayer || !hasValidMoveForPlayer(p2CurrCellX, p2CurrCellY))) {
        printWinScreen(p1CurrScore, p2CurrScore);
        return;
    }

    char input[MAX_SIZE_INPUT];
    unsigned x, y;
    if (isFirstPlayer) {
        SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
        std::cout << "Waiting for player 1...\n";
    }
    else {
        SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
        std::cout << "Waiting for player 2...\n";
    }

    std::cout << "X: ";
    std::cin.getline(input, MAX_SIZE_INPUT);
    x = myAtoi(input);
    std::cin.clear();

    std::cout << "Y: ";
    std::cin.getline(input, MAX_SIZE_INPUT);
    y = myAtoi(input);
    std::cin.clear();

    // Repeat until valid move
    while (!isMoveValid(x, y))
    {
        std::cout << ERROR_MESSAGE;

        std::cout << "X: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        x = myAtoi(input);
        std::cin.clear();

        std::cout << "Y: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        y = myAtoi(input);
        std::cin.clear();
    }

    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    playTurn(x, y);
}

void printWinScreen(int p1CurrScore, int p2CurrScore) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (p1CurrScore > p2CurrScore) {
        SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
        std::cout << "\nThe game has been won by player 1!\nPress any key to go back to the main menu!";
    }
    else if (p1CurrScore < p2CurrScore) {
        SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
        std::cout << "\nThe game has been won by player 2!\nPress any key to go back to the main menu!";
    }
    else {
        std::cout << "\nThe game is a tie! Press any key to go back to the main menu!";
    }

    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    char c;
    std::cin >> c;
    system(CLEAR_CONSOLE_CMD);
    mainMenu();
    return;
}
