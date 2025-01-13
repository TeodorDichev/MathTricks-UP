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
* Header: MathTricks definitions of Helper Functions
*
*/

#pragma once

#include "Constants.h";

int charToDigit(char ch);
double myAbs(double number);
int myAtoi(const char* str);
double mySqrt(double number);
unsigned getLength(const char* text);
unsigned myPow(unsigned base, unsigned power);
bool containsOnlyNumericalChars(const char* str);
int myStrCmp(const char* first, const char* second);
unsigned euclideanProxiScore(unsigned currRow, unsigned currCol, unsigned rows, unsigned cols);