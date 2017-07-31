#include <thread> 
#include <mutex> 
#include <iostream> 
  
int counter = 0; 
std::mutex counter_mutex; 
  
void worker() { 
         std::lock_guard<std::mutex> lock(counter_mutex); 
   if (counter == 1) { counter += 10; } 
   else if (counter >= 10) { counter += 15; } 
   else if (counter >= 50) { return; } 
         else { ++counter; } 
  
   std::cout << std::this_thread::get_id() << ": " << counter << '\n'; 
} 
  
int main() { 
    std::cout << __func__ << ": " << counter << '\n'; 
  
    std::thread t1(worker); 
    std::thread t2(worker); 
  
    t1.join(); 
    t2.join(); 
  
    std::cout << __func__ << ": " << counter << '\n'; 
}
