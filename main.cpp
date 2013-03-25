#include <iostream>
#include <iomanip>

#include "main.h"
#include "microcontroller.h"
#include "mopsr500.h"
#include "macrochippic32f42.h"
#include "rotamola34hc22.h"

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

// Some constants for microcontroller type
const string controllerTypeR500 = "R500";
const string controllerTypePIC32F42 = "PIC32F42";
const string controllerType34HC22 = "34HC22";

// Other constants
const int memoryLocationInvalid = -1;

// Application namespace
using namespace mcontroller;

// Function main()
// Main executable
int main(int argc, char *argv[])
{
	// VARIABLES USED FOR THIS PROGRAM
	
	// userOption: stores the user option. The program must handle both
	// upperand lowercase so that this variable will save only lowercase value.
	// The program have to change it to lowercase before saving
	char userOption;

	// The Microcontroller of the program
	Microcontroller* microcontroller;

	
	// EXECUTION OF PROGRAM
	
	// Start the program
	// Loop for user enter option until user enter 'q' or 'Q'
	do
	{
		// Display the application prompt
		displayApplicationPrompt();
		
		// Read user input
		userOption = inputOption();

		// Check the userOption variable and the switch the user to the right function
		switchOption(userOption, &microcontroller);

		// Display a newline character, just for decoration
		cout << endl;
		
	} while (userOption != 'q');
	
	// End the program
	return 0;
}

// Function displayConnectPrompt()
// Display the prompt when user connect to a microcontroller
void displayConnectPrompt(){
	cout << "type? ";
}

// Function displayLocationPrompt()
// Display the prompt location
void displayLocationPrompt(){
	cout << "location? ";
}

// Function optionErrorHandler()
// just display the error for the user
void optionErrorHandler(){
	cout << "Wrong option!" << endl
		 << "Type h for Help" << endl;
}

// Function switchOption()
// Switch user to the right option
void switchOption(char userOption, Microcontroller** microcontroller){
	
	switch (userOption){
	case optionConnect:
		optionConnectHandler(microcontroller);
		break;
	case optionDisplay:
		optionDisplayAllMemoryHandler(microcontroller);
		break;
	case optionExecute:
		optionExecuteHandler(microcontroller);
		break;
	case optionGo:
		optionExecuteFromSpecificLocationHandler(microcontroller);
		break;
	case optionHelp:
		optionHelpHandler();
		break;
	case optionLook:
		optionLookAtMemoryHandler(microcontroller);
		break;
	case optionModify:
		optionModifyMemoryHandler(microcontroller);
		break;
	case optionReset:
		optionResetHandler(microcontroller);
		break;
	case optionStatus:
		cout << "Status";
		break;
	case optionQuit:
		// If user want to quit, simply just quit the function
		return;
		break;
	default:
		optionErrorHandler();
		break;
	}
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

// Function optionConnectHandler()
// Handler for connect option
// Display the prompt to ask user enter microcontroller type
// and then connect to that microcontroller
void optionConnectHandler(Microcontroller** microcontroller){

	// first free memory for the existing microcontroller
	delete *microcontroller;
	
	// display the prompt to ask user to enter microcontroller type
	cout << "Enter the type of microcontroller to connect" << endl;
	displayConnectPrompt();

	// read the microcontroller type from user
	string inputMicrocontrollerType;
	cin >> inputMicrocontrollerType;

	// check whether the user input is valid and then allocate new object
	if(inputMicrocontrollerType == controllerTypeR500){
		*microcontroller = new MopsR500();
	} else if (inputMicrocontrollerType == controllerTypePIC32F42){
		*microcontroller = new MacrochipPIC32F42();
	} else if (inputMicrocontrollerType == controllerType34HC22) {
		*microcontroller = new Rotamola34HC22();
		cout << controllerType34HC22 << " connected!\n";
	} else {
		// display the error message
		cout << "Invalid type!\n";
	}
}

// Function optionResetHandler()
// Handle reset option
// Reset the comtroller, simply just call the reset method of the input micrcontroller
void optionResetHandler(mcontroller::Microcontroller** microcontroller){
	(*microcontroller)->reset();
}

// Function optionLookAtMemoryHandler()
// Ask the user to input an address and output the value at that address
void optionLookAtMemoryHandler(mcontroller::Microcontroller** microcontroller){

	// the memory location the user input
	int location;
	
	// input memory location
	location = (*microcontroller)->lookUpMemoryAddress();

	// check if the input location is valid
	if(location >= 0){
		// print out the value at the memory address
		unsigned int value = (*microcontroller)->getMemoryValueAtLocation(location);
		cout << "The value at location ";
		cout << hex << location;
		cout << " is: ";
		cout << hex << value;
		cout << endl;
	}
}

// Handler for Modify Memory option
void optionModifyMemoryHandler(mcontroller::Microcontroller** microcontroller){

	// The input memory address
	int location;

	// input address from user
	location = (*microcontroller)->lookUpMemoryAddress();

	// check if the location is valid
	if(location != memoryLocationInvalid){
		// print the old value
		unsigned int oldValue = (*microcontroller)->getMemoryValueAtLocation(location);
		cout << "Old value: ";
		cout << hex << oldValue;
		cout << endl;

		// print the new prompt
		cout << "new? ";

		// read the input value from user
		unsigned int inputNewValue;
		// validate input
		while(!(cin >> hex >> inputNewValue)){
			cerr << "Please input a valid hexadecimal integer!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "news? ";
		}

		// As each memory location is a byte size (unsigned char), only the
		// lower 8 bits of input should be stored.
		unsigned char newValue = (inputNewValue & 0xFF);
		(*microcontroller)->setMemoryValueAtLocation(location, newValue);

		// clear the cin
		cin.clear();
		cin.ignore(1000, '\n');
	}
}

// handler for the display all memory option
void optionDisplayAllMemoryHandler(mcontroller::Microcontroller** microcontroller){

	// the memory array
	unsigned char* memory = (*microcontroller)->getMemory();

	// the memory size
	int memorySize = (*microcontroller)->getMemorySize();

	// loop through the memory array and display
	for (int i = 0; i < memorySize; ++i)
	{
		// special case: add new line and print the left-most value
		if((i % 16) == 0){
			cout << endl;
			cout << std::setfill('0') << std::setw(4);
			cout << hex << i;
			cin.clear();
		}

		// special case: current column is column 8, print one more extra space
		if((i % 8) == 0){
			cout << " ";
		}

		// normal case: print the value in that memory address
		cout << " ";
		cout << std::setfill('0') << std::setw(2);
		int value = memory[i];
		cout << hex << value;
		cin.clear();
	}

	cout << endl;
}

// handler for execute option
void optionExecuteHandler(mcontroller::Microcontroller** microcontroller){
	int inputOpcode;

	// input opcode
	cout << "opcode? ";
	// validate input
	while(!(cin >> hex >> inputOpcode)){
		cerr << "Please input a valid hexadecimal integer!" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "news? ";
	}
	// clear the cin stream
	cin.clear();
	cin.ignore(1000, '\n');

	// execute the opcode
	(*microcontroller)->execute(inputOpcode);
	
}

// handler for execute from point option
void optionExecuteFromSpecificLocationHandler(mcontroller::Microcontroller** microcontroller){

	// input location from user
	int location = (*microcontroller)->inputHexadecimal("location? ");

	// input opcode
	int inputOpcode;
	cout << "opcode? ";
	// validate input
	while(!(cin >> hex >> inputOpcode)){
		cerr << "Please input a valid hexadecimal integer!" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "news? ";
	}
	// clear the cin stream
	cin.clear();
	cin.ignore(1000, '\n');

	// execute the opcode from location
	(*microcontroller)->executeFromLocation(inputOpcode, location);
}

