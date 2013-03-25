#include <iostream>
#include <iomanip>
#include <sstream>
#include "microcontroller.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::hex;
using std::string;
using std::stringstream;

// Implementation of the Microcontroller class
namespace mcontroller {

	// Constructor
	Microcontroller::Microcontroller(int memorySize){
		// init the memory size
		this->memorySize = memorySize;

		// init the memory array
		this->memory = new unsigned char [this->memorySize];
		this->initMemory(0);
	}

	// Destructor
	Microcontroller::~Microcontroller(){
		
	}

	// Getters
	unsigned char* Microcontroller::getMemory(){
		return this->memory;
	}
	int Microcontroller::getMemorySize(){
		return this->memorySize;
	}
	int Microcontroller::getProgramCounter(){
		return this->programCounter;
	}

	// Setters
	void Microcontroller::setProgramCounter(int programCounter){
		this->programCounter = programCounter;
	}

	// init the values of memory array all to the input value
	void Microcontroller::initMemory(int initialValue){
		// loop through the memory and init all value to initialValue
		for(int i = 0; i < this->memorySize; i++){
			this->memory[i] = initialValue;
		}
	}

	// get the value at the input address location
	unsigned char Microcontroller::getMemoryValueAtLocation(int location){
		if(location < 0 || location >= this->getMemorySize()){
			return 0;
		} else {
			return (this->getMemory())[location];
		}
	}

	// set the value at the input address location
	void Microcontroller::setMemoryValueAtLocation(int location, unsigned char value){
		if(location < 0 || location >= this->getMemorySize()){
			
		} else {
			(this->getMemory())[location] = value;
		}
	}

	// ask user to input a memory location and then return the memory
	// location if that address is exist, otherwise, print the message to cerr and
	// the return -1
	int Microcontroller::lookUpMemoryAddress(){

		// Init variables here
		// The input location
		int location = this->inputHexadecimal("location? ");

		// Validate that the location is out of memory array index
		if((location < 0) || (location >= this->getMemorySize())){
			// Display the error for user
			cerr << "Invalid address!" << endl;
			return -1;
		} else {
			// Address valid, return the address location
			return location;
		}
	}

	// read a hexadecimal number from user
	int Microcontroller::inputHexadecimal(string prompt){
		// The input location
		int location;

		// Display the prompt
		cout << prompt;

		// Read the location from user and ensure that user enter an hex int
		while(!(cin >> hex >> location)){
			cerr << "Please input a valid hexadecimal integer!" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << prompt;
		}

		cin.clear();
		cin.ignore(1000, '\n');

		return location;
	}

	// get the status string
	string Microcontroller::getStatusString(){
		stringstream stream;
		stream << "Current Program Counter location: " << hex << this->getProgramCounter();
		return stream.str();
	}
	
}
