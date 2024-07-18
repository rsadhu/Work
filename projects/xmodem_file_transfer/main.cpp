// Example usage:
#include "xmodem_protocol.h"
#include <sstream>

int main()
{
    XModem xmodem;

    // Simulate sending a file
    std::string in_file = "/Users/rakeshsadhu/dev/mygit/zeiss/rakesh-sadhu/xmodem_file_transfer/example.txt";
    std::string out_file = "/Users/rakeshsadhu/dev/mygit/zeiss/rakesh-sadhu/xmodem_file_transfer/received.txt";

    std::stringstream ss;
    std::istringstream iss("");
    xmodem.send(in_file, ss, iss);

    // Simulate receiving a file
    std::istringstream iss_receive(ss.str());
    std::ofstream output("/Users/rakeshsadhu/dev/mygit/zeiss/rakesh-sadhu/xmodem_file_transfer/received.txt", std::ios::binary);
    xmodem.receive(iss_receive, output, out_file);

    return 0;
}
