#include <iostream>
#include "uart.h"
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

const char *device = "/dev/ttys013";

int main(void)
{
    UART u(device, 96000);

    if (u.isConnected())
        std::cout << u.what() << " is connected\n";

    std::string file_path = "/Users/rakeshsadhu/dev/mygit/zeiss/rakesh-sadhu/tasks/task2_old/cmakelists.txt";
    // Read data from the file

    std::ifstream file_reader(file_path, std::ios::binary);
    if (!file_reader)
    {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return 1;
    }

    std::ostringstream ss;
    ss << file_reader.rdbuf();
    std::string file_data = ss.str();
    file_reader.close();

    std::vector<uint8_t> v_data(file_data.begin(), file_data.end());
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    u.send(v_data);
    return 0;
}