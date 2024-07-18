#include "serial_communication.h"
#include <iostream>

SerialCommunication::SerialCommunication(const std::string &port, unsigned int baud_rate)
    : serial_(io_), device_(port), baud_rate_(baud_rate)
{
    boost::system::error_code ec;

    serial_.open(port, ec);

    if (ec)
    {
        std::cerr << "Error opening serial port: " << ec.message() << std::endl;
        return;
    }

    is_connected_ = true;

    // Set serial port options
    serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
    // serial_.set_option(boost::asio::serial_port_base::character_size(8));
    // serial_.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
    // serial_.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
    // serial_.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
}

SerialCommunication::~SerialCommunication()
{
    serial_.close();
}

void SerialCommunication::writeData(const std::string &data)
{
    boost::system::error_code ec;
    boost::asio::write(serial_, boost::asio::buffer(data.c_str(), data.size()), ec);
    if (ec || 0 != ::tcflush(serial_.lowest_layer().native_handle(), TCIOFLUSH))
    {
        std::cerr << "Error writing to serial port: " << ec.message() << std::endl;
    }
}

std::string SerialCommunication::readData(size_t size)
{
    std::vector<char> buf(size);
    boost::asio::read(serial_, boost::asio::buffer(buf, size));
    return std::string(buf.begin(), buf.end());
}

void SerialCommunication::sendByte(uint8_t data)
{
    std::string str;
    str += data;
    this->writeData(str);
}

void SerialCommunication::receiveByte(uint8_t &data)
{
    std::string str;
    str = this->readData(1);
    data = str[0];
}

bool SerialCommunication::isConnected() const
{
    return is_connected_;
}

std::string SerialCommunication::what() const
{
    return device_;
}
