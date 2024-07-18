#include <iostream>
#include <vector>
#include "../icommunicator.h"

class UART : public IntfCommunicator
{
public:
    UART(const std::string &device, int baudrate);
    ~UART();
    size_t send(const std::string &data);
    std::string receive(size_t size);

    void send(const std::vector<uint8_t> &data);
    void receive(std::vector<uint8_t> &data);

    std::string what() const
    {
        return device_name_;
    }
    bool isConnected() const
    {
        return fd_ != -1;
    }

    void sendByte(uint8_t byte) override;
    void receiveByte(uint8_t &byte) override;

private:
    int fd_ = -1;
    int baudrate_ = 0;
    std::string device_name_;
};
