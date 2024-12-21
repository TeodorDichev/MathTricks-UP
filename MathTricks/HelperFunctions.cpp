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
* Header: MathTricks Helper Functions
*
*/

#include "HelperFunctions.h";

unsigned getLength(const char* text) {
	if (!text)
		return 0;

	unsigned index = 0;

	while (text[index])
		index++;

	return index;
}

int charToDigit(char ch) {
	if (ch >= '0' && ch <= '9')
		return ch - '0';

	return -1;
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

unsigned myAtoi(const char* str) {
	if (!str)
		return 0;

	unsigned int res = 0;

	if (!containsOnlyNumericalChars(str))
		return 0;

	while (*str)
	{
		res += charToDigit(*str);
		res *= 10;
		str++;
	}
	res /= 10;

	return res;
}
