/*
	ch01_mt_example.cpp - main file for the Chapter 01 multithreaded example.
	
	Revision 0
	
	Features:
			- 
			
	Notes:
			- 
			
	2016/10/30, Maya Posch
*/


#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <random>

using namespace std;


// --- Globals
mutex values_mtx;
mutex cout_mtx;
vector<int> values;


int randGen(const int& min, const int& max) {
    static thread_local mt19937 generator(hash<thread::id>()(this_thread::get_id()));
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}


void threadFnc(int tid) {
	// Calculate the result.
	cout_mtx.lock();
	cout << "Starting thread " << tid << ".\n";
	cout_mtx.unlock();
	
	values_mtx.lock();
	int val = values[0];
	values_mtx.unlock();
	
	int rval = randGen(0, 10);
	val += rval;
	
	cout_mtx.lock();
	cout << "Thread " << tid << " adding " << rval << ". New value: " << val << ".\n";
	cout_mtx.unlock();
	
	values_mtx.lock();
	values.push_back(val);
	values_mtx.unlock();
}


int main() {
	// Set global data in queue.
	values.push_back(42);
	
	// Start the threads, wait for them to finish.
	thread tr1(threadFnc, 1);
	thread tr2(threadFnc, 2);
	thread tr3(threadFnc, 3);
	thread tr4(threadFnc, 4);
	
	tr1.join();
	tr2.join();
	tr3.join();
	tr4.join();
	
	// Read the calculated values.
	cout << "Input: " << values[0] << ", Result 1: " << values[1] << ", Result 2: " << values[2] << ", Result 3: " << values[3] << ", Result 4: " << values[4] << "\n";
	
	
	return 1;
}
