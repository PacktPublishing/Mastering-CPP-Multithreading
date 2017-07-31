#include <iostream> 
#include <future> 
#include <chrono>
#include <thread>
 
using namespace std; 
 
int countdown (int from, int to) { 
   for (int i = from; i != to; --i) { 
         cout << i << '\n'; 
         this_thread::sleep_for(chrono::seconds(1)); 
   } 
 
   cout << "Finished countdown.\n"; 
   return from - to; 
} 
 
int main () { 
   packaged_task<int(int, int)> task(countdown);
   future<int> result = task.get_future();
   thread t (std::move(task), 10, 0);
 
   //  Other logic. 
 
   int value = result.get(); 
 
   cout << "The countdown lasted for " << value << " seconds.\n"; 
 
   t.join(); 
   return 0; 
} 
