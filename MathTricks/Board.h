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
* Header: MathTricks definitions of Board Functions
*
*/

#pragma once

#include <iostream> // for console manipulation
#include <fstream> // for file manipulation
#include <windows.h> // for color manipulation
#include "Constants.h";
#include "HelperFunctions.h";
#include "UserInterface.h";

int serializeLastTurn();
void deleteBoardMemory();
int deserializeLastGame();
void playTurn(unsigned row, unsigned col);
bool isMoveValid(unsigned row, unsigned col);
void fillBoard(unsigned cols, unsigned rows);
void randomlyPlaceOperation(char op, int val);
void printBoard(unsigned rows, unsigned cols);
bool hasValidMoveForPlayer(unsigned row, unsigned col);
void calculateScore(unsigned row, unsigned col, int& score);
