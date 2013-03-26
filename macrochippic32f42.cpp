#include <iostream>
#include <sstream>
#include <iomanip>
#include "macrochippic32f42.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::hex;
using std::stringstream;

// Implementation of MacrochipPIC34f42 class
namespace mcontroller {

	// Constructor
	MacrochipPIC32F42::MacrochipPIC32F42() : Microcontroller(1536){
		// After init the microcontroller, print the message to user
		std::cout << "Message: PIC32F42 connected!" << std::endl;
		
		// Reset the microcontroller to a clean state
		this->reset();
	}

	// static function for creating an instance of MacrochipPIC32F42 class
	Microcontroller* MacrochipPIC32F42::create(){
		return new MacrochipPIC32F42();
	}

	// get the status string
	string MacrochipPIC32F42::getStatusString(){
		stringstream stream;
		stream << "Message: Current Program Counter location: " << hex << this->getProgramCounter() << endl;
		stream << "Message: W register value: " << hex << (int)(this->getW());
		return stream.str();
	}

	// Reset the microcontroller
	// Upon reset, the program counter (PC) is set to 0. The W register is set to 0.
	void MacrochipPIC32F42::reset(){
		// Set program counter to 0
		this->programCounter = 0;

		// Set W to 0
		this->setW(0);

		// print the message
		cout << "Message: PIC32F42 Reseted!" << endl;
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
			this->executeAddValueToW(address);
			break;
		case 0x5B:				// subtract value from W
			this->executeSubtractValueFromW(address);
			break;
		case 0x6E:				// Goto address (branch always)
			this->executeGoToAddress(address);
			break;
		case 0x70:				// Branch if not equal
			this->executeBranchIfNotEqual(address);
			break;
		case 0xFF:				// Halt opcode
			this->executeHalt(address);
			break;
		default:				// invalid opcode
			cerr << "Error: Invalid opcode!" << endl;
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
		
		// get the high byte and low byte address of the destination address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);

		// compute the destination address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// write the content of register W to destination address
		this->setMemoryValueAtLocation(destinationAddress, this->getW());

		// set the program counter to the third byte after the opcode
		this->setProgramCounter(address + 3);
	}

	// 0x5A
	// Add Value to W
	// The first byte after the opcode is the value to be added to the W
	// register. The PC is set to the address of the second byte after the
	// opcode.
	void MacrochipPIC32F42::executeAddValueToW(int address){
		// add value to W
		this->setW(this->getW() + this->getMemoryValueAtLocation(address + 1));

		// set the program counter to the second byte after the opcode
		this->setProgramCounter(address + 2);
	}

	// 0x5B
	// Subtract Value from W
	// The first byte after the opcode is the value to be subtracted from the W
	// register. The PC is set to the address of the second byte after the
	// opcode.
	void MacrochipPIC32F42::executeSubtractValueFromW(int address){
		// subtract value from w
		this->setW(this->getW() - this->getMemoryValueAtLocation(address + 1));

		// set the program counter to the second byte after the opcode
		this->setProgramCounter(address + 2);
	}

	// 0x6E
	// Goto address (branch always)
	// The first byte after the opcode is the high byte of the address. The
	// second block of memory after the opcode is the low byte of the address.
	// After execution, the PC points to that address.
	void MacrochipPIC32F42::executeGoToAddress(int address){

		// get the high byte and low byte address of the destination address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);

		// compute the destination address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// set the program counter to the destination address
		this->setProgramCounter(destinationAddress);
	}

	// 0x70
	// Branch if not equal
	// The next value after the opcode is the comparison value. The second block
	// of memory after the opcode is the high byte of the branch target, and the
	// third block of memory is the low byte of the branch target. If the W
	// register is not the same as the comparison value, then the program
	// counter is set to equal the branch target. Otherwise, the program counter
	// is set to equal the fourth block of memory after the opcode.
	void MacrochipPIC32F42::executeBranchIfNotEqual(int address){

		// the value to compare
		unsigned char comparisonValue = this->getMemoryValueAtLocation(address + 1);
		
		// compare W to comparisonValue
		if(comparisonValue == this->getW()){
			// if equal, set the program counter to the 4 block of memory after
			// the opcode
			this->setProgramCounter(address + 4);
		} else {
			// get the high byte and low byte address of the destination address
			unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 2);
			unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 3);

			// compute the destination address
			int destinationAddress = (addressHighByte << 8) | addressLowByte;

			// set the program counter to the new address
			this->setProgramCounter(destinationAddress);
		}
	}

	// 0xFF
	// Halt opcode
	// Execution stops and the PC is not incremented.
	void MacrochipPIC32F42::executeHalt(int address){
		// nothing here, just display a message for user
		cout << "Message: Execution halt!" << endl;
	}

}
