#include <iostream>
#include "main.h"

using std::cout;
using std::cin;
using std::cerr;
using std::hex;
using std::endl;
using std::tolower;
using std::string;

// Some constants used for input option
const char errorCharacter = '!';
const char optionConnect = 'c';
const char optionDisplay = 'd';
const char optionExecute = 'e';
const char optionGo = 'g';
const char optionHelp = 'h';
const char optionLook = 'l';
const char optionModify = 'm';
const char optionReset = 'r';
const char optionStatus = 's';
const char optionQuit = 'q';

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
		// Display the application prompt
		displayApplicationPrompt();
		
		// Read user input
		userOption = inputOption();

		// Switch the user to the right option
		switchOption(userOption);

		// Display a newline character, just for decoration
		cout << endl;
		
	} while (userOption != 'q');
	
	// End the program
	return 0;
}

// Function optionErrorHandler()
// just display the error for the user
void optionErrorHandler(){
	cout << "Wrong option!" << endl
		 << "Type h for Help" << endl;
}

// Function switchOption()
// Switch user to the right option
void switchOption(char userOption){
	// Check the userOption variable and the switch the user to the right function
	switch (userOption){
	case optionConnect:
		cout << "Connect";
		break;
	case optionDisplay:
		cout << "Display";
		break;
	case optionExecute:
		cout << "Execute";
		break;
	case optionGo:
		cout << "Go";
		break;
	case optionHelp:
		optionHelpHandler();
		break;
	case optionLook:
		cout << "Look";
		break;
	case optionModify:
		cout << "Modify";
		break;
	case optionReset:
		cout << "Reset";
		break;
	case optionStatus:
		cout << "Status";
		break;
	case optionQuit:
		// If user want to quit, simply just quit this function
		return;
		break;
	default:
		optionErrorHandler();
		break;
	}
}

// Function displayConnectPrompt()
// Display the prompt when user connect to a microcontroller
void displayConnectPrompt(){
	
}

// Function optionHelpHandler()
// Display the help for user
void optionHelpHandler(){
	cout << "Help" << endl
		 << "Connect c" << endl
		 << "Display d" << endl;
}

// Function displayApplicationPrompt()
// Display the application prompt ">"
void displayApplicationPrompt(){
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
		return tolower(inputOption.at(0));
	}
	
}
