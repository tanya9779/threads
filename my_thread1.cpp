#include <iostream>
#include <thread>

// без мьютексов

int x;

void threadFunction1()
{
    for( int i = 0; i < 10003; ++i ) {
            x++;
	    // если мы поработали, то можно и отдохнуть - спать... 5 миллисекунд
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void threadFunction2()
{
    int y;
    int count=0;
    for( int i = 0; i < 10000; ++i ) {
        y = x; // считываем значение х - это быстрая операция
        if ( (y%2) == 0 ) { // больше х не используем в этой ф-ции
                std::cout << "x = " << y << std::endl;
                count++;
        }
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

