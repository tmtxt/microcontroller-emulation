#ifndef ROTOMOLA34HC22_H_FLAG
#define ROTOMOLA34HC22_H_FLAG

#include "microcontroller.h"

namespace mcontroller {
    class Rotamola34HC22 : public Microcontroller
	{
	private:
		// Special Purpose byte-sized registers called A and B
		unsigned char a;
		unsigned char b;
		
	public:
		// constructor
		Rotamola34HC22();

		// reset the microcontroller
		void reset();

		// Getters
		unsigned char getA();
		unsigned char getB();

		// Setters
		void setA(unsigned char);
		void setB(unsigned char);

		// execute the instruction coorecsponding to the opcode
		void execute();

		// execute from a specific location in memory
		void executeFromLocation(int);		
	};
}

#endif
