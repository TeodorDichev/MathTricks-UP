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
* Header: MathTricks constants
*
*/

#pragma once

constexpr unsigned MAX_SIZE = 1024;

constexpr char QUIT_SYMBOL = 'q';
constexpr char NEW_GAME_SYMBOL = 'n';
constexpr char CONTINUE_GAME_SYMBOL = 'c';
constexpr char MAIN_MENU_SYMBOL = 'm';
constexpr char TERMINATE_SYMBOL = '\0';

constexpr char CLEAR_CONSOLE_CMD[] = "cls";

// Adjust as needed to change operation appearance in board
constexpr char possibleOperations[] = { '+', '+', '+', '-', '*', '/' };
constexpr unsigned possibleOperationsSize = 6;