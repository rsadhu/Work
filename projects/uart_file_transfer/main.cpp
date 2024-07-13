#include <iostream>
#include "uart_device.h"

const char *device1 = "/dev/ttys009";
const char *device2 = "/dev/ttys010";

int main(void)
{
    UART u2(device2, 96000);

    if (u2.isConnected())
        std::cout << u2.what() << " is connected\n";

    std::string s{"hello this is test message"};
    auto sz = u2.send(s);

    std::cout << u2.receive(sz);

    UART u1(device1, 96000);

    if (u1.isConnected())
        std::cout << "\n"
                  << u1.what() << " is connected\n";

    sz = u1.send(s);

    std::cout << u1.receive(sz);

    return 0;
}