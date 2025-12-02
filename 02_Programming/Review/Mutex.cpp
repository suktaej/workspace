#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

std::mutex mtx;
int counter = 0;

void Increment()
{
    for(int i=0;i<1000;++i)
    {
        std::lock_guard<std::mutex> lock(mtx);  // 범위 끝에서 자동으로 unlock
        ++counter;
    }
}

void IncrementWithLock()
{
    mtx.lock();     //잠금
    std::cout<<"Thread "<< std::this_thread::get_id()<<"locked the mutex\n";
    for(int i=0;i<5;++i)
    {
        ++counter;
        std::cout << "Thread " << std::this_thread::get_id() << " counter: " << counter << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mtx.unlock();   //해제
    std::cout << "Thread " << std::this_thread::get_id() << " unlocked the mutex.\n";
}

void IncrementWithTryLock()
{
    if (mtx.try_lock()) // 잠금 시도
    { 
        std::cout << "Thread " << std::this_thread::get_id() << " acquired the mutex using try_lock.\n";
        ++counter;
        std::cout << "Thread " << std::this_thread::get_id() << " counter: " << counter << "\n";
        mtx.unlock(); // 잠금 해제
    } 
        std::cout << "Thread " << std::this_thread::get_id() << " could not acquire the mutex.\n";
}

int main()
{
    std::thread t1(Increment);
    std::thread t2(Increment);

    t1.join();
    t2.join();

    std::cout << "Counter: " << counter << "\n";

    std::thread t3(IncrementWithLock);
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 약간 딜레이
    std::thread t4(IncrementWithTryLock);

    t3.join();
    t4.join();

    return 0;
}