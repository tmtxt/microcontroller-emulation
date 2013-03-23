#include "mopsr500.h"

// Implementation of Mopsr500 class
namespace mcontroller {

	// Constructor
	MopsR500::MopsR500() : Microcontroller(1024){
		// After init the memory, reset the microcontroller
		reset();
	}

	// reset the microcontroller
	void MopsR500::reset(){
		
	}
	
}
