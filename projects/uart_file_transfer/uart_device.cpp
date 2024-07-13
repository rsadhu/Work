#include <fcntl.h>

#include <unistd.h>
#include <termios.h>
#include "uart_device.h"

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
    return write(fd_, data.c_str(), data.size());
}

std::string UART::receive(size_t size)
{
    std::string str;

    if (read(fd_, str.data(), size) == -1)
    {
        std::cout << "data wasn't read\n";
    }
    return str.data();
}
