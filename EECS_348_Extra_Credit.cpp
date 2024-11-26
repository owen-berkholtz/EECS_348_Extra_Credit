/*

- File Name: EECS_348_Extra_Credit
- Program: EECS 348 Extra Credit lab: Extracting double-precision numbers from strings

- Description: Program which repeatedly asks the user for a double floating point number then returns it to them as a number.
    Uses 2 functions: 'num_extractor' which convertes the user's string into the double float, and 'exponent' to help 'num_extractor'.
    Program handles errors well such as if the user's string contains characters.

- Author: Owen Berkholtz
- Date: 11/19/2024

- Please add the points to Test grade.

*/
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*

Helper function for 'num_extractor'. Calculates both positive and negative exponents

Input: 'base' = The number which is being multiplied by itself
       'power' = How many times the base number gets multiplied

Output: The result of the exponent power (base ^ power)

*/
double exponent(double base, int power) {
    //Check if the exponent is negative
	if (power < 0) {
		double result = 1; //Result is 1 to start with
        //Divide 1 by the base until power becomes 0
		for (int i = power; power < 0; power++) {
			result = result / base; //divide
		}
		return result; //return exponent
    //If the power is 0, then just return 1
	}
	if (power == 0) {
		return 1;
	}
    //If the power is 1, then return the base
	if(power == 1) {
		return base;
	}
    //Executes only if the power is 2 or greater
	else {
		double result = 1; //stores the final result
        //Multiply the base by itself 'power' times
		for (int i = 0; i < power; i++) {
			result = result * base;
		}
		return result; //return exponent answer
	}

}


/*

Function to take the string given by the user as an input and extracts the number from it.

Input: 'input' = The user's string

Output: The number as a double float number. If an error is raised, it returns -999999.99

*/
double num_extractor(string input) {

	double num = 0; // The final number which will be returned

	int cur_pos = 0; //The function's current position in the string

	int size = input.length(); //The length of the string

	int decimal_pos = 0; //The position of the decimal point in the string. Assumes it is at the start initially

	bool is_negative = false; //Used to check if the number is negative or not. Assumes it is not

    //Goes through the string and finds the position of the decimal place.
	for(decimal_pos; decimal_pos < size; decimal_pos++) {
		if (input[decimal_pos] == '.') {
			break;
		}
	}

    //Loop until the end of the string has been reached.
	while(cur_pos < size) {
        
		char pos = input[cur_pos]; //Stores the current character we are looking at

        //Check if the current character is a digit
		if (isdigit(pos)) {
			int digit = pos - '0'; //Convert the current character into an integer called 'digit'
			int pwr = (decimal_pos - cur_pos); //Calculates the current power to use depending upon the digits position in the number relative to the decimal point
			double add_digit = ( digit * exponent(10, pwr)); //The number which will be added to the final number

            //Correct add digit if the exponent is positive
			if (pwr > 0) {
				add_digit = add_digit/10;
			}
            //Add the number to the final one
			num = num+ add_digit;
            //Move the current position
			cur_pos++;
		}

        //Ignore the decimal point and move on.
		else if (pos == '.') {
			cur_pos++;
		}

        //Check if the character is a minus sign
		else if (pos == '-') {
			//If the minus sign is not in front of the number. Then return an error
			if(cur_pos != 0) {
				return -999999.99;
			}
			//If the minus sign is in front of the number. Then it is negative
			is_negative = true;
			cur_pos++;
		//If there is a plus sign in front of the number, then move on. Otherwise, return an error.
		}
		else if (pos == '+') {
			if(cur_pos != 0) {
				return -999999.99;
			}
			cur_pos++;
		
		//Return error for any other character.
		}
		else {
			return -999999.99;
		}
	}
	//If the number is negative, then subtract it from 0
	if (is_negative) {
	num = 0 - num;
}
//Return final number
return num;
}


//Main
int main()
{
	//Loop until the user decides to exit
	while (1) {
		string input; //String to store the user's input.

		//Prompts the user to input their string
		cout << "Please enter a String (enter 'END' to exit): ";
		cin >> input; //Recieve string

		//If the user types in 'END' then break the loop
		if (input == "END") {
			cout << "Goodbye :)";
			break;
		}

		double number = num_extractor(input); //Extract number

		//If there was no error, then return the extracted number.
		if (number != -999999.99){
		    cout << "The input is: "<<  fixed << setprecision(4)<< number << endl;
		}
		//Otherwise, say that there was an error
		else{
		    cout << "The input is Invalid!" << endl;
		}
	}
	return 0;
}