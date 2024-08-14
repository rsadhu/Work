#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

std::queue<int> q1;
std::mutex m1, m2;

void reader()
{
    long cnt = 0;
    while (cnt < 65536)
    {
        m1.lock();
        if (!q1.empty())
        {
            std::cout << q1.front() << " ";
            cnt++;
            q1.pop();
        }
        else
        {
            std::this_thread::sleep_for(2ms);
        }
        m1.unlock();
    }
}

void writer()
{
    long i = 0;
    while (i < 65536)
    {
        m1.lock();
        q1.push(i++);
        m1.unlock();
        // std::this_thread::sleep_for(2ms);
    }
}

int main(void)
{
    std::thread t1, t2;
    t1 = std::thread(&reader);
    t2 = std::thread(&writer);
    t1.join();
    t2.join();
    return 0;
}