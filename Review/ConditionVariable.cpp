#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Using condition_variable
// Thread가 특정 조건이 만족될 때 까지 대기
// 조건이 만족되면 동작하는 신호장치
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void worker()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [](){return ready;}); // ready가 true가 될 때 까지 대기
    // cv.wait_for();
    // cv.wait_until();
    std::cout<<"Worker thread is running\n";
}

int main(void)
{
    std::thread t(worker);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;   // 조건 변경
    }

    cv.notify_one();    // Thread를 깨움
    // cv.notify_all();
    t.join();

    return 0;
}