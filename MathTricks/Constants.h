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
* Header: MathTricks constants
*
*/

#pragma once

constexpr unsigned MAX_SIZE_INPUT = 1024;
constexpr unsigned MAX_BOARD_SIZE = 12;
constexpr unsigned MIN_BOARD_SIZE = 4;
constexpr unsigned VALUE_DIVISOR = 3;

constexpr unsigned FIRST_PLAYER_COLOR = 4;
constexpr unsigned SECOND_PLAYER_COLOR = 1;
constexpr unsigned DEFAULT_COLOR = 15;

constexpr char QUIT_SYMBOL = 'q';
constexpr char NEW_GAME_SYMBOL = 'n';
constexpr char CONTINUE_GAME_SYMBOL = 'c';
constexpr char MAIN_MENU_SYMBOL = 'm';
constexpr char TERMINATE_SYMBOL = '\0';
constexpr char ERROR_MESSAGE[] = "Invalid input! Please try again\n";
constexpr char CLEAR_CONSOLE_CMD[] = "cls";

// Adjust as needed to change operation appearance in board
constexpr char possibleOperations[] = { '+', '+', '+', '+', '-', '-', '*', '/' };
constexpr unsigned possibleOperationsSize = 8;