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
* Header: MathTricks Helper Functions
*
*/

#include "HelperFunctions.h";

int charToDigit(char ch) {
	if (ch >= '0' && ch <= '9')
		return ch - '0';

	return -1;
}

double myAbs(double number) {
	return (number < 0) ? -number : number;
}

int myAtoi(const char* str) {
	if (!str)
		return -1;

	unsigned int res = 0;

	if (!containsOnlyNumericalChars(str))
		return -1;

	while (*str)
	{
		res += charToDigit(*str);
		res *= 10;
		str++;
	}
	res /= 10;

	return res;
}

double mySqrt(double number)
{
	// for 0 and 1, the square roots are themselves
	if (number < 2)
		return number;

	double y = number;
	double z = (y + (number / y)) / 2;

	double epsilon = 1e-6; // Precision
	while (myAbs(y - z) >= epsilon) {
		y = z;
		z = (y + (number / y)) / 2;
	}

	return z;
}

unsigned getLength(const char* text) {
	if (!text)
		return 0;

	unsigned index = 0;

	while (text[index])
		index++;

	return index;
}

unsigned myPow(unsigned base, unsigned power) {
	unsigned result = 1;
	for (int i = 0; i < power; i++)
		result *= base;

	return result;
}

int myStrCmp(const char* str1, const char* str2) {
	while (*str1 && *str2) {
		if (*str1 == ' ' || *str1 == '\n') {
			++str1;
			continue;
		}
		if (*str2 == ' ' || *str2 == '\n') {
			++str2;
			continue;
		}

		if (*str1 != *str2)
			return *str1 - *str2;

		++str1;
		++str2;
	}

	return *str1 - *str2;
}

bool containsOnlyNumericalChars(const char* str) {
	if (!str)
		return false;

	while (*str) {
		if (*str > '9' || *str < '0')
			return false;

		str++;
	}

	return true;

}

// Function using Euclidean distance to calculate the proximity to the center
unsigned euclideanProxiScore(unsigned currRow, unsigned currCol, unsigned rows, unsigned cols) {
	// Center of the matrix
	double centerRow = (rows - 1) / 2.0;
	double centerCol = (cols - 1) / 2.0;

	// Euclidean distance from the point to the center
	double distance = mySqrt(myPow(currRow - centerRow, 2) + myPow(currCol - centerCol, 2));

	// Maximum possible distance (from center to farthest corner)
	double maxDistance = mySqrt(myPow(centerRow, 2) + myPow(centerCol, 2));

	// Scale the score: max at center (2) to min at corners (0)
	double score = PROXIMITY_SCORE_MULTIPLYER * (PROXIMITY_SCORE_CONSTANT - (distance / maxDistance));

	return (unsigned) score;
}
