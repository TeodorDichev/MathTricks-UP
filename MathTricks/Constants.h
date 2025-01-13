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

constexpr unsigned VALUE_DIVISOR = 8;
constexpr unsigned MIN_BOARD_SIZE = 4;
constexpr unsigned MAX_BOARD_SIZE = 12;
constexpr unsigned MAX_SIZE_INPUT = 1024;

constexpr unsigned DEFAULT_COLOR = 15;
constexpr unsigned FIRST_PLAYER_COLOR = 4;
constexpr unsigned SECOND_PLAYER_COLOR = 1;

constexpr char QUIT_SYMBOL = 'q';
constexpr char NEW_GAME_SYMBOL = 'n';
constexpr char MAIN_MENU_SYMBOL = 'm';
constexpr char TERMINATE_SYMBOL = '\0';
constexpr char CONTINUE_GAME_SYMBOL = 'c';
constexpr char CLEAR_CONSOLE_CMD[] = "cls";
constexpr char ERROR_MESSAGE[] = "Invalid input! Please try again\n";

constexpr char ADD_SYMBOL = '+';
constexpr char SUB_SYMBOL = '-';
constexpr char MUL_SYMBOL = 'x';
constexpr char DIV_SYMBOL = '/';

// Adjust as needed to change operation appearance in board
// possibleOperationsSize must be equal to possibleOperations[] length
constexpr unsigned possibleOperationsSize = 8;

// Must be above 1
constexpr double PROXIMITY_SCORE_CONSTANT = 1.2;

// Set up so as to not overflow numbers over 10
constexpr double PROXIMITY_SCORE_MULTIPLYER = 2.4;
constexpr char possibleOperations[] = { ADD_SYMBOL, ADD_SYMBOL, ADD_SYMBOL, ADD_SYMBOL, 
										SUB_SYMBOL, SUB_SYMBOL, MUL_SYMBOL, DIV_SYMBOL };
