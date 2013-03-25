#include <iostream>
#include "mopsr500.h"

// Implementation of Mopsr500 class
namespace mcontroller {

	// Constructor
	MopsR500::MopsR500() : Microcontroller(1024){
		// After init controller, display message for user
		std::cout << "R500 connected!" << std::endl;
		
		// Reset the microcontroller ti clean state
		this->reset();
	}

	// Reset the microcontroller
	// Upon reset, the microcontroller sets the program counter (PC) to location
	// 0. The microcontroller clears all internal memory and initialises it to
	// 0. This provides the programmer with a clean slate.
	void MopsR500::reset(){
		// Set program counter to 0
		this->programCounter = 0;

		// Clear all internal memory and init it to 0
		this->initMemory(0);

		// Response to the user that the controller is reset
		std::cout << "Micrcontroller reset!" << std::endl;
	}

	// execute the instruction coorecsponding to the opcode
	void MopsR500::execute(int opcode){
		
	}
	
}
