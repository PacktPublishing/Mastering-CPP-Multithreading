#include "Poco/ThreadPool.h" 
#include "Poco/Runnable.h" 
#include <iostream> 
 
class HelloRunnable: public Poco::Runnable { 
    virtual void run() { 
        std::cout << "Hello, world!" << std::endl; 
    } 
}; 
 
int main(int argc, char** argv) { 
    HelloRunnable runnable; 
    Poco::ThreadPool::defaultPool().start(runnable); 
    Poco::ThreadPool::defaultPool().joinAll(); 
    return 0; 
} 