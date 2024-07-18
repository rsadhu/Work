#include <gtest/gtest.h>
#include "../xmodem.h"
#include "../task2/serial_communication.h"
#include "../task2/uart.h"

TEST(TestMain, CheckIfSerialPortExchangeIsRightUsingPosix)
{
    const char *device1 = "/dev/ttys013";
    const char *device2 = "/dev/ttys014";

    UART u1(device1, 9600), u2(device2, 9600);

    if (u1.isConnected())
        std::cout << u1.what() << " is connected\n";

    if (u2.isConnected())
        std::cout << u2.what() << " is connected\n";

    std::vector<char> data = {'h', 'e', 'l', 'l', '0'};
    for (auto ch : data)
    {
        u1.sendByte(ch);
        uint8_t r_ch;
        u2.receiveByte(r_ch);
        std::cout << r_ch;
        EXPECT_EQ(ch, r_ch);
    }
}

TEST(TestMain, DISABLED_CheckIfSerialPortExchangeIsRightUsingBoost)
{
    const char *device1 = "/dev/ttys013";
    const char *device2 = "/dev/ttys014";

    SerialCommunication u1(device1, 9600), u2(device2, 9600);

    if (u1.isConnected())
        std::cout << u1.what() << " is connected\n";

    if (u2.isConnected())
        std::cout << u2.what() << " is connected\n";

    std::vector<char> data = {'h', 'e', 'l', 'l', '0'};
    for (auto ch : data)
    {
        u1.sendByte(ch);
        uint8_t r_ch;
        u2.receiveByte(r_ch);
        std::cout << r_ch;
        EXPECT_EQ(ch, r_ch);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}