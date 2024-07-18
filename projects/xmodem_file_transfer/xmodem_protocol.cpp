#include "xmodem_protocol.h"

void XModem::send(const std::string &filePath, std::ostream &outStream, std::istream &inStream)
{
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file");
    }

    char data[128];
    int blockNum = 1;
    int bytesRead;
    char response;

    // Wait for NAK
    while (inStream.get(response), response != NAK)
        ;

    while (file.read(data, 128) || (bytesRead = file.gcount()) > 0)
    {
        if (bytesRead < 128)
        {
            std::memset(&data[bytesRead], CTRLZ, 128 - bytesRead);
        }

        sendPacket(outStream, blockNum, data);
        inStream.get(response);
        if (response == ACK)
        {
            ++blockNum;
        }
        else
        {
            // Resend the packet on NAK or error
            sendPacket(outStream, blockNum, data);
        }
    }

    // Send EOT
    do
    {
        outStream.put(EOT);
        outStream.flush();
        inStream.get(response);
    } while (response != ACK);
}

void XModem::receive(std::istream &inStream, std::ostream &outStream, const std::string &filePath)
{
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Error opening file");
    }

    char packet[132];
    char response = NAK;
    int blockNum = 1;
    bool receiving = true;

    outStream.put(response);
    outStream.flush();

    while (receiving)
    {
        inStream.read(packet, 132);
        if (inStream.gcount() == 132)
        {
            if (packet[0] == SOH && packet[1] == blockNum && packet[2] == 255 - blockNum)
            {
                unsigned char checksum = 0;
                for (int i = 0; i < 128; ++i)
                {
                    checksum += packet[3 + i];
                }
                if (checksum == packet[131])
                {
                    file.write(&packet[3], 128);
                    ++blockNum;
                    response = ACK;
                }
                else
                {
                    response = NAK;
                }
            }
            else if (packet[0] == EOT)
            {
                response = ACK;
                outStream.put(response);
                outStream.flush();
                receiving = false;
            }
            else
            {
                response = NAK;
            }
        }
        else
        {
            response = NAK;
        }

        outStream.put(response);
        outStream.flush();
    }
}

void XModem::sendPacket(std::ostream &outStream, int blockNum, const char *data)
{
    char packet[132];
    packet[0] = SOH;
    packet[1] = blockNum;
    packet[2] = 255 - blockNum;
    std::memcpy(&packet[3], data, 128);
    unsigned char checksum = 0;
    for (int i = 0; i < 128; ++i)
    {
        checksum += data[i];
    }
    packet[131] = checksum;

    outStream.write(packet, 132);
    outStream.flush();
}