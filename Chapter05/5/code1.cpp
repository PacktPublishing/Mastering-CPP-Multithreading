#include <iostream> 
#include <thread> 
#include <mutex> 
 
std::mutex globalMutex; 
  
void worker(int i) { 
   globalMutex.lock(); 
         std::cout << "Outputting this from thread number: " << i << "\n"; 
   globalMutex.unlock(); 
} 
  
int main() { 
         std::thread t1(worker, 1);
         std::thread t2(worker, 2); 
  
         t1.join(); 
   t2.join(); 
 
   return 0; 
}
