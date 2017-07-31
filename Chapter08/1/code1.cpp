#include <iostream> 
#include <thread> 
#include <atomic> 
  
std::atomic<long long> data; 
void worker() { 
         data.fetch_add(1, std::memory_order_relaxed); 
} 
  
int main() { 
         std::thread t1(worker); 
         std::thread t2(worker); 
         std::thread t3(worker); 
         std::thread t4(worker); 
         std::thread t5(worker); 
    
         t1.join(); 
         t2.join(); 
         t3.join(); 
         t4.join(); 
         t5.join(); 
  
         std::cout << "Count value:" << data << '\n'; 
} 
