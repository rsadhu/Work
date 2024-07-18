#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "uart.h"
#include <thread>
#include <chrono>

UART::UART(const std::string &device, int baudrate)
{
    device_name_ = device;
    baudrate_ = baudrate;
    fd_ = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd_ == -1)
    {
        std::cerr << "Failed to open UART.  " << device_name_ << std::endl;
        exit(EXIT_FAILURE);
    }

    struct termios options;
    tcgetattr(fd_, &options);
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(fd_, TCSANOW, &options);
}

UART::~UART()
{
    close(fd_);
}

size_t UART::send(const std::string &data)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    auto sz = write(fd_, data.c_str(), data.size());
    if (sz <= 0)
    {
        std::cout << "\n failed to write data to device : " << device_name_ << "\n";
    }
    return sz;
}

std::string UART::receive(size_t size)
{
    std::string str;

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if (read(fd_, (void *)str.data(), size) == -1)
    {
        std::cout << "data wasn't read\n";
    }
    return str.data();
}

void UART::sendByte(uint8_t byte)
{
    std::string str;
    str += byte;
    send(str);
}

void UART::receiveByte(uint8_t &byte)
{
    std::string str = receive(1);
    byte = str[0];
}

void UART::send(const std::vector<uint8_t> &data)
{
    for (auto &ele : data)
    {
        this->sendByte(ele);
    }
}

void UART::receive(std::vector<uint8_t> &data)
{
    uint8_t byte;
    receiveByte(byte);
    data.push_back(byte);
}