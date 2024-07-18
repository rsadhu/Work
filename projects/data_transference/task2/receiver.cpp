#include "serial_communication.h"
#include "uart.h"
#include <fstream>
#include <iostream>
#include "../xmodem.h"

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <file> <serial_port_in> <baud_rate>\n";
        return 1;
    }

    std::string file_path = argv[1];
    std::string serial_port_in = argv[2];
    unsigned int baud_rate = std::stoi(argv[3]);

    // Receive data from the serial port
    try
    {
        // SerialCommunication serial_in(serial_port_in, baud_rate);
        UART serial_in(serial_port_in, baud_rate);
        XModem xmodem(&serial_in);

        std::ofstream file(file_path, std::ios::binary);
        if (!file)
        {
            std::cerr << "Failed to open file: " << file_path << std::endl;
            return 1;
        }

        // Continuously read data from the serial port and write to the file
        while (true)
        {
            std::vector<uint8_t> data_stream;
            xmodem.receive(data_stream);
            if (data_stream.size() == 0)
                break;

            std::string data((char *)data_stream.data());

            file.write(data.c_str(), data.size());
        }

        file.close();
        std::cout << "Data received and saved successfully." << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
