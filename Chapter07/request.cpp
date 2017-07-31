/*
	request.cpp - implementation of the Request class.
	
	Revision 0
	
	Notes:
			- 
			
	2016/11/19, Maya Posch
	(c) Nyanko.ws
*/


#include "request.h"


// --- PROCESS ---
void Request::process() {
	outFnc("Starting processing request " + std::to_string(value) + "...");
	
	//
}


// --- FINISH ---
void Request::finish() {
	outFnc("Finished request " + std::to_string(value));
}
