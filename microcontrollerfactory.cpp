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

using std::cout;
using std::pair;
using std::cerr;
using std::endl;
using std::string;

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
			// notify user
			cerr << "Error: Invalid Microcontroller type." << endl;
			cout << "Message: Valid types of Microcontroller are "
				 << this->getAvailableMicrocontrollersString()
				 << endl;
			return 0;
		} else {
			// exist
			// get the create function from the map
			createFunction* createFn = this->createFunctionMap[name];			
			return createFn();
		}
	}

	// function to get all available microcontroller
	set<string> MicrocontrollerFactory::getAvailableMicrocontrollersSet(){
		// get the iterator
		map<string, createFunction*>::iterator it;

		// the return set
		set<string> microcontrollerSet;

		// iterate through the map
		for (it = this->createFunctionMap.begin(); it != this->createFunctionMap.end(); ++it){
			// insert the key to the set
			microcontrollerSet.insert(it->first);
		}

		return microcontrollerSet;
	}

	// function to get a string of all available microcontroller
	string MicrocontrollerFactory::getAvailableMicrocontrollersString(){
		// get the iterator
		map<string, createFunction*>::iterator it;

		// the return string
		string microcontrollerString;

		// iterate through the map
		for (it = this->createFunctionMap.begin(); it != this->createFunctionMap.end(); ++it){
			// get the key and then append to the string
			microcontrollerString.append(it->first);
			microcontrollerString.append(" ");
		}

		return microcontrollerString;
	}
}

