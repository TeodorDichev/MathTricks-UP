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

void randomlyPlaceOperation(char op, int val);
void printBoard(unsigned cols, unsigned rows);
void fillBoard(unsigned cols, unsigned rows);
void deleteBoardMemory(unsigned rows);
bool isMoveValid(unsigned x, unsigned y);
bool hasValidMoveForPlayer(unsigned x, unsigned y);
void playTurn(unsigned x, unsigned y);
void calculateScore(unsigned x, unsigned y, int& score);
int serializeLastTurn();
int deserializeLastGame();
