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
* Header: MathTricks definitions of Helper Functions
*
*/

#pragma once

#include "Constants.h";

unsigned getLength(const char* text);
int charToDigit(char ch);
bool containsOnlyNumericalChars(const char* str);
unsigned myAtoi(const char* str);
int myStrCmp(const char* first, const char* second);