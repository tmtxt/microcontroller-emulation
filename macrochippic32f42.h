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

		// create function
		static Microcontroller* create();

		// Getters
		unsigned char getW();

		// Setters
		void setW(unsigned char);

		// reset microcontroller
		void reset();

		// execute the instruction coorecsponding to the opcode
		void execute();

		// execute from a specific location in memory
		void executeFromLocation(int);

		// execute functions
		void executeMoveValueToW(int);
		void executeMoveWToMemory(int);
		void executeAddValueToW(int);
		void executeSubtractValueFromW(int);
		void executeGoToAddress(int);
		void executeBranchIfNotEqual(int);
		void executeHalt(int);
	};
}

#endif
