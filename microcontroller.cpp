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
		initMemory(0);
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

	// init the values of memory array all to the input value
	void Microcontroller::initMemory(int initialValue){
		int i;
		
		// loop through the memory and init all value to initialValue
		for(i = 0; i < memorySize; i++){
			memory[i] = initialValue;
		}
	}
	
}
