#include <iostream>
#include "uart_device.h"

const char *device1 = "/dev/tty.Bluetooth-Incoming-Port";
const char *device2 = "/dev/ttyUSB1";

int main(void)
{
    UART u1(device1, 96000);

    if (u1.isConnected())
        std::cout << u1.what() << " is connected\n";

    std::string s{"hello this is test message"};
    auto sz = u1.send(s);

    std::cout << u1.receive(sz);

    return 0;
}