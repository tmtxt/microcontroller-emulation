// NOTE: When you want to add more microcontroller, remember to make changes to
// those places:
// makefile: microcontrollerfactory.o target, add the header file of the new
// new microcontroller class that you want to add
// this file must include that header
// in the constructor of MicrcontrollerFactory class, call the
// addMicrocontroller function to add new microcontroller

#include <iostream>
#include <string>
#include <map>
#include <set>
#include "microcontroller.h"
#include "microcontrollerfactory.h"
#include "mopsr500.h"
#include "macrochippic32f42.h"
#include "rotamola34hc22.h"

using std::pair;
using std::cerr;
using std::endl;

// Implementation for MicrocontrollerFactory class
namespace mcontroller {

	// Constructor
	MicrocontrollerFactory::MicrocontrollerFactory(){

		// Init all available micrcontrollers here so that later when there are
		// more microcontroller classes, just add them here
		this->addMicrocontroller("R500", MopsR500::create);
		this->addMicrocontroller("PIC32F42", MacrochipPIC32F42::create);
		this->addMicrocontroller("34HC22", Rotamola34HC22::create);
	}

	// function to add more microcontroller
	// name is the key for the microcontroller
	// createFn is the pointer to create function of that class
	void MicrocontrollerFactory::addMicrocontroller(string name, createFunction* createFn){

		// add the microcontroller name and its create function to the map
		this->createFunctionMap.insert(pair<string, createFunction*>(name, createFn));

	}

	// create the microcontroller with the input name
	// if no microcontroller found, return 0
	Microcontroller* MicrocontrollerFactory::createMicrocontroller(string name){


		// check if the create function is exist
		if(this->createFunctionMap.find(name) == this->createFunctionMap.end()){
			// not exist
			cerr << "Invalid Type!" << endl;
			return 0;
		} else {
			// exist
			// get the create function from the map
			createFunction* createFn = this->createFunctionMap[name];			
			return createFn();
		}
	}
}

