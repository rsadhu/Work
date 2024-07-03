#include <QCoreApplication>
#include "chatserver.h"

const int server_port_num = 1234;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    ChatServer server;
    if (!server.startServer(server_port_num)) {
        qCritical() << "Failed to start server!";
        return 1;
    }
    return a.exec();
}
