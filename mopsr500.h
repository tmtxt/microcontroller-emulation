#ifndef MOPSR500_H_FLAG
#define MOPSR500_H_FLAG

#include "microcontroller.h"

namespace mcontroller {
	
    class MopsR500 : public Microcontroller
	{
	public:
		// constructor
		MopsR500();

		// create function
		static Microcontroller* create();

		// execute the instruction coorecsponding to the opcode
		void execute();

		// execute from a specific location in memory
		void executeFromLocation(int);

		// functions to execute opcode
		void executeAddValueToMemory(int);
		void executeSubtractValueFromMemory(int);
		void executeGoToAddress(int);
		void executeBranchRelative(int);
		void executeHalt(int);

		// reset the microcontroller
		void reset();
	};
}

#endif
