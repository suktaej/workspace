#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

constexpr int BUFFER_SIZE = 2;

class Semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    explicit Semaphore(int init = 0)
        : count(init) {}
    
    void acquire()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){return count > 0;});
        --count;
    }

    void release()
    {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

Semaphore sem(BUFFER_SIZE); 

void worker(int id) 
{
    std::cout << "[Thread " << id << "] Waiting...\n";

    sem.acquire(); 

    std::cout << "[Thread " << id << "] Entered! (Working...)\n";
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    std::cout << "[Thread " << id << "] Leaving.\n";

    sem.release(); 
}

int main() 
{
    std::vector<std::thread> threads;

    for (int i = 1; i <= 5; ++i) 
    {
        threads.emplace_back(worker, i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 순차적 실행을 위해 살짝 텀을 줌
    }

    for (auto& t : threads) 
        t.join();

    return 0;
}