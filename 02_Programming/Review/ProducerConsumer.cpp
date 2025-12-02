#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

static constexpr int BUFFER_SIZE = 5;
std::vector<int> buffer;

class Semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore(int init)
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

Semaphore empty(BUFFER_SIZE);
Semaphore full(0);
std::mutex mtx; // buffer 보호용 mutex

void producer(int id, int produceCount)
{
    for(int i =0; i< produceCount; ++i)
    {
        int item = id * 100 + i;
        empty.acquire();
    }
}