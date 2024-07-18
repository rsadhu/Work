#ifndef I_COMMUNICATOR_H
#define I_COMMUNICATOR_H
#include <iostream>

class IntfCommunicator
{
public:
    virtual void sendByte(uint8_t d) = 0;
    virtual void receiveByte(uint8_t &d) = 0;

    virtual void send(const std::vector<uint8_t> &data) = 0;
    virtual void receive(std::vector<uint8_t> &data) = 0;

    virtual std::string what() const = 0;

    virtual bool isConnected() const = 0;

    virtual ~IntfCommunicator()
    {
    }
};
#endif //