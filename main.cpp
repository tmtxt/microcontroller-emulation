#include <iostream>
#include <iomanip>

#include "main.h"
#include "microcontroller.h"
#include "mopsr500.h"
#include "macrochippic32f42.h"
#include "rotamola34hc22.h"
#include "microcontrollerfactory.h"

using std::cout;
using std::cin;
using std::cerr;
using std::hex;
using std::endl;
using std::tolower;
using std::string;

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
	Microcontroller* microcontroller = 0;

	
	// EXECUTION OF PROGRAM

	// print welcome
	cout << "MICROCONTROLLER SIMULATOR" << endl;
	
	// Start the program
	// Loop for user enter option until user enter 'q' or 'Q'
	do
	{
		// Display the application prompt
		cout << "Message: Enter the option you want. Type h for help" << endl;
		cout << "> ";
		
		// Read user input
		userOption = inputOption();

		cout << endl;

		// Check the userOption variable and the switch the user to the right function
		switchOption(userOption, &microcontroller);

		if(userOption != 'q'){
			// Display a newline character, just for decoration
			cout << endl;
		}
		
	} while (userOption != 'q');

	// print the goodbye message
	cout << "Quitting..." << endl;
	cout << "Thank you for using my software." << endl;
	
	// End the program
	return 0;
}

// Function switchOption()
// Switch user to the right option
void switchOption(char userOption, Microcontroller** microcontroller){
	
	switch (userOption){
	case optionConnect:
		optionConnectHandler(microcontroller);
		break;
	case optionDisplay:
		executeOptionIfConnected(microcontroller, optionDisplayAllMemoryHandler);
		break;
	case optionExecute:
		executeOptionIfConnected(microcontroller, optionExecuteHandler);
		break;
	case optionGo:
		executeOptionIfConnected(microcontroller, optionExecuteFromSpecificLocationHandler);
		break;
	case optionLook:
		executeOptionIfConnected(microcontroller, optionLookAtMemoryHandler);
		break;
	case optionModify:
		executeOptionIfConnected(microcontroller, optionModifyMemoryHandler);
		break;
	case optionReset:
		executeOptionIfConnected(microcontroller, optionResetHandler);
		break;
	case optionStatus:
		executeOptionIfConnected(microcontroller, optionDisplayStatusHandler);
		break;
	case optionHelp:
		optionHelpHandler();
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

// Function optionErrorHandler()
// just display the error for the user
void optionErrorHandler(){
	cerr << "Error: Wrong option!" << endl;
	cout << "Message: Type h for Help." << endl;
}

// Function optionHelpHandler()
// Display the help for user
void optionHelpHandler(){
	cout << "Usage: Type in these options to execute." << endl;
	cout << "c\tConnect to microcontroller." << endl;
	cout << "d\tDisplay all memory." << endl;
	cout << "e\tExecute from current PC." << endl;
	cout << "g\tExecution from a specific location." << endl;
	cout << "h\tDisplay help." << endl;
	cout << "l\tLook at memory." << endl;
	cout << "m\tModify memory." << endl;
	cout << "r\tReset microcontroller." << endl;
	cout << "s\tDisplay PC and registers." << endl;
	cout << "q\tQuit the program." << endl;
}

// Handler for connect option
// Display the prompt to ask user enter microcontroller type
// and then connect to that microcontroller
void optionConnectHandler(Microcontroller** microcontroller){

	// a factory for creating microcontroller
	MicrocontrollerFactory factory;

	// first free memory for the existing microcontroller
	delete *microcontroller;
	
	// display the prompt to ask user to enter microcontroller type
	cout << "Message: Connect to Microcontroller" << endl;
	cout << "Message: Auto disconnect other Microcontroller (if aleady connected)" << endl;
	cout << "Message: Enter the type of microcontroller to connect" << endl;
	cout << "type? ";

	// read the microcontroller type from user
	string inputMicrocontrollerType;
	cin >> inputMicrocontrollerType;

	// create microcontroller
	(*microcontroller) = factory.createMicrocontroller(inputMicrocontrollerType);
	
}

// Handle reset option
// Reset the controller, simply just call the reset method of the input micrcontroller
void optionResetHandler(mcontroller::Microcontroller** microcontroller){
	(*microcontroller)->reset();
}

// Ask the user to input an address and output the value at that address
void optionLookAtMemoryHandler(mcontroller::Microcontroller** microcontroller){

	// display the message for user
	cout << "Message: Look at memory." << endl;
	cout << "Message: Enter the memory location to look at (hexadecimal format)." << endl;
	
	// the memory location the user input
	int location;
	
	// input memory location
	location = (*microcontroller)->lookUpMemoryAddress();

	// check if the input location is valid
	if(location != Microcontroller::memoryLocationInvalid){
		// print out the value at the memory address
		unsigned int value = (*microcontroller)->getMemoryValueAtLocation(location);
		cout << "Message: The value at location ";
		cout << hex << location;
		cout << " is: ";
		cout << hex << value;
		cout << endl;
	}
}

// Handler for Modify Memory option
void optionModifyMemoryHandler(mcontroller::Microcontroller** microcontroller){

	// display the message for user
	cout << "Message: Modify memory." << endl;
	cout << "Message: Enter the memory location to modify (hexadeciaml format)." << endl;
	
	// The input memory address
	int location;

	// input address from user
	location = (*microcontroller)->lookUpMemoryAddress();

	// check if the location is valid
	if(location != Microcontroller::memoryLocationInvalid){
		// print the old value
		unsigned int oldValue = (*microcontroller)->getMemoryValueAtLocation(location);
		cout << "Message: Old value: ";
		cout << hex << oldValue;
		cout << endl;

		// print the message
		cout << "Message: Enter the new value (hexadecimal format)." << endl;
		cout << "new? ";

		// read the input value from user
		unsigned int inputNewValue;
		// validate input
		while(!(cin >> hex >> inputNewValue)){
			cerr << "Error: Please input a valid hexadecimal integer!" << endl;
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

	// print the message for user
	cout << "Message: Display all memory." << endl;
	
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

	// print the message for user
	cout << "Message: Execute from current PC" << endl;
	
	// execute the opcode
	(*microcontroller)->execute();
	
}

// handler for execute from point option
void optionExecuteFromSpecificLocationHandler(mcontroller::Microcontroller** microcontroller){

	// display the message for user
	cout << "Message: Execute from specific location." << endl;
	cout << "Message: Enter the memory location to execute (hexadecimal format)." << endl;
	
	// input location from user
	int location = (*microcontroller)->inputHexadecimal("location? ");

	// execute the opcode from location
	(*microcontroller)->executeFromLocation(location);
}

// This function will query and display microcontroller status.
void optionDisplayStatusHandler(mcontroller::Microcontroller** microcontroller){
	cout << "Message: Display Microcontroller status" << endl;
	cout << (*microcontroller)->getStatusString() << endl;
}

// Check if the microcontroller is currently connected, execute handlerFunction
// otherwise, prinpt the error to cerr
void executeOptionIfConnected(Microcontroller** microcontroller, optionHandler* handlerFunction){
	
	// check whether the microcontroller is connected
	if((*microcontroller) == 0){
		// Not connected
		// print the message to cerr
		cerr << "Error: Not connected to any controller!" << endl;
		cerr << "Message: Type c to connect to a controller." << endl;
		cerr << "Message: Type h for help." << endl;
	} else {
		// Connected
		// execute the handler function
		handlerFunction(microcontroller);
	}
}
