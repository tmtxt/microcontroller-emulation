#include <iostream>
#include <string>
#include <map>
#include <set>
#include "microcontroller.h"

using std::map;
using std::string;
using std::set;

namespace mcontroller {
	
	// Factory class for handling creating of Microcontroller
	class MicrocontrollerFactory
	{
		// VARIABLES AND DATATYPE
	public:
		// define a function type using typedef
		// this function is the create() function in Micrcontroller sub class
		typedef Microcontroller* createFunction(void);

	private:
		// a map datatype to to hold the pointer to the createFunction()
		map<string, createFunction*> createFunctionMap;

		// FUNCTIONS
	public:
		// constructor
		MicrocontrollerFactory();

		// function to create microcontroller
		Microcontroller* createMicrocontroller(string);

		// function to get all available microcontroller
		set<string> getAvailableMicrocontrollers();

	private:
		// function to add more microcontroller
		void addMicrocontroller(string, createFunction*);
	
	};

}
