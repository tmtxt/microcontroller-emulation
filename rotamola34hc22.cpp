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

			break;
		case 0x37:				// load A with value

			break;
		case 0x38:				// load B with value

			break;
		case 0x53:				// increment A

			break;
		case 0x5A:				// branch always

			break;
		case 0x5B:				// branch if A<B

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

}
