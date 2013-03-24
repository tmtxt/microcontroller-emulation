#ifndef MACROCHIPPIC32F42_H_FLAG
#define MACROCHIPPIC32F42_H_FLAG
#include "microcontroller.h"

namespace mcontroller {
    class MacrochipPIC32F42 : public Microcontroller {
	private:
		// Special purpose byte-sized register called W
		char w;
		
	public:
		// constructor
		MacrochipPIC32F42();

		// Getters
		char getW();

		// Setters
		void setW(char);

		// reset microcontroller
		void reset();
	};
}

#endif
