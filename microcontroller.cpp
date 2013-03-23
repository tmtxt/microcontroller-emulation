#include "microcontroller.h"

// Implementation of the Microcontroller class
namespace mcontroller {

	// Constructor
	Microcontroller::Microcontroller(int memorySize){
		// init the memory size
		this->memorySize = memorySize;

		// init the memory array
		this->memory = new unsigned char[this->memorySize];

	}

	// Getters
	unsigned char* Microcontroller::getMemory(){
		return memory;
	}
	int Microcontroller::getMemorySize(){
		return memorySize;
	}
	int Microcontroller::getProgramCounter(){
		return programCounter;
	}

	// Setters
	void Microcontroller::setProgramCounter(int location){
		programCounter = location;
	}
	
}
