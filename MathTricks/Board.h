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
* Header: MathTricks definitions of Board Functions
*
*/

#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>
#include "Constants.h";
#include "HelperFunctions.h";
#include "UserInterface.h";

void printBoard(unsigned width, unsigned height);
void fillBoard(unsigned width, unsigned height);
void deleteBoardMemory(unsigned height);
bool isMoveValid(unsigned x, unsigned y);
bool hasValidMoveForPlayer(unsigned x, unsigned y);
void playTurn(unsigned x, unsigned y);
void calculateScore(unsigned x, unsigned y, int& score);
