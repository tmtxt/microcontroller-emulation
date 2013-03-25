#include <iostream>
#include "macrochippic32f42.h"

// Implementation of MacrochipPIC34f42 class
namespace mcontroller {

	// Constructor
	MacrochipPIC32F42::MacrochipPIC32F42() : Microcontroller(1536){
		// After init the microcontroller, print the message to user
		std::cout << "PIC32F42 connected!" << std::endl;
		
		// Reset the microcontroller to a clean state
		this->reset();
	}

	// Reset the microcontroller
	// Upon reset, the program counter (PC) is set to 0. The W register is set to 0.
	void MacrochipPIC32F42::reset(){
		// Set program counter to 0
		this->programCounter = 0;

		// Set W to 0
		this->setW(0);
	}

	// Getters
	unsigned char MacrochipPIC32F42::getW(){
		return this->w;
	}

	// Setters
	void MacrochipPIC32F42::setW(unsigned char w){
		this->w = w;
	}

	// execute the instruction coorecsponding to the opcode
	void MacrochipPIC32F42::execute(unsigned char opcode){
		
	}

	// execute from a specific location in memory
	void MacrochipPIC32F42::executeFromLocation(unsigned char opcode, int address){
		
	}
	
}
