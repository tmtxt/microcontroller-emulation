#ifndef MACROCHIPPIC32F42_H_FLAG
#define MACROCHIPPIC32F42_H_FLAG
#include "microcontroller.h"

namespace mcontroller {
    class MacrochipPIC32F42 : public Microcontroller {
	private:
		// Special purpose byte-sized register called W
		unsigned char w;
		
	public:
		// constructor
		MacrochipPIC32F42();

		// Getters
		unsigned char getW();

		// Setters
		void setW(unsigned char);

		// reset microcontroller
		void reset();

		// execute the instruction coorecsponding to the opcode
		void execute(int);
	};
}

#endif
