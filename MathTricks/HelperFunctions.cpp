/**
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

void printCentered(const char* text) {
    int length = 0;
    while (text[length]) {
        length++;
    }

    int padding = (CONSOLE_WIDTH - length) / 2;
    std::cout << std::setw(padding + length) << text;
}

unsigned getLength(const char* text) {
	if (!text)
		return 0;

	unsigned index = 0;

	while (text[index])
		index++;

	return index;
}

bool isDigit(char ch) {
	return '0' <= ch && ch <= '9';
}

unsigned stringToUnsignedInteger(const char* numberString) {
	if (!numberString) {
		return 0; // error value
	}

	unsigned result = 0;
	while (*numberString) {
		char ch = *numberString;
		if (!isDigit(ch)) {
			return 0; // error value
		}
		result *= 10;
		result += (ch - '0');
		numberString++;
	}

	return result;
}

