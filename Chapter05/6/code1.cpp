#include <chrono> 
#include <mutex> 
#include <thread> 
#include <iostream> 
  
std::chrono::milliseconds interval(50); 
  
std::mutex mutex; 
int job_shared = 0;
int job_exclusive = 0; 
  
void worker0() { 
   std::this_thread::sleep_for(interval);
  
         while (true) { 
               if (mutex.try_lock()) { 
                     std::cout << "Shared (" << job_shared << ")\n"; 
                     mutex.unlock(); 
                     return; 
               }  
         else { 
                     ++job_exclusive; 
                           std::cout << "Exclusive (" << job_exclusive << ")\n"; 
                           std::this_thread::sleep_for(interval); 
               } 
         } 
} 
  
void worker1() { 
   mutex.lock(); 
         std::this_thread::sleep_for(10 * interval); 
         ++job_shared; 
         mutex.unlock(); 
} 
  
int main() { 
         std::thread t1(worker0); 
         std::thread t2(worker1); 
  
         t1.join(); 
         t2.join(); 
}
