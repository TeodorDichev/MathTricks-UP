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
* Header: MathTricks definitions of User Interface Functions
*
*/

#pragma once

#include <iostream> // for console manipulation
#include "Constants.h"
#include "HelperFunctions.h"
#include "Board.h"


void mainMenu();
void mathTricks();
void newGameMenu();
void printWinScreen(int p1CurrScore, int p2CurrScore);
void printNextTurn(unsigned p1CurrRow, unsigned p1CurrCol, int p1CurrScore,
    unsigned p2CurrRow, unsigned p2CurrCol, int p2CurrScore, bool isFirstPlayer);