#ifndef MICROCONTROLLER_H_FLAG
#define MICROCONTROLLER_H_FLAG

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
		void execute(int);


	};
}

#endif
