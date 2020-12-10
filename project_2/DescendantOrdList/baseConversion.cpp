//Daniel Kelley
//File: baseConversion.cpp
//Date: 10/21/2019
//Purpose: To help convert a decimal number to any base 2 through 36

#include "baseConversion.h"

namespace std {

	namespace baseConv {

		char ValueToChar(int num) {

			if (num >= 0 && num <= 9)
				return (char)(num + '0');
			else
				return (char)(num - 10 + 'A');

		}

		void StringReverse(char *string) {

			for (int i = 0; i < strlen(string) / 2; i++) {

				//for each iteration, we want (n) and ((length - 1) - n) swapped
				char temp = string[i];
				string[i] = string[strlen(string) - i - 1];
				string[strlen(string) - i - 1] = temp;

			}

		}

		char * FromDecimal(char result[], int inputNum, int base) {

			int index = 0;

			if (inputNum == 0)
				result[index++] = '0';

			while (inputNum > 0) {

				//call ValueToChar with the remainder of (input / base)
					//this tells us what the value of each digit is(this is done in reverse order)
				result[index++] = ValueToChar(inputNum % base);
				inputNum /= base;

			}
			result[index] = '\0';

			// Reverse the result
			StringReverse(result);

			return result;

		}

	}

}