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
* Header: MathTricks User Interface Functions
*
*/

#include "UserInterface.h";

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

void mathTricks() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

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
            break;
        else if (*input == CONTINUE_GAME_SYMBOL) {
            std::cout << '\n';
            mainMenu();
            break;
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
        std::cout << "Rows: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        std::cin.clear();
        unsigned rows = myAtoi(input);

        std::cout << "Cols: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        std::cin.clear();
        unsigned cols = myAtoi(input);

        if (cols < MIN_BOARD_SIZE || cols > MAX_BOARD_SIZE
            || rows < MIN_BOARD_SIZE || rows > MAX_BOARD_SIZE)
            std::cout << ERROR_MESSAGE;
        else
        {
            system(CLEAR_CONSOLE_CMD);
            fillBoard(rows, cols);
            printBoard(rows, cols);
            serializeLastTurn(); // initial save
            printNextTurn(0, 0, 0, rows - 1, cols - 1, 0, true); // initial turn
            return;
        }
    } while (true);

}

// Freeing memory happens here ;)
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
    std::cin.clear();
    std::cin.ignore(); // to ignore the key so that mainMenu does not throw exception
    system(CLEAR_CONSOLE_CMD);
    // At the end of any game deleting board memory so as to not allow memory leaks
    deleteBoardMemory();
    mainMenu();
    return;
}

void printNextTurn(unsigned p1CurrRow, unsigned p1CurrCol, int p1CurrScore,
    unsigned p2CurrRow, unsigned p2CurrCol, int p2CurrScore, bool isFirstPlayer) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
    std::cout << "Player 1 is currently on [" << p1CurrRow << ", " << p1CurrCol
        << "], and has " << p1CurrScore << " points\n";

    SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
    std::cout << "Player 2 is currently on [" << p2CurrRow << ", " << p2CurrCol
        << "], and has " << p2CurrScore << " points\n";

    // In order for the game to be fair we wait for the second player to complete their turn if they have a valid move
    // The boolean fields are there for readability
    bool p1HasNoValidMoves = !hasValidMoveForPlayer(p1CurrRow, p1CurrCol);
    bool p2HasNoValidMoves = !hasValidMoveForPlayer(p2CurrRow, p2CurrCol);

    if ((p1HasNoValidMoves && p2HasNoValidMoves) 
        || (isFirstPlayer && p2HasNoValidMoves) 
        || (isFirstPlayer && p1HasNoValidMoves))
    {
        printWinScreen(p1CurrScore, p2CurrScore);
        return;
    }

    char input[MAX_SIZE_INPUT];
    unsigned row, col;
    if (isFirstPlayer) {
        SetConsoleTextAttribute(hConsole, FIRST_PLAYER_COLOR);
        std::cout << "Waiting for player 1...\n";
    }
    else {
        SetConsoleTextAttribute(hConsole, SECOND_PLAYER_COLOR);
        std::cout << "Waiting for player 2...\n";
    }

    std::cout << "Row: ";
    std::cin.getline(input, MAX_SIZE_INPUT);
    row = myAtoi(input);
    std::cin.clear();

    std::cout << "Col: ";
    std::cin.getline(input, MAX_SIZE_INPUT);
    col = myAtoi(input);
    std::cin.clear();

    // Repeat until valid move
    while (!isMoveValid(row, col))
    {
        std::cout << ERROR_MESSAGE;

        std::cout << "Row: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        row = myAtoi(input);
        std::cin.clear();

        std::cout << "Col: ";
        std::cin.getline(input, MAX_SIZE_INPUT);
        col = myAtoi(input);
        std::cin.clear();
    }

    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    playTurn(row, col);
}
