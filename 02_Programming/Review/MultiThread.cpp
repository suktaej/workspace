#include <iostream>
#include <thread>
#include <vector>

void worker(std::vector<int>::iterator start, std::vector<int>::iterator end, int* result)
{
    int sum = 0;

    for(auto it = start; it<end;++it)
        sum += *it;

    *result = sum;

    std::thread::id thisID = std::this_thread::get_id();
    std::cout<<"Thread :"<<thisID<<" from "<<*start<<" to "<<*(end-1)<<" Sum :"<<sum;
}
void func1()
{
    for(int i=0;i<1000000;++i)
        std::cout<<"1 ";
}

void func2()
{
    for(int i=0;i<1000000;++i)
        std::cout<<"2 ";
}

void func3()
{
    for(int i=0;i<1000000;++i)
        std::cout<<"3 ";
}

void threadTest1()
{
    std::thread t1(func1);
    std::thread t2(func2);
    std::thread t3(func3);

    t1.join();  // 쓰레드 종료 시 호출되는 함수
    t2.detach();// 쓰레드 실행 후 자동으로 백그라운드에서 실행하도록 지정(잊어버림)
    t3.join();

    std::cout<<"End";
}

void threadTest2()
{
    std::vector<int> data(10000);

    for(int i = 0; i< 10000; ++i)
        data[i] = i;

    std::vector<int> particalSums(4);
    std::vector<std::thread> workers;

    for (int i = 0; i < 4; i++) 
        workers.push_back(std::thread(worker, data.begin() + i * 2500,data.begin() + (i + 1) * 2500, &particalSums[i]));

    for (int i = 0; i < 4; i++) 
        workers[i].join();
    
      int total = 0;

      for (int i = 0; i < 4; i++) 
        total += particalSums[i];
      
      std::cout << "Total sum: " << total << std::endl;
}

int main(void)
{
   threadTest1();
   return 0;
}