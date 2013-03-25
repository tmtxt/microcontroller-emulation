#include <iostream>
#include "macrochippic32f42.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

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
	void MacrochipPIC32F42::execute(){
		this->executeFromLocation(this->getProgramCounter());
	}

	// execute from a specific location in memory
	void MacrochipPIC32F42::executeFromLocation(int address){
		// get the opcode in memory
		unsigned char opcode = this->getMemoryValueAtLocation(address);

		// switch it to the right function
		switch(opcode){
		case 0x50:				// move value to W
			this->executeMoveValueToW(address);
			break;
		case 0x51:				// move W to memory
			this->executeMoveWToMemory(address);
			break;
		case 0x5A:				// add value to W

			break;
		case 0x5B:				// subtract value from W

			break;
		case 0x6E:				// Goto address (branch always)

			break;
		case 0x70:				// Branch if not equal

			break;
		case 0xFF:				// Halt opcode

			break;
		default:				// invalid opcode
			cerr << "Invalid opcode!" << endl;
			break;

		}
	}

	// 0x50
	// Move Value to W
	// The first byte after the opcode is the value to be written to the W
	// register. The PC is set to the address of the second byte after the
	// opcode.
	void MacrochipPIC32F42::executeMoveValueToW(int address){
		// set the new value for W
		this->setW(this->getMemoryValueAtLocation(address + 1));

		// set the program counter to the second byte after the opcode
		this->setProgramCounter(address + 2);
	}

	// 0x51
	// Move W to memory
	// The first byte after the opcode is the high byte of the memory address,
	// and the second byte is the low byte of the memory address. The memory
	// address can be determined by (high byte << 8) | low byte. The W
	// register’s contents are written to this memory address. The PC is set to
	// the address of the third byte after the opcode.
	void MacrochipPIC32F42::executeMoveWToMemory(int address){
		
		// get the high byt and low byte address of the destination address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);

		// compute the destination address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// write the content of register W to destination address
		this->setMemoryValueAtLocation(destinationAddress, this->getW());

		// set the program counter to the third byte after the opcode
		this->setProgramCounter(address + 3);
	}
}
