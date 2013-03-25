#ifndef MOPSR500_H_FLAG
#define MOPSR500_H_FLAG

#include "microcontroller.h"

namespace mcontroller {
	
    class MopsR500 : public Microcontroller
	{
	public:
		// constructor
		MopsR500();

		// execute the instruction coorecsponding to the opcode
		void execute(int);

		// functions to execute opcode
		void executeAddValueToMemory();
		void executeSubtractValueFromMemory();
		void executeGoToAddress();
		void executeBranchRelative();
		void executeHalt();

		// reset the microcontroller
		void reset();
	};
}

#endif
