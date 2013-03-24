#include "macrochippic32f42.h"

// Implementation of MacrochipPIC34f42 class
namespace mcontroller {

	// Constructor
	MacrochipPIC32F42::MacrochipPIC32F42() : Microcontroller(1536){
		// After init the memory, reset the microcontroller
		reset();
	}

	// Reset the microcontroller
	void MacrochipPIC32F42::reset(){
		
	}
	
}
