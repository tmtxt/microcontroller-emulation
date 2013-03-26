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
		std::cout << "Message: R500 connected" << std::endl;
		
		// Reset the microcontroller ti clean state
		this->reset();
	}

	// static function for creating an instance of MacrochipPIC32F42 class
	Microcontroller* MopsR500::create(){
		return new MopsR500();
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
		std::cout << "Message: Micrcontroller reseted." << std::endl;
	}

	// execute the instruction coorecsponding to the opcode
	void MopsR500::execute(){
		this->executeFromLocation(this->getProgramCounter());
	}

	// execute from a specific location in memory
	void MopsR500::executeFromLocation(int address){
		unsigned char opcode = this->getMemoryValueAtLocation(address);
		switch(opcode){
			
		case 0x0A:				// add value to memory
			this->executeAddValueToMemory(address);
			break;

		case 0x13:				// subtract value from memory
			this->executeSubtractValueFromMemory(address);
			break;

		case 0x16:				// go to address
			this->executeGoToAddress(address);
			break;

		case 0x17:				// branch relative
			this->executeBranchRelative(address);
			break;

		case 0xFF:				// halt opcode
			this->executeHalt(address);
			break;
			
		default:				// invalid opcode
			cerr << "Error: Invalid opcode!" << endl;
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
	void MopsR500::executeAddValueToMemory(int address){

		// get the value to add
		unsigned char valueToAdd = this->getMemoryValueAtLocation(address + 1);

		// get the low and high byte of the address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 2);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 3);

		// compute the destination address from the high and low byte of address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// add the valueToAdd to destination
		this->setMemoryValueAtLocation(destinationAddress,
									   this->getMemoryValueAtLocation(destinationAddress) + valueToAdd);
		
		// move the program counter to the fourth byte after the opcode
		this->setProgramCounter(address + 4);
		
	}

	// 0x13
	// Subtract Value from Memory
	// The format of the instruction is the same as add value to memory
	// function. The value should be subtracted from the memory this time.
	void MopsR500::executeSubtractValueFromMemory(int address){

		// get the value to subtract
		unsigned char valueToSubtract = this->getMemoryValueAtLocation(address + 1);

		// get the low and high byte of the address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 2);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 3);

		// compute the destination address from the high and low byte of address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// subtract the valueToSubtract from destination
		this->setMemoryValueAtLocation(destinationAddress,
									   this->getMemoryValueAtLocation(destinationAddress) - valueToSubtract);

		// move the program counter to the fourth byte after the opcode
		this->setProgramCounter(address + 4);
	}

	// 0x16
	// Go to address (always branch)
	// The first byte after the opcode is the high byte of the address. The second
	// byte after the opcode is the low byte of the address. After execution, the PC
	// points to that address.
	void MopsR500::executeGoToAddress(int address){

		// compute the address from the low and high byte
		// the memory address can be determined by (high byte << 8) | low byte
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);
		int addressToGo = ((addressHighByte << 8) | addressLowByte);

		// set the program counter point to the new address
		this->setProgramCounter(addressToGo);
	}

	// 0x17
	// Branch relative
	// The program branches to a new location, relative to the current location. The
	// first byte after the opcode is the value that will be added to the PC. The
	// value must be treated as a signed value, i.e.: 128 = -128).
	void MopsR500::executeBranchRelative(int address){

		// get the value from the next byte after the opcode and then add
		// convert it to signed int
		int valueToMove = (signed char)(this->getMemoryValueAtLocation(address + 1));

		// move the program counter to the new location
		this->setProgramCounter(address + valueToMove);
	}

	// 0xFF
	// Halt opcode
	// Execution stops and the PC is not incremented.
	void MopsR500::executeHalt(int address){
		// nothing to do here, just print out a message
		cout << "Message: Execution halt!" << endl;
	}
	
}
