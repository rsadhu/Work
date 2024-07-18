#include <iostream>
#include "uart.h"
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

const char *device = "/dev/ttys014";

int main(void)
{
    UART u(device, 96000);

    if (u.isConnected())
        std::cout << u.what() << " is connected\n";

    std::string file_path = "/Users/rakeshsadhu/dev/mygit/zeiss/rakesh-sadhu/tasks/task2_old/cmakelists_copy.txt";

    std::ofstream file_writer(file_path, std::ios::binary);
    if (!file_writer)
    {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return 1;
    }
    while (true)
    {
        std::vector<uint8_t> v_data;
        u.receive(v_data);
        if (v_data.size() == 0)
            break;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string data = (char *)v_data.data();

        file_writer.write(data.c_str(), data.size());
    }
    file_writer.close();

    return 0;
}