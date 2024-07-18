#include "shared_mem.h"
#include <iostream>

int main()
{
    SharedMemory shm("shared_memory", 1024);

    int cnt = 10;
    while (cnt-- > 0)
    {
        char buffer[1024];
        shm.readData(buffer, sizeof(buffer));
        std::cout << "Data received: " << buffer << std::endl;
    }

    return 0;
}
