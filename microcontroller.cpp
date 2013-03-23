#include "microcontroller.h"

// Implementation of the Microcontroller class
namespace mcontroller {

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
