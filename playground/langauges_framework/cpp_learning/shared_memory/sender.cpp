#include "shared_mem.h"
#include <iostream>

int main()
{
    SharedMemory shm("shared_memory", 1024);

    int cnt = 10;
    while (cnt-- > 0)
    {
        std::string message = "Hello from sender!";
        shm.writeData(message.c_str(), message.size() + 1);

        std::cout << "Data sent: " << message << std::endl;
    }
    return 0;
}
