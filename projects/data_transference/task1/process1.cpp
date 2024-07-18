#include "../xmodem.h"
#include <iostream>
#include "sm_communicator.h"

int main()
{
    Communicator c;
    XModem xmodem(&c);

    // Example receiving data
    std::vector<uint8_t> dataReceived;
    if (xmodem.receive(dataReceived))
    {
        // std::cout << __FILE__ << " " << __FUNCTION__ << "\nData received successfully: ";
        for (const auto &byte : dataReceived)
        {
            std::cout << byte;
        }
        std::cout << std::endl;
        //  std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
    else
    {
        // std::cout << __FILE__ << " " << __FUNCTION__ << "\nFailed to receive data." << std::endl;
    }

    return 0;
}
