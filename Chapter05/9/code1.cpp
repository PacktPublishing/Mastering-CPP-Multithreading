#include <iostream>
#include <future>
 
using namespace std; 
 
bool is_prime (int x) { 
   cout << "Calculating prime...\n"; 
   for (int i = 2; i < x; ++i) { 
         if (x % i == 0) { 
               return false; 
         } 
   } 
 
   return true; 
} 
 
int main () { 
   future<bool> pFuture = std::async (is_prime, 343321); 
 
   cout << "Checking whether 343321 is a prime number.\n"; 
 
   // Wait for future object to be ready. 
 
   bool result = pFuture.get(); 
   if (result) {
         cout << "Prime found.\n"; 
   } 
   else { 
         cout << "No prime found.\n"; 
   } 
 
   return 0; 
} 
