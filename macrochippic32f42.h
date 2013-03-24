#ifndef MACROCHIPPIC32F42_H_FLAG
#define MACROCHIPPIC32F42_H_FLAG
#include "microcontroller.h"

namespace mcontroller {
    class MacrochipPIC32F42 : public Microcontroller {
		
	public:
		// constructor
		MacrochipPIC32F42();

		// reset microcontroller
		void reset();
	};
}

#endif
