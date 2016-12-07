#include <iostream>
#include <thread>
#include <mutex>

int x;
std::mutex lock;

void threadFunction1()
{
    for( int i = 0; i < 10003; ++i ) {
            lock.lock();
            x++;
            lock.unlock();
	    // если мы поработали, то можно и отдохнуть - спать... 5 миллисекунд
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void threadFunction2()
{
    int count=0;
    for( int i = 0; i < 10000; ++i ) {
        lock.lock();
        if ( (x%2) == 0 ) {
                std::cout << "x = " << x << std::endl;
                count++;
        }
        lock.unlock();
        // спать... 5 миллисекунд
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    std::cout << "count = " << count << std::endl;
}

int main()
{
     std::thread t1(threadFunction1);
     std::thread t2(threadFunction2);
     t1.join();
     t2.join();
     return 0;
}

