#include <iostream> 
#include <chrono> 
#include <thread> 
typedef std::chrono::time_point<std::chrono::high_resolution_clock> timepoint; 
int main() { 
         std::cout << "Starting sleep.\n"; 
 
         timepoint start = std::chrono::high_resolution_clock::now(); 
 
         std::this_thread::sleep_for(std::chrono::seconds(2)); 
 
         timepoint end = std::chrono::high_resolution_clock::now(); 
         std::chrono::duration<double, std::milli> elapsed = end - start; 
         std::cout << "Slept for: " << elapsed.count() << " ms\n"; 
} 
