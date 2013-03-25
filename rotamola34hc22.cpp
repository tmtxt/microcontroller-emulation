#include <iostream>
#include "rotamola34hc22.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// Implementation of Rotomola34HC22 class
namespace mcontroller {

	// Constructor
	Rotamola34HC22::Rotamola34HC22() : Microcontroller(512){
		// After init the memory, reset the microcontroller
		reset();
	}

	// reset the microcontroller
	void Rotamola34HC22::reset(){
		this->setProgramCounter(509);
	}

	// Getters
	unsigned char Rotamola34HC22::getA(){
		return this->a;
	}

	unsigned char Rotamola34HC22::getB(){
		return this->b;
	}

	// Setters
	void Rotamola34HC22::setA(unsigned char a){
		this->a = a;
	}
	
	void Rotamola34HC22::setB(unsigned char b){
		this->b = b;
	}

	// execute the instruction coorecsponding to the opcode
	void Rotamola34HC22::execute(){
		this->executeFromLocation(this->getProgramCounter());
	}

	// execute from a specific location in memory
	void Rotamola34HC22::executeFromLocation(int address){
		// get the opcode
		unsigned char opcode = this->getMemoryValueAtLocation(address);

		// switch user to the right function
		switch(opcode){
		case 0x0C:				// move A to memory
			this->executeMoveAToMemory(address);
			break;
		case 0x37:				// load A with value
			this->executeLoadAWithValue(address);
			break;
		case 0x38:				// load B with value
			this->executeLoadBWithValue(address);
			break;
		case 0x53:				// increment A
			this->executeIncrementRegisterA(address);
			break;
		case 0x5A:				// branch always
			this->executeBranchAlways(address);
			break;
		case 0x5B:				// branch if A<B
			this->executeBranchIfALessThanB(address);
			break;
		case 0x5D:				// branch if less than A

			break;
		case 0x64:				// halt opcode

			break;
		default:				// invalid opcode
			cerr << "Invalid opcode!" << endl;
			break;
		}
	}

	// 0x0C
	// Move A to memory
	// The first byte after the opcode represents the high byte of the memory
	// address. The second byte after the opcode represents the low byte of the
	// memory address. The memory address can be determined by (high byte << 8)
	// | low byte. The contents of the A register are moved to this memory
	// address. The PC is set to the third byte after the opcode.
	void Rotamola34HC22::executeMoveAToMemory(int address){
		
		// get the high byte and low byte address of the destination address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);

		// compute the destination address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// move the content of A to the destination address in memory
		this->setMemoryValueAtLocation(destinationAddress, this->getA());

		// set the program counter to the thrid byte after the opcode
		this->setProgramCounter(address + 3);
	}

	// 0x37
	// Load A with Value
	// The first byte after the opcode is the value to load into the A register.
	// The PC is set to the second byte after the opcode.
	void Rotamola34HC22::executeLoadAWithValue(int address){
		// load value from the first byte after the opcode to A
		this->setA(this->getMemoryValueAtLocation(address + 1));

		// set the program counter the the second byte after opcode
		this->setProgramCounter(address + 2);
	}

	// 0x38
	// Load B with Value
	// The first byte after the opcode is the value to load into the B register.
	// The PC is set to the second byte after the opcode.
	void Rotamola34HC22::executeLoadBWithValue(int address){
		// load value from the first byte after the opcode to B
		this->setB(this->getMemoryValueAtLocation(address + 1));

		// set the program counter the the second byte after opcode
		this->setProgramCounter(address + 2);
	}

	// 0x53
	// Increment Register A
	// The value of register A is incremented, and the result is stored back
	// into A. The value of the PC is incremented, so it points to the next byte
	// after the opcode.
	void Rotamola34HC22::executeIncrementRegisterA(int address){
		// increare the value of A
		this->setA(this->getA() + 1);

		// move the program counter to the next byte
		this->setProgramCounter(address);
	}

	// 0x5A
	// Branch Always
	// The first byte after the opcode represents the high byte of the memory
	// address. The second byte after the opcode represents the low byte of the
	// memory address. The PC is set to this memory address.
	void Rotamola34HC22::executeBranchAlways(int address){
		
		// get the high byte and low byte address of the destination address
		unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
		unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);

		// compute the destination address
		int destinationAddress = (addressHighByte << 8) | addressLowByte;

		// set the program counter to the new address
		this->setProgramCounter(destinationAddress);

	}

	// 0x5B
	// Branch if A < B
	// The first byte after the opcode represents the high byte of the memory
	// address. The second byte after the opcode represents the low byte of the
	// memory address. If the content of A is less than B, the PC is set to this
	// memory address. Otherwise, the PC is set to the third byte after the
	// opcode.
	void Rotamola34HC22::executeBranchIfALessThanB(int address){
		// compare the value of A and B
		if(this->getA() < this->getB()){

			// get the high byte and low byte address of the destination address
			unsigned char addressHighByte = this->getMemoryValueAtLocation(address + 1);
			unsigned char addressLowByte = this->getMemoryValueAtLocation(address + 2);

			// compute the destination address
			int destinationAddress = (addressHighByte << 8) | addressLowByte;

			// set the program counter to the new address
			this->setProgramCounter(destinationAddress);
			
		} else {
			
			// set the program counter to the third byte after the opcode
			this->setProgramCounter(address + 1);
			
		}
	}

}
