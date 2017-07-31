/*
	dispatcher.cpp - Implementation of the Dispatcher class.
	
	Revision 0
	
	Features:
			- 
			
	Notes:
			- 
			
	2016/11/19, Maya Posch
	(c) Nyanko.ws
*/


#include "dispatcher.h"

#include <iostream>
using namespace std;


// Static initialisations.
queue<AbstractRequest*> Dispatcher::requests;
queue<Worker*> Dispatcher::workers;
mutex Dispatcher::requestsMutex;
mutex Dispatcher::workersMutex;
vector<Worker*> Dispatcher::allWorkers;
vector<thread*> Dispatcher::threads;


// --- INIT ---
// Start the number of requested worker threads.
bool Dispatcher::init(int workers) {
	thread* t = 0;
	Worker* w = 0;
	for (int i = 0; i < workers; ++i) {
		w = new Worker;
		allWorkers.push_back(w);
		t = new thread(&Worker::run, w);
		threads.push_back(t);
	}
	
	return true;
}


// --- STOP ---
// Terminate the worker threads and clean up.
bool Dispatcher::stop() {
	for (int i = 0; i < allWorkers.size(); ++i) {
		allWorkers[i]->stop();
	}
	
	cout << "Stopped workers.\n";
	
	for (int j = 0; j < threads.size(); ++j) {
		threads[j]->join();
		
		cout << "Joined threads.\n";
	}
	
	return true;
}


// --- ADD REQUEST ---
void Dispatcher::addRequest(AbstractRequest* request) {
	// Check whether there's a worker available in the workers queue, else add
	// the request to the requests queue.
	workersMutex.lock();
	if (!workers.empty()) {
		Worker* worker = workers.front();
		worker->setRequest(request);
		condition_variable* cv;
		worker->getCondition(cv);
		cv->notify_one();
		workers.pop();
		workersMutex.unlock();
	}
	else {
		workersMutex.unlock();
		requestsMutex.lock();
		requests.push(request);
		requestsMutex.unlock();
	}
	
	
}


// --- ADD WORKER ---
bool Dispatcher::addWorker(Worker* worker) {
	// If a request is waiting in the requests queue, assign it to the worker.
	// Else add the worker to the workers queue.
	// Returns true if the worker was added to the queue and has to wait for
	// its condition variable.
	bool wait = true;
	requestsMutex.lock();
	if (!requests.empty()) {
		AbstractRequest* request = requests.front();
		worker->setRequest(request);
		requests.pop();
		wait = false;
		requestsMutex.unlock();
	}
	else {
		requestsMutex.unlock();
		workersMutex.lock();
		workers.push(worker);
		workersMutex.unlock();
	}
	
	return wait;
}
