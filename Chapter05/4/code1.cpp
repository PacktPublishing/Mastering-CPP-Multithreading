#include <iostream> 
#include <thread> 
  
void worker(int i) { 
         std::cout << "Outputting this from thread number: " << i << "\n"; 
} 
  
int main() { 
         std::thread t1(worker, 1);
         std::thread t2(worker, 2); 
  
         t1.join(); 
   t2.join(); 
 
   return 0; 
} 
