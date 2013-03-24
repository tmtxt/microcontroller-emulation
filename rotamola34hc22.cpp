#include "rotamola34hc22.h"

// Implementation of Rotomola34HC22 class
namespace mcontroller {

	// Constructor
	Rotamola34HC22::Rotamola34HC22() : Microcontroller(512){
		// After init the memory, reset the microcontroller
		reset();
	}

	// reset the microcontroller
	void Rotamola34HC22::reset(){
		
	}

	// Getters
	unsigned char Rotamola34HC22::getA(){
		return this->a;
	}

	unsigned char Rotamola34HC22::getB(){
		return this->b;
	}

	// Setters
	void Rotamola34HC22::setA(unsigned char a){
		this->a = a;
	}
	
	void Rotamola34HC22::setB(unsigned char b){
		this->b = b;
	}

}
