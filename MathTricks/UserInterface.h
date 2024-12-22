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
* Header: MathTricks definitions of User Interface Functions
*
*/

#pragma once

#include <iostream>
#include <iomanip>
#include "Constants.h"
#include "HelperFunctions.h"
#include "Board.h"

void mathTricks();
void mainMenu();
void newGameMenu();
void printNextTurn(unsigned p1CurrCellX, unsigned p1CurrCellY, int p1CurrScore,
    unsigned p2CurrCellX, unsigned p2CurrCellY, int p2CurrScore, bool isFirstPlayer);