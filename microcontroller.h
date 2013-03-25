#ifndef MICROCONTROLLER_H_FLAG
#define MICROCONTROLLER_H_FLAG

#include <iostream>

using std::string;

namespace mcontroller {
    class Microcontroller
	{
	protected:
		// program counter: internal CPU register that point to the memory
		// location that contains the next instruction
		int programCounter;

		// microcontroller's memory, dynamically allocated
		unsigned char* memory;

		// the size of the memory (also the size of the memory array), measured
		// in byte
		int memorySize;

		// some other utility functions
		
		// init the values of memory array all to the input value
		void initMemory(int);
		
	public:
		// constructor
		Microcontroller(int);

		// destructor
		

		// getters
		int getProgramCounter();
		unsigned char* getMemory();
		int getMemorySize();

		// setters
		void setProgramCounter(int);
		
		// reset the controller
		virtual void reset() = 0;

		// execute the instruction coorecsponding to the opcode
		virtual void execute(int) = 0;

		// some other utility functions
		
		// get the value at the input address location
		unsigned char getMemoryValueAtLocation(int);

		// set the value at the input address location
		void setMemoryValueAtLocation(int, unsigned char);

		// look up memory
		int lookUpMemoryAddress();

		// read a hexadecimal number from user
		int inputHexadecimal(string);

	};
}

#endif
