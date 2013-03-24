#ifndef MICROCONTROLLER_H_FLAG
#define MICROCONTROLLER_H_FLAG

namespace mcontroller {
    class Microcontroller
	{
	protected:
		// program counter: internal CPU register that point to the memory
		// location that contains the next instruction
		unsigned char* programCounter;

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
		unsigned char* getProgramCounter();
		unsigned char* getMemory();
		int getMemorySize();

		// setters
		void setProgramCounter(unsigned char*);
		
		// reset the controller
		virtual void reset() = 0;

		// execute the instruction coorecsponding to the opcode
		void execute(int);

		// some other utility functions
		
		// get the value at the input address location
		unsigned char getMemoryValueAtLocation(int);

		// set the value at the input address location
		void setMemoryValueAtLocation(int, unsigned char);

	};
}

#endif
