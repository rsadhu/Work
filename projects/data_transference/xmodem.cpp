#include "xmodem.h"
#include <iostream>
#include <thread>
#include <chrono>

uint8_t XModem::calculateChecksum(const std::vector<uint8_t> &packet)
{
    uint8_t checksum = 0;
    for (const auto &byte : packet)
    {
        checksum += byte;
    }
    return checksum;
}

void XModem::sendByte(uint8_t byte)
{
    if (sender_)
    {
        sender_->sendByte(byte); // serial port connector
    }
}

int XModem::readByte()
{
    uint8_t byte = 0;
    if (sender_)
    {
        sender_->receiveByte(byte); // serial port connector
    }
    return byte != 0 ? ACK : -1;
}

bool XModem::waitForResponse(int &response)
{
    auto start = std::chrono::steady_clock::now();
    while (true)
    {
        response = readByte();
        if (response != -1)
        {
            return true;
        }
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count() > TIMEOUT)
        {
            return false;
        }
    }
}

bool XModem::sendPacket(const std::vector<uint8_t> &packet, uint8_t packetNumber)
{
    std::vector<uint8_t> fullPacket;
    fullPacket.push_back(SOH);
    fullPacket.push_back(packetNumber);
    fullPacket.push_back(255 - packetNumber);
    fullPacket.insert(fullPacket.end(), packet.begin(), packet.end());

    while (fullPacket.size() < PACKET_SIZE + 3)
    {
        fullPacket.push_back(CNT_Z); // Padding with Ctrl-Z
    }

    fullPacket.push_back(calculateChecksum(packet));

    for (int retries = 0; retries < MAX_RETRIES; ++retries)
    {

        for (const auto &byte : fullPacket)
        {
            sendByte(byte);
        }

        int response;

        if (waitForResponse(response))
        {
            if (response == ACK)
            {
                return true;
            }
            else if (response == NAK)
            {
                std::cout << "\nNAK received, retrying..." << std::endl;
            }
            else if (response == CAN)
            {
                std::cout << "\nTransmission cancelled." << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "\nTimeout, retrying..." << std::endl;
        }
    }
    return false;
}

bool XModem::receivePacket(std::vector<uint8_t> &packet, uint8_t &packetNumber)
{
    packet.resize(PACKET_SIZE);
    int response;
    for (int retries = 0; retries < MAX_RETRIES; ++retries)
    {
        sendByte(NAK);

        if (waitForResponse(response))
        {
            if (response == SOH)
            {
                uint8_t receivedPacketNumber = readByte();
                uint8_t receivedPacketNumberComplement = readByte();

                if (receivedPacketNumber != packetNumber || receivedPacketNumber + receivedPacketNumberComplement != 0xFF)
                {
                    sendByte(NAK);
                    continue;
                }

                for (int i = 0; i < PACKET_SIZE; ++i)
                {
                    packet[i] = readByte();
                }

                uint8_t receivedChecksum = readByte();
                if (receivedChecksum != calculateChecksum(packet))
                {
                    sendByte(NAK);
                    continue;
                }

                sendByte(ACK);
                packetNumber++;
                return true;
            }
            else if (response == EOT)
            {
                sendByte(ACK);
                return false;
            }
            else if (response == CAN)
            {
                std::cout << "\nTransmission cancelled." << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "\nTimeout, retrying..." << std::endl;
        }
    }
    return false;
}

bool XModem::send(const std::vector<uint8_t> &data)
{
    uint8_t packetNumber = 1;
    size_t offset = 0;

    while (offset < data.size())
    {
        std::vector<uint8_t> packet(data.begin() + offset, data.begin() + std::min(data.size(), offset + PACKET_SIZE));
        if (!sendPacket(packet, packetNumber))
        {
            return false;
        }

        offset += PACKET_SIZE;
        std::cout << "\n content sent so far is " << (((double)offset / (double)data.size()) * 100) << "\n";
        packetNumber++;
    }

    sendByte(EOT);
    int response;
    if (waitForResponse(response) && response == ACK)
    {
        return true;
    }
    return false;
}

bool XModem::receive(std::vector<uint8_t> &data)
{
    uint8_t packetNumber = 1;
    std::vector<uint8_t> packet;

    while (true)
    {

        if (!receivePacket(packet, packetNumber))
        {
            break;
        }

        data.insert(data.end(), packet.begin(), packet.end());

        if (packet.size() < PACKET_SIZE)
        {
            break;
        }
    }

    return true;
}
