#ifndef XMODEM_H
#define XMODEM_H

#include <vector>
#include "icommunicator.h"

#define DISABLE_COPY(Class)        \
    Class(const Class &) = delete; \
    Class &operator=(const Class &) = delete;
#define DISABLE_MOVE(Class)   \
    Class(Class &&) = delete; \
    Class &operator=(Class &&) = delete;

#define DISABLE_COPY_MOVE(Class) \
    DISABLE_COPY(Class)          \
    DISABLE_MOVE(Class)

class XModem
{
    DISABLE_COPY_MOVE(XModem)

public:
    XModem(IntfCommunicator *sender = nullptr) : sender_{sender} {};
    ~XModem() = default;

    bool send(const std::vector<uint8_t> &data);
    bool receive(std::vector<uint8_t> &data);

private:
    static const int PACKET_SIZE = 128;
    static const int SOH = 0x01;
    static const int EOT = 0x04;
    static const int ACK = 0x06;
    static const int NAK = 0x15;
    static const int CAN = 0x18;
    static const int CNT_Z = 0x1A;
    static const int TIMEOUT = 1000; // milliseconds
    static const int MAX_RETRIES = 10;

    uint8_t calculateChecksum(const std::vector<uint8_t> &packet);
    bool sendPacket(const std::vector<uint8_t> &packet, uint8_t packetNumber);
    bool receivePacket(std::vector<uint8_t> &packet, uint8_t &packetNumber);
    bool waitForResponse(int &response);
    void sendByte(uint8_t byte);
    int readByte();
    IntfCommunicator *sender_ = nullptr;
};

#endif // XMODEM_H
