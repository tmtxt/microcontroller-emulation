#ifndef ROTOMOLA34HC22_H_FLAG
#define ROTOMOLA34HC22_H_FLAG

#include "microcontroller.h"

namespace mcontroller {
    class Rotomola34HC22 : public Microcontroller
	{
	public:
		// constructor
		Rotomola34HC22();

		// reset the microcontroller
		void reset();
	};
}

#endif
