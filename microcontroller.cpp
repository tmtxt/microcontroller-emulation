#include <iostream>
#include "microcontroller.h"

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

	// Getters
	unsigned char* Microcontroller::getMemory(){
		return this->memory;
	}
	int Microcontroller::getMemorySize(){
		return this->memorySize;
	}
	unsigned char* Microcontroller::getProgramCounter(){
		return this->programCounter;
	}

	// Setters
	void Microcontroller::setProgramCounter(unsigned char* programCounter){
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
		return (this->getMemory())[location];
	}
	
}
