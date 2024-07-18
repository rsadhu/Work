#include "serial_communication.h"
#include "uart.h"
#include <fstream>
#include <iostream>
#include "../xmodem.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <file> <serial_port_out> <baud_rate>\n";
        return 1;
    }

    std::string file_path = argv[1];
    std::string serial_port_out = argv[2];
    unsigned int baud_rate = std::stoi(argv[3]);

    // Read data from the file
    std::ifstream file(file_path, std::ios::binary);
    if (!file)
    {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return 1;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string file_data = ss.str();
    file.close();

    // Send data over the serial port
    try
    {
        // SerialCommunication serial_out(serial_port_out, baud_rate);
        UART serial_out(serial_port_out, baud_rate);
        XModem modem(&serial_out);

        std::vector<uint8_t> data{file_data.begin(), file_data.end()};
        modem.send(data);
        std::cout << "Data sent successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
