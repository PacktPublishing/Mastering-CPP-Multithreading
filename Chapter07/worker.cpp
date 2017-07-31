/*
	worker.cpp - Implementation of the Worker class.
	
	Revision 0
	
	Features:
			- 
			
	Notes:
			- 
			
	2016/11/19, Maya Posch
	(c) Nyanko.ws
*/


#include "worker.h"
#include "dispatcher.h"

#include <chrono>

using namespace std;


// --- GET CONDITION ---
void Worker::getCondition(condition_variable* &cv) {
	cv = &(this)->cv;
}


// --- RUN ---
// Runs the worker instance.
void Worker::run() {
    while (running) {
          if (ready) {
                ready = false;
                request->process();
                request->finish();
          }
                      if (Dispatcher::addWorker(this)) {
                while (!ready && running) {
                      unique_lock<mutex> ulock(mtx);
                      if (cv.wait_for(ulock, chrono::seconds(1)) == cv_status::timeout) {
                      }
                }
          }
    }
 } 
