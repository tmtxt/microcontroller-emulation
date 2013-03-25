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

		// reset the microcontroller
		void reset();
	};
}

#endif
