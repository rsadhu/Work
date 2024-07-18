#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdexcept>

#define SOH 0x01   // Start of Header
#define EOT 0x04   // End of Transmission
#define ACK 0x06   // Acknowledgment
#define NAK 0x15   // Negative Acknowledgment
#define CAN 0x18   // Cancel
#define CTRLZ 0x1A // End of file padding character

class XModem
{
public:
    void send(const std::string &filePath, std::ostream &outStream, std::istream &inStream);
    void receive(std::istream &inStream, std::ostream &outStream, const std::string &filePath);

private:
    void sendPacket(std::ostream &outStream, int blockNum, const char *data);
};
