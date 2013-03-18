#include <iostream>
#include "main.h"

using std::cout;
using std::cin;
using std::cerr;
using std::hex;
using std::endl;
using std::tolower;
using std::string;

const char errorCharacter = '!';

// Function main()
// Main executable
int main(int argc, char *argv[])
{
	// VARIABLES USED FOR THIS PROGRAM
	// userOption: stores the user option. The program must handle both
	// upperand lowercase so that this variable will save only lowercase value.
	// The program have to change it to lowercase before saving
	char userOption;

	// Start the program
	// Loop for user enter option until user enter 'q' or 'Q'
	do
	{
		// Display the prompt
		displayPrompt();
		
		// Read user input
		userOption = inputOption();

		// Switch the user to the right option
		switchOption(userOption);
		
	} while (userOption != 'q');
	
	// End the program
	return 0;
}

// Function switchOption()
// Switch user to the right option
void switchOption(char userOption){
	
}

// Function displayPrompt()
// Display the application promt ">"
void displayPrompt(){
	cout << ">" << " ";
}

// Function inputOption()
// Read from user input and then return the input value
// If error, return constant errorCharacter
char inputOption(){
	
	// inputOption: stores what the user types in. After that the program haves
	// to check. If the string length > 1 then ask the user to reinput.
	// Otherwise, get the first character and then put into the userOption
	// variable below
	string inputOption;

	// Read from user input
	cin >> inputOption;

	// Check the inputOption length, if it's greater than 1, return
	// errorCharacter
	if (inputOption.length() > 1)
	{
		return errorCharacter;
	} else {
		// If its length is 1, return the first character
		return inputOption.at(0);
	}
	
}
