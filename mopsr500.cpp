#include <iostream>
#include "mopsr500.h"

using std::cout;
using std::cerr;
using std::endl;
using std::hex;

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
		switch(opcode){
			
		case 0x0A:				// add value to memory
			this->executeAddValueToMemory();
			break;

		case 0x13:				// subtract value from memory

			break;

		case 0x16:				// go to address

			break;

		case 0x17:				// branch relative

			break;

		case 0xFF:				// halt opcode

			break;
			
		default:				// invalid opcode
			cerr << "Invalid opcode!" << endl;
			break;
		}
	}

	
	// FUNCTIONS TO EXECUTE OPCODE

	// 0x0A
	// Add Value to Memory
	// The first byte after the opcode is the value that is to be added to memory.
	// The second byte after the opcode is the high byte of the address, and the
	// third byte is the low byte of the address. The memory address can be
	// determined by (high byte << 8) | low byte. After execution, the PC points to
	// the fourth byte after the opcode.
	void MopsR500::executeAddValueToMemory(){
		unsigned char opcode = 0x0A;
		
		// store the opcode to memory location where the program counter is
		// currently pointing to
		this->getMemory()[this->getProgramCounter()] = opcode;

		// input value from user
		int inputValue = this->inputHexadecimal("value? ");

		// get only the 8bit lower bytes of the input to put the memory
		unsigned char valueToAdd = (inputValue & 0xFF);

		// add the value into the next byte after the opcode
		this->setMemoryValueAtLocation(this->getProgramCounter() + 1,
									   this->getMemoryValueAtLocation(this->getProgramCounter() + 1) + valueToAdd);
		

		// get the low and high byte of the address
		unsigned char addressLowByte = (this->getProgramCounter() & 0xFF);
		unsigned char addressHighByte = ((this->getProgramCounter() >> 8) & 0xFF);

		// put the low and high byte of the address to memory
		this->setMemoryValueAtLocation(this->getProgramCounter() + 2, addressLowByte);
		this->setMemoryValueAtLocation(this->getProgramCounter() + 3, addressHighByte);

		// move the program counter to the fourth byte after the opcode
		this->setProgramCounter(this->getProgramCounter() + 4);
		
	}
	
}
