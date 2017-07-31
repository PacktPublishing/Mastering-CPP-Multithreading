#include <iostream> 
#include <thread> 
#include <chrono> 
  
void worker() { 
   std::this_thread::sleep_for(std::chrono::seconds(1)); 
} 
  
int main() { 
         std::thread t1(worker); 
         std::thread t2(worker); 
  
         std::cout << "thread 1 id: " << t1.get_id() << "\n"; 
         std::cout << "thread 2 id: " << t2.get_id() << "\n"; 
  
         std::swap(t1, t2); 
  
         std::cout << "Swapping threads..." << "\n"; 
 
         std::cout << "thread 1 id: " << t1.get_id() << "\n"; 
         std::cout << "thread 2 id: " << t2.get_id() << "\n"; 
  
         t1.swap(t2); 
  
         std::cout << "Swapping threads..." << "\n"; 
 
         std::cout << "thread 1 id: " << t1.get_id() << "\n"; 
         std::cout << "thread 2 id: " << t2.get_id() << "\n"; 
  
         t1.join(); 
         t2.join(); 
} 
