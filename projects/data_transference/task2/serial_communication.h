#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <boost/asio.hpp>
#include <string>
#include "../icommunicator.h"

class SerialCommunication : public IntfCommunicator
{
public:
    SerialCommunication(const std::string &port, unsigned int baud_rate);
    ~SerialCommunication();

    bool isConnected() const override;
    std::string what() const override;

    void writeData(const std::string &data);
    std::string readData(size_t size);

    void sendByte(uint8_t data) override;
    void receiveByte(uint8_t &data) override;

    void send(const std::vector<uint8_t> &data) override
    {
        // not implemented
    }
    void receive(std::vector<uint8_t> &data) override
    {
        // not implemented
    }

private:
    boost::asio::io_service io_;
    boost::asio::serial_port serial_;
    bool is_connected_ = false;
    std::string device_;
    size_t baud_rate_ = 0;
};

#endif // SERIALCOMMUNICATION_H
