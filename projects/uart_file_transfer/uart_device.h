#include <iostream>
#include <string.h>
#include <vector>

class UART
{
public:
    UART(const std::string &device, int baudrate);
    ~UART();
    size_t send(const std::string &data);
    std::string receive(size_t size);

    std::string what() const
    {
        return device_name_;
    }
    bool isConnected() const
    {
        return fd_ != -1;
    }

private:
    int fd_ = -1;
    int baudrate_ = 0;
    std::string device_name_;
};
