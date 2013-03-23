#include "macrochippic34f42.h"

// Implementation of MacrochipPIC34f42 class
namespace mcontroller {

	// constructor
	MacrochipPIC32F42::MacrochipPIC32F42(){
		// init the memory size to 1536 bytes
		memorySize = 1536;

		// init the memory array
		memory = new unsigned char[memorySize];
	}
}
