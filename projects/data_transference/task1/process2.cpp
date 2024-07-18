#include "xmodem.h"
#include <iostream>
#include "sm_communicator.h"

int main()
{
    Communicator c;
    XModem xmodem(&c);

    // Example data to send
    std::vector<uint8_t> dataToSend = {'H', 'e', 'l', 'l', 'o', ' ', 'X', 'M', 'O', 'D', 'E', 'M'};
    if (xmodem.send(dataToSend))
    {
        //   std::cout << __FILE__ << " " << __FUNCTION__ << "\nData sent successfully." << std::endl;
    }
    else
    {
        // std::cout << __FILE__ << " " << __FUNCTION__ << "\nFailed to send data." << std::endl;
    }
    return 0;
}
