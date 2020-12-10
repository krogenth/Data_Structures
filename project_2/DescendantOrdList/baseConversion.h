#pragma once
//FileName : baseConversion.h 
//Author:Daniel Kelley
//Date 10/21/2019
//Purpose: To allow the conversion of decimal numbers to any base between 2 and 36
//
//**NOTE THE CLASS IS USED TO IMPLEMENT AN UNORDERED LIST. 
//       THE CLIENT INSERTS ITEMS AT THE END OF THE LIST BY INVOKING METHOD 
//			LastPosition() followed by NextPosition() before calling Insert().
//
//
//ASSUMPTIONS: That no one would be foolish enough to try to convert past base-36
//
//                       SUMMARY OF METHODS:
/*
char reVal(int num);									//
void strev(char *str);
char * fromDeci(char res[], int inputNum, int base);
*/

#include <string>
#include <cstring>
#include <math.h>

namespace std {

	namespace baseConv {

		char ValueToChar(int num);
		//returns the character equivalent of the given value
		//Pre: a value exists
		//Post: a character is returned to be added to the base-n number string

		void StringReverse(char *string);
		//reverses the given character array
		//Pre: a character array
		//Post: a character array is reversed

		char * FromDecimal(char result[], int inputNum, int base);
		//converts a decimal number to a given base-n number
		//Pre: a number and base-n have been decided
		//Post: a character array of the converted number is returned

	}

}