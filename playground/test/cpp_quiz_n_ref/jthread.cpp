#include <thread>
#include <iostream>
#include <functional>

int x = 10;
void thread(void)
{
    std::cout << "jthread execution " << x << "\n";
}

using namespace std::placeholders;

int main(void)
{

    std::function<void(void)> cb = std::bind(&thread);

    std::thread jtd(cb);

    cb();

    std::cout << "\n main\n";
    return 0;
}