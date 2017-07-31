/*
	main.cpp - Main file for the Dispatcher demo application.
	
	Revision 0 
	
	Features:
			- 
			
	Notes:
			- 
			
	2016/11/19, Maya Posch
	(c) Nyanko.ws
*/


#include "dispatcher.h"
#include "request.h"

#include <iostream>
#include <string>
#include <csignal>
#include <thread>
#include <chrono>

using namespace std;


// Globals
sig_atomic_t signal_caught = 0;
mutex logMutex;


void sigint_handler(int sig) {
	signal_caught = 1;
}


void logFnc(string text) {
	logMutex.lock();
	cout << text << "\n";
	logMutex.unlock();
}


int main() {
	// Install signal handler.
	signal(SIGINT, &sigint_handler);
	
	// Initialise the dispatcher with 10 worker threads.
	Dispatcher::init(10);
	
	cout << "Initialised.\n";
	
	// Generate requests in a continuous loop until terminated with SIGINT or
	// limit has been reached.
	int cycles = 0;
	Request* rq = 0;
	while (!signal_caught && cycles < 50) {
		rq = new Request();
		rq->setValue(cycles);
		rq->setOutput(&logFnc);
		Dispatcher::addRequest(rq);
		cycles++;
	}
	
	this_thread::sleep_for(chrono::seconds(5));
	
	// Cleanup.
	Dispatcher::stop();
	cout << "Clean-up done.\n";
	
	return 0;
}
